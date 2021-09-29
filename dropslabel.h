#ifndef DROPSLABEL_H
#define DROPSLABEL_H

#include <QObject>
#include <QDebug>
#include <QMimeData>
#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QPixmap>
#include <QWidget>
#include <QUrl>
#include <QList>
#include "mainwindow.h"


class DropsLabel : public QLabel                      //   СТАРТОВЫЙ ЛЕЙБЛ КУДА НАДО ПЕРЕТАЩИТЬ ФАЙЛ
{
   Q_OBJECT
public:
    DropsLabel( QWidget* parent = 0 );

protected:
    void dragEnterEvent(QDragEnterEvent *event) ;
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

 signals:
    void signal1(QString);

};

#endif // DROPSLABEL_H
