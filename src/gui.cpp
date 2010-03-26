#include <QtCore/QFile>
#include <QtDebug>
#include "gui.h"

RfxParent::RfxParent() : QrbFrame(1, 1) {
	header = new QLabel();
	xmlList = new QrbEditList;
	cssList = new QrbEditList;
//	QLabel		*visualPart; //virtual pointer. Should point to specific drawing device forthe specific class
	layout = new QGridLayout();
	elemName = "parent";
	initLayouts();
	initAttributeTypes();
}

void RfxParent::setProperty(const QString &name, const QString &value) {
	if(xmlList)
		xmlList->setValue(name, value);
	if(cssList)
		cssList->setValue(name, value);
}

void RfxParent::initLayouts() {
	layout->addWidget(header, 0, 0);
	layout->addWidget(xmlList, 1, 0);
	layout->addWidget(cssList, 2, 0);
	setLayout(layout);
}

QDomElement *RfxParent::xmlFromList() {
	return RfxXml::mapToXml(elemName, xmlList->result());
}

void RfxParent::cssFromList(QFile *f) { // TODO --> cssManager :: mapToCss
	//return mapToCss(elemName + QString(".") + xmlList->result()["class"].toString(), cssList->result());
	if(cssList) {
		QrbCssMap res = cssList->result();
		f->write((elemName + QString(".") + xmlList->result()["class"].toString() + "{\n").toAscii());
		QStringList k = res.keys();
		for(int i = 0; i < k.count(); i++) {
			f->write(("\t" + k[i] + ":" + res[k[i]].toString() + ";\n").toAscii());
		}
		f->write(QString("}\n").toAscii());
	}
}

void RfxParent::xmlToList(const QDomElement &xml) {
	QDomNamedNodeMap dnnm = xml.attributes();
	for(int i = 0; i < dnnm.count(); i++) {
		if(dnnm.item(i).nodeValue() != "")// don't replace by empty... TODO: think it over
			xmlList->setValue(dnnm.item(i).nodeName(), dnnm.item(i).nodeValue());
	}
	emit previewIsNecessary();
}

void RfxParent::cssToList(const QrbCssMap &cssMap) {
	for(QrbCssMap::const_iterator property = cssMap.begin(); property != cssMap.end(); property++) {
		if(property.value() != "")// don't replace by empty... TODO: think it over
			cssList->setValue(property.key(), property.value());
	}
	emit previewIsNecessary();
}

void RfxParent::initAttributeTypes() {

}

RfxGraphic::RfxGraphic() {
	header->setText("Graphic config:");
	elemName = "graphic";
	initAttributeTypes();
	initLayouts();
}

void RfxGraphic::initLayouts() {
	layout->removeWidget(cssList);
	cssList->~QrbEditList();
	cssList = 0;
}

void RfxGraphic::initAttributeTypes() {
	QMap<QString, QrbEditList::Type> attrib;
	attrib.insert("title", QrbEditList::Text);
	attrib.insert("pen", QrbEditList::Text);
	attrib.insert("color", QrbEditList::Text);//change type to #RRGGBB
	xmlList->init(attrib);
}

void RfxGraphic::changeAttributeList(const QStringList &coordList){
	xmlList->delRow("x");
	xmlList->delRow("y");
	xmlList->delRow("z");
	xmlList->delRow("r");
	xmlList->delRow("phi");
	xmlList->delRow("psi");
	for(QStringList::const_iterator i = coordList.begin(); i != coordList.end(); i++){
		xmlList->addRow(*i, QrbEditList::Text);
	}
}

RfxAxis::RfxAxis() {
	header->setText("Axis config:");
	elemName = "axis";
	initAttributeTypes();
	initLayouts();
}

void RfxAxis::initLayouts() {
	layout->removeWidget(cssList);
	cssList->~QrbEditList();
	cssList = 0;
}

