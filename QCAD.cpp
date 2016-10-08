#include <QCAD.h>
#include "democad.h"

QCAD::QCAD( void )
{
	m_pCad = new DemoCad;
}

QCAD::~QCAD( void )
{
	if( m_pCad != NULL )
	{
		delete m_pCad;
		m_pCad = NULL;
	}
}

void QCAD::onSetPos(int nx, int ny, int width, int height)
{
	if( m_pCad != NULL )
        m_pCad->setGeometry( nx, ny, width, height );
}

void QCAD::onShow()
{
	if( m_pCad != NULL )
		m_pCad->show();
}

void QCAD::onOriginalInit()
{
	if( m_pCad != NULL )
		m_pCad->getGraphicView()->resetSize();
}

void QCAD::onSetParent(QWidget *parent /* = 0 */)
{
	if( m_pCad != NULL && parent != NULL )
		m_pCad->setParent( parent );
}

void QCAD::onSetSubWindow(bool bTag /* = false */)
{
	if( bTag )
		m_pCad->setWindowFlags( Qt::SubWindow );
}

void QCAD::setDXFFilePath(QString path)
{
	if( m_pCad != NULL )
	    return;
}

void QCAD::getCADDataList(QList<CADData * > &cadData)
{
	//< 先清除所有的实体数据
	cadData.clear();

	//< 
	if( m_pCad != NULL )
	{
		for(QList<RS_Entity *>::iterator it = m_pCad->getGraphicView()->getContainer()->getEntities().begin();
			it != m_pCad->getGraphicView()->getContainer()->getEntities().end();
			it++)
		{
			if(!(*it)->isVisible()) continue;

			CADData * tmpData = new CADData;
			
			//< 如果为引线则直接加入到实体链表里去
			if( (*it)->isLead() )
			{
				tmpData->isLead = true;
				cadData.append( tmpData );
				continue;
			}
			
			//< 设置实体类型
			switch( (*it)->rtti() )
			{
			case RS2::EntityPoint:
				tmpData->nType = CADData::cad_entity_point;
				break;
			case RS2::EntityArc:
				tmpData->nType = CADData::cad_entity_arc;
				break;
			case RS2::EntityLine:
				tmpData->nType = CADData::cad_entity_line;
				break;
			case RS2::EntitySpline:
				tmpData->nType = CADData::cad_antity_spline;
			default:
				break;
			}

			//< 设置实体数据，若类型不正确则直接跳出该次循环
			if( tmpData->nType < 0 )
			{
				delete tmpData;
				tmpData = NULL;
				continue;
			}



			
		}
	}
}



