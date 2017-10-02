#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;   // para não termos que digitar pair<int, int> várias vezes,
                              // fazemos isso para deixar o código mais organizado

//---------------------
#define MAXN 10100
// como não existe o Infinito no computador, usaremos um número bem grande
#define INFINITO 999999999

int n, m;                      // número de vértices e arestas
int distancia[MAXN];           // o array de distâncias à fonte
int processado[MAXN];          // o array que guarda se um vértice foi processado
vector<pii> vizinhos[MAXN];    // nossas listas de adjacência. O primeiro elemento do par representa a distância e o segundo representa o vértice
//---------------------

int Prim(){
  
  for(int i = 2;i <= n;i++) distancia[i] = INFINITO; // definimos todas as distâncias como infinito, exceto a de S = 1.
  distancia[1] = 0;                                  // Assim, garantimos que o primeiro vértice selecionado será o próprio 1.
  
  priority_queue< pii, vector<pii>, greater<pii> > fila; // Criamos uma fila de prioridade onde o menor fica no topo.
  fila.push( pii(distancia[1], 1) );                     // Como se pode ver, colocamos o primeiro elemento como seja a distância do
                                                         // vértice a Árvore Geradora Mínima e o segundo como sendo o próprio vértice
  
  while(true){ // rodar "infinitamente"
    
    int davez = -1;
    
    // selecionamos o vértice mais próximo
    while(!fila.empty()){
      
      int atual = fila.top().second;
      fila.pop();
      
      if(!processado[atual]){ // podemos usar esse vértice porque ele ainda não foi processado
        davez = atual;
        break;
      }
      
      // se não, continuamos procurando
    }
    
    if(davez == -1) break; // se não achou ninguém, é o fim do algoritmo
    
    processado[davez] = true; // marcamos para não voltar para este vértice
    
    // agora, tentamos atualizar as distâncias
    for(int i = 0;i < (int)vizinhos[davez].size();i++){
      
      int dist  = vizinhos[davez][i].first;
      int atual = vizinhos[davez][i].second;
      
      // A nova possível distância é dist.
      // Comparamos isso com distancia[atual].
      // Porém, é importante checar se o vértice atual não foi processado ainda
      
      if( distancia[atual] > dist && !processado[atual]){  // vemos que vale a pena usar o vértice davez
        distancia[atual] = dist;                         // atualizamos a distância
        fila.push( pii(distancia[atual], atual) );       // inserimos na fila de prioridade
      }
    }
  }
  
  int custo_arvore = 0;
  for(int i = 1;i <= n;i++) custo_arvore += distancia[i];
  
  return custo_arvore;
}

int main(){
  
  cin >> n >> m;
  
  for(int i = 1;i <= m;i++){
    
    int x, y, tempo;
    cin >> x >> y >> tempo;
    
    vizinhos[x].push_back( pii(tempo, y) );
    vizinhos[y].push_back( pii(tempo, x) );
  }
  
  cout << Prim() << endl; // imprimimos a resposta
  
  return 0;
}