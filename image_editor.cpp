
#include <QtGui>
#include "image_editor.h"

ImageEditor::ImageEditor()
{
	window = new QWidget;

  imageLabelBefore = new QLabel;
  imageLabelBefore->setBackgroundRole(QPalette::Base);
  //imageLabelBefore->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  imageLabelBefore->setScaledContents(false);
  imageLabelAfter  = new QLabel;
  imageLabelAfter ->setBackgroundRole(QPalette::Base);
  //imageLabelAfter ->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  imageLabelAfter ->setScaledContents(true);
  filterLabel = new QLabel(tr("Filter: "));

  execButton = new QPushButton(tr("Execute"));
  loadButton = new QPushButton(tr("Load"));
  saveButton = new QPushButton(tr("Save"));
  undoButton = new QPushButton(tr("Undo"));

  filterBox = new QComboBox;
  filterBox->addItem(tr("-- select --"));
  filterBox->addItem(tr("Sobel"));
  filterBox->addItem(tr("RGB to Gray"));
  filterBox->addItem(tr("Threshold"));
  filterBox->addItem(tr("Median"));

  windowLayout = new QVBoxLayout;
  imageLayout  = new QHBoxLayout;
  toolLayout   = new QHBoxLayout;

  imageLayout->addWidget(imageLabelBefore);
  imageLayout->addWidget(imageLabelAfter);

  toolLayout->addWidget(filterLabel);
  toolLayout->addWidget(filterBox);
  toolLayout->addWidget(execButton);
  toolLayout->addWidget(loadButton);
  toolLayout->addWidget(saveButton);
  toolLayout->addWidget(undoButton);

  windowLayout->addLayout(toolLayout);
  windowLayout->addLayout(imageLayout);
  window->setLayout(windowLayout);
  setCentralWidget(window);

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
