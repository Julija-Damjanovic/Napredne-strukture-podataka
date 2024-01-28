/*tekst zadatka preuzet sa sajta https://arena.petlja.org/ , sa takmicenja(domaci zadaci sa kursa Diaa)*/
/*Прост троугао
Vremensko ograničenje: 1 s
Memorijsko ograničenje: 64 MB
Ulaz: standardni ulaz
Izlaz: standardni izlaz

Прости троугао је троугао који садржи све просте бројеве.

          2
        3   5
      7  11  13
    17 19  23  29
        ....

За унети прост број израчунати ред и колону у којој се он налази у простом троуглу.

Улаз:
Са стандардног улаза се прво учитава највећи могући прост број 
n
 (50 ≤ n ≤ 10^5), затим број упита 
m
 (5 ≤ m ≤ 10^5), а након тога и 
m
 бројева.

Излаз:
На стандардни излаз исписати за сваки упит ред и колону у којој се број налази. Уколико број није прост, тј. не налази се у простом троуглу исписати -1.

Пример:
Улаз:
50
5
7
3
23
4
13

Излаз:
3 1
2 1
4 3
-1
3 3

*/
/*Resenje*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<int> sieve(int limit) {
    std::vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= limit; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                isPrime[j] = false;
            }
        }
    }

    std::vector<int> primes;
    for (int i = 2; i <= limit; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

std::pair<int, int> findPositionInTriangle(int n, const std::vector<int>& primes) {
    int count = 0;
    int row = 1;
    int col = 1;

    while (count < primes.size()) {
        if (primes[count] == n) {
            return std::make_pair(row, col);
        }

        count++;
        col++;

        if (col > row) {
            row++;
            col = 1;
        }
    }

    return std::make_pair(-1, -1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m, x;
    std::cin >> n;

    std::vector<int> primes = sieve(n);

    std::cin >> m;

    while (m--) {
        std::cin >> x;

        std::pair<int, int> position = findPositionInTriangle(x, primes);

        if (position.first == -1) {
            std::cout << -1 << "\n";
        } else {
            std::cout << position.first << " " << position.second << "\n";
        }
    }

    return 0;
}
