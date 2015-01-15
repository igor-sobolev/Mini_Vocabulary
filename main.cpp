#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(resources);
    //QStringList paths = QCoreApplication::libraryPaths();
    //paths.append(".");
    //paths.append("imageformats");
    //paths.append("audio");
    //paths.append("platforms");
    //paths.append("sqldrivers");
    //QCoreApplication::setLibraryPaths(paths);

    QApplication a(argc, argv);

    MainWindow *w = new MainWindow();
    w->show();

    return a.exec();;
}
