
#include <QtGui>
#include "image_editor.h"

ImageEditor::ImageEditor()
{
  imageLabelBefore = new QLabel;
  imageLabelBefore->setBackgroundRole(QPalette::Base);
  imageLabelBefore->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  imageLabelBefore->setScaledContents(true);
  imageLabelAfter  = new QLabel;
  imageLabelAfter ->setBackgroundRole(QPalette::Base);
  imageLabelAfter ->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  imageLabelAfter ->setScaledContents(true);

  setCentralWidget(imageLabelBefore);
  createActions();
  createMenus();

  setWindowTitle(tr("Image Editor"));
  resize(500, 400);
}

void ImageEditor::open()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));
  if(!fileName.isEmpty()) {
    QImage image(fileName);
    if(image.isNull()) {
      QMessageBox::information(this, tr("Image Editor"), tr("Cannot open %1.").arg(fileName));
      return;
    }
    imageLabelBefore->setPixmap(QPixmap::fromImage(image));

  }
}

void ImageEditor::createActions()
{
  openAct = new QAction(tr("&Open..."), this);
  openAct->setShortcut(tr("Ctrl+O"));
  connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

  exitAct = new QAction(tr("E&xit"), this);
  exitAct->setShortcut(tr("Ctrl+Q"));
  connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void ImageEditor::createMenus()
{
  fileMenu = new QMenu(tr("&File"), this);
  fileMenu->addAction(openAct);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);

  helpMenu = new QMenu(tr("&Help"), this);
  // helpMenu->addAction(aboutAct);

  menuBar()->addMenu(fileMenu);
  menuBar()->addMenu(helpMenu);
}
