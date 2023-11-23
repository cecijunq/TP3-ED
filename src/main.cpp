#include <iostream>
#include "../include/segTree.hpp"

int main() {
    SegTree s = SegTree(3);

    //s.build_tree(0,0,7);
    //s.imprime(s.get_raiz());
    int **m;
    m = new int*[2];
    m[0] = new int[2];
    m[1] = new int[2];
    for(int k = 0; k < 3; k++) {
        int n;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                std::cin >> n;
                m[i][j] = n;
            }
        }
        std::cout << "k = " << k << std::endl;
        s.atualiza_no_recursivo(k, m, s.get_raiz());
        s.imprime(s.get_raiz());

    }
    /*int n, q;

    // recebe a quantidade de instantes de tempo
    std::cin >> n;
    
    // recebe a quantidade de operações a serem realizadas
    std::cin >> q;

    char op;

    for(int i = 0; i < q; i++) {
        if(op == 'u') {

        } else if(op == 'q') {

        } else {
            // tratamento de exceção: se o caractere inserido não for 'u' nem 'v', a execução do programa é encerrada
            return 0;
        }
    }*/
}