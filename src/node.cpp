#include "../include/node.hpp"
#include <math.h>

Node::Node() {}

void Node::limpa() {
    for(int i = 0; i < 2; i++) {
        delete matriz[i];
    }
    delete matriz;
}

void Node::add_matrix() {
    // define a matriz como uma matriz identidade
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

void Node::inicializa_matriz_nula() {
    // define a matriz como uma matriz nula
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

void Node::define_intervalo(int i, int j) {
    intervalo_inicio = i;
    intervalo_fim = j;
}

void Node::produto_matrizes(long int **esq, long int **dir) {
    inicializa_matriz_nula();

    // 1º for loop: percorre as linhas da matriz "esq" e da matriz do nó corrente
    for(int i = 0; i < 2; i++) {
        // 2º for loop: percorre as colunas da matriz di nó corrente e as da matriz "dir"
        for(int j = 0; j < 2; j++) {
            // 3º for loop: percorre as colunas de "esq" e as linhas de "dir"
            for(int k = 0; k < 2; k++) {
                matriz[i][j] += esq[i][k] * dir[k][j];
            }
            // para cada posição da matriz "matriz" seleciona apenas os 8 últimos dígitos (se ele tiver mais de 8)
            matriz[i][j] = seleciona_digitos(matriz[i][j]);
        }
    }
}

void Node::multiplica_vetor(long int *vetor) {
    long int resultado[2];
    resultado[0] = 0;
    resultado[1] = 0;

    // 1º for loop: percorre os índices do vetor "resultado" e linhas da matriz do nó corrente
    for(int i = 0; i < 2; i++) {
        // 2º for loop: percorre as colunas da matriz do nó corrente e os índices do veotr "vetor"
        for(int j = 0; j < 2; j++) {
            resultado[i] += matriz[i][j] * vetor[j];
        }
    }

    // para cada posição do vetor "resultado" seleciona apenas os 8 últimos dígitos (se ele tiver mais de 8)
    for(int i = 0; i < 2; i++) {
        resultado[i] = seleciona_digitos(resultado[i]);
    }

    std::cout << resultado[0] << " ";
    std::cout << resultado[1] << std::endl;
}

long int Node::seleciona_digitos(long int n) {
    // contador que armazena quantos dígitos o inteiro 'n' tem
    int n_digitos = 0;
    // array que armazenará os 8 últimos dígitos de 'n' ao contrário (último dígito estará na primeira posição do array e o primeiro, na última posição)
    long int saida_valida[8];
    
    // divisões consecutivas de 'n' por 10, a fim de obter os seus dígitos
    // a condição "n/10 >= 10" só deixa de ser satisfeita se 'n' tem 8 ou menos dígitos
    // a condição "n_digitos < 8" só deixa de ser satisfeita se 'n' tem mais de 8 dígitos
    while(n/10 >= 10 || n_digitos < 8) {
        if(n_digitos >= 8) break;
        // os dígitos são obtidos através do resto e são armazenados no array
        saida_valida[n_digitos] = n%10;
        n = n/10;
        n_digitos++;
    }
    
    // se 'n' tem menos do que 8 dígitos, a célula da matriz que tem seu conteúdo analisado permanece guardando o mesmo valor
    if(n_digitos != 8) return n;
    long int saida_final[8];
    bool zeros_inicio = true;
    int j = 0;
    
    // percorre o array da última até a primeira posição, com o objetivo de eliminar o '0' que são encontrados antes de encontrar um algarismo entre 1 e 9
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
    
    // transforma os dígitos armazenados no array em um inteiro e, ao fim, retorna esse inteiro
    for(int i = 0; i < j; i++) {
        int x = pow(10,j-1-i);
        n_final += (x * saida_final[i]);
    }
    return n_final;
}
