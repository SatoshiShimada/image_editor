
#include <QtGui>
#include "image_editor.h"
#include <iostream>

ImageEditor::ImageEditor()
{
	window    = new QWidget;
	imageArea = new QWidget;
	general   = new QWidget;
	rgb2gray  = new QWidget;
	threshold = new QWidget;

	toolTab = new QTabWidget;

	windowLayout = new QVBoxLayout;
	imageLayout  = new QHBoxLayout;
	toolLayout   = new QHBoxLayout;
	infoLayout   = new QHBoxLayout;
	topLayout    = new QVBoxLayout;

	createImageArea();
	createGeneralTab();
	createRgb2GrayTab();
	createThresholdTab();

	imageLayout->addWidget(imageLabelBefore);
	imageLayout->addWidget(imageLabelAfter);
	imageArea->setLayout(imageLayout);

	// tab append
	toolTab->addTab(general, tr("General"));
	toolTab->addTab(rgb2gray, tr("RGB to GRAY"));
	toolTab->addTab(threshold, tr("Threshold"));

	windowLayout->addWidget(toolTab);
	windowLayout->addStretch();
	windowLayout->addWidget(imageArea);
	window->setLayout(windowLayout);
	setCentralWidget(window);

	setSignals();
	createActions();
	createMenus();

	setWindowTitle(tr("Image Editor"));
	//resize(400, 300);
}

void ImageEditor::createImageArea()
{
	// create image area
	imageLabelBefore = new QLabel;
	imageLabelBefore->setBackgroundRole(QPalette::Base);
	//imageLabelBefore->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imageLabelBefore->setScaledContents(false);
	imageLabelAfter  = new QLabel;
	imageLabelAfter ->setBackgroundRole(QPalette::Base);
	imageLabelAfter ->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imageLabelAfter ->setScaledContents(false);
}

void ImageEditor::createGeneralTab()
{
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

	general->setLayout(topLayout);
}

void ImageEditor::createRgb2GrayTab()
{
}

void ImageEditor::createThresholdTab()
{
	//thresholdTypeLabel = new QLabel(tr("Threshold Type:"));
	thresholdTypeLabel  = new QLabel(tr("Threshold Type:"));
	thresholdValueLabel = new QLabel(tr("Threshold Value:"));
	thresholdTypeBox    = new QComboBox;
	thresholdValueBox   = new QSpinBox;
	thresholdExecButton = new QPushButton(tr("Execute"));

	thresholdTypeBox->addItem(tr("Static"));
	thresholdTypeBox->addItem(tr("Mode"));
	thresholdTypeBox->addItem(tr("discrim"));
	thresholdTypeBox->addItem(tr("Dynamic"));

	thresholdValueBox->setMaximum(255);
	thresholdValueBox->setMinimum(0);

	thresholdLayout = new QGridLayout;
	thresholdLayout->addWidget(thresholdTypeLabel, 0, 0, Qt::AlignRight);
	thresholdLayout->addWidget(thresholdTypeBox, 0, 1);
	thresholdLayout->addWidget(thresholdValueLabel, 1, 0, Qt::AlignRight);
	thresholdLayout->addWidget(thresholdValueBox, 1, 1);
	thresholdLayout->addWidget(thresholdExecButton, 2, 0);

	threshold->setLayout(thresholdLayout);
}

void ImageEditor::load()
{
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

void ImageEditor::open()
{
	inFileName = QFileDialog::getOpenFileName(this, tr("Open File"));
	load();
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
	connect(loadButton, SIGNAL(clicked()), this, SLOT(load()));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveFile()));
	connect(outFileNameSetButton, SIGNAL(clicked()), this, SLOT(setOutFileName()));
}
