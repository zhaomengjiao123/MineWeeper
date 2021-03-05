#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon("E:/素材/图片/1579588492118_mh1587477563718.jpg"));
    w.setWindowTitle("扫雷");
    w.show();
    return a.exec();
}
