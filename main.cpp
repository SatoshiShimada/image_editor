
#include <QApplication>
#include <QTranslator>

#include "image_editor.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

#if 0
	// Translator
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
