
#include <QtGui>
#include "image_editor.h"
#include <iostream>

ImageEditor::ImageEditor()
{
	window = new QWidget;

	imageLabelBefore = new QLabel;
	imageLabelBefore->setBackgroundRole(QPalette::Base);
	imageLabelBefore->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imageLabelBefore->setScaledContents(false);
	imageLabelAfter  = new QLabel;
	imageLabelAfter ->setBackgroundRole(QPalette::Base);
	imageLabelAfter ->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imageLabelAfter ->setScaledContents(false);
	filterLabel = new QLabel(tr("Filter: "));

	execButton = new QPushButton(tr("Execute"));
	loadButton = new QPushButton(tr("Load"));
	saveButton = new QPushButton(tr("Save"));
	undoButton = new QPushButton(tr("Undo"));
	outFileNameSetButton = new QPushButton(tr("Set"));

	fileNameEdit = new QLineEdit;

	filterBox = new QComboBox;
	filterBox->addItem(tr("-- select --"));
	filterBox->addItem(tr("Sobel"));
	filterBox->addItem(tr("RGB to Gray"));
	filterBox->addItem(tr("Threshold"));
	filterBox->addItem(tr("Median"));

	windowLayout = new QVBoxLayout;
	imageLayout  = new QHBoxLayout;
	toolLayout   = new QHBoxLayout;
	infoLayout   = new QHBoxLayout;
	topLayout    = new QVBoxLayout;

	imageLayout->addWidget(imageLabelBefore);
	imageLayout->addWidget(imageLabelAfter);

	toolLayout->addWidget(filterLabel);
	toolLayout->addWidget(filterBox);
	toolLayout->addWidget(execButton);
	toolLayout->addWidget(loadButton);
	toolLayout->addWidget(saveButton);
	toolLayout->addWidget(undoButton);

	infoLayout->addWidget(fileNameEdit);
	infoLayout->addWidget(outFileNameSetButton);

	topLayout->addLayout(toolLayout);
	topLayout->addLayout(infoLayout);

	windowLayout->addLayout(topLayout);
	windowLayout->addLayout(imageLayout);
	window->setLayout(windowLayout);
	setCentralWidget(window);

	setSignals();
	createActions();
	createMenus();

	setWindowTitle(tr("Image Editor"));
	resize(500, 400);
}

void ImageEditor::open()
{
	inFileName = QFileDialog::getOpenFileName(this, tr("Open File"));
	if(!inFileName.isEmpty()) {
		QImage image(inFileName);
		if(image.isNull()) {
			QMessageBox::information(this, tr("Image Editor"), tr("Cannot open %1.").arg(inFileName));
			return;
		}
		imageLabelBefore->setPixmap(QPixmap::fromImage(image));

		QByteArray ba = inFileName.toAscii();
		char *fileNameAscii = ba.data();
		imageP = new ImageProcessing(fileNameAscii);
	}
}

void ImageEditor::save()
{
	outFileName = QFileDialog::getSaveFileName(this, tr("Save File"));
	imageP->save(outFileName.toAscii().data());
}

void ImageEditor::saveFile()
{
	char *f = imageP->getFileName();
	try {
		imageP->save(f);
	} catch(cv::Exception) {
		//
	}
	return;
}

void ImageEditor::setOutFileName()
{
	QString str = fileNameEdit->text();
	char *fn = str.toAscii().data();
	imageP->setFileName(fn);
}

void ImageEditor::execFilter()
{
	QString str = filterBox->currentText();
	
	if(str.isEmpty()) {
		QMessageBox::information(this, tr("Image Editor"), tr("Select filter!"));
		return;
	}
	if(inFileName.isEmpty()) {
		QMessageBox::information(this, tr("Image Editor"), tr("Select image!"));
		return;
	}
	if(str == tr("Sobel")) {
		fileNameEdit->setText(str);
	} else if(str == tr("RGB to Gray")) {
		imageP->RGB2GRAY();
		imageP->save(imageP->tmpFileName);
		QImage image(imageP->tmpFileName);
		if(image.isNull()) return;
		imageLabelAfter->setPixmap(QPixmap::fromImage(image));
	} else if(str == tr("Threshold")) {
		imageP->Threshold(100);
		imageP->save(imageP->tmpFileName);
		QImage image(imageP->tmpFileName);
		if(image.isNull()) return;
		imageLabelAfter->setPixmap(QPixmap::fromImage(image));
	}
}

void ImageEditor::createActions()
{
	openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcut(tr("Ctrl+O"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	saveAct = new QAction(tr("&Save..."), this);
	saveAct->setShortcut(tr("Ctrl+S"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcut(tr("Ctrl+Q"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void ImageEditor::createMenus()
{
	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	helpMenu = new QMenu(tr("&Help"), this);
	// helpMenu->addAction(aboutAct);

	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(helpMenu);
}

void ImageEditor::setSignals()
{
	connect(execButton, SIGNAL(clicked()), this, SLOT(execFilter()));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveFile()));
	connect(outFileNameSetButton, SIGNAL(clicked()), this, SLOT(setOutFileName()));
}
