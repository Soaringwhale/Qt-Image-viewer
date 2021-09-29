#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        label = new QLabel;                                        //  лейбл для изображений
        label->setBackgroundRole(QPalette::Base);
        label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);        //   ignored - позволяем масштабировать лейбл как угодно
        label->setScaledContents(true);                            //  если это включено, то при мастшабировании увеличиваться будет содержимое лейбла, а не сам лейбл.

         scrollArea = new QScrollArea;
         scrollArea->setBackgroundRole(QPalette::Dark);

         scrollArea->setWidget(label);      // помещаем лейбл на область прокрутки
         setCentralWidget(scrollArea);                   // делаем область прокрутки центральным виджетом
         label->resize(scrollArea->size());

         labelButtonRight = new QLabel(this);
         labelButtonLeft = new QLabel(this);
         labelButtonDelete = new QLabel(this);
         labelButtonFullScreen = new QLabel(this);

         labelButtonLeft->resize(100, 70);
         labelButtonRight->resize(100,70);
         labelButtonDelete->resize(65,70);
         labelButtonFullScreen->resize(70,70);

         labelButtonRight->installEventFilter(this);
         labelButtonLeft->installEventFilter(this);            //  сообщаем что теперь главное окно будет обрабатывать их события
         labelButtonDelete->installEventFilter(this);
         labelButtonFullScreen->installEventFilter(this);
         scrollArea->installEventFilter(this);


         QPixmap img(":/STRELKA1.png");
         QPixmap img2(":/STRELKA2.png");
         QPixmap img3(":/KREST.png");
         QPixmap img4(":/FULLSCREEN.png");


         labelButtonLeft->setPixmap(img.scaled(labelButtonLeft->size()));
         labelButtonRight->setPixmap(img2.scaled(labelButtonRight->size()));
         labelButtonDelete->setPixmap(img3.scaled(labelButtonDelete->size()));
         labelButtonFullScreen->setPixmap(img4.scaled(labelButtonFullScreen->size()));


         QHBoxLayout *layout = new QHBoxLayout(this);

         layout->addWidget(labelButtonFullScreen,0, Qt::AlignBottom | Qt::AlignLeft);
         layout->addSpacing(530);
         layout->addWidget(labelButtonLeft,0,Qt::AlignBottom | Qt::AlignLeft);
         layout->addWidget(labelButtonDelete,0,Qt::AlignBottom | Qt::AlignCenter);
         layout->addWidget(labelButtonRight,0, Qt::AlignBottom | Qt::AlignRight);
         layout->addSpacing(800);

         scrollArea->setLayout(layout);


         setAcceptDrops(true);
         setWindowTitle("Image Viewer");

}

MainWindow::~MainWindow() { delete ui; }


bool MainWindow::eventFilter(QObject *watched, QEvent *event)                   // фильтр событий, будет обрабатывать события нажатия на лейблы (стрелки и пр)
{
    if(watched == labelButtonLeft && event->type() == QEvent::MouseButtonPress)
    {
      return(skipLeft());
    }

    if(watched == labelButtonRight && event->type() == QEvent::MouseButtonPress)
    {
      return(skipRight());
    }

    if(watched == labelButtonDelete && event->type() == QEvent::MouseButtonPress)
    {
      return(deletePic());
    }

    if(watched == labelButtonFullScreen && event->type() == QEvent::MouseButtonPress)
    {
      scrollArea->setWidgetResizable(!scrollArea->widgetResizable());          //  меняем режим растяжения на противоположный
      label->adjustSize();                              // подгоняем размер лейбла под размер фотки (при отвязанном режиме лейбл уменьшится в размер фотки, при привязанном все равно ничего не произойдет)
      return true;
    }

    if(watched == scrollArea && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Right)
        {
            skipRight();
            return true;
        }
    }

    if(watched == scrollArea && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Left)
        {
            skipLeft();
            return true;
        }
    }
    return false;
}

bool MainWindow::skipRight()
{
    int n = 0;
    for(QString name : picturesFileNames)         //  проходим по всему списку ИМЕН картинок в папке
    {
        if(currentFilePath == dir.path()+"/"+ name && n != picturesFileNames.size()-1)
        {
            n=n+1;
            QImage image(dir.path()+"/"+ picturesFileNames.at(n));        //  открываем следующую картинку после текущей
            label->setPixmap(QPixmap::fromImage(image));
            currentFilePath = dir.path()+"/"+picturesFileNames.at(n);
            return true;
        }
       n++;
    }
    return false;
}

bool MainWindow::skipLeft()
{
    int n = 0;
    for(QString name : picturesFileNames)         //  проходим по всему списку ИМЕН картинок в папке
    {
        if(currentFilePath == dir.path()+"/"+ name && n != 0)
        {
            QImage image(dir.path()+"/"+picturesFileNames.at(--n));        //  открываем предыдущую картинку от текущей
            label->setPixmap(QPixmap::fromImage(image));
            currentFilePath = dir.path()+"/"+picturesFileNames.at(n);
            return true;
        }
       n++;
    }
    return false;
}

bool MainWindow::deletePic()
{
    QMessageBox::StandardButton answer;
    answer = QMessageBox::question(this, "Подтверждение удаления", "Удалить файл?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (answer == QMessageBox::Yes) {
        int n = 0;
        for(QString name : picturesFileNames)         //  проходим по всему списку ИМЕН картинок в папке
        {
            if(currentFilePath == dir.path()+"/"+ name && n != picturesFileNames.size()-1)
            {
                QImage image(dir.path()+"/"+ picturesFileNames.at(n+1));        //  открываем следующую картинку после текущей
                label->setPixmap(QPixmap::fromImage(image));
                picturesFileNames.takeAt(n);
                QFile(currentFilePath).remove();
                currentFilePath = dir.path()+"/"+picturesFileNames.at(n+1);
                return true;
            }
           n++;
        }
    }
    else if (answer == QMessageBox::No)
        return false;
    else
       return false;
}

void MainWindow::open(QString path)            // СРАБАТЫВАЕТ ТОЛЬКО ПРИ ОТПУСКАНИИ ФАЙЛА НА ОБЛАСТЬ
{
            this-> showMaximized();       //  показать, растянув на весь экран
            currentFilePath = path;

            QImage image(currentFilePath);        //  создаем объект QImage по этому пути

            label->resize(image.size());
            label->setPixmap(QPixmap::fromImage(image).scaled(label->size()));        //  устанавливаем картинку на лейбл

            scrollArea->setWidgetResizable(false);       //   виджет расположенный на этой области прокрутки(лейбл) примет ее размер, и будет менять свой размер вместе с ней

            QFileInfo info(currentFilePath);             // инфа об открытом файле
            dir.setPath(info.absolutePath());        // получаем его директорию (папку где он лежит)

            QStringList filterList;
            filterList << "*.jpg" << "*.png";        //  создаем список строк с нужными форматами
            dir.setNameFilters(filterList);                 // ставим этот фильтр на QDir

            picturesFileNames = dir.entryList();         // получаем ИМЕНА (без путей) всех картинок в папке

}

  void MainWindow::scaleImage(double factor)
   {
       Q_ASSERT(label->pixmap());
       scaleFactor *= factor;
       label->resize(scaleFactor * label->pixmap()->size());

       adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
       adjustScrollBar(scrollArea->verticalScrollBar(), factor);
   }

  void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
   {
       scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
   }
