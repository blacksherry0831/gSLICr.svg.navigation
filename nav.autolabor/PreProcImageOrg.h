#pragma once
#ifndef _PreProcImageOrg_H_
#define _PreProcImageOrg_H_
/*-----------------------------------------*/
#include <QDir>
#include <QThread>
#include <QImage>
#include <QDateTime>
#include <QQueue>
#include <QCoreApplication>
/*-----------------------------------------*/
#include "DriveAuto.h"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
class PreProcImageOrg : public QObject
{
    Q_OBJECT

public:
	Q_INVOKABLE explicit PreProcImageOrg(QObject *parent = nullptr);
	~PreProcImageOrg();
private:
	bool mSafeArea;
	bool mSaveImage;
private:
	QString mPaths;
public:
	void InitImageSavePath();
public:
	void SaveQImage(const QImage & _img);
	void SetResize(const int _w,const int _h);
private:
	static bool CreateDir(const QString & path);
public:
signals:
	void sig_1_frame_bgra(QImage, QDateTime);
public slots :
	void ImageProc(QImage _img, QDateTime _time);
	void DrawSafeArea(const bool _r);
	void SetSaveImage(const bool _s);
};

#endif