void RfxAxis::initAttributeTypes() {
	QMap<QString, QrbEditList::Type> attrib;
//enum Type { Text, Boolean, Int, Float, Date, Currency, Percent, Passwd, Variants };
	attrib.insert("name", QrbEditList::Text);
	attrib.insert("direction", QrbEditList::Text);//Change to $d[%];$d[%]
	attrib.insert("min", QrbEditList::Text);//Change to Axis-Type
	attrib.insert("max", QrbEditList::Text);//Change to Axis-Type
	attrib.insert("major", QrbEditList::Text);//3 types: int, [start][every]
	attrib.insert("minor", QrbEditList::Text);
	attrib.insert("skip", QrbEditList::Text);//Change to Axis-Type
	xmlList->init(attrib);
	QStringList l;
	l.append("double");
	l.append("datetime");
	xmlList->addRow("type", QrbEditList::Variants, l);
}

RfxLabel::RfxLabel() {
	header->setText("Label setup:");
	elemName = "label";
	initAttributeTypes();
}

void RfxLabel::initAttributeTypes() {
	QMap<QString, QrbEditList::Type> attrib;
//enum Type { Text, Boolean, Int, Float, Date, Currency, Percent, Passwd, Variants };
	attrib.insert("class", QrbEditList::Text);
	attrib.insert("style", QrbEditList::Text);
	attrib.insert("text", QrbEditList::Text);
	xmlList->init(attrib);
	attrib.clear();
	attrib.insert("top", QrbEditList::Text);
	attrib.insert("left", QrbEditList::Text);
	attrib.insert("width", QrbEditList::Text);
	attrib.insert("height", QrbEditList::Text);
	attrib.insert("padding", QrbEditList::Int);
	attrib.insert("background-color", QrbEditList::Text);//#RRGGBB
	attrib.insert("background-image", QrbEditList::Text);//URL
	attrib.insert("background-position", QrbEditList::Text);
	attrib.insert("background-repeat", QrbEditList::Text);
	attrib.insert("border-width", QrbEditList::Text);
	attrib.insert("border-style", QrbEditList::Text);
	attrib.insert("border-color", QrbEditList::Text);
	attrib.insert("color", QrbEditList::Text);
	attrib.insert("font-family", QrbEditList::Text);
	attrib.insert("font-size", QrbEditList::Text);
	attrib.insert("font-style", QrbEditList::Text);
	attrib.insert("opacity", QrbEditList::Float);
	attrib.insert("z-index", QrbEditList::Int);
	cssList->init(attrib);
}

void RfxLabel::initAttributes(QDomElement *xml, RfxCss *css) {
	xmlToList(*xml);
	cssToList(css->getStyle("label" + QString(".") + xmlList->result()["class"].toString()));//TODO: think about empty subclass
}

RfxLegend::RfxLegend() {
	labels = new QrbTab(QString(), &createNewLabel);
	header->setText("Legend setup:");
	elemName = "legend";
	initLayouts();
	initAttributeTypes();
}

void RfxLegend::initLayouts() {
	layout->addWidget(labels, 0, 1, 3, 1);
}

void RfxLegend::initAttributeTypes() {
	QMap<QString, QrbEditList::Type> attrib;
//enum Type { Text, Boolean, Int, Float, Date, Currency, Percent, Passwd, Variants };
	attrib.insert("class", QrbEditList::Text);
	attrib.insert("style", QrbEditList::Text);
	attrib.insert("rows", QrbEditList::Int);
	attrib.insert("columns", QrbEditList::Int);
	xmlList->init(attrib);
	attrib.clear();
	attrib.insert("top", QrbEditList::Text);
	attrib.insert("left", QrbEditList::Text);
	attrib.insert("width", QrbEditList::Text);
	attrib.insert("height", QrbEditList::Text);
	attrib.insert("padding", QrbEditList::Text);
	attrib.insert("background-color", QrbEditList::Text);
	attrib.insert("border-width", QrbEditList::Text);
	attrib.insert("border-style", QrbEditList::Text);
	attrib.insert("border-color", QrbEditList::Text);
	attrib.insert("color", QrbEditList::Text);
	attrib.insert("line-height", QrbEditList::Text);
	attrib.insert("opacity", QrbEditList::Float);
	attrib.insert("z-index", QrbEditList::Int);
	cssList->init(attrib);
}

