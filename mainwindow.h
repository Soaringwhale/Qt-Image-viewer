#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>
#include <QLayout>
#include <QPixmap>
#include <QDebug>
#include <QKeyEvent>
#include <QtGui>
#include <QMimeData>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool eventFilter(QObject *watched, QEvent *event);

public slots:
     void open(QString);

 private:
     void scaleImage(double factor);
     void adjustScrollBar(QScrollBar *scrollBar, double factor);

     bool skipLeft();
     bool skipRight();
     bool deletePic();
     QSize updateSize(QSize);
     void clearLayout(QLayout *layout);
     bool changeViewMode();

     QLabel *label;
     QLabel *labelButtonLeft;
     QLabel *labelButtonRight;
     QLabel *labelButtonDelete;
     QLabel *labelButtonFullScreen;
     QStringList picturesFileNames;
     QString currentFilePath;
     QDir dir;

     QScrollArea *scrollArea;
     float scaleFactor;

     QVBoxLayout *vlayout;
     QHBoxLayout *hlayout;

     QMenu *fileMenu;
     QMenu *viewMenu;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
