#include "showallqdlg.h"
#include <QScrollBar>

ShowAllQDlg::ShowAllQDlg(QWidget *parent)
	: QDialog(parent)
{
	this->setWindowTitle( tr("探针记录坐标") );
	resize( 800, 450 );
	m_QTable = new DetQTable( this );
	
}

ShowAllQDlg::~ShowAllQDlg()
{

}

void ShowAllQDlg::resizeEvent(QResizeEvent * event)
{
	m_QTable->setGeometry( 10, 10, width() - 20, height() - 20 );
}




DetQTable::DetQTable(  QWidget * parent /* = NULL */ )
	: QTableView( parent )
{
	this->setAutoFillBackground( true );

	//< 设置数据model
	m_sourceModel = new DetQTableModel(this);
	m_proxyModel  = new QSortFilterProxyModel(this);
	m_proxyModel->setSourceModel(m_sourceModel);
	this->setModel(m_proxyModel);
	//< 设置委托
	m_itemDelegate = new DetQTableDelegate(this);
	this->setItemDelegate( m_itemDelegate );

	this->verticalHeader()->hide();
	this->setSelectionMode( QAbstractItemView::SingleSelection );
	this->horizontalHeader()->setStretchLastSection(true);
	this->verticalHeader()->setStretchLastSection(true);

	//< 设置表格样式
	this->setStyleSheet("QTableView{ \
						padding:4px 4px 5px 4px; \
					    background: rgb(220,220,220); \
		                gridline-color: #888888; \
						border: 2px solid #FFFFFF \
						} \
		                QTableCornerButton::section{ \
						background:Transparent; \
		                border: 1px solid #FFFFFF; \
						margin: 0px 1px 1px 0px; \
						} \
						");

	//this->verticalScrollBar()->setMinimumHeight( 100 );
}

void DetQTable::resizeEvent( QResizeEvent *event )
{
	int width =  this->width();
	int height = this->height();

	const int wthFirst = 50;
	const int wthOther = ( width - wthFirst - 10 ) / ( table_header_count - 1 );

	this->horizontalHeader()->resizeSection(_Q_index, wthFirst );
	for( int i = _x_coor; i <= _z_micro_adjust; ++i )  //< 最后一列不设置宽度，自动调节
	{
		this->horizontalHeader()->resizeSection( i, wthOther );
	}
}

//< 如果点击ENTER，Qt会发送 RETURN 的 Key 事件，然后直接往下切到下一行
void DetQTable::keyPressEvent( QKeyEvent * event )
{
	if( event->key() == Qt::Key_Return )
	{
		QKeyEvent keyEvent( QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier );
		QApplication::sendEvent( this, &keyEvent );
	}
	else
		QTableView::keyPressEvent( event );
}




QVariant DetQTableModel::headerData(int section, Qt::Orientation orientation, int role ) const
{
	if(role != Qt::DisplayRole)
	{
		return QVariant();
	}

	QString text = "";
	if( orientation == Qt::Vertical )
	{
		//< 列表头暂时不设定
	}
	else
	{
		switch( section )
		{
		case _Q_index:
			text = tr("变量号");
			break;
		case _x_coor:
			text = tr(" x 坐标");
			break;
		case _x_micro_adjust:
			text = tr(" x 微调");
			break;
		case _y_coor:
			text = tr(" y 坐标");
			break;
		case _y_micro_adjust:
			text = tr(" y 微调");
			break;
		case _z_coor:
			text = tr(" z 坐标");
			break;
		case _z_micro_adjust:
			text = tr(" z 微调");
			break;
		case _dir_:
			text = tr( "位置" );
			break;
		default:
			break;
		}
	}

	return text;
}

QVariant DetQTableModel::data(const QModelIndex &index, int role) const
{
	if(!index.isValid())
	{
		return QVariant();
	}

	int row    = index.row();
	int column = index.column();
	QString value = NULL;

	QString dirStr[XYZ_DIR_COUNT] = 
	{
		tr("左"), tr("右"), tr("上"), tr("下"), tr("Z向"), tr("左上"), tr("右上"), tr("左下"), tr("右下")
	};

	RS_Vector tmpVec = g_SavedData.value( row+1 , RS_Vector(0., 0., 0. ) );
	QParaTableExtraData tmpData = g_QTableExtraDataMap.value( row+1, QParaTableExtraData() );
	if( role == Qt::DisplayRole )
	{	
		switch( column )
		{
		case _Q_index: //< 登录点号
			value = QString::number( row + 1 );
			break;
		case _x_coor:  //< NC文件行号
			value = QString::number( tmpVec.x, 'd', 4 );
			break;
		case _x_micro_adjust:
			value = QString::number( tmpData.QMicroAdjust.x, 'd', 4 );
			break;
		case _y_coor:
			value = QString::number( tmpVec.y, 'd', 4 );
			break;
		case _y_micro_adjust:
			value = QString::number( tmpData.QMicroAdjust.y, 'd', 4 );
			break;
		case _z_coor:
			value = QString::number( tmpVec.z, 'd', 4 );
			break;
		case _z_micro_adjust:
			value = QString::number( tmpData.QMicroAdjust.z, 'd', 4 );
			break;
		case _dir_:
			if( tmpData.dir < 0 )
				value = "---";
			else
				value = dirStr[tmpData.dir];
			break;
		default:
			break;
		}

		if( column != _Q_index && column !=_dir_ )
			value += " ";  //< 后面多加一个空格为了美观（数据不顶格写）
		return value;  
	}

	return QVariant();
}

