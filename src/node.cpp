#include "../include/node.hpp"
#include <math.h>

Node::Node() {}

void Node::add_matrix() {
    matriz = new long int*[2];
    matriz[0] = new long int[2];
    matriz[1] = new long int[2];
    
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            if(i == j) matriz[i][j] = 1;
            else matriz[i][j] = 0;
        }
    }
}

void Node::set_matrix(long int **nova) {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            matriz[i][j] = nova[i][j];
        }
    }
}

long int **Node::get_matrix() {
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
    matriz = new long int*[2];
    matriz[0] = new long int[2];
    matriz[1] = new long int[2];

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

void Node::produto_matrizes(long int **esq, long int **dir) {
    inicializa_matriz_nula();

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                matriz[i][j] += esq[i][k] * dir[k][j];
            }
            matriz[i][j] = seleciona_digitos(matriz[i][j]);
        }
    }
}

long int *Node::multiplica_vetor(long int *vetor) {
    long int *resultado = new long int[2];
    resultado[0] = 0;
    resultado[1] = 0;

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            resultado[i] += matriz[i][j] * vetor[j];
        }
    }

    for(int i = 0; i < 2; i++) {
        resultado[i] = seleciona_digitos(resultado[i]);
    }
    return resultado;
}

long int Node::seleciona_digitos(long int n) {
    int n_digitos = 0;
    long int saida_valida[8];
    while(n/10 >= 10 || n_digitos < 8) {
        if(n_digitos >= 8) break;
        saida_valida[n_digitos] = n%10;
        n = n/10;
        n_digitos++;
    }
    long int saida_final[8];
    bool zeros_inicio = true;
    int j = 0;
    for(int i = n_digitos-1; i >= 0; i--) {
        if(saida_valida[i] != 0) {
            zeros_inicio = false;
        }

        if(saida_valida[i] != 0 || zeros_inicio == false) {
            saida_final[j] = saida_valida[i];
            j++;
        }
    }
    long int n_final = 0;
    for(int i = 0; i < j; i++) {
        int x = pow(10,j-1-i);
        n_final += (x * saida_final[i]);
    }
    return n_final;
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