#ifndef QTSPLAYTREE_H
#define QTSPLAYTREE_H

#include <QObject>
#include <vector>
#include <QDebug>
#include "SplayTree.hpp"
#include "folder.hpp"

class QtSplayTree : public QObject
{
    Q_OBJECT

private:
    SplayTree<int, char> tree[3];
    std::string tree_path[3];

public:
    explicit QtSplayTree(QObject *parent = nullptr);

signals:


public slots:
    // 初始化槽
    void init_solt(int tid, std::vector<int> init_nodes);
    // 清空槽
    void clear_solt(int tid);
    // 查找槽
    bool find_solt(int tid, int node);
    // 插入槽
    void insert_solt(int tid, int node);
    // 删除槽
    void erase_solt(int tid, int node);
    // 合并槽，将tree1和tree2合并到tree0中，操作将清空所有树
    bool join_solt();
    // 拆分槽，将指定的tree拆分到tree1和tree2中，操作将清空所有树
    void split_solt(int tid, int x);

};



#endif // QTSPLAYTREE_H
