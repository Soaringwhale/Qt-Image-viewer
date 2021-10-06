#include "mainwindow.h"
#include "dropslabel.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
   QStringList paths(QApplication::libraryPaths());
   paths.append(".");
   QApplication::setLibraryPaths(paths);

    QApplication a(argc, argv);
    DropsLabel label;
    MainWindow mainwindow;

    QObject::connect(&label, SIGNAL(signal1(QString)), &mainwindow, SLOT(open(QString)));

//    if (argc != 2)
//    {
//        qWarning("Usage: file_size file");
//        return 1;
//    }

    QString filename = argv[1];                   // Имя файла передается в качестве аргумента при открытии файла этой программой
    for(auto c : filename)
    {
        if(c == '\\') {filename.replace(c,'/'); }     //   заменяем слеши на обратные, т.к. при drag drop и обычном открытии файла слеши получаются противоположными, нам нужны одинаковые
    }

      if (!QFile(filename).exists())                // Проверяем существование файла
      {
        qWarning("The file does not exist");          // если файл не найден (запуск программы без файла), то открываем лейбл

           label.show();
      }
      else
      {
           mainwindow.open(filename);
      }

    // label.emit signal1(filename);

    return a.exec();
}
