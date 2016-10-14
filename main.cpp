
/*
 * Main program for Image Editor.
 *
 * Author: Satoshi SHIMADA
 * Date: Sep 19, 2015
 * Last-update: Oct 14, 2016
 */

#include <QApplication>
#include <QTranslator>

#include "image_editor.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

#if 0
	// Translator
	// English to Japanese
	QTranslator trans;
	trans.load("ja.qm", qApp->applicationDirPath());
	app.installTranslator(&trans);
#endif

	ImageEditor imageEditor;

#if defined(Q_OS_SYMBIAN)
	imageViweer.showMaximized();
#else
	imageEditor.show();
#endif

	return app.exec();
}

