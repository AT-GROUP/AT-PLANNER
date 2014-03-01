
#ifndef AARCHEDITOR_AGArchLink_H
#define AARCHEDITOR_AGArchLink_H

#include <QtWidgets/QGraphicsLineItem>

class AArchLink;

class AGArchLink : public QGraphicsLineItem
{
public:
	AGArchLink(AArchLink * _link);
	void setStartItem(QGraphicsItem * start_item);
	void setEndItem(QGraphicsItem * end_item);
	void updateShape();
private:
	AArchLink * m_pLink;
	QGraphicsItem * m_pStartItem, *m_pEndItem;
};


#endif
