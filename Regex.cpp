//NOME: Patrícia da Silva Rodrigues
//NUSP:11315590



#include <iostream>
#include <fstream>
#include <list>
#include <stack> // Pilha para usar na DFS
#include <math.h>
#include <string.h>
#include "pilhaC.h"
#include "GRAFO.h"



//sep Alfabeto
bool sepAlpha(char c)
{
    if (c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'g' || c == 'h' || c == 'i' || c == 'j' || c == 'k' || c == 'l' || c == 'm' || c == 'n' || c == 'o' || c == 'p' || c == 'q' || c == 'r' || c == 's' || c == 't' || c == 'u' || c == 'v' || c == 'w' || c == 'x' || c == 'y' || c == 'z')
        return true;
    if (c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F' || c == 'G' || c == 'H' || c == 'I' || c == 'J' || c == 'K' || c == 'L' || c == 'M' || c == 'N' || c == 'O' || c == 'P' || c == 'Q' || c == 'R' || c == 'S' || c == 'T' || c == 'U'|| c == 'V' || c == 'W' || c == 'X' || c == 'Y' || c == 'Z')
        return true;
    return false;
}

//sep NUmeros
bool sepNum(char c)
{
    if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
        return true;
    return false;
}

//sep vogais
bool sepVog(char c)
{
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        return true;
    if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        return true;
    return false;
}


//pega o padrão de texto e cria um regex interpretável pelo programa
Pilha* criaRegex(char *regex)
{
    Pilha *emp;
    emp = pilha_cria(); //usamos a pilha para empilhar os caracteres que comporão o regex
    for (int i = 0; i < strlen(regex); i++)
    {
        //empilharemos aqui os caracteres 
        if (regex[i] == '(' || regex[i] == ')' || regex[i] == ':' || regex[i] == '|' || regex[i] == '&' || regex[i] == '*' || regex[i] == '@' || regex[i] == '+' || regex[i] == '.' || sepAlpha(regex[i]) == true || sepNum(regex[i]) == true)
        {
            if (regex[i] != '[')
                pilha_push(emp, regex[i]);
        }
        //aqui verificamos se se trata de um [a-z], ou seja, todas as letras do alfabeto são validas. O caracter utilizado para representar é #
        if (regex[i] == '[' && regex[i + 1] == 'a' && regex[i + 2] == '-' && regex[i + 3] == 'z' && regex[i + 4] == ']')
        {
            pilha_push(emp, '#'); //alfabeto alfanumérico
            i = i + 4;
            continue;
        }
        //aqui verificamos se se trata de um [a-z], ou seja, todas os números são validos. O caracter utilizado para representar é %
        if (regex[i] == '[' && regex[i + 1] == '0' && regex[i + 2] == '-' && regex[i + 3] == '9' && regex[i + 4] == ']')
        {
            pilha_push(emp, '%'); //algarismos de 0 a 9
            i = i + 4;
            continue;
        }
        //aqui verificamos se se trata de um [^AEIOU], ou seja, todas as letras do alfabeto são validas. O caracter utilizado para representar é #
        if (regex[i] == '[' && regex[i + 1] == '^' && regex[i + 2] == 'A' && regex[i + 3] == 'E' && regex[i + 4] == 'I' && regex[i + 5] == 'O' && regex[i + 6] == 'U' && regex[i + 7] == ']')
        {
            pilha_push(emp, '#'); //alfabeto alfanumérico
            i = i + 7;
            continue;
        }
        //aqui verificamos se se trata de um [AEIOU], ou seja, todas as vogais do alfabeto são validas. O caracter utilizado para representar é ~
        if (regex[i] == '['  && regex[i + 1] == 'A' && regex[i + 2] == 'E' && regex[i + 3] == 'I' && regex[i + 4] == 'O' && regex[i + 5] == 'U' && regex[i + 6] == ']')
        {
            pilha_push(emp, '~'); //VOGAIS
            i = i + 6;
            continue;
        }
    }

    return emp;
}


//Aqui o automato do regex é gerado, ou seja, as conexões são estabelecidas em um grafo de ordenação topológica 
void Grafo::NFA(char *regex, int tam)
{
    Pilha *p;
    // Teste do TAD Pilha
    p = pilha_cria();
    //o código é identico ao visto em aula
    for (int i = 0; i < tam; i++)
    {
        int ant = i;
        if (regex[i] == '(' || regex[i] == '|')
        {
            pilha_push(p, i);
            if(regex[i] == '(')
                adicionarAresta(i, i+1);
        }
        else
        {
            if (regex[i] == ')')
            {
                int otopo = pilha_pop(p);
                if (regex[otopo] == '|')
                {
                    ant = pilha_pop(p);

                    adicionarAresta(ant, otopo + 1);
                    adicionarAresta(otopo, i);
                }
                else
                {
                    ant = otopo;
                }
            }
            if (i + 1 < strlen(regex) && regex[i + 1] == '*')
            {
                adicionarAresta(ant, i + 1);
                adicionarAresta(i + 1, ant);
            }
            if (regex[i] == '+' || regex[i] == '.' ||  regex[i] == ':' || regex[i] == '@' || regex[i] == '#' || regex[i] == '~' || regex[i] == '%' ||regex[i] == '(' || regex[i] == '*' || regex[i] == ')' || sepAlpha(regex[i]) || sepNum(regex[i]))
                adicionarAresta(i, i+1);
        }
    }

}

//a função recebe a palavra e a expressão regex e verifica se elas combinam.
bool Grafo::reconhece(char* pal, char* regexExp)
{
    reset();
    //inicialmente rodamos a dfsR para 0
    dfsR(0);
    bool resp;

    bool * atingidosFinais = (bool*)malloc(V * sizeof(bool));//usaremos no final
    bool * atingidos = (bool*)malloc(V * sizeof(bool));
    
    for(int i = 0; i < V; i++)
    {
        atingidos[i] = false;
        atingidos[i] = visitados[i]; //copiamos o vetor visitados para o atingidos
        
    }
    //para cada letra i de pal[i] fazermos o loop
    for(int i = 0; i < strlen(pal); i++)
    {
        //a cada nova iteração criamos um novo vetor prox e enchemos ele com false
        bool * prox = (bool*)malloc(V * sizeof(bool));
        for(int j = 0; j < V; j++)
            prox[j] = false;

        //para cada letra j da expressão regexExp[j] verificaremos com a palavra i
        for(int j = 0; j < V; j++)
        {
            //verificamos aqui se a palavra em que estamos e o caracter da regex combinam. Caso combinem e o vetor atingidos esteja false, rodamos a dfsR para esse caracter j
            if(regexExp[j] == pal[i] && !atingidos[j])
            {
                dfsR(j);
                
                for(int k = 0; k < V; k++)
                    if(visitados[k] == true && atingidos[k] == false) //se, ao rodar a dfsR para o j atingirmos algum ponto que não foi marcado no atingidos, marcaremos como verdadeiro
                        atingidos[k] = visitados[k];
            }
            //Ao rodarmos a dfsR(no inicio em zero, posteriormente mudará) verificaremos novamente para todos aqueles j da expressão que foram atingidos a combinação
            if(atingidos[j] == true)
            {

                if(regexExp[j] == pal[i])  //caso o caracter j da regex seja igual ao caracter i da palavra, tornaremos o prox de j verdadeiro (mudei de prox[j+1] para prox[j] devido a falha de segmentação qnd tento atingir o ultimo prox[j+1])
                {
                    prox[j] = true;
                }
                if(regexExp[j] == '#')//caso o caracter i da palavra seja algum elemento do alfabeto, prox[j] = true
                {
                    if(sepAlpha(pal[i]))
                    {
                        prox[j] = true;
                    }
                }

                if(regexExp[j] == '%')//caso o caracter i da palavra seja algum elemento numerico, prox[j] = true
                {
                    if(sepNum(pal[i]))
                    {
                        prox[j] = true;
                    }
                }
                if(regexExp[j] == '~')//caso o caracter i da palavra seja algum elemento vogal, prox[j] = true
                {
                    if(sepVog(pal[i]))
                    {
                        prox[j] = true;
                    }
                }
            }
        }

        bool * marked = (bool*)malloc(V * sizeof(bool));  //aqui todos os atingidos ficam falsos, para posteriormente verificarmos marcarmos as posições com a dfsR dos prox[j que foram marcados] 
        for(int j = 0; j < V; j++)
            atingidos[j] = false;
        bool* aux;
        for(int j = 0; j <= V; j++)
        {
            if(prox[j])//para todos os prox[j] que foram marcados com true
            {
                atingidos[j-1] = true;
                for(int k = 0; k < V; k++)//o vetor marked fica cheio de falsos
                    marked[k] = false;
                reset();
                dfsR(j);//rodo a dfsR para os elementos que estão verdadeiros em prox
                for(int i = 0; i < V; i++)
                    marked[i] = visitados[i];//marked recebe todos os elementos que foram atingidos na dfsR
                atingidos = aux;
                for(int k = 0; k < V; k++)//para todos os elementos de k a V 
                    if(marked[k])//caso algum deles tenha sido marcado com true
                        atingidos[k] = true;//ficara true também nos atingidos 
            }
            aux = atingidos;
        }
        if(i == strlen(pal)-1) // caso seja a ultima iteração, salvo o vetor atingidos antes que ele se perca
            for(int k = 0; k < V; k++)
                atingidosFinais[k] = atingidos[k];
    }
    reset();

    return  atingidosFinais[V-1];//caso o ultimo elemento tenha sido atingido do altomato, a expressão e a palavra combinam
}



int main()
{
    char *expReg;
    char *exp;

    int n;
    cout << ("Digite a expressão regular \n") << endl;
    string aux;
    getline(cin, aux);
    n = aux.length();
    expReg = (char *)malloc(n * sizeof(char));
    strcpy(expReg, aux.c_str());

    int m;
    cout << ("Digite o teste \n") << endl;
    string aux1;
    getline(cin, aux1);
    m = aux1.length();
    exp = (char *)malloc(m * sizeof(char));
    strcpy(exp, aux1.c_str());

    
    Pilha * p = criaRegex(expReg);



    int tam = pilha_tam(p);


    char *expressao = (char*)malloc(tam * sizeof(char));

    Grafo grafo(tam);

    for(int i = 0; i < tam; i++)
    {
        expressao[tam - i-1] = pilha_pop(p); 
    }


    grafo.NFA(expressao, tam);

    
    bool resp = grafo.reconhece(exp, expressao);
    if(resp)
        cout << "S" << endl;
    else
        cout << "N" << endl;
    return 0;
    
}