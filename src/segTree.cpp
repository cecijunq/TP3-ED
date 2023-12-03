#include "../include/segTree.hpp"

SegTree::SegTree(int n) {
    seg_tree = build_tree(0, n-1);
    n_vertices = 2*n-1;
}

SegTree::~SegTree() {
    limpa(seg_tree);
}

void SegTree::limpa(Node *no) {
    if(no->get_ramo_esq() == nullptr) {
        no->limpa();
        delete no;
        return;
    }
    if(no->get_ramo_dir() == nullptr) {
        no->limpa();
        delete no;
        return;
    }
    limpa(no->get_ramo_esq());
    limpa(no->get_ramo_dir());
}

Node *SegTree::get_raiz() {
    return seg_tree;
}

Node *SegTree::build_tree(int esq, int dir) {
    Node *novo = new Node;
    if(esq == dir) {
        // inicializa a matriz do dado "novo" como uma matriz identidade
        novo->add_matrix();
        novo->define_intervalo(esq, dir);
        // define que um nó, ao ser criado, não tem filhos
        novo->set_ramo(nullptr, nullptr);
        return novo;
    }

    novo->define_intervalo(esq, dir);
    // quebra o array na metade
    int m = (esq + dir)/2;

    // constroi os dos ramos da raiz em questão
    Node *no_esq = build_tree(esq, m);
    Node *no_dir = build_tree(m+1, dir);
    // define que a matriz armazenado no nó é igual ao produto das matrizes dos seus dois filhos
    novo->produto_matrizes(no_esq->get_matrix(), no_dir->get_matrix());
    // define os filhos do nó
    novo->set_ramo(no_esq, no_dir);
    return novo;
}

long int **SegTree::atualiza_no_recursivo(int pos, long int **nova_matriz, Node *no) {
    // Se a condição for atendida, atribui ao campo "matriz" do dado "no" a matriz "nova_matriz"
    if(pos == no->get_intervalo_inicio() && pos == no->get_intervalo_fim()) {
        no->set_matrix(nova_matriz);
        return no->get_matrix();

    }
    // se "pos" estiver dentro do intervalo do nó passado como parâmetro a essa chamada da função, chama essa função para os dois ramos do nó
    // corrente e define que a matriz do nó corrente é igual ao produto das matrizes dos dois ramos
    if(pos >= no->get_intervalo_inicio() && pos <= no->get_intervalo_fim()) {
        Node *pos_esq = no->get_ramo_esq();
        Node *pos_dir = no->get_ramo_dir();

        // aponta para os dois ramos do nó corrente, para percorrê-los
        long int **matriz_esq = atualiza_no_recursivo(pos, nova_matriz, pos_esq);
        long int **matriz_dir = atualiza_no_recursivo(pos, nova_matriz, pos_dir);
        // nó corrente passa a armazenar o produto das matrizes do seus ramos
        no->produto_matrizes(matriz_esq, matriz_dir);

        return no->get_matrix();

    } else {
        return no->get_matrix();
    }
}

void SegTree::consulta(int comeco, int fim, Node *no, Node *aux) {
    // "media" é igual ao inteiro que é a "fronteira" entre os intervalos dos dois ramos do nó corrente "no"
    int media = (no->get_intervalo_inicio() + no->get_intervalo_fim()) / 2;
    
    // caso 1: se a condição for atendida, a matriz de "no" é multiplicada à matriz de "aux", que é o resultado da multiplicação de todas as
    // matrizes das folhas que estão no intervalo [comeco, fim] passado quando chama a função pela primeira vez
    if(comeco == no->get_intervalo_inicio() && fim == no->get_intervalo_fim()) {
        aux->produto_matrizes(aux->get_matrix(), no->get_matrix());
       
    } 
    // caso 2: se "fim" é menor do que "media", significa que o nó está no ramo da esquerda da árvore. Indica que o intervalo que quer pegar está
    // apenas no ramo da esquerda
    else if(fim <= media) {
        consulta(comeco, fim, no->get_ramo_esq(), aux);

    } 
    // caso 3: se "comeco" é maior do que "media", significa que o nó está no ramo da direita da árvore. Indica que o intervalo que quer pegar está
    // apenas no ramo direita
    else if(comeco >= media+1) {
        consulta(comeco, fim, no->get_ramo_dir(), aux);

    } 
    // caso 4: indica que o intervalo que quer pegar está tanto no ramo da direita, como da esquerda
    else if(comeco >= no->get_intervalo_inicio() && fim <= no->get_intervalo_fim()) {
        consulta(comeco, media, no->get_ramo_esq(), aux);
        consulta(media+1, fim, no->get_ramo_dir(), aux);
    }
}