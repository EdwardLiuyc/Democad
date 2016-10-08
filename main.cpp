#include "democad.h"
#include <QtGui/QApplication>
#include <QTextCodec>
#include <stdio.h>

int main(int argc, char *argv[])
{
	QTextCodec *codec = QTextCodec::codecForName("GBK");
	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	qDebug() << "\n***********DemoCad last compile in" << __DATE__ << __TIME__ << "***********";
#ifdef __arm__
	qDebug() << "***********compiled by linux-arm-g++!***********";
#else
	qDebug() << "***********compiled by linux-g++(x86)!***********";
#endif

	QApplication a(argc, argv);
	DemoCad w;

#ifndef Q_OS_WIN
	if( argv[1] != NULL )
	{
		QString firstStr = QString( QLatin1String(argv[1]) );
		//if( firstStr == "-show" )
			//w.show();

		if( firstStr == "-v" )
			qDebug() << "version 1.1.0921";
		else
		{
			qDebug() << "command not supported!";
			return a.exec();
		}
	}
	w.show();
#else
	w.show();
#endif

	return a.exec();
}
