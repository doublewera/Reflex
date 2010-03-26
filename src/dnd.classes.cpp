#include "dnd.classes.h"

RFXDragAndDrop::RFXDragAndDrop(const QDomElement &xml) {
	treeview = xml;
	preview = new QPixmap();
}

DragNDropLegend::DragNDropLegend() : RFXDragAndDrop(QDomElement()) { // TODO!!!!!!!!!!!!!!!!DEFAULT

}

DragNDropLegend::DragNDropLegend(const QDomElement &legendXml) : RFXDragAndDrop(legendXml) {

}

void DragNDropLegend::init() {

}

DragNDropGrid::DragNDropGrid() : RFXDragAndDrop(QDomElement()) { // TODO!!!!!!!!!!!!!!!!DEFAULT

}

DragNDropGrid::DragNDropGrid(const QDomElement &gridXml) : RFXDragAndDrop(gridXml) {

}

void DragNDropGrid::init() {

}

DragNDropPicture::DragNDropPicture() : QrbFrame(1, 1) { // TODO!!!!!!!!!!!!!!!!DEFAULT

}

DragNDropPicture::DragNDropPicture(const QDomElement &picXml) : QrbFrame(1, 1) {

}

void DragNDropPicture::init() {

}

void DragNDropPicture::addGrid(DragNDropGrid *g) {
	gridStack.append(g);
}

void DragNDropPicture::delGrid(DragNDropGrid *g) {
	gridStack.removeAll(g);
}

void DragNDropPicture::addLegend(DragNDropLegend *l) {
	legendStack.append(l);
}

void DragNDropPicture::delLegend(DragNDropLegend *l) {
	legendStack.removeAll(l);
}

void DragNDropPicture::addTextLabel(const QString &s) {
	labelStack.append(new QLabel(s));
}

void DragNDropPicture::addImgLabel(const QString &fileName) {
	QLabel *l = new QLabel();
	QPixmap p;
	p.load(fileName);
	l->setPixmap(p);
	labelStack.append(l);
}

void DragNDropPicture::delLabel(QLabel *l) {
	labelStack.removeAll(l);
}
#include <QtDebug>
DragNDropRFXEditor::DragNDropRFXEditor(const QDomDocument &layout) : QrbFrame(1,1) {
	int i;
	lineLabel = new QLabel("line");
	textLabel = new QLabel("Type here...");
	imgLabel = new QLabel();
	///Load icon
	QPixmap p;
	p.load("house.png");
	imgLabel->setPixmap(p);
	//end of Load Icon
	legendLabel = new QLabel("legend");
	picturePlace = new DragNDropPicture();

	QLabel *l = new QLabel();
	p.load("2d.png");
	l->setPixmap(p);
	gridList.append(l);
	l = new QLabel();
	p.load("polar.png");
	l->setPixmap(p);
	gridList.append(l);
	l = new QLabel();
	p.load("3d.png");
	l->setPixmap(p);
	gridList.append(l);
//	p.load("cylindric.png");
///	l->setPixmap(p);
//	gridList.append(l);
//	p.load("spheric.png");
//	l->setPixmap(p);
//	gridList.append(l);
	gridLayout = new QGridLayout();
	for(i = 0; i < gridList.count(); i++) {
		gridLayout->addWidget(gridList[i], 0, i);
	}
	l = new QLabel();
	p.load("example.png");
	l->setPixmap(p);
	gridLayout->addWidget(l, 1, 0, 1, i);
//	gridLayout->addWidget(picturePlace, 1, 0, 1, i);
	setLayout(gridLayout);
}

