#ifndef PLANITEM_H
#define PLANITEM_H

#include <QGraphicsItem>
#include <QRectF>

#include <ATItems/AT_PlanItem.h>

class G_PlanItem: public QGraphicsItem
{
    public:
        G_PlanItem(AT_PlanItem *p_item);
        ~G_PlanItem();
        virtual QRectF boundingRect() const;
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
        AT_PlanItem* getAT_PlanItem();
    private:
        AT_PlanItem* p_mPlanItem;
};

#endif // PLANITEM_H