void RfxLegend::initAttributes(QDomElement *xml, RfxCss *css) {
	xmlToList(*xml);
	cssToList(css->getStyle("legend" + QString(".") + xmlList->result()["class"].toString()));//TODO: think about empty subclass
	// set xml to children recursively
	QDomNodeList nodeList = xml->elementsByTagName("label");
	for(int i = 0; i < nodeList.count(); i++) {
		(qobject_cast<RfxLabel*> (labels->widget(i)))->initAttributes(&(nodeList.item(i).toElement()), css);
	}
}

QDomElement *RfxLegend::constructXMLWithChildren(QFile *cssFile) {
	QDomElement *xml = xmlFromList();
	RfxParent *p;
	int i = 0;
	for(i = 0; i < labels->count(); i++) {
		if(labels->tabText(i) != "") {
			p = qobject_cast<RfxParent*>(labels->widget(i));
			p->cssFromList(cssFile);
			xml->appendChild(*(p->xmlFromList()));
		}
	}
	cssFromList(cssFile);
	return xml;
}

const QStringList RfxGrid::typeNames = RfxGrid::i_typeNames();

const QStringList RfxGrid::i_typeNames() {
	QStringList l;
	l.append("cartesian2d");
	l.append("polar");
	l.append("cartesian3d");
	l.append("cylindric");
	l.append("spheric");
	return l;
}

RfxGrid::RfxGrid() {
	header->setText("Grid setup:");
	graphics = new QrbTab(QString(), &createNewGraphic);
	axes = new QTabWidget();
	axes->addTab(new RfxAxis(), "x");
	axes->addTab(new RfxAxis(), "y");
	connectNewGraphicToGrid(0);
	connect(graphics, SIGNAL(tabCreated(int)), this, SLOT(connectNewGraphicToGrid(int)));
	connect(xmlList, SIGNAL(dataChanged(const QString&, const QVariant&)), this, SLOT(changeGridType(const QString&, const QVariant&)));
	elemName = "grid";
	initLayouts();
	initAttributeTypes();
}

void RfxGrid::connectNewGraphicToGrid(int index) {
	connect(this, SIGNAL(gridTypeChanged(const QStringList &)),
		qobject_cast<RfxGraphic*>(graphics->widget(index)), SLOT(changeAttributeList(const QStringList &)));
}

void RfxGrid::initLayouts() {
	layout->addWidget(graphics, 0, 1, 2, 1);
	layout->addWidget(axes, 2, 1);
}

void RfxGrid::initAttributeTypes() {
	QMap<QString, QrbEditList::Type> attrib;
	attrib.insert("class", QrbEditList::Text);
	attrib.insert("style", QrbEditList::Text);
	attrib.insert("offset", QrbEditList::Text);//$d[%];$d[%]
	xmlList->init(attrib);
	xmlList->addRow("type", QrbEditList::Variants, typeNames);
	attrib.clear();
	attrib.insert("top", QrbEditList::Text);
	attrib.insert("left", QrbEditList::Text);
	attrib.insert("width", QrbEditList::Text);
	attrib.insert("height", QrbEditList::Text);
	attrib.insert("background-color", QrbEditList::Text);
	attrib.insert("border-width", QrbEditList::Text);
	attrib.insert("border-style", QrbEditList::Text);
	attrib.insert("border-color", QrbEditList::Text);
	attrib.insert("color", QrbEditList::Text);
	attrib.insert("line-height", QrbEditList::Text);
	attrib.insert("opacity", QrbEditList::Float);
	attrib.insert("z-index", QrbEditList::Int);
	cssList->init(attrib);
}

void RfxGrid::initAttributes(QDomElement *xml, RfxCss *css) {
	xmlToList(*xml);
	cssToList(css->getStyle("grid" + QString(".") + xmlList->result()["class"].toString()));//TODO: think about empty subclass
	// set xml to children recursively
	QDomNodeList nodeList = xml->elementsByTagName("graphic");
	for(int i = 0; i < nodeList.count(); i++) {
		(qobject_cast<RfxGraphic*> (graphics->widget(i)))->xmlToList(nodeList.item(i).toElement());
	}
	nodeList = xml->elementsByTagName("axis");
	for(int i = 0; i < nodeList.count(); i++) {
		(qobject_cast<RfxAxis*> (axes->widget(i)))->xmlToList(nodeList.item(i).toElement());
	}
}

