/*tekst zadatka preuzet sa sajta https://arena.petlja.org/ , sa takmicenja(domaci zadaci sa kursa Diaa)*/

/*Игра живота
Vremensko ograničenje: 1 s
Memorijsko ograničenje: 64 MB
Ulaz: standardni ulaz
Izlaz: standardni izlaz

У игри живота учествују два играча. Играчи покушавају да победе природну селекцију тако што ће изабрати најбољу могућу опцију. Правила игре:
Сваки играч бира низ од n поља која су попуњена јединкама r или b.
Главна табла се попуњава тако што се упореде поља играча. Уколико оба играча имају поставиљену исту јединку на i-том пољу, онда се у таблу на 
i-том пољу поставља r, а уколико оба играча имају постављене различите јединке на i-том пољу, онда се у табелу на 
i-том пољу поставља b. Другим речима, две исте јединке изумиру и рађају једину r, док две различите јединке изумиру и рађају јединку b.
Од два различита исхода игре, бољи је онај који на првом различитом пољу садржи једину b.
Потребно је написати програм који ће из гомиле од n
различито попуњених низова изабрати пар који даје најбољи могући исход. На стандардни излаз исписати тражени пар, тако да први низ буде бољи од другог.

Улаз:
Са стандардног улаза се уноси број n (1 ≤ n ≤ 10^5), затим број m (3 ≤ m ≤ 20), а затим и n
ниски, где је свака ниска дужине m.

Излаз:
На стандардни излаз исписати пар ниски, сваку у засебном реду, које дају најбољи могући исход игре. Уколико има више таквих парова исписати онај који се први јавља са улаза.

Пример:
Улаз:
5 4
rrrr
rrbr
rbbb
bbrr
bbbr

Излаз:
bbrr
rrbr

Напомена: Овде имамо два решења bbrr rrbr и bbbr rrrr, јер оба дају исход bbbr. Изабрали смо прво решење како bbrr долази пре bbbr на улазу.
*/


/*Resenje*/

#include <iostream>
#include <vector>

class Trie {
public:
    struct Node {
        Node *b = nullptr;  // 'b' branch
        Node *r = nullptr;  // 'r' branch
    };
private:
    void freeTrie(Node *root) {
        if (root == nullptr) return;
        freeTrie(root->b);
        freeTrie(root->r);
        delete root;
    }

    Node *m_trie;
public:
    Trie() : m_trie(new Node()) {}

    ~Trie() {
        freeTrie(m_trie);
    }

    void add(const std::string &word) {
        auto trie = m_trie;
        for (auto c : word) {
            if (c == 'b') {
                if (trie->b == nullptr) {
                    trie->b = new Node();
                }
                trie = trie->b;
            } else {
                if (trie->r == nullptr) {
                    trie->r = new Node();
                }
                trie = trie->r;
            }
        }
    }

    std::pair<std::string, int> findLongestPrefix(std::string &word) {
        std::pair<std::string, int> result;
        int maxLength = 0;
        auto length = word.size();
        std::string prefix;
        auto trie = m_trie;
        auto i = 0u;

        for (; i < length; i++) {
            // The best outcome is along the opposite branches
            if (word[i] == 'b') {
                if (trie->r == nullptr) break;
                ++maxLength;
                trie = trie->r;
                prefix.push_back('r');
            } else {
                if (trie->b == nullptr) break;
                ++maxLength;
                trie = trie->b;
                prefix.push_back('b');
            }
        }

        // Complete the remaining part of the word
        for (; i < length; i++) {
            if (word[i] == 'b') {
                if (trie->r == nullptr) {
                    prefix.push_back('b');
                    trie = trie->b;
                } else {
                    prefix.push_back('r');
                    trie = trie->r;
                }
            } else {
                if (trie->b == nullptr) {
                    prefix.push_back('r');
                    trie = trie->r;
                } else {
                    prefix.push_back('b');
                    trie = trie->b;
                }
            }
        }

        if (prefix == word) {
            result = std::make_pair("", 0);
        } else {
            result = std::make_pair(prefix, maxLength);
        }

        return result;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;

    std::string input;

    int maxLength = -1;
    std::string s1 = "", s2 = "";
    auto trie = new Trie();

    while (n) {
        std::cin >> input;
        trie->add(input);
        auto pair = trie->findLongestPrefix(input);
        if (pair.second > maxLength) {
            maxLength = pair.second;
            s1 = input;
            s2 = pair.first;
        }
        --n;
    }
    std::cout << s1 << '\n' << s2 << std::endl;
    delete trie;

    return 0;
}
