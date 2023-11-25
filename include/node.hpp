#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

class Node {
    private:
        int **matriz;
        Node *_ramo_esq;
        Node *_ramo_dir;
        int _pos;
        int index_matriz;
        int intervalo_inicio;
        int intervalo_fim;

    public:
        //Node(int i, int j);
        Node();
        void add_matrix();
        void set_matrix(int **nova);
        int **get_matrix();
        Node *get_ramo_esq();
        Node *get_ramo_dir();
        int get_intervalo_fim();
        int get_intervalo_inicio();
        int get_pos();
        void inicializa_matriz_nula();
        void set_ramo(Node *ramo_esq, Node *ramo_dir);
        void set_pos(int pos);
        void set_index(int index);
        void define_intervalo(int i, int j);
        void produto_matrizes(int **esq, int **dir);
        int *multiplica_vetor(int *vetor);
        void imprime();
};

#endif 