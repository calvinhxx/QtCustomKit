#include "FlowLayout.h"
#include "FlowLayout_p.h"
#include <QWidget>

FlowLayout::FlowLayout(QWidget *parent, int margin, int hSpacing, int vSpacing)
    : QLayout(parent), d_ptr(new FlowLayoutPrivate(this, hSpacing, vSpacing))
{
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::FlowLayout(int margin, int hSpacing, int vSpacing)
    : d_ptr(new FlowLayoutPrivate(this, hSpacing, vSpacing))
{
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::~FlowLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

void FlowLayout::addItem(QLayoutItem *item)
{
    Q_D(FlowLayout);

    d->itemList.append(item);
}

int FlowLayout::horizontalSpacing() const
{
    Q_D(const FlowLayout);
    //有自定义值取自定义值,没有取QStyle默认边距
    if (d->m_hSpace >= 0)
    {
        return d->m_hSpace;
    }
    else
    {
        return d->smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
    }
}

int FlowLayout::verticalSpacing() const
{
    Q_D(const FlowLayout);

    if (d->m_vSpace >= 0)
    {
        return d->m_vSpace;
    }
    else
    {
        return d->smartSpacing(QStyle::PM_LayoutVerticalSpacing);
    }
}

Qt::Orientations FlowLayout::expandingDirections() const
{
    return 0;
}

bool FlowLayout::hasHeightForWidth() const
{
    return true;
}

int FlowLayout::heightForWidth(int width) const
{
    Q_D(const FlowLayout);

    int height = d->doLayout(QRect(0, 0, width, 0), true);
    return height;
}

int FlowLayout::count() const
{
    Q_D(const FlowLayout);

    return d->itemList.size();
}

QLayoutItem* FlowLayout::itemAt(int index) const
{
    Q_D(const FlowLayout);

    return d->itemList.value(index);
}

QSize FlowLayout::minimumSize() const
{
    Q_D(const FlowLayout);

    QSize size;
    QLayoutItem *item;
    foreach (item, d->itemList)
        size = size.expandedTo(item->minimumSize());

    size += QSize(2*margin(), 2*margin());
    return size;
}

void FlowLayout::setGeometry(const QRect &rect)
{
    Q_D(FlowLayout);

    QLayout::setGeometry(rect);
    d->doLayout(rect, false);
}

QSize FlowLayout::sizeHint() const
{
    return minimumSize();
}

QLayoutItem* FlowLayout::takeAt(int index)
{
    Q_D(FlowLayout);

    if (index >= 0 && index < d->itemList.size())
        return d->itemList.takeAt(index);
    else
        return 0;
}

//
FlowLayoutPrivate::FlowLayoutPrivate(FlowLayout* q, int hSpacing, int vSpacing):
   q_ptr(q), m_hSpace(hSpacing), m_vSpace(vSpacing)
{

}

int FlowLayoutPrivate::doLayout(const QRect &rect, bool testOnly) const
{
    Q_Q(const FlowLayout);

    int left, top, right, bottom ;
    q_ptr->getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;

    QLayoutItem *item;
    foreach (item, itemList) {
        QWidget *wid = item->widget();
        int spaceX = q->horizontalSpacing();
        if (spaceX == -1)
            spaceX = wid->style()->layoutSpacing(
                QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);
        int spaceY = q->verticalSpacing();
        if (spaceY == -1)
            spaceY = wid->style()->layoutSpacing(
                QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Vertical);

        int nextX = x + item->sizeHint().width() + spaceX;
        if (nextX - spaceX > effectiveRect.right() && lineHeight > 0) {
            x = effectiveRect.x();
            y = y + lineHeight + spaceY;
            nextX = x + item->sizeHint().width() + spaceX;
            lineHeight = 0;
        }

        if (!testOnly)
            item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));

        x = nextX;
        lineHeight = qMax(lineHeight, item->sizeHint().height());
    }
    return y + lineHeight - rect.y() + bottom;
}

int FlowLayoutPrivate::smartSpacing(QStyle::PixelMetric pm) const
{
    Q_Q(const FlowLayout);

    QObject *parent = q->parent();
    if (!parent)
    {
        return -1;
    }
    else if (parent->isWidgetType())
    {
        QWidget *pw = static_cast<QWidget *>(parent);
        return pw->style()->pixelMetric(pm, 0, pw);
    }
    else
    {
        return static_cast<QLayout *>(parent)->spacing();
    }
}

//