void RfxGrid::changeGridType(const QString &paramName, const QVariant &value) {
	if (paramName != "type")
		return;
	QStringList l;
	switch (typeNames.indexOf(value.toString())) {
	case Cartesian2d:
		axes->setTabText(0, "x");
		axes->setTabText(1, "y");
		if(axes->count()>2) {
			axes->widget(2);
			axes->removeTab(2);
		}
		l.append("x");
		l.append("y");
		break;
	case Polar:
		axes->setTabText(0, "r");
		axes->setTabText(1, "phi");
		if(axes->count()>2) {
			axes->widget(2);
			axes->removeTab(2);
		}
		l.append("r");
		l.append("phi");
		break;
	case Cartesian3d:
		axes->setTabText(0, "x");
		axes->setTabText(1, "y");
		if(axes->count()<3)
			axes->addTab(createNewAxis(), "z");
		else
			axes->setTabText(2, "z");
		l.append("x");
		l.append("y");
		l.append("z");
		break;
	case Cylindric:
		axes->setTabText(0, "r");
		axes->setTabText(1, "phi");
		axes->setTabText(2, "z");
		if(axes->count()<3)
			axes->addTab(createNewAxis(), "z");
		else
			axes->setTabText(2, "z");
		l.append("r");
		l.append("phi");
		l.append("z");
		break;
	case Spheric:
		axes->setTabText(0, "r");
		axes->setTabText(1, "phi");
		axes->setTabText(2, "psi");
		if(axes->count()<3)
			axes->addTab(createNewAxis(), "psi");
		else
			axes->setTabText(2, "psi");
		l.append("r");
		l.append("phi");
		l.append("psi");
		break;
	}
        emit gridTypeChanged(l);
}

QDomElement *RfxGrid::constructXMLWithChildren(QFile *cssFile) {
	QDomElement *xml = xmlFromList();
	RfxParent *p;
	int i = 0;
	for(i = 0; i < axes->count(); i++) {
		if(axes->tabText(i) != "") {
			p = qobject_cast<RfxParent*>(axes->widget(i));
			xml->appendChild(*(p->xmlFromList()));
			xml->lastChildElement().setAttribute("name", axes->tabText(i));
		}
	}
	for(i = 0; i < graphics->count()-1; i++) {
		if(graphics->tabText(i) != "") {
			p = qobject_cast<RfxParent*>(graphics->widget(i));
			xml->appendChild(*(p->xmlFromList()));
		}
	}
	cssFromList(cssFile);
	return xml;
}

RfxPicture::RfxPicture() {
	grids = new QrbTab(QString(), &createNewGrid);
	legends = new QrbTab(QString(), &createNewLegend);
	labels = new QrbTab(QString(), &createNewLabel);
	children = new QStackedWidget();
	children->addWidget(grids);
	children->addWidget(legends);
	children->addWidget(labels);
	header->setText("Picture setup:");
	elemName = "picture";
	QStringList l;
	l.append("show Legends");
	l.append("show Labels");
	l.append("show Grids");
	switchGridsLegendsLabels = new QrbLink(l);
	connect(switchGridsLegendsLabels, SIGNAL(clicked(int)), children, SLOT(setCurrentIndex(int)));
	initLayouts();
	initAttributeTypes();
}

void RfxPicture::initLayouts() {
	layout->removeWidget(cssList);
	layout->removeWidget(xmlList);
	layout->addWidget(switchGridsLegendsLabels, 0, 1);
	layout->addWidget(xmlList, 1, 0, 1, 2);
	layout->addWidget(cssList, 2, 0, 1, 2);
	layout->addWidget(children, 0, 2, 3, 1);
}

