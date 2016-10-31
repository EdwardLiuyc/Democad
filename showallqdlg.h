#ifndef SHOWALLQDLG_H
#define SHOWALLQDLG_H

#include <QDialog>
#include <QTableView>
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>
#include <QItemDelegate>
#include <QPainter>
#include "Parameter.h"

class DetQTable;
class DetQTableDelegate;
class DetQTableModel;


enum TableHeader
{
	_Q_index,
	_x_coor,
	_y_coor,
	_z_coor,
	table_header_count
};

class ShowAllQDlg : public QDialog
{
	Q_OBJECT

public:
	ShowAllQDlg(QWidget *parent);
	~ShowAllQDlg();

protected:
	void resizeEvent(QResizeEvent * event);

private:
	DetQTable * m_QTable;
};

class DetQTable : public QTableView
{
	Q_OBJECT

public:
	DetQTable( QWidget * parent = NULL );
	~DetQTable(){}

protected:
	void resizeEvent( QResizeEvent *event );

private:
	QSortFilterProxyModel * m_proxyModel;
	DetQTableModel       * m_sourceModel;
	DetQTableDelegate    * m_itemDelegate;
};

class DetQTableModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit DetQTableModel( QWidget * parent = NULL ) : QAbstractItemModel( parent ){}
	~DetQTableModel(){}

	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &index) const
	{
		Q_UNUSED(index);
		return QModelIndex();
	}
	int rowCount(const QModelIndex &parent = QModelIndex()) const
	{
		return 500;  //< 共500个点
	}
	int columnCount(const QModelIndex &parent = QModelIndex()) const
	{
		return table_header_count;
	}
	Qt::ItemFlags flags(const QModelIndex &index) const
	{
		Q_UNUSED(index);
		Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;

		return flags;
	}

	void resetModel()
	{
		this->reset();
	}

private:

};

class DetQTableDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	explicit DetQTableDelegate( QWidget * parent )
		: QItemDelegate( parent ){}
	~DetQTableDelegate(){}

	//< @brief 用于设置描画参数
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:


};

#endif // SHOWALLQDLG_H
