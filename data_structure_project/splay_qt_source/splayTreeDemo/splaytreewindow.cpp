#include "splaytreewindow.h"
#include "ui_splaytreewindow.h"


SplayTreeWindow::SplayTreeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SplayTreeWindow)
{
    ui->setupUi(this);
    setWindowTitle("SplayTree 演示程序");

    // 初始化CMD
    CMDmodel = new QStringListModel(this);
    CMDlist << "### Splay Tree CMD System" << "### Designed by Wang Zhukang, Shandong University." << "";
    ui->CMD->setModel(CMDmodel);
    CMDmodel->setStringList(CMDlist);

    // CMD输入
    connect(ui->CMDline, &ui->CMDline->returnPressed, this, &SplayTreeWindow::prase);

    // instruct
    QStringList instruct;
    instruct    << "[Splay Tree Instruction]"
                << ""
                << "> init TID [nodes]"
                << "Init Splay Tree TID with "
                << "nodes."
                << ""
                << "> clear TID"
                << "Clear Tree TID."
                << ""
                << "> find TID node"
                << "Find node in Tree TID."
                << ""
                << "> insert TID node"
                << "Insert node in Tree TID."
                << ""
                << "> delete TID node"
                << "Delete node in Tree TID."
                << ""
                << "> join"
                << "Join Tree 1 and Tree 2, "
                << "then clear them. Make sure"
                << "Tree 1 all < Tree 2."
                << ""
                << "> split TID x"
                << "Split Tree TID to Tree 1 "
                << "and Tree 2, s.t. Tree 1 <"
                << "x and Tree 2 > x."
    ;

    QStringListModel* instmodel = new QStringListModel(this);
    ui->instruct->setModel(instmodel);
    instmodel->setStringList(instruct);

    // pix
    treepix[0] = new QImage("visual/tree/tree0");
    treepix[1] = new QImage("visual/tree/tree1");
    treepix[2] = new QImage("visual/tree/tree2");
    treepix[1]->scaled(ui->tree1->width(), ui->tree1->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    treepix[2]->scaled(ui->tree2->width(), ui->tree2->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->tree1->setPixmap(QPixmap::fromImage(*treepix[1]));
    ui->tree2->setPixmap(QPixmap::fromImage(*treepix[2]));
    ui->tree1->setScaledContents(true);
    ui->tree2->setScaledContents(true);
}

SplayTreeWindow::~SplayTreeWindow()
{
    delete ui;
}

void SplayTreeWindow::prase()
{
    QString s = ui->CMDline->text();
    QStringList prase_s = s.split(' ');
    QString line = "> "; line += s;
    CMDlist << line;

    if (prase_s.length() == 0)
    {
        update(); return;
    }
    if (prase_s[0] == "init")
    {
        if (prase_s.length() == 1)
        {
            line = "Error: Invalid Parameter! TID is needed.";
            CMDlist << line; update(); return;
        }
        int tid = prase_s[1].toInt();
        if (tid != 1 and tid != 2)
        {
            line = "Error: Invalid Parameter! TID is expected to be 1 or 2.";
            CMDlist << line; update(); return;
        }
        std::vector<int> nodes;
        for (int i = 2; i < prase_s.length(); i++)
            nodes.push_back(prase_s[i].toInt());
        tree.init_solt(tid, nodes);
        line = "Init complete.";
    }
    else if (prase_s[0] == "clear")
    {
        if (prase_s.length() == 1)
        {
            line = "Error: Invalid Parameter! TID is needed.";
            CMDlist << line; update(); return;
        }
        int tid = prase_s[1].toInt();
        if (tid != 1 and tid != 2)
        {
            line = "Error: Invalid Parameter! TID is expected to be 1 or 2.";
            CMDlist << line; update(); return;
        }
        if (prase_s.length() > 2)
        {
            line = "Error: Invalid Parameter! Expected to get only one parameter TID.";
            CMDlist << line; update(); return;
        }
        tree.clear_solt(tid);
        line = "Clear complete.";
    }
    else if (prase_s[0] == "find")
    {
        if (prase_s.length() == 1)
        {
            line = "Error: Invalid Parameter! TID is needed.";
            CMDlist << line; update(); return;
        }
        int tid = prase_s[1].toInt();
        if (tid != 1 and tid != 2)
        {
            line = "Error: Invalid Parameter! TID is expected to be 1 or 2.";
            CMDlist << line; update(); return;
        }
        if (prase_s.length() > 3)
        {
            line = "Error: Invalid Parameter! Expected to get only two parameter TID and node.";
            CMDlist << line; update(); return;
        }
        int node = prase_s[2].toInt();
        if (tree.find_solt(tid, node))
            line = "Node found.";
        else
            line = "Node Not found.";
    }
    else if (prase_s[0] == "insert")
    {
        if (prase_s.length() == 1)
        {
            line = "Error: Invalid Parameter! TID is needed.";
            CMDlist << line; update(); return;
        }
        int tid = prase_s[1].toInt();
        if (tid != 1 and tid != 2)
        {
            line = "Error: Invalid Parameter! TID is expected to be 1 or 2.";
            CMDlist << line; update(); return;
        }
        if (prase_s.length() > 3)
        {
            line = "Error: Invalid Parameter! Expected to get only two parameter TID and node.";
            CMDlist << line; update(); return;
        }
        int node = prase_s[2].toInt();
        tree.insert_solt(tid, node);
        line = "Insert complete.";
    }
    else if (prase_s[0] == "delete")
    {
        if (prase_s.length() == 1)
        {
            line = "Error: Invalid Parameter! TID is needed.";
            CMDlist << line; update(); return;
        }
        int tid = prase_s[1].toInt();
        if (tid != 1 and tid != 2)
        {
            line = "Error: Invalid Parameter! TID is expected to be 1 or 2.";
            CMDlist << line; update(); return;
        }
        if (prase_s.length() > 3)
        {
            line = "Error: Invalid Parameter! Expected to get only two parameter TID and node.";
            CMDlist << line; update(); return;
        }
        int node = prase_s[2].toInt();
        tree.erase_solt(tid, node);
        line = "Delete complete.";
    }
    else if (prase_s[0] == "join")
    {
        if (prase_s.length() != 1)
        {
            line = "Error: Invalid Parameter! No more parameter is needed.";
            CMDlist << line; update(); return;
        }
        if (tree.join_solt())
        {
            line = "Join complete. Tree 0 has shown..."; CMDlist << line;
            // 弹出弹窗
            QDialog* dig = new QDialog(this);
            dig->resize(1000, 600);
            dig->setWindowTitle("Join Result");
            dig->show();
            QLabel* label = new QLabel(dig);
            label->setAutoFillBackground(true);
            label->setGeometry(QRect(0, 0, 1000, 600));
            label->show();
            treepix[0]->load("visual/tree/tree0");
            treepix[0]->scaled(1000, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            label->setPixmap(QPixmap::fromImage(*treepix[0]));
            line = "All trees clear."; CMDlist << line;
            update(); return;
        }
        else
            line = "Join must make sure tree1 or tree2 is not empty, and tree1 all < tree2";
    }
    else if (prase_s[0] == "split")
    {
        if (prase_s.length() == 1)
        {
            line = "Error: Invalid Parameter! TID is needed.";
            CMDlist << line; update(); return;
        }
        int tid = prase_s[1].toInt();
        if (tid != 1 and tid != 2)
        {
            line = "Error: Invalid Parameter! TID is expected to be 1 or 2.";
            CMDlist << line; update(); return;
        }
        if (prase_s.length() > 3)
        {
            line = "Error: Invalid Parameter! Expected to get only two parameter TID and x.";
            CMDlist << line; update(); return;
        }
        int x = prase_s[2].toInt();
        tree.split_solt(tid, x);
        line = "Split complete.";
    }
    else
        line = "Error: Invalid Instruction! No instruction found.";
    CMDlist << line;
    update();
}

void SplayTreeWindow::update()
{
    CMDmodel->setStringList(CMDlist);
    ui->CMD->scrollTo(CMDmodel->index(CMDlist.length() - 1));
	treepix[0]->load("visual/tree/tree0");
    treepix[1]->load("visual/tree/tree1");
    treepix[2]->load("visual/tree/tree2");
    treepix[1]->scaled(ui->tree1->width(), ui->tree1->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    treepix[2]->scaled(ui->tree2->width(), ui->tree2->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->tree1->setPixmap(QPixmap::fromImage(*treepix[1]));
    ui->tree2->setPixmap(QPixmap::fromImage(*treepix[2]));
}

