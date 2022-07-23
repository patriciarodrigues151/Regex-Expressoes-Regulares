#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <list>
#include <stack> // Pilha para usar na DFS
#include <math.h>


using namespace std;

struct no
{
    int valor;
    int dist;
};

class Grafo
{

public:
    Grafo(int V);
    ~Grafo();
    void deleteGrafo();
    void adicionarAresta(int v1, int v2);
    void adicionaArestaTrans(int v1, int v2);
    void printM();
    void printMb();
    void dfsR(int v);
    void bfsR(int v);
    void printVisitados();
    void printCC();
    void printPais();
    // verifica se o grafo direcionado tem ciclo
    bool temCiclo();
    int V; // número de vertices
    int *pais;
    bool *visitados;
    int *cc;
    int *dist;
    no **matriz;
    bool contemCiclos;
    void reset();
    int mediaDist();
    void NFA(char *regex, int tam);
    bool verificaExp(char *exp);
    bool reconhece(char *palavra, char*regexExp);
    bool recognizes(char * txt);
private:
    void individuo(int a, int b);
    void identificaCompCon(int v);
    void bfsR(int v, int grau);
};

Grafo::Grafo(int V)
{
    //inicializa matriz
    this->V = V;
    this->contemCiclos = false;

    matriz = (no **)malloc(V * sizeof(no *));

    for (int i = 0; i < V; i++)
    {
        matriz[i] = (no *)malloc(V * sizeof(no));
    }

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            matriz[i][j].valor = 0;
            matriz[i][j].dist = -1;
        }
    }
    //inicializa vetor visitados
    visitados = (bool *)malloc(V * sizeof(bool));

    for (int i = 0; i < V; i++)
    {
        visitados[i] = false;
    }

    //inicializa vetor pais
    pais = (int *)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++)
    {
        pais[i] = -1;
    }

    cc = (int *)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++)
    {
        cc[i] = -1;
    }

    dist = (int *)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++)
    {
        dist[i] = -1;
    }
}

Grafo::~Grafo()
{
    delete[] visitados;
    delete[] pais;
    delete[] cc;
    delete[] dist;
    delete[] matriz;
}

void Grafo::deleteGrafo()
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            matriz[i][j].valor = 0;
            matriz[i][j].dist = -1;
        }
    }
    this->contemCiclos = false;
}

void Grafo::printM()
{

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << matriz[i][j].valor << " ";
        }

        // Newline for new row
        cout << endl;
    }
}

void Grafo::printMb()
{

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << matriz[i][j].valor << "(" << matriz[i][j].dist << ")"
                 << " ";
        }

        // Newline for new row
        cout << endl;
    }
}

void Grafo::reset()
{
    for (int i = 0; i < V; i++)
    {
        visitados[i] = false;
        dist[i] = -1;
        cc[i] = -1;
        pais[i] = -1;

        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                matriz[i][j].dist = -1;
            }
        }
    }
}

void Grafo::printVisitados()
{
    for (int i = 0; i < V; i++)
    {
        cout << visitados[i] << " ";
    }

    // Newline for new row
    cout << endl;
}

void Grafo::printPais()
{
    for (int i = 0; i < V; i++)
    {
        cout << pais[i] << " ";
    }

    // Newline for new row
    cout << endl;
}

void Grafo::printCC()
{
    for (int i = 0; i < V; i++)
    {
        cout << cc[i] << " ";
    }

    // Newline for new row
    cout << endl;
}

void Grafo::dfsR(int v)
{
    if (visitados[v] == false)
    {
        visitados[v] = true;
        for (int i = 0; i < V; i++)
        {
            if (matriz[v][i].valor == 1 || matriz[v][i].valor == 2)
            {

                if (pais[i] == -1)
                {
                    pais[i] = v;
                }

                if (visitados[i] != -1)
                {
                    contemCiclos = true;
                }
                dfsR(i);
            }
        }
    }
}

void Grafo::bfsR(int v)
{
    bfsR(v, 1);
    matriz[v][v].dist = 0;
    dist[v] = 0;
}

void Grafo::bfsR(int v, int grau)
{

    for (int add = 0; add < V; add++)
    {
        if (((matriz[v][add].valor == 1 || matriz[v][add].valor == 2) && matriz[v][add].dist > grau) || ((matriz[v][add].valor == 1 || matriz[v][add].valor == 2) && matriz[v][add].dist == -1 && dist[add] == -1))
        {
            matriz[v][add].dist = grau;
            dist[add] = grau;
        }
    }

    if (visitados[v] == false)
    {
        visitados[v] = true;
        for (int i = 0; i < V; i++)
        {
            if (matriz[v][i].valor == 1 || matriz[v][i].valor == 2)
            {
                if (pais[i] == -1)
                {
                    pais[i] = v;
                }
                else
                {
                    contemCiclos = true;
                }
                bfsR(i, grau + 1);
            }
        }
    }
}

void Grafo::adicionarAresta(int v1, int v2)
{
    matriz[v1][v2].valor = 1;
}


