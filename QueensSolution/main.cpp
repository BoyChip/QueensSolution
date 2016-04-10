#include "queens.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    queens w;
    w.setWindowTitle("Game xếp hậu ! Style Hoa Thiên Cốt Team !");
    w.setWindowIcon(QIcon(":/MyPic/icon.png"));
    w.setGeometry(100, 100, 800, 500);
    w.setMaximumSize(QSize(800, 500));
    w.setMinimumSize(800, 500);
    w.show();

    return a.exec();
}
