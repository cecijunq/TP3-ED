#ifndef SEG_TREE_HPP
#define SEG_TREE_HPP

#include "./node.hpp"

class SegTree {
    private:
        Node *seg_tree;   
        int n_vertices;     

    public:
        SegTree(int n);
        Node *get_raiz();
        Node *build_tree(int pos_segtree, int esq, int dir);
        long int **atualiza_no_recursivo(int pos, long int **nova_matriz, Node *no);
        void consulta(int comeco, int fim, Node *no, Node *aux);
        void imprime(Node *no);
};

#endif