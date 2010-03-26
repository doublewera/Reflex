/***************************************************************************
* table.cpp                                                                *
* This program is free software; you can redistribute it and/or modify     *
* it under the terms of the GNU General Public License as published by     *
* the Free Software Foundation; either version 2 of the License, or        *
* (at your option) any later version.                                      *
* Copyright 2007 David Parunakian                                          *
* Copyright 2007 Wera Barinova                                             *
***************************************************************************/

#include "table.h"

Table::Table(QTextStream *istream, bool hasTitle) {
	_istream = istream;
	if (hasTitle && !_istream->atEnd())
		_title = _istream->readLine();
	if (!_istream->atEnd())
		_header = _istream->readLine().replace("\t"," ").split(" ", QString::SkipEmptyParts);
	_line = QStringList();
}

QString Table::title() {
	return _title;
}

QStringList Table::headers() {
	return _header;
}

QString Table::header(int section) {
	if (section < _header.count() && section >= 0)
		return _header.at(section);
	else
		return QString();
}

QStringList Table::values() {
	return _line;
}

QString Table::value(int section) {
	if (section < _line.count() && section >= 0)
		return _line.at(section);
	else
		return QString();
}

bool Table::nextLine(const QString &separator) {
	QString line;
	if (!_istream->atEnd() && ((line = _istream->readLine()) != separator)) {
		_line = line.replace("\t"," ").split(" ", QString::SkipEmptyParts);
		if (_line.isEmpty())
			return nextLine(separator);
		return true;
	}
	return false;
}
