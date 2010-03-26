#include <QtXml/QDomDocument>
#include "classes.gui.h"
#include <QtDebug>

#define DTDHREF    "hexagon.dtd"
#define STYLESHEET ".default.css"
#define HEXAGONXML ".default.xml"

QDomElement ReflexGUIWidget::xmlGen(const QString &elemName) {
	QDomDocument frag;
	QDomElement elem = frag.createElement(elemName);
	QMap<QString, QVariant> res = xmllist->result();
	QStringList k = res.keys();
	for(QStringList::iterator i = k.begin(); i != k.end(); i++){
		elem.setAttribute(*i, res[*i].toString());
	}
	return elem;
}

QrbCSSmap ReflexGUIWidget::cssGen(){
	return csslist->result();
}

QDomDocument ReflexGUIPicture::getxml() {
	int i = 0;
	QDomDocument picxml("picture SYSTEM \"hexagon.dtd\"");
        picxml.appendChild(picxml.createProcessingInstruction("xml-stylesheet", QString("type=\"text/css\" href=\"") + QString(STYLESHEET) + "\""));
	QFile cssFile(STYLESHEET);
	cssFile.open(QIODevice::WriteOnly);

	QDomElement elem = xmlGen("picture");
	for(i = 0; i < gridTab->count(); i++) {
		elem.appendChild(((ReflexGUIGridTab *)(gridTab->widget(i)))->getxml());
		elem.lastChildElement().setAttribute("class", gridTab->tabText(i));
		cssOutput(&cssFile, (ReflexGUIWidget *)(gridTab->widget(i)), QString("grid") + "." + gridTab->tabText(i));
	}
	for(i = 0; i < legendTab->count(); i++) {
		elem.appendChild(((ReflexGUILegendTab *)(legendTab->widget(i)))->getxml());
		elem.lastChildElement().setAttribute("class", legendTab->tabText(i));
		cssOutput(&cssFile, (ReflexGUIWidget *)(legendTab->widget(i)), QString("legend") + "." + legendTab->tabText(i));
	}
	for(i = 0; i < labelTab->count(); i++) {
		elem.appendChild(((ReflexGUILabelTab *)(labelTab->widget(i)))->xmlGen("label"));
		elem.lastChildElement().setAttribute("class", labelTab->tabText(i));
		cssOutput(&cssFile, (ReflexGUIWidget *)(labelTab->widget(i)), QString("label") + "." + labelTab->tabText(i));
	}

	picxml.appendChild(elem);
	cssOutput(&cssFile, this, "picture");
	cssFile.close();

	QFile xmlFile(HEXAGONXML);
	xmlFile.open(QIODevice::WriteOnly);
	xmlFile.write(picxml.toString().toAscii());
	xmlFile.close();
	return picxml;
}

void ReflexGUIPicture::cssOutput(QFile *f, ReflexGUIWidget *w, const QString &className) {
	f->write(QString(className + "{\n").toAscii());
	QrbCSSmap tmp = w->cssGen();
	QStringList k = tmp.keys();
	for(int i = 0; i < k.count(); i++) {
		f->write(("\t" + k[i] + ":" + tmp[k[i]].toString() + ";\n").toAscii());
	}
	f->write(QString("}\n").toAscii());
}


QDomElement ReflexGUIGridTab::getxml() {
	int i;
	QDomElement gridxml = xmlGen("grid");
	for(i = 0; i < qgac->count(); i++) {
		if (qgac->isTabEnabled(i)){
			gridxml.appendChild(((ReflexGUIAxisTab *)(qgac->widget(i)))->xmlGen("axis"));
			gridxml.lastChildElement().setAttribute("name", qgac->tabText(i));
		}
	}
	for(i = 0; i < qggc->count(); i++) {
		if (qggc->isTabEnabled(i))
			gridxml.appendChild(((ReflexGUIGraphicTab *)(qggc->widget(i)))->xmlGen("graphic"));
	}
	return gridxml;
}

QDomElement ReflexGUILegendTab::getxml() {
	QDomElement legxml = xmlGen("legend");
	for(int i = 0; i < labelTab->count(); i++) {
		legxml.appendChild(((ReflexGUILabelTab *)(labelTab->widget(i)))->xmlGen("label"));
		legxml.lastChildElement().setAttribute("class", labelTab->tabText(i));
	}
	return legxml;
}
