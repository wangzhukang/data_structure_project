#ifndef SplayTree_H
#define SplayTree_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <climits>
#include <cstdio>
#include <vector>
#include <queue>
#include "ErrorMessage.hpp"

//----------------------------------- class SplayNode -----------------------------------//
template <class K, class E>
class SplayNode
{
public:
    // data
    K key;
    E value;
    // child node
    SplayNode<K, E>* left;
    SplayNode<K, E>* right;
    
    // constructor
    SplayNode()
    {
        this->left = NULL; this->right = NULL;
    }
    SplayNode(const K& key)
    :   key(key)
    {
        this->left = NULL; this->right = NULL;
    }
    SplayNode(const K& key, const E& value)
    :   key(key), value(value)
    {
        this->left = NULL; this->right = NULL;
    }
    SplayNode(const SplayNode<K, E>& node)
    :   key(node.key), value(node.value)
    {
        this->left = NULL; this->right = NULL;
    }
};

// overload <<
template <class K, class E>
std::ostream& operator << (std::ostream& out, const SplayNode<K, E>& node)
{
    out << node.key << ": " << node.value;
    return out;
}

//----------------------------------- class SplayNode -----------------------------------//


//----------------------------------- class SplayTree -----------------------------------//
template <class K, class E>
class SplayTree
{
private:
    // root
    SplayNode<K, E>* root;

public:
    // constructor
    SplayTree();
    SplayTree(SplayNode<K, E>* root);
    SplayTree(const SplayTree<K, E>& tree);
    // destructor
    ~SplayTree();
    // return if empty
    bool empty() const;
    // clear the splay tree
    void clear();
    // max-key node in tree. If tree is empty, return NULL
    SplayNode<K, E>* maxNode();
    // min-key node in tree. If tree is empty, return NULL
    SplayNode<K, E>* minNode();
    // find node with key, return ptr. If not exist, return NULL
    SplayNode<K, E>* find(const K& key);
    // insert node with key and value. If exist, update value
    void insert(const K& key, const E& value);
    // delete node with key. If not exist, do nothing
    void erase(const K& key);
    // join two splay trees t1 and t2, make sure t1 all < t2
    static SplayNode<K, E>* join(SplayTree<K, E>& t1, SplayTree<K, E>& t2);
    // split one splay tree to two splay trees t1 and t2 based on x, make sure t1 all < x, t2 all > x
    static std::pair<SplayNode<K, E>*, SplayNode<K, E>*> split(SplayTree<K, E>& t, const K& x);
    // ascending order output
    void output() const;
    // visual (generate dot file)
    void visual(const std::string& dotfile) const;


protected:
    // postorder delete
    void make_empty(SplayNode<K, E>* r);
    // inorder output
    void inorder_output(SplayNode<K, E>* r) const;
    // L-splay
    void L_splay(SplayNode<K, E>* p, SplayNode<K, E>* gp);
    // R-splay
    void R_splay(SplayNode<K, E>* p, SplayNode<K, E>* gp);
    // LL-splay
    void LL_splay(SplayNode<K, E>* gp, SplayNode<K, E>* ggp);
    // RR-splay
    void RR_splay(SplayNode<K, E>* gp, SplayNode<K, E>* ggp);
    // LR-splay
    void LR_splay(SplayNode<K, E>* gp, SplayNode<K, E>* ggp);
    // RL-splay
    void RL_splay(SplayNode<K, E>* gp, SplayNode<K, E>* ggp);
    // plot
    void plot(SplayNode<K, E>* r, std::ofstream& out) const;

};

//---------------------------------------------------------------------------------------//

// constructor
template <class K, class E>
SplayTree<K, E>::SplayTree()
{
    this->root = NULL;
}

template <class K, class E>
SplayTree<K, E>::SplayTree(SplayNode<K, E>* root)
{
    this->root = root;
}

template <class K, class E>
SplayTree<K, E>::SplayTree(const SplayTree<K, E>& tree)
{
    this->root = tree.root;
}

