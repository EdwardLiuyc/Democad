#ifndef PUBLICFUCTION_H
#define PUBLICFUCTION_H

#include "Parameter.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QTextEdit>
#include "QDebug"

void ReSizeCsCal(int x, int y, int w, int h, int* nx, int* ny, int* nw, int* nh,
                 int screenx, int screeny, int realx, int realy, int iMode, bool Lflag);

/*设置按钮显示颜色圆角*/
QString SetPushButtonSheetStyle(int bgcolor_r, int bgcolor_g, int bgcolor_b, int outR, int inR,
									int bcolor_r, int bcolor_g, int bcolor_b,
									int pbgcolor_r, int pbgcolor_g, int pbgcolor_b);

bool checkIllegalChar(QString qStr);															// 判断字符串中是否存在非数字字符
void strFormat(QString &qStr, int iTotal, int iSub);											// 字符串的格式化显示
bool readFile(QString Path, QVector<QString> &mcBuff);											// 读取文件信息
bool writeToFile(QString Path, QVector<QString> mcBuff);										// 将加工条件保存到文件中

void getFileName(QString fullfilename, char *filename);			// 获取文件名


QRegExpValidator* setInputDataFormat_Digit(QObject *parent, bool bInteger = false, bool bUnInt = false);
QRegExpValidator* setInputDataFormat_DigitAlphabet(QObject *parent);

void HoldTimer(int nT = 20);

#endif // PUBLICFUCTION_H