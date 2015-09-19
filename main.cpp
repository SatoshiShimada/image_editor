
#include <QApplication>

#include "image_editor.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  ImageEditor imageEditor;

#if defined(Q_OS_SYMBIAN)
  imageViweer.showMaximized();
#else
  imageEditor.show();
#endif

  return app.exec();
}
