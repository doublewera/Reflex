#include "picmanager.h"

PicManager::PicManager() : QrbTab(QString(), &createPicturePage) {
	connect(this, SIGNAL(tabCreated(int)), this, SLOT(openPictureProject(int)));
}

void PicManager::openPictureProject(int index) {
	RfxXml *newXml = new RfxXml(tabText(index) + ".xml");
	RfxCss *newCss = newXml.constructCssFileManager();
	xml.insert(index, newXml);
	css.insert(index, newCss);
	// init picture by XML recursively
	(qobject_cast<RfxPicture*>widget(index))initAttributes( &(newXml->documentElement()), newCss );
	// connect this picture and its children to the control system of xml+css
	// it can reduce the speed of work. Think it over
	connect(, SIGNAL(), this, SLOT(xmlChanged()));
	connect(, SIGNAL(), this, SLOT(cssChanged()));
}

PicManager::~PicManager() {
	delete css;
	delete xml;
}
