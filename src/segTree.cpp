#include "../include/segTree.hpp"

SegTree::SegTree(int n) {
    seg_tree = build_tree(0, 0, n-1);
    n_vertices = 2*n-1;
}

Node *SegTree::get_raiz() {
    return seg_tree;
}

Node *SegTree::build_tree(int pos, int esq, int dir) {
    Node *novo = new Node;
    if(esq == dir) {
        novo->add_matrix();
        novo->define_intervalo(esq, dir);
        novo->set_pos(pos);
        novo->set_index(esq);
        novo->set_ramo(nullptr, nullptr);
        return novo;
    }

    novo->define_intervalo(esq, dir);
    novo->set_pos(pos);
    // quebra o array na metade
    int m = (esq + dir)/2;

    // constroi os dos ramos
    Node *no_esq = build_tree(2*pos + 1, esq, m);
    Node *no_dir = build_tree(2*pos + 2, m+1, dir);
    novo->produto_matrizes(no_esq->get_matrix(), no_dir->get_matrix());
    novo->set_ramo(no_esq, no_dir);
    return novo;
}

long int **SegTree::atualiza_no_recursivo(int pos, long int **nova_matriz, Node *no) {
    if(pos == no->get_intervalo_inicio() && pos == no->get_intervalo_fim()) {
        no->set_matrix(nova_matriz);
        return no->get_matrix();

    } 
    if(pos >= no->get_intervalo_inicio() && pos <= no->get_intervalo_fim()) {
        Node *pos_esq = no->get_ramo_esq();
        Node *pos_dir = no->get_ramo_dir();

        long int **matriz_esq = atualiza_no_recursivo(pos, nova_matriz, pos_esq);
        long int **matriz_dir = atualiza_no_recursivo(pos, nova_matriz, pos_dir);
        no->produto_matrizes(matriz_esq, matriz_dir);

        return no->get_matrix();

    } else {
        return no->get_matrix();
    }
}

void SegTree::consulta(int comeco, int fim, Node *no, Node *aux) {
    int media = (no->get_intervalo_inicio() + no->get_intervalo_fim()) / 2;
    if(comeco == no->get_intervalo_inicio() && fim == no->get_intervalo_fim()) {
        aux->produto_matrizes(aux->get_matrix(), no->get_matrix());
        
    } else if(fim <= media) {
        consulta(comeco, fim, no->get_ramo_esq(), aux);

    } else if(comeco >= media+1) {
        consulta(comeco, fim, no->get_ramo_dir(), aux);

    } else if(comeco >= no->get_intervalo_inicio() && fim <= no->get_intervalo_fim()) {
        consulta(comeco, media, no->get_ramo_esq(), aux);
        consulta(media+1, fim, no->get_ramo_dir(), aux);
    }
}

void SegTree::imprime(Node *no) {
    Node *esq = no->get_ramo_esq();
    Node *dir = no->get_ramo_dir();
    if(esq == nullptr || dir == nullptr) {
        no->imprime();
    } else {
        imprime(esq);
        imprime(dir);
        no->imprime();
    }
}