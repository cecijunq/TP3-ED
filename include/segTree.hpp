#ifndef SEG_TREE_HPP
#define SEG_TREE_HPP

#include "./node.hpp"

class SegTree {
    private:
        // aponta para a raiz da árvore
        Node *seg_tree;  
        int n_vertices;

    public:
        /*
         @brief Construtor: constroi a árvore (chama a função "build_tree") e atribui à variável n_vertices que a árvore possui 2n-1 vértices
         */
        SegTree(int n);
        /*
         @brief Destrutor
         */
        ~SegTree();
        /*
         @brief deleta todas os endereços de memórias alocados no heap
         */
        void limpa(Node *no);
        /*
         @brief retorna o endereço armazenado em seg_tree, que corresponde ao endereço do primeiro elemento da árvore (ou seja, a raiz)
         */
        Node *get_raiz();
        /*
         @brief constroi a árvore, de modo que, quando os inteiros "esq" e "dir", cria-se uma matriz identidade e atribui-a ao campo "matriz"
            do dado Node
         */
        Node *build_tree(int esq, int dir);
        /*
         @brief essa função é a responsável por implementar a tarefa da atualização da matriz cuja posição é "pos" (ou seja, atribui à matriz
            cuja coordenada é (pos,pos) a matriz "nova_matriz". Para fazer essa atualização, percorre recursivamente a árvore e, quando o 
            parâmetro "pos" for igual aos intervalos de início e de fim do nó corrente (que é o passado como parâmetro da função), substitui o
            o campo "matriz" do dado "no" pela matriz "nova_matriz" e, depois, desempilha as chamadas, multiplicando os nós filhos de uma mesma
            raiz (raiz de uma subárvore é igual ao produto dos seus filhos).
         */
        long int **atualiza_no_recursivo(int pos, long int **nova_matriz, Node *no);
        /*
         @brief essa função implementa a tarefa de consulta proposta no trabalho. Se os campos "comeco" e "fim" forem iguais ao intervalo do 
            dado "no", multiplica a matriz armazenada em "no" à matriz "aux", que é, inicialmente, uma matriz identidade. Caso o intervalo não
            seja igual a "comeco" e "fim", continua percorrendo a árvore recursivamente.
         */
        void consulta(int comeco, int fim, Node *no, Node *aux);
};

#endif