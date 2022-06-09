#include "qtsplaytree.h"

QtSplayTree::QtSplayTree(QObject *parent) : QObject(parent)
{
    tree_path[0] = "visual/tree/tree0";
    tree_path[1] = "visual/tree/tree1";
    tree_path[2] = "visual/tree/tree2";
    createfolder("visual/tree");
    tree[1].visual(tree_path[1]);
    tree[2].visual(tree_path[2]);
}

// 初始化槽
void QtSplayTree::init_solt(int tid, std::vector<int> init_nodes)
{
    tree[tid].clear();
    for (auto& x: init_nodes)
        tree[tid].insert(x, ' ');
    tree[tid].visual(tree_path[tid]);
}

// 清空槽
void QtSplayTree::clear_solt(int tid)
{
    tree[tid].clear();
    tree[tid].visual(tree_path[tid]);
}

// 查找槽
bool QtSplayTree::find_solt(int tid, int node)
{
    auto p = tree[tid].find(node);
    tree[tid].visual(tree_path[tid]);
    return p != NULL;
}

// 插入槽
void QtSplayTree::insert_solt(int tid, int node)
{
    tree[tid].insert(node, ' ');
    tree[tid].visual(tree_path[tid]);
}

// 删除槽
void QtSplayTree::erase_solt(int tid, int node)
{
    tree[tid].erase(node);
    tree[tid].visual(tree_path[tid]);
}

// 合并槽，将tree1和tree2合并到tree0中，操作将清空所有树
bool QtSplayTree::join_solt()
{
    if (tree[1].empty() or tree[2].empty())
        return false;
    if (tree[1].maxNode()->key >= tree[2].minNode()->key)
        return false;
    else
    {
        tree[0] = SplayTree<int, char>(SplayTree<int, char>::join(tree[1], tree[2]));
        tree[0].visual(tree_path[0]);
        tree[0].clear();
        tree[1] = SplayTree<int, char>(); tree[1].visual(tree_path[1]);
        tree[2] = SplayTree<int, char>(); tree[1].visual(tree_path[2]);
        return true;
    }
}

// 拆分槽，将指定的tree拆分到tree1和tree2中
void QtSplayTree::split_solt(int tid, int x)
{
    auto p = SplayTree<int, char>::split(tree[tid], x);
    auto t1 = SplayTree<int, char>(p.first); auto t2 = SplayTree<int, char>(p.second);
    tree[1] = t1; tree[2] = t2;
    tree[1].visual(tree_path[1]); tree[2].visual(tree_path[2]);
}