// destructor (do not provide destructor, please use clear())
template <class K, class E>
SplayTree<K, E>::~SplayTree()
{

}

// postorder delete
template <class K, class E>
void SplayTree<K, E>::make_empty(SplayNode<K, E>* r)
{
    if (r == NULL)
        return;
    if (r->left != NULL)
        this->make_empty(r->left);
    if (r->right != NULL)
        this->make_empty(r->right);
    delete r; r = NULL;
}

// return if empty
template <class K, class E>
bool SplayTree<K, E>::empty() const
{
    return (this->root == NULL);
}

// clear the splay tree
template <class K, class E>
void SplayTree<K, E>::clear()
{
    this->make_empty(this->root);
    this->root = NULL;
}

// inorder output
template <class K, class E>
void SplayTree<K, E>::inorder_output(SplayNode<K, E>* r) const
{
    if (r == NULL)
        return;
    if (r->left != NULL)
        this->inorder_output(r->left);
    std::cout << *r << ", ";
    if (r->right != NULL)
        this->inorder_output(r->right);
}

// ascending order output
template <class K, class E>
void SplayTree<K, E>::output() const
{
    std::cout << "{";
    this->inorder_output(this->root);
    std::cout << "}" << std::endl;
}

// L-splay
template <class K, class E>
void SplayTree<K, E>::L_splay(SplayNode<K, E>* p, SplayNode<K, E>* gp)
{
    SplayNode<K, E>* q = p->left;
    SplayNode<K, E>* qr = q->right;
    q->right = p; p->left = qr; 
    if (gp != NULL)
    {
        if (gp->left == p)      gp->left = q;
        else                    gp->right = q;
    }
    else
        this->root = q;
}

// R-splay
template <class K, class E>
void SplayTree<K, E>::R_splay(SplayNode<K, E>* p, SplayNode<K, E>* gp)
{
    SplayNode<K, E>* q = p->right;
    SplayNode<K, E>* ql = q->left;
    q->left = p; p->right = ql;
    if (gp != NULL)
    {
        if (gp->left == p)      gp->left = q;
        else                    gp->right = q;
    }
    else
        this->root = q;
}

// LL-splay
template <class K, class E>
void SplayTree<K, E>::LL_splay(SplayNode<K, E>* gp, SplayNode<K, E>* ggp)
{
    SplayNode<K, E>* p = gp->left;
    SplayNode<K, E>* q = p->left;
    SplayNode<K, E>* qr = q->right;
    SplayNode<K, E>* pr = p->right;
    q->right = p; p->right = gp; p->left = qr; gp->left = pr;
    if (ggp != NULL)
    {
        if (ggp->left == gp)    ggp->left = q;
        else                    ggp->right = q;
    }
    else
        this->root = q;
}

// RR-splay
template <class K, class E>
void SplayTree<K, E>::RR_splay(SplayNode<K, E>* gp, SplayNode<K, E>* ggp)
{
    SplayNode<K, E>* p = gp->right;
    SplayNode<K, E>* q = p->right;
    SplayNode<K, E>* ql = q->left;
    SplayNode<K, E>* pl = p->left;
    q->left = p; p->left = gp; p->right = ql; gp->right = pl;
    if (ggp != NULL)
    {
        if (ggp->left == gp)    ggp->left = q;
        else                    ggp->right = q;
    }
    else
        this->root = q;
}

// LR-splay
template <class K, class E>
void SplayTree<K, E>::LR_splay(SplayNode<K, E>* gp, SplayNode<K, E>* ggp)
{
    SplayNode<K, E>* p = gp->left;
    SplayNode<K, E>* q = p->right;
    SplayNode<K, E>* ql = q->left;
    SplayNode<K, E>* qr = q->right;
    p->right = ql; gp->left = qr; q->left = p; q->right = gp;
    if (ggp != NULL)
    {
        if (ggp->left == gp)    ggp->left = q;
        else                    ggp->right = q;
    }
    else
        this->root = q;
}