Qt::ItemFlags DetQTableModel::flags(const QModelIndex &index) const
{
	Q_UNUSED(index);
	Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;

	int row = index.row();
	int column = index.column();
	if( column == _x_micro_adjust && g_QTableExtraDataMap.value(row+1).isEditable[0] )
		flags |= Qt::ItemIsEditable;
	else if( column == _y_micro_adjust && g_QTableExtraDataMap.value(row+1).isEditable[1] )
		flags |= Qt::ItemIsEditable;
	else if( column == _z_micro_adjust && g_QTableExtraDataMap.value(row+1).isEditable[2] )
		flags |= Qt::ItemIsEditable;

	return flags;
}

QModelIndex DetQTableModel::index(int row, int column, const QModelIndex &parent ) const
{
	return createIndex(row, column, 0);
}

void DetQTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	Q_ASSERT(index.isValid());

	QStyleOptionViewItemV4 opt = option;

	int row    = index.row();
	int column = index.column();

	//painter->setFont( FONT_LIGHT_12_SIMHEI );
	painter->setPen(QColor(0, 0, 0));

	if( column == _z_coor || column == _x_coor || column == _y_coor )
		painter->fillRect(option.rect, QBrush(QColor(255,255,255)));
	else
		painter->fillRect(option.rect, QBrush(QColor(210,210,210)));

	if ((option.state & QStyle::State_Selected)
		&& (option.state & QStyle::State_Active))
	{
		
		painter->setPen(QColor(255, 255, 255));
		painter->fillRect(option.rect, QBrush(QColor(102, 102, 153)));       
	}

	if(column == _Q_index || column == _dir_)
	{
		opt.widget->style()->drawItemText(painter, opt.rect, Qt::AlignCenter, opt.palette, true, index.data().toString());
	}
	else
	{
		opt.widget->style()->drawItemText(painter, opt.rect
			, Qt::AlignRight | Qt::AlignVCenter, opt.palette, true, index.data().toString());
	}
}



QWidget *DetQTableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	int column = index.column();
	if( column == _x_micro_adjust || column == _y_micro_adjust || column == _z_micro_adjust )
	{
		QLineEdit *editor = new QLineEdit(parent);
		editor->setAlignment(Qt::AlignCenter);

		editor->setValidator(new QRegExpValidator(QRegExp("^-?[0-9]{0,2}\\.[0-9]{0,4}$"), editor));
		editor->setStyleSheet("QLineEdit{ \
							  font-size: 15px; \
							  font-family: SIMHEI; \
							  font-weight: bold; \
							  color:blue; \
			                  border-width: 2px; \
							  border-color: #0000FF; \
							  border-style: solid; \
			                  background-color: #00FF00; \
							  selection-background-color: Transparent; \
			                  selection-color:#0000FF; \
							  }");
		return editor;
	}
	else
	{
		return QItemDelegate::createEditor(parent, option, index);
	}

}

void DetQTableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	int column = index.column();
	if( column == _x_micro_adjust || column == _y_micro_adjust || column == _z_micro_adjust )
	{
		QString string(index.model()->data(index, Qt::EditRole).toString());

		QAbstractItemModel *model = const_cast<QAbstractItemModel*>(index.model());
		model->setData(index, "", Qt::EditRole);
		QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
		lineEdit->selectAll();
		lineEdit->setText(string);
	}
	else
	{
		QItemDelegate::setEditorData(editor, index);
	}

}

void DetQTableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
	QString text = lineEdit->text();
	if ( text.isNull() || text.isEmpty() )
	{
		return;
	}

	int row = index.row();
	int column = index.column();
	switch( column )
	{
	case _x_micro_adjust:
		g_QTableExtraDataMap[row+1].QMicroAdjust.x = text.toDouble();
		break;
	case _y_micro_adjust:
		g_QTableExtraDataMap[row+1].QMicroAdjust.y = text.toDouble();
		break;
	case _z_micro_adjust:
		g_QTableExtraDataMap[row+1].QMicroAdjust.z = text.toDouble();
		break;
	default:
		QItemDelegate::setModelData(editor, model, index);
		break;
	}
}
