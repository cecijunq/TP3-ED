#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

class Node {
    private:
        long int **matriz;
        Node *_ramo_esq;
        Node *_ramo_dir;
        int intervalo_inicio;
        int intervalo_fim;

    public:
        //Node(int i, int j);
        Node();
        //~Node();
        void limpa();
        void add_matrix();
        void set_matrix(long int **nova);
        long int **get_matrix();
        Node *get_ramo_esq();
        Node *get_ramo_dir();
        int get_intervalo_fim();
        int get_intervalo_inicio();
        void inicializa_matriz_nula();
        void set_ramo(Node *ramo_esq, Node *ramo_dir);
        void define_intervalo(int i, int j);
        void produto_matrizes(long int **esq, long int **dir);
        long int *multiplica_vetor(long int *vetor);
        long int seleciona_digitos(long int n);
        void imprime();
};

#endif 