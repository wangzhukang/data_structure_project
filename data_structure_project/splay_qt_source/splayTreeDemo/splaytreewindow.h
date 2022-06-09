#ifndef SPLAYTREEWINDOW_H
#define SPLAYTREEWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QLabel>
#include <QString>
#include <QStringList>
#include <QStringListModel>
#include <QTextDocument>
#include <QImage>
#include <QPixmap>
#include <QDialog>
#include "qtsplaytree.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SplayTreeWindow; }
QT_END_NAMESPACE

class SplayTreeWindow : public QMainWindow
{
    Q_OBJECT

public:
    SplayTreeWindow(QWidget *parent = nullptr);
    ~SplayTreeWindow();
    // 处理CMD信息
    void prase();
    // 更新CMD信息
    void update();

private:
    // UI
    Ui::SplayTreeWindow *ui;
    // CMD中的字符串列表
    QStringList CMDlist;
    // CMD StringList Model
    QStringListModel* CMDmodel;
    // Splay Tree
    QtSplayTree tree;
    // picture
    QImage* treepix[3];
};

#endif // SPLAYTREEWINDOW_H
