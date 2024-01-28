/*tekst zadatka preuzet sa sajta https://arena.petlja.org/ , sa takmicenja(domaci zadaci sa kursa Diaa)*/
/*ASCII Уметност

Vremensko ograničenje	Memorijsko ograničenje	ulaz	izlaz
1 s	64 MB	standardni ulaz	standardni izlaz
Дата су два фајла, димензије 
n
×
n
 и 
m
×
m
, респективно. Први фајл је оригинална слика задата ascii карактерима. Други фајл представља покушај копирања дела оригиналне слике. Проверити да ли је покушај копирања успео.

Улаз
Са стандардног улаза се уноси прво број 
n
 (
1
≤
n
≤
200
), затим број 
m
 (
m
≤
n
). Након тога се уноси матрица карактера димезије 
n
×
n
, а на крају матрица карактера димензије 
m
×
m
.

Излаз
Уколико је друга матрица садржана у првој на стандардни излаз исписати da, а иначе ne.

Napomena: Уколико задатак решите наивним алгоритмом, а при томе прођу сви тест примери, рачуна се као да је решено 30% задатка.

Пример
Улаз
18 4
~.____......_....~
~|.._.\..../.\...~
~|.|_).|../._.\..~
~|.._.<../.___.\.~
~|_|_\_\/_/_..\_\~
~|.__.)_._|.\.|.|~
~|.._.\|.||..\|.|~
~|.|_).|.||.|\..|~
~|____/___|_|.\_|~
~|.|/./.../.\....~
~|.'./.../._.\...~
~|...\../.___.\..~
~|_|\_\/_/__.\_\.~
~|.._.\|.._.\....~
~|.|_).|.|_).|...~
~|.._.<|..__/....~
~|_|.\_\_|.......~
~................~
_._|
|.||
|.||
___|
Излаз
da
Пример
Улаз
19 4
###################
#.................#
#.................#
#._..._......_....#
#|.\.|.|..../.\...#
#|..\|.|.../._.\..#
#|.|\..|../.___.\.#
#|_|_\_|_/_/.._\_\#
#|_._|.\.\..././..#
#.|.|...\.\././...#
#.|.|....\.V./....#
#|___|_...\_/.....#
#|.____|..........#
#|.._|............#
#|.|___...........#
#|_____|..........#
#.................#
#.................#
###################
nnnn
nnnn
nnnn
nnnn
Излаз
ne
Пример
Улаз
17 3
.................
.................
.................
...(.)_____(.)...
..../.O...O.\....
...|...(@)...|...
...\....~..../...
....\.<}*{>./....  
.___/..___..\___.
()___./...\.___()
....(.\___/.)....
.../_./...\._\...
..(__).....(__)..
.................
.................
.................
.................
(@)
.~.
}*{
Излаз
da
*/
/*Resenje*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int prime = 31;
const int mod = 1e9 + 9;

long long calculateHash(const vector<string>& matrix, int row, int col, int size) {
    long long hashValue = 0;
    long long pPow = 1;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            hashValue = (hashValue + (matrix[row + i][col + j] - 'a' + 1) * pPow) % mod;
            pPow = (pPow * prime) % mod;
        }
    }

    return hashValue;
}

bool isEqual(const vector<string>& original, const vector<string>& copyAttempt, int row, int col, int m) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            if (original[row + i][col + j] != copyAttempt[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool rabinKarpSearch(const vector<string>& original, const vector<string>& copyAttempt) {
    int n = original.size();
    int m = copyAttempt.size();

    if (n < m) {
        return false;
    }

    long long copyAttemptHash = calculateHash(copyAttempt, 0, 0, m);

    for (int i = 0; i <= n - m; ++i) {
        for (int j = 0; j <= n - m; ++j) {
            if (i == 0 && j == 0) {
                // Calculate the hash of the first window
                continue;
            }

            // Update hash using rolling hash
            long long originalHash = calculateHash(original, i, j, m);

            if (originalHash == copyAttemptHash && isEqual(original, copyAttempt, i, j, m)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    // Reading original matrix
    vector<string> original(n);
    for (int i = 0; i < n; ++i) {
        cin >> original[i];
    }

    // Reading copy attempt matrix
    vector<string> copyAttempt(m);
    for (int i = 0; i < m; ++i) {
        cin >> copyAttempt[i];
    }

    // Checking if the copy attempt is successful
    bool result = rabinKarpSearch(original, copyAttempt);

    // Printing the result
    cout << (result ? "da" : "ne") << endl;

    return 0;
}

