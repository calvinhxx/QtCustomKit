#ifndef FLOWLAYOUT_H
#define FLOWLAYOUT_H

#include "Kits_global.h"

#include <QLayout>
#include <QScopedPointer>

class FlowLayoutPrivate;
class KITS_EXPORT FlowLayout : public QLayout
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(FlowLayout)
public:

    explicit FlowLayout(QWidget *parent, int margin = -1, int hSpacing = -1, int vSpacing = -1);
    explicit FlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1);
    ~FlowLayout();

    int horizontalSpacing() const;
    int verticalSpacing() const;
    QSize minimumSize() const override;
    void setGeometry(const QRect &rect) override;
    QSize sizeHint() const override;

    Qt::Orientations expandingDirections() const override;
    bool hasHeightForWidth() const override;
    int heightForWidth(int width) const override;
    int count() const override;
    void addItem(QLayoutItem *item) override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;

private:
    QScopedPointer<FlowLayoutPrivate> d_ptr;
};

#endif // FLOWLAYOUT_H