// RL-splay
template <class K, class E>
void SplayTree<K, E>::RL_splay(SplayNode<K, E>* gp, SplayNode<K, E>* ggp)
{
    SplayNode<K, E>* p = gp->right;
    SplayNode<K, E>* q = p->left;
    SplayNode<K, E>* ql = q->left;
    SplayNode<K, E>* qr = q->right;
    p->left = qr; gp->right = ql; q->left = gp; q->right = p;
    if (ggp != NULL)
    {
        if (ggp->left == gp)    ggp->left = q;
        else                    ggp->right = q;
    }
    else
        this->root = q;
}

// max-key node in tree. If tree is empty, return NULL
template <class K, class E>
SplayNode<K, E>* SplayTree<K, E>::maxNode()
{
    std::vector<SplayNode<K, E>*> vec_p; vec_p.push_back(this->root);
    std::vector<char> vec_d;
    while (vec_p.back() != NULL && vec_p.back()->right != NULL)
    {
        vec_p.push_back(vec_p.back()->right);
        vec_d.push_back('R');
    }
    int times = vec_d.size();
    for (int i = 0; i < times / 2; i++)
    {
        vec_p.pop_back(); vec_p.pop_back();
        this->RR_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
    }
    if (times % 2)
    {
        vec_p.pop_back();
        this->R_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
    }
    return this->root;
}

// min-key node in tree. If tree is empty, return NULL
template <class K, class E>
SplayNode<K, E>* SplayTree<K, E>::minNode()
{
    std::vector<SplayNode<K, E>*> vec_p; vec_p.push_back(this->root);
    std::vector<char> vec_d;
    while (vec_p.back() != NULL && vec_p.back()->left != NULL)
    {
        vec_p.push_back(vec_p.back()->left);
        vec_d.push_back('L');
    }
    int times = vec_d.size();
    for (int i = 0; i < times / 2; i++)
    {
        vec_p.pop_back(); vec_p.pop_back();
        this->LL_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
    }
    if (times % 2)
    {
        vec_p.pop_back();
        this->L_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
    }
    return this->root;
}

// find node with key, return ptr
template <class K, class E>
SplayNode<K, E>* SplayTree<K, E>::find(const K& key)
{
    // find
    std::vector<SplayNode<K, E>*> vec_p; vec_p.push_back(this->root);
    std::vector<char> vec_d;
    while (vec_p.back() != NULL && vec_p.back()->key != key)
    {
        if (key > vec_p.back()->key)
        {
            vec_p.push_back(vec_p.back()->right);
            vec_d.push_back('R');
        }
        else
        {
            vec_p.push_back(vec_p.back()->left);
            vec_d.push_back('L');
        }
    }

    // splay
    SplayNode<K, E>* find_node = vec_p.back();
    if (vec_p.back() == NULL)     // not find
    {
        if (vec_d.size() != 0)
        {
            vec_p.pop_back(); vec_d.pop_back();
        }
    }
    int times = vec_d.size();
    for (int i = 0; i < times / 2; i++)
    {
        vec_p.pop_back(); vec_p.pop_back();
        char dp = vec_d.back(); vec_d.pop_back();
        char dq = vec_d.back(); vec_d.pop_back();
        if (dq == 'R' && dp == 'R')
            this->RR_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
        else if (dq == 'L' && dp == 'L')
            this->LL_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
        else if (dq == 'R' && dp == 'L')
            this->RL_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
        else if (dq == 'L' && dp == 'R')
            this->LR_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
    }
    if (times % 2)
    {
        vec_p.pop_back();
        if (vec_d.back() == 'R')
            this->R_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
        else
            this->L_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
    }

    return find_node;
}

