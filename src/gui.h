#ifndef _REFLEX_GUI_H_
#define _REFLEX_GUI_H_

#include <qrbxml/cssmanager.h>
#include <qrbxml/xmlmanager.h>

#include <QtXml/QDomDocument>
#include <QtGui/QLabel>
#include <QtGui/QGridLayout>
#include <QtGui/QStackedWidget>
#include <QtCore/QStringList>
#include <qrb/tab.h>
#include <qrb/editlist.h>
#include <qrb/frame.h>
#include <qrb/link.h>

class RfxParent : public QrbFrame {
Q_OBJECT

signals:
	//Must be catched by visual part and redraw preview
	void previewIsNecessary();

public slots:
	void setProperty(const QString &name, const QString &value);

public:
	RfxParent();

	// Read the XML element and fill out the EditLists as necessary
	//Fills the list and refresh preview: Calls xmlToList()
	//fills the editList by the special part of xml-tree
	void xmlToList(const QDomElement &xml);
	void cssToList(const QrbCssMap &cssMap);
	//called from the exportXml(). Class-independent
	QDomElement *xmlFromList();
	void cssFromList(QFile *f);

	virtual QDomElement *constructXMLWithChildren(QFile *cssFile) {return xmlFromList();}
	virtual void initAttributes(QDomElement *xml, RfxCss *css);
        /** Merges existing data and new data:
        // * adds children with their parameters if no such child present
        // * edits existing children by replacing values if the box is checked, otherwise leaves old values
	*/

protected:
	//Class-dependent:
	//called from the constructor.
	virtual void initAttributeTypes();
	virtual void initLayouts();

protected:
	QLabel		*header;
	QrbEditList	*xmlList, *cssList;
	QLabel		*visualPart; //virtual pointer. Should point to specific drawing device forthe specific class
	QString		elemName;
	QGridLayout	*layout;
};

class RfxGraphic : public RfxParent {
Q_OBJECT

public:
	RfxGraphic();
private slots:
	void changeAttributeList(const QStringList &coordList);
private:
	void initAttributeTypes();
	void initLayouts();
};

class RfxAxis : public RfxParent {
public:
	RfxAxis();
private:
	void initAttributeTypes();
	void initLayouts();
};

class RfxLabel : public RfxParent {
public:
	RfxLabel();
	void initAttributes(QDomElement *xml, RfxCss *css);
private:
	void initAttributeTypes();
//	void initLayouts();
};

class RfxLegend : public RfxParent {
Q_OBJECT
public:
	RfxLegend();
	QDomElement *constructXMLWithChildren(QFile *cssFile);
	void initAttributes(QDomElement *xml, RfxCss *css);
private:
	void initAttributeTypes();
	void initLayouts();
	static QWidget *createNewLabel() {return new RfxLabel();}
	QrbTab	*labels;
};

class RfxGrid : public RfxParent {
Q_OBJECT

signals:
	void gridTypeChanged(const QStringList &l);

private slots:
	void changeGridType(const QString &paramName, const QVariant &value);
	void connectNewGraphicToGrid(int index);

public:
	RfxGrid();
	enum Type {Cartesian2d = 0, Polar, Cartesian3d, Cylindric, Spheric};
	QDomElement *constructXMLWithChildren(QFile *cssFile);
	void initAttributes(QDomElement *xml, RfxCss *css);
	static const QStringList typeNames;
private:
	static const QStringList i_typeNames();
	void initAttributeTypes();
	void initLayouts();
	static QWidget *createNewGraphic() {return new RfxGraphic();}
	static QWidget *createNewAxis() {return new RfxAxis();}
	QrbTab	*graphics;
	QTabWidget *axes;
};

class RfxPicture : public RfxParent {
Q_OBJECT

signals:
	void refreshXml();
	void refreshXml();

public:
	RfxPicture();
	~RfxPicture();
	void initAttributes(QDomElement *xml, RfxCss *css);

private slots:
	void sendXmlRefreshSignal();
	void sendCssRefreshSignal();
connect(cssList, SIGNAL(dataChanged(const QString &, const QVariant &)), , SLOT(sendCssRefreshSignal(const QString &, const QVariant &)));
connect(xmlList, SIGNAL(dataChanged(const QString &, const QVariant &)), , SLOT(sendXmlRefreshSignal(const QString &, const QVariant &)));
void RfxPicture::sendXmlRefreshSignal(const QString &fieldName, const QVariant &value) {
}
void RfxPicture::sendXmlRefreshSignal(const QString &fieldName, const QVariant &value) {
}

private:
	QDomElement *constructXMLWithChildren(QFile *cssFile);
	void initAttributeTypes();
	void initLayouts();
	static QWidget *createNewGrid() {return new RfxGrid();}
	static QWidget *createNewLegend() {return new RfxLegend();}
	static QWidget *createNewLabel() {return new RfxLabel();}
	QrbTab	*grids, *legends, *labels;
	QStackedWidget	*children;
	QrbLink *switchGridsLegendsLabels;
};

QWidget *createPicturePage();

#endif
