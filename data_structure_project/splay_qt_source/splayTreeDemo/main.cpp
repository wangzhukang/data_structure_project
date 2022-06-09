#include "splaytreewindow.h"
#include "SplayTree.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    try {
        QApplication a(argc, argv);
        SplayTreeWindow w;
        w.show();
        return a.exec();
    }
    catch (ErrorMessage e) {
       std::cerr << e.what() << std::endl;
    }
    return 0;
}