// insert node with key and value. If exist, update value
template <class K, class E>
void SplayTree<K, E>::insert(const K& key, const E& value)
{
    // find
    std::vector<SplayNode<K, E>*> vec_p; vec_p.push_back(this->root);
    std::vector<char> vec_d;
    while (vec_p.back() != NULL && vec_p.back()->key != key)
    {
        if (key > vec_p.back()->key)
        {
            vec_p.push_back(vec_p.back()->right);
            vec_d.push_back('R');
        }
        else
        {
            vec_p.push_back(vec_p.back()->left);
            vec_d.push_back('L');
        }
    }

    // insert or update
    if (vec_p.back() == NULL)       // insert
    {
        if (vec_p.size() >= 2)      // not root
        {
            if (vec_d.back() == 'R')
            {
                vec_p[vec_p.size() - 2]->right = new SplayNode<K, E>(key, value); 
                vec_p[vec_p.size() - 1] = vec_p[vec_p.size() - 2]->right;
            }
            else if (vec_d.back() == 'L')
            {
                vec_p[vec_p.size() - 2]->left = new SplayNode<K, E>(key, value); 
                vec_p[vec_p.size() - 1] = vec_p[vec_p.size() - 2]->left;
            }
        }
        else                        // root
        {
            this->root = new SplayNode<K, E>(key, value);
            vec_p[0] = this->root;
        }
    }
    else                            // update
        vec_p.back()->value = value;

    // splay
    int times = vec_d.size();
    for (int i = 0; i < times / 2; i++)
    {
        vec_p.pop_back(); vec_p.pop_back();
        char dp = vec_d.back(); vec_d.pop_back();
        char dq = vec_d.back(); vec_d.pop_back();
        if (dq == 'R' && dp == 'R')
            this->RR_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
        else if (dq == 'L' && dp == 'L')
            this->LL_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
        else if (dq == 'R' && dp == 'L')
            this->RL_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
        else if (dq == 'L' && dp == 'R')
            this->LR_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
    }
    if (times % 2)
    {
        vec_p.pop_back();
        if (vec_d.back() == 'R')
            this->R_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
        else
            this->L_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
    }
}

// delete node with key. If not exist, do nothing
template <class K, class E>
void SplayTree<K, E>::erase(const K& key)
{
    // find
    std::vector<SplayNode<K, E>*> vec_p; vec_p.push_back(this->root);
    std::vector<char> vec_d;
    while (vec_p.back() != NULL && vec_p.back()->key != key)
    {
        if (key > vec_p.back()->key)
        {
            vec_p.push_back(vec_p.back()->right);
            vec_d.push_back('R');
        }
        else
        {
            vec_p.push_back(vec_p.back()->left);
            vec_d.push_back('L');
        }
    }

    // delete
    if (vec_p.back() != NULL)       // find
    {
        if (vec_p.size() > 1)      // not delete root
        {
            SplayNode<K, E>* del_node = vec_p.back();
            SplayTree<K, E> del_node_left(del_node->left);
            SplayTree<K, E> del_node_right(del_node->right);
            SplayNode<K, E>* r = SplayTree<K, E>::join(del_node_left, del_node_right);
            delete vec_p.back(); vec_p.pop_back(); del_node = NULL;
            if (vec_d.back() == 'R')
                vec_p.back()->right = r;
            else if (vec_d.back() == 'L')
                vec_p.back()->left = r;
            vec_d.pop_back();
        }
        else                        // delete root
        {
            SplayTree<K, E> left_tree(this->root->left);
            SplayTree<K, E> right_tree(this->root->right);
            this->root = SplayTree<K, E>::join(left_tree, right_tree);
            delete vec_p.back(); vec_p.pop_back();
        }
    }
    else                            // not find
    {
        if (vec_d.size() != 0)
        {
            vec_p.pop_back(); vec_d.pop_back();
        }
    }

    // splay
    int times = vec_d.size();
    for (int i = 0; i < times / 2; i++)
    {
        vec_p.pop_back(); vec_p.pop_back();
        char dp = vec_d.back(); vec_d.pop_back();
        char dq = vec_d.back(); vec_d.pop_back();
        if (dq == 'R' && dp == 'R')
            this->RR_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
        else if (dq == 'L' && dp == 'L')
            this->LL_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
        else if (dq == 'R' && dp == 'L')
            this->RL_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
        else if (dq == 'L' && dp == 'R')
            this->LR_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
    }
    if (times % 2)
    {
        vec_p.pop_back();
        if (vec_d.back() == 'R')
            this->R_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
        else
            this->L_splay(vec_p.back(), (vec_p.size() >= 2) ? vec_p[vec_p.size() - 2] : NULL);
    }
}

