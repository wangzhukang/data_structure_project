/********************************************************************************
** Form generated from reading UI file 'splaytreewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPLAYTREEWINDOW_H
#define UI_SPLAYTREEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SplayTreeWindow
{
public:
    QWidget *centralwidget;
    QListView *CMD;
    QLineEdit *CMDline;
    QLabel *tree1;
    QLabel *tree2;
    QListView *instruct;
    QMenuBar *menubar;

    void setupUi(QMainWindow *SplayTreeWindow)
    {
        if (SplayTreeWindow->objectName().isEmpty())
            SplayTreeWindow->setObjectName(QString::fromUtf8("SplayTreeWindow"));
        SplayTreeWindow->resize(1080, 621);
        SplayTreeWindow->setMinimumSize(QSize(1080, 621));
        SplayTreeWindow->setMaximumSize(QSize(1080, 621));
        SplayTreeWindow->setBaseSize(QSize(1080, 621));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier New"));
        font.setBold(true);
        font.setWeight(75);
        SplayTreeWindow->setFont(font);
        centralwidget = new QWidget(SplayTreeWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        CMD = new QListView(centralwidget);
        CMD->setObjectName(QString::fromUtf8("CMD"));
        CMD->setGeometry(QRect(0, 470, 1080, 151));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Courier New"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        CMD->setFont(font1);
        CMD->setAutoScroll(true);
        CMD->setMovement(QListView::Static);
        CMDline = new QLineEdit(centralwidget);
        CMDline->setObjectName(QString::fromUtf8("CMDline"));
        CMDline->setGeometry(QRect(0, 445, 1080, 25));
        QFont font2;
        font2.setPointSize(9);
        CMDline->setFont(font2);
        tree1 = new QLabel(centralwidget);
        tree1->setObjectName(QString::fromUtf8("tree1"));
        tree1->setGeometry(QRect(253, 20, 400, 400));
        tree1->setMaximumSize(QSize(500, 500));
        tree1->setSizeIncrement(QSize(500, 500));
        tree1->setBaseSize(QSize(500, 500));
        tree1->setAutoFillBackground(true);
        tree2 = new QLabel(centralwidget);
        tree2->setObjectName(QString::fromUtf8("tree2"));
        tree2->setGeometry(QRect(667, 20, 400, 400));
        tree2->setAutoFillBackground(true);
        instruct = new QListView(centralwidget);
        instruct->setObjectName(QString::fromUtf8("instruct"));
        instruct->setGeometry(QRect(0, 0, 240, 445));
        instruct->setFont(font1);
        instruct->setFlow(QListView::TopToBottom);
        SplayTreeWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SplayTreeWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1080, 23));
        SplayTreeWindow->setMenuBar(menubar);

        retranslateUi(SplayTreeWindow);

        QMetaObject::connectSlotsByName(SplayTreeWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SplayTreeWindow)
    {
        SplayTreeWindow->setWindowTitle(QCoreApplication::translate("SplayTreeWindow", "SplayTreeWindow", nullptr));
        CMDline->setPlaceholderText(QCoreApplication::translate("SplayTreeWindow", "\350\257\267\345\234\250\346\255\244\350\276\223\345\205\245\346\223\215\344\275\234\346\214\207\344\273\244", nullptr));
        tree1->setText(QCoreApplication::translate("SplayTreeWindow", "Tree1", nullptr));
        tree2->setText(QCoreApplication::translate("SplayTreeWindow", "Tree2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SplayTreeWindow: public Ui_SplayTreeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPLAYTREEWINDOW_H
