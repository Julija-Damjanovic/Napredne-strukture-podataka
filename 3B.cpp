/*tekst zadatka preuzet sa sajta https://arena.petlja.org/ , sa takmicenja(domaci zadaci sa kursa Diaa)*/
/*Провера циклуса

Vremensko ograničenje	Memorijsko ograničenje	ulaz	izlaz
1 s	64 MB	standardni ulaz	standardni izlaz

Провера циклуса
У будућности ће постојати више светова и унутар сваког света људи ће моћи да се телепортују са једне на другу планету. Напиши програм који за сваки свет испитује да ли је могуће да се помоћу низа телепортовања вратимо на локацију са које смо кренули.

Улаз
Са стандардног улаза се учитава број светова 
n
 (
1
≤
n
≤
20
) унутар којих је могуће телепортовање. За сваки свет, са стандардног улаза се учитава број планета 
v
 (
2
≤
v
≤
5000
), а затим из наредног реда и број телепортационих линкова 
e
 (
1
≤
e
≤
v
2
). У наредних 
e
 редова описани су телепортациони линкови тако што су задате почетна и крајња планета (бројеви од 
0
 до 
v
−
1
).

Излаз
На стандардни излаз за сваки свет исписати da ако постоји нека планета у коју је могуће вратити се када се једном из ње телепортујемо тј. ne у супротном.

Пример
Улаз
2
5
5
0 1
2 1
2 3
3 4
4 2
5
5
0 1
2 1
2 3
3 4
4 0
Излаз
da
ne
Објашњење
У првом свету је могуће, на пример, вратити се на планету 2 путем 3, 4, 2. У другом свету није могуће вратити се ни на једну почетну планету.
*/
/*Resenje*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool hasCycle(vector<vector<int>>& graph, vector<int>& inDegree, int vertices) {
    queue<int> q;

    for (int i = 0; i < vertices; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : graph[node]) {
            --inDegree[neighbor];
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    for (int i = 0; i < vertices; ++i) {
        if (inDegree[i] > 0) {
            return true; // Cycle detected
        }
    }

    return false; // No cycle detected
}

int main() {
    int worlds;
    cin >> worlds;

    for (int w = 0; w < worlds; ++w) {
        int planets;
        cin >> planets;

        vector<vector<int>> graph(planets);
        vector<int> inDegree(planets, 0);

        int teleportLinks;
        cin >> teleportLinks;

        for (int i = 0; i < teleportLinks; ++i) {
            int start, end;
            cin >> start >> end;
            graph[start].push_back(end);
            ++inDegree[end];
        }

        if (hasCycle(graph, inDegree, planets)) {
            cout << "da" << endl;
        } else {
            cout << "ne" << endl;
        }
    }

    return 0;
}
