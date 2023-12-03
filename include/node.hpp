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
        /*
         @brief Construtor
         */
        Node();
        /*
         @brief deleta todas os endereços de memórias alocados no heap
         */
        void limpa();
        /*
         @brief cria uma nova matriz 2x2 e a inicializa como uma matriz identidade
         */
        void add_matrix();
        /*
         @brief atribui ao campo "matriz" desse TAD a matriz "nova" passada como parâmetro
         */
        void set_matrix(long int **nova);
        /*
         @brief retorna a matriz 2x2 armazenada no atributo "matriz"
         */
        long int **get_matrix();
        /*
         @brief retorna o ponteiro "_ramo_esq"
         */
        Node *get_ramo_esq();
        /*
         @brief retorna o ponteiro "_ramo_dir"
         */
        Node *get_ramo_dir();
        /*
         @brief retorna o inteiro "intervalo_fim"
         */
        int get_intervalo_fim();
        /*
         @brief retorna o inteiro "intervalo_inicio"
         */
        int get_intervalo_inicio();
        /*
         @brief faz com que todos os elementos da matriz sejam iguais a zero
         */
        void inicializa_matriz_nula();
        /*
         @brief atribui aos campos "_ramo_esq" e "ramo_dir" os ponteiros "ramo_esq" e "ramo_dir", respectivamente
         */
        void set_ramo(Node *ramo_esq, Node *ramo_dir);
        /*
         @brief atribui aos campos "intervalo_inicio" e "intervalo_inicio" os ponteiros "i" e "j", respectivamente
         */
        void define_intervalo(int i, int j);
        /*
         @brief realiza a multiplicação da matriz 'esq' com a 'dir' e a matriz obtida é atribuída ao campo "matriz" desse TAD
         */
        void produto_matrizes(long int **esq, long int **dir);
        /*
         @brief realiza a multiplicação da matriz armazenada no campo "matriz" pelo veotr "vetor" passado à função. O resultado da
            multiplicação é retornado
         */
        void multiplica_vetor(long int *vetor);
        /*
         @brief checa se o inteiro passado como parâmetro tem mais de 8 dígitos e, se tiver, seleciona apenas o 8 dígitos menos significativos
         */
        long int seleciona_digitos(long int n);
};

#endif