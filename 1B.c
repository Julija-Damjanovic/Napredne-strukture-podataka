/*tekst zadatka preuzet sa sajta https://arena.petlja.org/ , sa takmicenja(domaci zadaci sa kursa Diaa)*/
/*РНА
Vremensko ograničenje: 1 s
Memorijsko ograničenje: 64 MB
Ulaz: standardni ulaz
Izlaz: standardni izlaz

РНА је ланац који се састоји од нуклеотида. Нуклеотиди су изграђени од нуклеобаза и то су: (c) цитозин, (a) аденин, (g) гванин, и (u) урацил. РНА ланац је секвенциран и од њега је добијен низ карактера. Желимо да направимо програм који ће да манипулише овакав ланац. Наш програм обрађује 3 типа упита:

1. b <indeks> - са позиције <indeks> уништавамо нуклеотид;
2. p <indeks> <baza> - на позицију <indeks> смештамо нови нуклеотид са базом <baza> (уколико на позицији <indeks> није уништен нуклеотид, прво га уништимо);
3. c <indeks1> <indeks2> <baza> - рачуна колико има нуклеотида са базом <baza> у опсегу од <indeks1> до <indeks2>.

Временска сложеност алгоритма треба да буде 
O(n+qlogn), а просторна O(n), где q представља број упита.

Улаз:
Са стандардног улаза се уноси ниска дужине n(1 ≤ n ≤ 2⋅10^5) која се састоји само од карактера c, a, g и u. Затим се уноси број q(1 ≤ n ≤ 2⋅10^5) и за њим q упита, сваки у засебном реду.

Излаз:
За сваки упит трећег типа исписати резултат у засебни ред стандардног излазa.

Пример:
Улаз:
caggucuau
5
c 1 4 a
p 1 g
c 0 3 g
b 2
c 0 3 g

Излаз:
1
3
2
*/
/*Resenje*/

	OK	1	0,52s	10,00MB
11	OK	1	0,50s	10,00MB
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class Nucleotide {
private:
    int c;
    int a;
    int g;
    int u;

public:
    Nucleotide() : c(0), a(0), g(0), u(0) { }

    Nucleotide(char character) : c(0), a(0), g(0), u(0) {
        if (character == 'c') {
            ++c;
        } else if (character == 'a') {
            ++a;
        } else if (character == 'g') {
            ++g;
        } else if (character == 'u') {
            ++u;
        }
    }

    Nucleotide operator+(const Nucleotide& other) const {
        Nucleotide result;
        result.c = this->c + other.c;
        result.a = this->a + other.a;
        result.g = this->g + other.g;
        result.u = this->u + other.u;
        return result;
    }

    Nucleotide& operator+=(const Nucleotide& other) {
        *this = *this + other;
        return *this;
    }

    void destroy(char character) {
        if (character == 'c') {
            --c;
        } else if (character == 'a') {
            --a;
        } else if (character == 'g') {
            --g;
        } else if (character == 'u') {
            --u;
        }
    }

    void add(char character) {
        if (character == 'c') {
            ++c;
        } else if (character == 'a') {
            ++a;
        } else if (character == 'g') {
            ++g;
        } else if (character == 'u') {
            ++u;
        }
    }

    int result(char character) {
        if (character == 'c') {
             return c;
        }
        if (character == 'a') {
            return a;
        }
        if (character == 'g') {
            return g;
        }
        if (character == 'u') {
            return u;
        }
        return 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Nucleotide& nucleotide);
};

std::ostream& operator<<(std::ostream& os, const Nucleotide& nucleotide) {
    os << "(c: " << nucleotide.c << ", a: " << nucleotide.a << ", g: " << nucleotide.g << ", u: " << nucleotide.u << ")";
    return os;
}

class SegmentTree {
public:
    SegmentTree(const std::string &nucleotide) {
        int n = std::pow(2, std::ceil(std::log2(nucleotide.size())));
        m_tree = std::vector<Nucleotide>(2 * n);

        for(int i = 0; i < n; i++) {
            m_tree[n + i] = Nucleotide(nucleotide[i]);
        }
        for(int i = n - 1; i > 0; i--) {
            m_tree[i] = m_tree[2 * i] + m_tree[2 * i + 1];
        }
    }

    Nucleotide sum(int l, int d) {
        const int n = m_tree.size() / 2;

        Nucleotide sum = Nucleotide();
        l = n + l; d = n + d;
        while (l <= d)
        {
            if(l % 2) sum += m_tree[l++];
            if(d % 2 == 0) sum += m_tree[d--];
            l /= 2; d /= 2;
        }

        return sum;
    }

    void update(const int i, const char old, const char newChar) {
        int k = m_tree.size() / 2 + i;
        m_tree[k].destroy(old);
        m_tree[k].add(newChar);

        for(k /= 2; k > 0; k /= 2) {
            m_tree[k] = m_tree[2 * k] + m_tree[2 * k + 1];
        }
    }


    ~SegmentTree() {}

private:
    std::vector<Nucleotide> m_tree;
};

int main() {

    std::string nucleotide;
    std::cin >> nucleotide;
    auto segmentTree = new SegmentTree(nucleotide);
    int n, l, d;
    std::cin >> n;

    char nucleobase;

    while (n) {
        std::cin >> nucleobase;
        if (nucleobase == 'c') {
            std::cin >> l >> d >> nucleobase;
            std::cout  << segmentTree->sum(l, d).result(nucleobase) << std::endl;
        }
        else if (nucleobase == 'p') {
            std::cin >> l >> nucleobase;
            segmentTree->update(l, nucleotide[l], nucleobase);
            nucleotide[l] = nucleobase;
        }
        else if (nucleobase == 'b') {
            std::cin >> l;
            segmentTree->update(l, nucleotide[l], 'x');
            nucleotide[l] = 'x';
        }
        --n;
    }

    return 0;
}

