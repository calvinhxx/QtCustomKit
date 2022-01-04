#ifndef FLOWLAYOUT_P_H
#define FLOWLAYOUT_P_H

#include "FlowLayout.h"

#include <QStyle>
#include <QLayout>

class FlowLayout;
class FlowLayoutPrivate
{
    Q_DECLARE_PUBLIC(FlowLayout)
public:

    explicit FlowLayoutPrivate(FlowLayout* q, int hSpacing, int vSpacing);
    ~FlowLayoutPrivate() = default;

private:
    int doLayout(const QRect &rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm) const;

    QList<QLayoutItem *> itemList;
    int m_hSpace;
    int m_vSpace;

private:
    FlowLayout* q_ptr = nullptr;
};

#endif // FLOWLAYOUT_P_H

