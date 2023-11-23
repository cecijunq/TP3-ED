#include "../include/segTree.hpp"

SegTree::SegTree(int n) {
    //seg_tree = new Node[2*n-1];
    seg_tree = build_tree(0, 0, n-1);
    n_vertices = 2*n-1;
}
/*SegTree::SegTree(int n) {
    seg_tree = new Node[2*n-1];
    n_vertices = 2*n-1;
}*/

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

/*void SegTree::build_tree(int pos, int esq, int dir) {
    if(esq == dir) {
        seg_tree[pos].add_matrix();
        seg_tree[pos].define_intervalo(esq, dir);
        return;
    }

    seg_tree[pos].define_intervalo(esq, dir);
    // quebra o array na metade
    int m = (esq + dir)/2;

    // constroi os dos ramos
    build_tree(2*pos + 1, esq, m);
    build_tree(2*pos + 2, m+1, dir);
}*/

/*void SegTree::atualiza_no(int pos, Node *no) {
    Node *pai = get_raiz();

    while(pos != pai->get_intervalo_inicio() && pos != pai->get_intervalo_fim()) {
        if(pos < pai->get_intervalo_fim() && pos >= pai->get_intervalo_inicio()) {
            pai = pai->get_ramo_esq();

        } else if(pos > pai->get_intervalo_inicio() && pos <= pai->get_intervalo_fim()) {
            pai = pai->get_ramo_dir();

        } else if(pos == pai->get_intervalo_inicio() && pos == pai->get_intervalo_fim()) {
            int matriz[2][2];
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 2; j++) {
                    int n;
                    std::cin >> n;
                    matriz[i][j] = n;
                }
            }
        }
    }
}*/

int **SegTree::atualiza_no_recursivo(int pos, int **nova_matriz, Node *no) {
    if(pos == no->get_intervalo_inicio() && pos == no->get_intervalo_fim()) {
        std::cout << "entrou " << pos << std::endl;
        no->set_matrix(nova_matriz);
        return no->get_matrix();

    } 
    if(pos >= no->get_intervalo_inicio() && pos <= no->get_intervalo_fim()) {
        Node *pos_esq = no->get_ramo_esq();
        Node *pos_dir = no->get_ramo_dir();

        int **matriz_esq = atualiza_no_recursivo(pos, nova_matriz, pos_esq);
        int **matriz_dir = atualiza_no_recursivo(pos, nova_matriz, pos_dir);
        no->produto_matrizes(matriz_esq, matriz_dir);

        return no->get_matrix();

    } else {
        return no->get_matrix();
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

/*void SegTree::imprime() {
    std::cout << "entrou" << std::endl;
    for(int i = 0; i < n_vertices; i++) {
        if(2*i+1 >= n_vertices && 2*i+2 >= n_vertices) seg_tree[i].imprime();
        else std::cout << "x" << std::endl;
        std::cout << std::endl;
    }
}*/