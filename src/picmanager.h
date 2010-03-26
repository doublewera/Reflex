#ifndef _PICTURE_MANAGER_H_
#define _PICTURE_MANAGER_H_

#include <QtCore/QList>
#include <qrb/tab.h>
#include <qrbxml/xmlmanager.h>
#include <qrbxml/cssmanager.h>
#include "gui.h"

#define DTDHREF    "hexagon.dtd"
#define STYLESHEET ".default.css"
#define DEFAULT    "default"
//#define DEFAULTXML "."default.xml"

class PicManager : public QrbTab {
Q_OBJECT

public slots:
	void openPictureProject(int index);
	void cssChanged();
	void xmlChanged();

public:
	PicManager();
	~PicManager();
private:
	QList<RfxCss*> css;
	QList<RfxXml*> xml;
};

#endif

void PicManager::cssChanged(int index) {
	css[index]->setSelectorProperty(const QString &selector, const QString &property, const QString &value)
}
