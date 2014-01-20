#include <QtItems/G_PlanItem.h>
#include <QPainter>
#include <QString>

G_PlanItem::G_PlanItem(AT_PlanItem * p_item)
    :QGraphicsItem(0), p_mPlanItem(p_item)
{
}

G_PlanItem::~G_PlanItem()
{
}

QRectF G_PlanItem::boundingRect() const
{
    return QRectF(0,0,80,30);
}

void G_PlanItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int duration = p_mPlanItem->getDuration();
    Q_UNUSED(option) Q_UNUSED(widget);
    painter->setPen(QColor(Qt::black));
    painter->drawRect(0,0,duration,30);
    painter->drawText(duration/2, 15, QString::fromStdString(p_mPlanItem->getName()));
}

AT_PlanItem* G_PlanItem::getAT_PlanItem()
{
    return p_mPlanItem;
}
