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

/*int **SegTree::consulta(int comeco, int fim, Node *no) {
    bool cond1 = comeco >= no->get_intervalo_inicio();
    bool cond2 = fim <= no->get_intervalo_fim();
    if(comeco == no->get_intervalo_inicio() && fim == no->get_intervalo_fim()) {
        return no->get_matrix();
    }
    if(no->get_intervalo_inicio() == no->get_intervalo_fim() && cond1 && cond2) {
        return no->get_matrix();

    } else if(cond1 && cond2) {
        int **proximo_esq = consulta(comeco, fim, no->get_ramo_esq());
        int **proximo_dir = consulta(comeco, fim, no->get_ramo_dir());
        no->produto_matrizes(no->get_matrix(), proximo_esq);
        no->produto_matrizes(no->get_matrix(), proximo_dir);
        
    } else {
        Node *node_aux = new Node();
        node_aux->add_matrix();
    }
}*/
Node *SegTree::consulta(int comeco, int fim, Node *no, Node *aux) {
    int mediana = (comeco + fim) / 2;
    if(comeco == no->get_intervalo_inicio() && fim == no->get_intervalo_fim()) {
        aux->produto_matrizes(aux->get_matrix(), no->get_matrix());
        //return no->get_matrix();
    } else if(fim < mediana) {
        consulta(comeco, fim, no->get_ramo_esq(), aux);

    } else if(comeco > mediana+1) {
        consulta(comeco, fim, no->get_ramo_dir(), aux);

    } else if(comeco >= no->get_intervalo_inicio() && fim <= no->get_intervalo_fim() && fim > mediana+1) {
        consulta(comeco, mediana, no->get_ramo_esq(), aux);
        consulta(mediana + 1, fim, no->get_ramo_dir(), aux);
    }

    return aux;
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