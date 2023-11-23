#include "../include/node.hpp"

Node::Node() {}

void Node::add_matrix() {
    matriz = new int*[2];
    matriz[0] = new int[2];
    matriz[1] = new int[2];
    
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            if(i == j) matriz[i][j] = 1;
            else matriz[i][j] = 0;
        }
    }
}

void Node::set_matrix(int **nova) {
    matriz = nova;
}

int **Node::get_matrix() {
    return matriz;
}

Node *Node::get_ramo_esq() {
    return _ramo_esq;
}

Node *Node::get_ramo_dir() {
    return _ramo_dir;
}

int Node::get_intervalo_fim(){
    return intervalo_fim;
} 

int Node::get_intervalo_inicio(){
    return intervalo_inicio;
} 

int Node::get_pos() {
    return _pos;
}

void Node::inicializa_matriz_nula() {
    matriz = new int*[2];
    matriz[0] = new int[2];
    matriz[1] = new int[2];

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            matriz[i][j] = 0;
        }
    }
}

void Node::set_ramo(Node *ramo_esq, Node *ramo_dir) {
    _ramo_esq = ramo_esq;
    _ramo_dir = ramo_dir;
}

void Node::set_pos(int pos) {
    _pos = pos;
}

void Node::set_index(int index) {
    index_matriz = index;
}

void Node::define_intervalo(int i, int j) {
    intervalo_inicio = i;
    intervalo_fim = j;
}

void Node::produto_matrizes(int **esq, int **dir) {
    inicializa_matriz_nula();

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            //int soma_prod = 0;
            for(int k = 0; k < 2; k++) {
                matriz[i][j] += esq[i][k] * dir[k][j];
            }
            //matriz[i][j] = soma_prod;
        }
    }
}

void Node::imprime() {
    std::cout << intervalo_inicio << " " << intervalo_fim << std::endl;
    std::cout << _pos << std::endl;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            std::cout << matriz[i][j] << " ";
        } 
        std::cout << std::endl;
    }
    std::cout << std::endl;
}