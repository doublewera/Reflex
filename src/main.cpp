/***************************************************************************
* main.cpp                                                                 *
* This program is free software; you can redistribute it and/or modify     *
* it under the terms of the GNU General Public License as published by     *
* the Free Software Foundation; either version 2 of the License, or        *
* (at your option) any later version.                                      *
* Copyright 2007-2009 Wera Barinova and David Parunakian                   *
***************************************************************************/

#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QPicture>

#include <QtCore/QFile>
#include <QtCore/QBuffer>
#include <QtCore/QTextStream>
#include <QtCore/QDataStream>

#include <QtDebug>

#include "datar.h"
//#include "picmanager.h"
// #include <ql/graphic.h>

#define SEPARATOR "===================================================="
#define FILE_FORMAT "PNG"

int main(int argc, char **argv) {
	QApplication app(argc,argv);
	Datar d(argv[1]);
/*	QMainWindow mainWindow;
	PicManager *centralWidget = new PicManager();

	mainWindow.setCentralWidget(centralWidget);
	mainWindow.show();
	mainWindow.resize(800,600);
	return app.exec();*/
	return 0;
}
//        QLabel *centralWidget = new QLabel();
//	QPixmap p;
//	p.load("qlogo.png","PNG");
//	centralWidget->setPixmap(p);

/*	QTextStream in(stdin);
	QString formatString;
	QDomDocument format("format");

	for (QString line = in.readLine(); !in.atEnd() && line != SEPARATOR; line = in.readLine())

	        formatString.append(line);

	format.setContent(formatString);

        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);

        Picture picture(&in, format);
        picture.draw().save(&buffer, FILE_FORMAT);

        QFile file;
        file.open(stdout, QIODevice::WriteOnly);
        QDataStream out(&file);
        out.writeRawData(buffer.data().data(), buffer.data().length());
*/
