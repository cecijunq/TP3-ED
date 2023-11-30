#include <iostream>
#include "../include/segTree.hpp"
#include "../include/memlog.hpp"

int main() {
    iniciaMemLog("tp3");
    ativaMemLog();
    int n, q;

    // recebe a quantidade de instantes de tempo
    std::cin >> n;
    defineFaseMemLog(0);
    SegTree s = SegTree(n);
    
    // recebe a quantidade de operações a serem realizadas
    std::cin >> q;

    char op;

    defineFaseMemLog(1);
    for(int i = 0; i < q; i++) {
        std::cin >> op;
        if(op == 'u') {
            long int **m;
            m = new long int*[2];
            m[0] = new long int[2];
            m[1] = new long int[2];
            int index;
            std::cin >> index;
            if(index >= n) {
                desativaMemLog();
                return 0;
            }
            int num;
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 2; j++) {
                    std::cin >> num;
                    if(num < 0) {
                        desativaMemLog();
                        return 0;
                    }
                    m[i][j] = num;
                    leMemLog((long int)(m[i][j]), sizeof(double),0);
                }
            }
            s.atualiza_no_recursivo(index, m, s.get_raiz());

        } else if(op == 'q') {
            int nasc, morte;
            std::cin >> nasc;
            std::cin >> morte;
            if(nasc < 0 || nasc >= n || morte < 0 || morte >= n) {
                desativaMemLog();
                return 0;
            }
            Node *aux = new Node();
            aux->add_matrix();
        
            s.consulta(nasc, morte, s.get_raiz(), aux);

            long int *vetor = new long int[2];
            for(int i = 0; i < 2; i++) {
                int num;
                std::cin >> num;
                if(num < 0) {
                    desativaMemLog();
                    return 0;
                }
                vetor[i] = num;
            }

            long int *vetor_result = aux->multiplica_vetor(vetor);
            std::cout << vetor_result[0] << " ";
            std::cout << vetor_result[1] << std::endl;

            delete []vetor_result;

        } else {
            // tratamento de exceção: se o caractere inserido não for 'u' nem 'v', a execução do programa é encerrada
            desativaMemLog();
            return 0;
        }
    }
    finalizaMemLog();
}
