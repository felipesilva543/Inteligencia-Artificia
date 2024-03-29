#ifndef BFS_H
#define BFS_H

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>    //Lista para a busca em larura
#include "enum.h"
#include "grafo.h"
#include "state.h"
#include "node.h"

using namespace std;
//Busca em largura.
class Breadth_Search{
public:
    Breadth_Search(){}

    vector<Node> BFS(State _origem, State _destino, Grafo grafo){

        //Inicializando no raiz do grafo
        Node noInit;
        noInit.setAction(Action(_origem, _destino));
        noInit.setCustoDeCaminho(0);
        noInit.setPai(nullptr);
        noInit.setState(State(_origem.getState()));
        //Finalizando no raiz do grafo

        // Fila
        queue<Node> borda;
        // Vetor de respostas
        vector<Node> resp;

        //Verificando se o estado inicial é o destido
        if(noInit.getStateNode().getState() == _destino.getState()){
            return resp;
        }
        //fim_verif_

        //Se não for add na borda
        borda.push(noInit);

        //Declarando explorados
        bool viewed[TAM_MAPA];
        for(int i = 0; i <  TAM_MAPA; i++){
            viewed[i] = false;
        }
        //fim_dec_expl

        while (true) {
            //Verificando se borda está vazia, se sim, lança um exceção de erro
            if(borda.empty()){
                throw string("Falha pois borda está vazia!\n");
            }
            //fim_Verif

            //Pegando o que esta da borda (Na ourdem que entrou)
            noInit = borda.front();

            //Tirando da borda e setando que foi explorado
            borda.pop();
            int localAtual = noInit.getStateNode().getState();
            if(!viewed[localAtual]){
                //cout << "Visitando " << localAtual << "..." << endl;
                resp.push_back(noInit);
                viewed[localAtual] = true;
            }
            //fim_Tirando

            /* Verifica se o nó tem vizinhos e para cada vizinho se n estiver em explorados
               verifica se é onde quer chegar, se sim retorna a solução, se n, add na borda*/
            int COLUNA;
            for(COLUNA = 0; COLUNA < TAM_MAPA; COLUNA++){
                if(grafo.getPeso(localAtual, COLUNA)){
                    Node newNo = Node(State(COLUNA), &noInit, Action(localAtual, COLUNA), 0);
                    if(!viewed[newNo.getStateNode().getState()]){
                        if((newNo.getStateNode().getState()) == _destino.getState()){
                            return resp;
                        }
                        borda.push(newNo);
                    }
                }
            }
        }
    }
};


#endif // BFS_H
