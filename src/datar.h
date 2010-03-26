#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

/************************************
Data reader
Data processor
Two or three data-readers per line (graphic) - one per axis
************************************/

#include <QStringList>

class Datar { // it was Table
public:
	Datar(const QString &codeString, const QStringList &header);
	void debugPrint();
private:
//QString insert
//pointers:
//parse(const QString &format);
	CalcNode cn;

	QStringList partsList;
};

enum ValueType { ErroneousType = 0, Integer, Double, DateTime, TimeDelta };

class CalcNode {
public:
	QPair<ValueType> vt; // vt[0] - type of function
	TYPE calculate();
private:
	void *addr; // function or value address
	QPair<CalcNode> cn; // if empty - addr is a value addr
};

TYPE CalcNode::calculate() {
	return (addr*)(calculate(cn[0]), calculate(cn[1]));
}

#endif