void RfxPicture::initAttributeTypes() {
	QMap<QString, QrbEditList::Type> attrib;
//enum Type { Text, Boolean, Int, Float, Date, Currency, Percent, Passwd, Variants };
	attrib.insert("class", QrbEditList::Text);
	attrib.insert("style", QrbEditList::Text);
	xmlList->init(attrib);
	QStringList l;
	l.append("png");
	l.append("jpg");
	xmlList->addRow("format", QrbEditList::Variants, l);
	attrib.clear();
	attrib.insert("width", QrbEditList::Text);
	attrib.insert("height", QrbEditList::Text);
	attrib.insert("background-color", QrbEditList::Text);
	attrib.insert("background-image", QrbEditList::Text);
	attrib.insert("background-position", QrbEditList::Text);
	attrib.insert("background-repeat", QrbEditList::Text);
	attrib.insert("border-width", QrbEditList::Text);
	attrib.insert("border-style", QrbEditList::Text);
	attrib.insert("border-color", QrbEditList::Text);
	cssList->init(attrib);
}

void RfxPicture::initAttributes(QDomElement *xml, RfxCss *css) {
	xmlToList(*xml);
	cssToList(css->getStyle("picture" + QString(".") + xmlList->result()["class"].toString()));//TODO: think about empty subclass
	// set xml to children recursively
	QDomNodeList nodeList = xml->elementsByTagName("grid");
	for(int i = 0; i < nodeList.count(); i++) {
		(qobject_cast<RfxGrid*> (grids->widget(i)))->initAttributes(&(nodeList.item(i).toElement()), css);
	}
	nodeList = xml->elementsByTagName("legend");
	for(int i = 0; i < nodeList.count(); i++) {
		(qobject_cast<RfxLegend*> (legends->widget(i)))->initAttributes(&(nodeList.item(i).toElement()), css);
	}
	nodeList = xml->elementsByTagName("label");
	for(int i = 0; i < nodeList.count(); i++) {
		(qobject_cast<RfxLabel*> (labels->widget(i)))->initAttributes(&(nodeList.item(i).toElement()), css);
	}
}

QWidget *createPicturePage() {
	return new RfxPicture();
}

QDomDocument RfxPicture::createXMLDocument() {
//RfxXml::createXMLDocument(DTDHREF, STYLESHEET, *elem)
	QDomDocument picxml("picture SYSTEM \"hexagon.dtd\"");
	picxml.appendChild(picxml.createProcessingInstruction("xml-stylesheet", QString("type=\"text/css\" href=\"") + QString(STYLESHEET) + "\""));

	QFile cssFile(STYLESHEET);
	cssFile.open(QIODevice::WriteOnly);
	QDomElement *elem = constructXMLWithChildren(&cssFile);
	cssFile.close();

	picxml.appendChild(*elem);
	//writing xml to file TODO: choose the file
	QFile xmlFile(HEXAGONXML);
	xmlFile.open(QIODevice::WriteOnly);
	xmlFile.write(picxml.toString().toAscii());
	xmlFile.close();
	return picxml;
}

QDomElement *RfxPicture::constructXMLWithChildren(QFile *cssFile) {
	QDomElement *xml = xmlFromList();
	cssFromList(cssFile);
	int i = 0;
	for(i = 0; i < grids->count(); i++) {
		if(grids->tabText(i) != "") {
			xml->appendChild(*((qobject_cast<RfxGrid*>(grids->widget(i)))->constructXMLWithChildren(cssFile)));
		}
	}
	for(i = 0; i < legends->count(); i++) {
		if(legends->tabText(i) != "") {
			xml->appendChild(*((qobject_cast<RfxLegend*>(legends->widget(i)))->constructXMLWithChildren(cssFile)));
		}
	}
	RfxParent *p;
	for(i = 0; i < labels->count(); i++) {
		if(labels->tabText(i) != "") {
			p = qobject_cast<RfxParent*>(labels->widget(i));
			p->cssFromList(cssFile);
			xml->appendChild(*(p->xmlFromList()));
		}
	}
	return xml;
}

RfxPicture::~RfxPicture() {
	createXMLDocument();
}
