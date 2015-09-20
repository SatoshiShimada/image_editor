
#include <QApplication>
#include <QTranslator>

#include "image_editor.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// Translator
	QTranslator trans;
	trans.load("ja.qm", qApp->applicationDirPath());
	app.installTranslator(&trans);

	ImageEditor imageEditor;

#if defined(Q_OS_SYMBIAN)
	imageViweer.showMaximized();
#else
	imageEditor.show();
#endif

	return app.exec();
}
