
#include <QMainWindow>
#include <QApplication>
#include <QLabel>
#include <QMenu>

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

    QLabel *imageLabelBefore;
    QLabel *imageLabelAfter;

    QAction *openAct;
    QAction *exitAct;

    QMenu *fileMenu;
    QMenu *helpMenu;
};