// join two splay trees t1 and t2, make sure t1 all < t2
template <class K, class E>
SplayNode<K, E>* SplayTree<K, E>::join(SplayTree<K, E>& t1, SplayTree<K, E>& t2)
{
    // t1.output();
    SplayNode<K, E>* left_r = t1.maxNode();
    if (left_r != NULL)
    {
        left_r->right = t2.root;
        return left_r;
    }
    SplayNode<K, E>* right_r = t2.minNode();
    return right_r;
}

// split one splay tree to two splay trees t1 and t2 based on x, make sure t1 all < x, t2 all > x.
// one splay tree must be splited at most once
template <class K, class E>
std::pair<SplayNode<K, E>*, SplayNode<K, E>*> SplayTree<K, E>::split(SplayTree<K, E>& t, const K& x)
{
    SplayNode<K, E>* x_root = t.find(x);
    if (x_root == NULL)
    {
        t.insert(x, E()); x_root = t.find(x);
    }
    std::pair<SplayNode<K, E>*, SplayNode<K, E>*> p;
    p.first = x_root->left; p.second = x_root->right;
    delete x_root; x_root = NULL;
    return p;
}

// visual (generate dot file)
// example: dotfile = "visual/tree", then dot file stored in "visual/tree.dot", image stored in dot file stored in "visual/tree.png"
template <class K, class E>
void SplayTree<K, E>::visual(const std::string& dotfile) const
{
    std::ofstream out(dotfile + ".dot");
    if (!out)
    {
        std::string message = "Error opening file ";
        throw ErrorMessage(message + dotfile + ".dot" + " !");
    }
    out << "digraph G{\n";
    out << "node[shape=circle];\n";
    this->plot(this->root, out);
    out << "}";
    out.close();
    std::string cmd = "dot " + dotfile
                     + ".dot" + " | gvpr -c -f visual/binarytree.gvpr | neato -n -Tpng -o " 
                     + dotfile + ".png\n";
    system(cmd.c_str());
}

// plot
template <class K, class E>
void SplayTree<K, E>::plot(SplayNode<K, E>* r, std::ofstream& out) const
{
    if (r == NULL)
        return;
    // level-order plot
    std::queue<SplayNode<K, E>*> q;
    q.push(this->root);
    out << "Node_" << r->key << "[label=\"" << r->key << "\"];\n";
    while (r != NULL)
    {
        if (r->left != NULL)
        { 
            out << "Node_" << r->left->key << "[label=\"" << r->left->key << "\"];\n";
            out << "Node_" << r->key << "->" << "Node_" << r->left->key << ";\n";
            q.push(r->left); 
        }
        else
        {
            out << "Unleft_" << r->key << "[label=\"" << r->key << "\"];\n";
            out << "Node_" << r->key << "->" << "Unleft_" << r->key << "[style=invis];\n";
            out << "Unleft_" << r->key << "[style=invis];\n";
        }
        if (r->right != NULL)
        { 
            out << "Node_" << r->right->key << "[label=\"" << r->right->key << "\"];\n";
            out << "Node_" << r->key << "->" << "Node_" << r->right->key << ";\n";
            q.push(r->right);
        }
        else
        {
            out << "Unright_" << r->key << "[label=\"" << r->key << "\"];\n";
            out << "Node_" << r->key << "->" << "Unright_" << r->key << "[style=invis];\n";
            out << "Unright_" << r->key << "[style=invis];\n";
        }
        q.pop();
        if (q.empty()) 
            return;
        r = q.front();
    }
}

//----------------------------------- class SplayTree -----------------------------------//

#endif
