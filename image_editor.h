
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

private:
	ImageProcessing *imageP;

	void createMenus();
	void updateActions();
	void createActions();
	void setSignals();

	QWidget *window;

	QVBoxLayout *windowLayout;
	QHBoxLayout *imageLayout;
	QHBoxLayout *toolLayout;
	QHBoxLayout *infoLayout;
	QVBoxLayout *topLayout;

	QPushButton *execButton;
	QPushButton *loadButton;
	QPushButton *saveButton;
	QPushButton *undoButton;
	QPushButton *outFileNameSetButton;

	QLineEdit *fileNameEdit;

	QComboBox *filterBox;

	QLabel *filterLabel;
	QLabel *imageLabelBefore;
	QLabel *imageLabelAfter;

	QString inFileName;
	QString outFileName;

	QAction *openAct;
	QAction *saveAct;
	QAction *exitAct;

	QMenu *fileMenu;
	QMenu *helpMenu;
};
