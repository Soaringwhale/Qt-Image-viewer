#include "dropslabel.h"

DropsLabel::DropsLabel(QWidget* parent) : QLabel(parent)
{
    setAcceptDrops(true);

    QPixmap img(":/START.png");
    setFixedSize(img.size());
    setPixmap(img.scaled(img.size()));

}

void DropsLabel::dragEnterEvent(QDragEnterEvent *event)
 {
    event->acceptProposedAction();
 }

void DropsLabel::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void DropsLabel::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void DropsLabel::dropEvent(QDropEvent *event)
{
    event->acceptProposedAction();
    QList<QUrl> urls = event->mimeData()->urls();

    QString str = "";
    for(int i = 1; i <urls[0].path().size(); i++)        //  убираем лишний символ в начале пути "/"
    {
        str = str + urls[0].path()[i];
    }

    QImage img(str);

    if(!img.isNull())
    {
        emit signal1(str);             //   если по пути лежит изображение, испускаем сигнал1 чтобы открыть главное окно
        this->close();
    }
}
