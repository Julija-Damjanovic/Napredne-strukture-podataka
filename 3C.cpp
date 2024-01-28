/*tekst zadatka preuzet sa sajta https://arena.petlja.org/ , sa takmicenja(domaci zadaci sa kursa Diaa)*/
/*Мостови и Ојлерови циклуси

Vremensko ograničenje	Memorijsko ograničenje	ulaz	izlaz
1 s	64 MB	standardni ulaz	standardni izlaz

Ако се неусмереном графу уклоне мостови, одредити колико тако добијених компоненти повезаности садржи Ојлеров циклус. За проналазак мостова користити алгоритам који је најгоре временске сложености као DFS.

Улаз
Са стандардног улаза уноси се број 
n
 (број чворова), број 
m
 (број грана), затим у наредних 
m
 редова парови бројева који представљају неусмерене гране.

Излаз
На стандардни излаз исписати тражени број.

Пример
Улаз
7 9
0 1
0 2
1 2
1 3
2 3
3 4
4 5 
4 6
5 6
Излаз
1
*/
/*Resenje*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std; 

using Graph = vector<vector<int>>;

vector<bool> visited;
vector<int> degrees;
vector<int> parents;
vector<int> times;
vector<int> lower_times;
int pre;

void initialize_graph(Graph &g, int n) {
    g.resize(n);
    visited.resize(n, false);
    degrees.resize(n, 0);
    parents.resize(n, -1);
    pre = 0;
    times.resize(n, -1);
    lower_times.resize(n, -1);
}

void add_edge(Graph &g, int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
    degrees[u]++;
    degrees[v]++;
}

void remove_edge(Graph &g, int u, int v) {
    g[u].erase(find(g[u].begin(),g[u].end(),v));
    g[v].erase(find(g[v].begin(),g[v].end(),u));
    degrees[u]--;
    degrees[v]--;
}

void most(Graph &g, int u) {
    visited[u] = true;
    times[u] = lower_times[u] = pre++;
    for(int v : g[u]) {
        if(!visited[v]) {
            parents[v] = u;
            most(g, v);
            lower_times[u] = min(lower_times[u], lower_times[v]);
            if(times[u] < lower_times[v])
                remove_edge(g, u, v);
        }
        else if( v != parents[u])
            lower_times[u] = min(lower_times[u], times[v]);
    }
}

void DFS(Graph &g, int u, int &odd) {
    visited[u] = true;
    if (degrees[u] %2)
        ++odd;
    for(int v : g[u]) {
        if(!visited[v]) 
            DFS(g, v, odd);
    }
}

int eulerian(Graph& g) {
    int n = g.size();
    int odd = 0, e = 0;
    fill(visited.begin(), visited.end(), false);
    for(int i=0; i<n; i++) {
        if(!visited[i]){
            DFS(g,i,odd);
            e += odd == 0;
        }
        odd = 0;
    }
   
    return e;
}

int main () {
    Graph g;
    int n, m;
    cin >> n >> m;
    initialize_graph(g, n);
    int u, v;
    for(int i=0; i<m; i++){
        cin >> u >> v;
        add_edge(g, u, v);
    }
    most(g, 0); 
    cout << eulerian(g) << endl;
    
    return 0;
}
