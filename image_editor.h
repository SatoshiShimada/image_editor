
/*
 * Graphical user interface program for Image Editor.
 * Using Qt4.
 *
 * Author: Satoshi SHIMADA
 * Date: Sep 19, 2015
 * Last-update: Oct 14, 2016
 */

#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QMenu>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTabWidget>
#include <QSpinBox>
#include <QGroupBox>

#include "image_processing.h"

class ImageEditor : public QMainWindow 
{
	Q_OBJECT

public:
	ImageEditor();

private slots:
	void open();
	void save();
	void execFilter();
	void saveFile();
	void setOutFileName();
	void load();
	void thresholdExec();

private:
	ImageProcessing *imageP;
	bool f_isOpenFile;

	void createMenus();
	void createActions();
	void createImageArea();
	void createGeneralTab();
	void createRgb2GrayTab();
	void createThresholdTab();
	void createHistgramTab();
	void createGradientTab();
	void createThinningTab();
	void createHoughTab();
	void createSmoothTab();
	void updateActions();
	void setSignals();

	QWidget *window;
	QWidget *imageArea;
	QWidget *general;
	QWidget *rgb2gray;
	QWidget *threshold;
	QWidget *histgram;
	QWidget *gradient;
	QWidget *thinning;
	QWidget *hough;
	QWidget *smooth;

	QTabWidget *toolTab;

	QGroupBox *imageGroup;

	QVBoxLayout *windowLayout;
	QHBoxLayout *imageLayout;
	QHBoxLayout *toolLayout;
	QHBoxLayout *infoLayout;
	QVBoxLayout *topLayout;
	QGridLayout *thresholdLayout;

	QPushButton *execButton;
	QPushButton *loadButton;
	QPushButton *saveButton;
	QPushButton *undoButton;
	QPushButton *outFileNameSetButton;
	QPushButton *thresholdExecButton;

	QLineEdit *fileNameEdit;

	QSpinBox *thresholdValueBox;

	QComboBox *filterBox;
	QComboBox *thresholdTypeBox;

	QLabel *filterLabel;
	QLabel *imageLabelBefore;
	QLabel *imageLabelAfter;
	QLabel *thresholdTypeLabel;
	QLabel *thresholdValueLabel;

	QString inFileName;
	QString outFileName;

	QAction *openAct;
	QAction *saveAct;
	QAction *exitAct;

	QMenu *fileMenu;
	QMenu *helpMenu;
};

