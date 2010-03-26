#ifndef _REFLEX_DND_CLASSES_H_
#define _REFLEX_DND_CLASSES_H_

#include <QtXml/QDomDocument>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <qrb/frame.h>

class RFXDragAndDrop : public QImage {
public:
	RFXDragAndDrop(const QDomElement &xml);
protected:
	virtual void init() {}
private:
	QPixmap		*preview;
	QDomElement	treeview;
};

class DragNDropLegend : public RFXDragAndDrop {
public:
	DragNDropLegend();
	DragNDropLegend(const QDomElement &legendXml);
private:
	virtual void init();
};

class DragNDropGrid : public RFXDragAndDrop {
public:
	DragNDropGrid();
	DragNDropGrid(const QDomElement &gridXml);
private:
	virtual void init();
};

class DragNDropPicture : public QImage, public QrbFrame {
public:
	DragNDropPicture();
	DragNDropPicture(const QDomElement &legendXml);
	void addGrid(DragNDropGrid *g);
	void delGrid(DragNDropGrid *g);
	void addLegend(DragNDropLegend *l);
	void delLegend(DragNDropLegend *l);
	void addTextLabel(const QString &s);
	void addImgLabel(const QString &fileName);
	void delLabel(QLabel *l);

private:
	virtual void init();
	QList<DragNDropGrid *>   gridStack;
	QList<DragNDropLegend *> legendStack;
	QList<QLabel *>          labelStack;
};

class DragNDropRFXEditor : public QrbFrame {
public:
	DragNDropRFXEditor(const QDomDocument &layout);
private:
	QList<QLabel *>	 gridList;
	QLabel 		*lineLabel,
			*textLabel,
			*imgLabel,
			*legendLabel;
	DragNDropPicture *picturePlace;
	QGridLayout	*gridLayout;
};

#endif

