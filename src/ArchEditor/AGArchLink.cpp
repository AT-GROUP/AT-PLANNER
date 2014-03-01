
#include "AGArchLink.h"

//=====================AGArchLink==================================
AGArchLink::AGArchLink(AArchLink * _link)
	:QGraphicsLineItem(), m_pLink(_link), m_pStartItem(nullptr), m_pEndItem(nullptr)
{

}

void AGArchLink::setStartItem(QGraphicsItem * start_item)
{
	m_pStartItem = start_item;
}

void AGArchLink::setEndItem(QGraphicsItem * end_item)
{
	m_pEndItem = end_item;
}

void AGArchLink::updateShape()
{
	auto bb_start = m_pStartItem->sceneBoundingRect().center(), bb_end = m_pEndItem->sceneBoundingRect().center();
	setLine(bb_start.x(), bb_start.y(), bb_end.x(), bb_end.y());
}

