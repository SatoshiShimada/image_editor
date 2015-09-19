
#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QMenu>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class ImageEditor : public QMainWindow 
{
	Q_OBJECT

public:
	ImageEditor();

private slots:
	void open();

private:
	void createMenus();
	void updateActions();
	void createActions();

	QWidget *window;

	QVBoxLayout *windowLayout;
	QHBoxLayout *imageLayout;
	QHBoxLayout *toolLayout;

	QPushButton *execButton;
	QPushButton *loadButton;
	QPushButton *saveButton;
	QPushButton *undoButton;

	QComboBox *filterBox;

	QLabel *filterLabel;
	QLabel *imageLabelBefore;
	QLabel *imageLabelAfter;

	QAction *openAct;
	QAction *exitAct;

	QMenu *fileMenu;
	QMenu *helpMenu;
};
