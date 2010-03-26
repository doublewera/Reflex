/***************************************************************************
* table.h                                                                  *
* This program is free software; you can redistribute it and/or modify     *
* it under the terms of the GNU General Public License as published by     *
* the Free Software Foundation; either version 2 of the License, or        *
* (at your option) any later version.                                      *
* Copyright 2007 David Parunakian                                          *
***************************************************************************/

#ifndef _TABLE_H_
#define _TABLE_H_

#include <QtCore/QTextStream>
#include <QtCore/QStringList>

class Table {
public:
	Table(QTextStream *istream, bool hasTitle = false);
	QString title();
	QStringList headers();
	QStringList values();
	QString header(int section);
	QString value(int section);
	bool nextLine(const QString &separator = "The end.");

private:
	QTextStream *_istream;
	QString _title;
	QStringList _header, _line;
};

#endif
