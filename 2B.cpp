/*tekst zadatka preuzet sa sajta https://arena.petlja.org/ , sa takmicenja(domaci zadaci sa kursa Diaa)*/

/*
Периодичност ниске

Vremensko ograničenje	Memorijsko ograničenje	ulaz	izlaz
0,1 s	64 MB	standardni ulaz	standardni izlaz

Периодичност ниске
Реч 
w
је периодична ако постоји непразна реч 
p=p1p2
и природан број 
n≥2 тако да је w=p^np1. На пример, реч 
abacabаcabacab
је периодична јер се понавља 
abac, при чему се последње понављање не завршава цело већ се зауставља са 
ab, тј. реч је (abac)3ab. Напиши програм који проверава да ли је унета реч периодична.

Улаз
Прва линија стандардног улаза садржи реч која се састоји само од малих слова енглеског алфабета – њих највише 50000.

Излаз
На стандардни излаз исписати реч da ако реч јесте периодична тј. ne ако није.

Пример
Улаз
abbaabbaabbaa
Излаз
da

*/
/*Resenje*/

#include <iostream>
#include <vector>
#include <string>

int main() {
std::ios_base::sync_with_stdio(false);
std::string s;
std::cin >> s;
if(s.size()>50001)
    return -1;
std::vector<int> kmp(s.size() + 1, 0);
    kmp[0] = -1;

for (int i = 0; i < s.size(); i++) {
    int k = i;
    while (k > 0 && s[i] != s[kmp[k]])
        k = kmp[k];
        kmp[i + 1] = kmp[k] + 1;
    }

if (2 * kmp[s.size()] >= s.size())
std::cout << "da" << std::endl;
else
std::cout << "ne" << std::endl;

return 0;
}
