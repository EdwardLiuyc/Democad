/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!
**
**********************************************************************/
#ifndef QG_SNAPTOOLBAR_H
#define QG_SNAPTOOLBAR_H

class QG_CadToolBar;
class QG_ActionHandler;

#include <QToolBar>
#include <QAction>
#include "rs_snapper.h"
#include "qg_actionhandler.h"

class QG_SnapToolBar : public QToolBar
{
    Q_OBJECT

public:
    QG_SnapToolBar( const QString & title, QG_ActionHandler* ah, QWidget * parent = 0 );
    virtual ~QG_SnapToolBar();

    RS_SnapMode getSnaps ( void );
    void saveSnapMode(void );
    virtual void setActionHandler(QG_ActionHandler* ah);
    QVector<QAction*> getActions() const;

protected:
    QG_ActionHandler* actionHandler;

private slots:
	void actionTriggeredSnapFree();
	void actionTriggeredSnapGrid();
	void actionTriggeredSnapEndpoint();
	void actionTriggeredSnapOnEntity();
	void actionTriggeredSnapCenter();
	void actionTriggeredSnapMiddle();
	void actionTriggeredSnapDistance();
	void actionTriggeredSnapIntersection();

public slots:
    void setSnaps(RS_SnapMode);

signals:
    void snapsChanged(RS_SnapMode);

private:
    //自由捕捉，例如捕捉端点时，如果不设置自由捕捉，会只能设置端点
    QAction *snapFree;
    QAction *snapGrid;
    QAction *snapEnd;
    QAction *snapOnEntity;
    QAction *snapCenter;
    QAction *snapMiddle;
    QAction *snapDistance;
    QAction *snapIntersection;

    RS_SnapMode snapMode;
    QVector<QAction*> m_vSnapActions;//保存自己所有的action的指针
    int m_iActionCounts;

    void init();

};

#endif // QG_SNAPTOOLBAR_H
