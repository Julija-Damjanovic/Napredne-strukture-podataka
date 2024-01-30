/*tekst zadatka preuzet sa sajta https://arena.petlja.org/ , sa takmicenja(domaci zadaci sa kursa Diaa)*/
/*
Припадност тачке простом полигону

Vremensko ograničenje	Memorijsko ograničenje	ulaz	izlaz
0,3 s	64 MB	standardni ulaz	standardni izlaz

Припадност тачке простом полигону
Написати програм који за дати прост многоугао 
P и тачку T испитује да ли тачка T припада многоуглу. Многоугао садржи своје странице и темена.

Улаз
У провом реду стандардног улаза је број 
n, такав да је 
3≤n≤50000, број темена многоугла. У сваком од следећих n редова су по два цела броја раздвојена размаком, координате једног темена. Темена су дата у редоследу обиласка многоугаоне линије, у једном од два могућа редоследа. У последњем реду су још два цела броја раздвојена размаком, координате тачке 
T.
Излаз
На стандардни излаз исписати реч da ако тачка 
T припада многоугlu, а реч ne ако не припадa.

Пример 1
Улаз
8
0 0
5 0
5 1
1 1
1 3
5 3
5 4
0 4
2 2
Излаз
ne

Пример 2
Улаз
4
0 0
5 0
5 5
0 5
2 2
Излаз
da

*/
/*Resenje*/
#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    double x, y;
    Point(double _x, double _y) : x(_x), y(_y) {}
};

double Orientation(const Point& p, const Point& p1, const Point& p2) {
    return (p1.x - p.x) * (p2.y - p.y) - (p2.x - p.x) * (p1.y - p.y);
}

bool Between(const Point& p, const Point& p1, const Point& p2) {
    return
        std::min(p1.x, p2.x) <= p.x && std::max(p1.x, p2.x) >= p.x &&
        std::min(p1.y, p2.y) <= p.y && std::max(p1.y, p2.y) >= p.y;
}

bool OnLine(const Point& p, const Point& p1, const Point& p2) {
    return std::abs(Orientation(p, p1, p2)) < 1e-8 && Between(p, p1, p2);
}

bool LinesIntersect(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    double d1 = Orientation(p1, p3, p4);
    double d2 = Orientation(p2, p3, p4);
    double d3 = Orientation(p3, p1, p2);
    double d4 = Orientation(p4, p1, p2);
    return (d1 * d2 < 0 && d3 * d4 < 0) ||
           (std::abs(d1) < 1e-8 && Between(p1, p3, p4)) ||
           (std::abs(d2) < 1e-8 && Between(p2, p3, p4)) ||
           (std::abs(d3) < 1e-8 && Between(p3, p1, p2)) ||
           (std::abs(d4) < 1e-8 && Between(p4, p1, p2));
}

bool PointInPolygon(Point p, const std::vector<Point>& polygon) {
    size_t n = polygon.size();
    bool result = false;
    for (size_t i = 0; i < n; i++) {
        Point p1 = polygon[i];
        Point p2 = polygon[(i + 1) % n];

        if (OnLine(p, p1, p2))
            return true;

        Point rightEnd(std::max(p1.x, p2.x) + 1, p.y);
        if (LinesIntersect(p, rightEnd, p1, p2) &&
            ((p1.y < p.y && p2.y >= p.y) || (p2.y < p.y && p1.y >= p.y)))
            result = !result;
    }
    return result;
}

int main() {
    int n;
    double x, y;
    std::cin >> n;
    std::vector<Point> polygon;
    for (int i = 0; i < n; i++) {
        std::cin >> x >> y;
        polygon.push_back(Point(x, y));
    }
    std::cin >> x >> y;
    Point testPoint(x, y);
    if (PointInPolygon(testPoint, polygon))
        std::cout << "da" << std::endl;
    else
        std::cout << "ne" << std::endl;
    return 0;
}
