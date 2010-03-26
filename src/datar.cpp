#include "datar.h"
#include <math.h>

enum DataType {Error = 0, Constant, SubFormula, MathFunc};
enum MathFuncNumber {NoSuchFunc = 0, NaturalLog, BinaryLog, DecimalLog, Log}
#define ERROR		0
#define CONSTANT	1
#define LEFTBRACKET

Datar::Datar(const QString &codeString, const QStringList &header) {
	partsList = codeString.split("|");
	for(int i = 1; i < partsList.length(); i += 2) {
	}
}

// Пока без оптимизации. Надо бы как-нибудь упростить вычисления.
// Но пока ограничимчся топорной задачкой "калькулятор" для
// комиссии первого курса ВМиК. Методом рекурсивного спуска :(
double Datar::calculate(const QString &formula, const QStringList &header = "", const QString &currDataLine) {
	double result = 0;
	if (header == "") {
		switch (beginOf(formula)) {
		case Constant:
		case SubFormula:
		case MathFunc:
			mathFuncNumber(formula)
		default : //HERE MUST BE A REPORT ERROR
			break;
		}
	}
	else {
	}
	return result;
}

DataType Datar::beginOf(const QString &formula) {
	if (((formula[0] >= QChar('0')) && (formula[0] <= QChar('9'))) || (formula[0] == QChar('+')) || (formula[0] == QChar('-'))) {
		return Constant;
	}
	else if (formula[0] == QChar('\\')) {
		return MathFunc;
	}
	else if (formula[0] == QChar('(')) {
		return SubFormula;
	}
	else
		return Error;
}


MathFuncNumber Datar::mathFuncNumber (const QString &formula) {
	QString funcName = formula.split("{")[0];
	if (funcName == "\ln"){
		return NaturalLog;
	}
	else if (funcName == "\lb") {
		return BinaryLog;
	}
	else if (funcName == "\lg") {
		return DecimalLog;
	}
	else if (funcName == "\log_") {
		return Log;
	}
	else
		return NoSuchFunc;
}

void Datar::debugPrint() {
	qDebug() << partList;
}
/******************************************
formula ::= <const>
	| "|" <columnCombination> "|"
	| "(" <formula> ")"
	| <formula> <mathOp> <formula>
	| <mathFunc> "{" <formula> "}"

cn ::= <const>
	| "$" <columnName> "$"
columnCombination ::= <cn>
		| ( <cn> )? "." ( <cn> )? ( ( "e"|"E" ) <cn> )?
		| <dateCombination>
		| <timeCombination> ( <timeZone> )?
		| <dateCombination> "T" <timeCombination> ( <timeZone> )?

dateCombination ::= <cn> ( "-" <cn> ( "-" <cn> )? )?
		| <cn> ( <cn> ( <cn> )? )?

timeCombination ::= <cn> ( ":" <cn> ( ":" <cn> )? )?
		| <cn> ( <cn> ( <cn> )? )?
hhmm ::= <cn> ( ":" <cn> )?
	| <cn> ( <cn> )?
timeZone ::= "Z" | ("+" | "-") <hhmm>

mathFunc ::=	  "\ln"
		| "\lb"
		| "\lg"
		| "\log_{" <formula> "}"

const ::= <float> | <integer> | "\e" | "\pi" | "\h" | "\c" | "\Re"
float ::= ( <integer> )? "." ( <integer> )? ( ( "e"|"E" ) <integer> )?
integer ::= ("+"|"-")?("0"-"9")+

plusOrMinus ::= "+"
		| "-"
mathOp ::= <plusOrMinus>
		| "*"
		| "^"
		| "/"
		| ":"
		| "%"
******************************************/
