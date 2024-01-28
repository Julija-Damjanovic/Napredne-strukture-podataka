/*tekst zadatka preuzet sa sajta https://arena.petlja.org/ , sa takmicenja(domaci zadaci sa kursa Diaa)*/

/*Такси растојање око правоугаоника

Vremensko ograničenje	Memorijsko ograničenje	ulaz	izlaz
0,2 s	64 MB	standardni ulaz	standardni izlaz

Такси растојање око правоугаоника
Дате су тачке 
A, B и правоугаоник 
MPNQ, страница паралелних осама, задат теменима P, Q једне своје дијагонале. Одредити дужину најкраће полигоналне линије са почетком A и крајем B, страница паралелних осама, која не садржи унутрашње тачке правоугаоника 
MPNQ.

Улаз
Са стандардног улаза се уноси 8 реалних бројева из интервала 
[−1000,1000], заокружених на највише четири децимале. У првом реду се уносе x и y координата тачке A, у другом тачке B, у трећем тачке P, а у четвртом тачке Q.
Подаци су такви да тачке 
A и B нису унутар правоугаоника.

Излаз
На стандардни излаз исписати тражену дужину на четири децимале.

Пример
Улаз
0.0 -2.00
0.0 2.00
-1.0 -1.0
1.0 1.0

Излаз
6.0000
*/
/*Resenje*/
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

bool Order(double t1, double t2, double t3, double t4) {
double m = min(t1, t4), M = max(t1, t4);
    return (m <= t2 && m <= t3 && M >= t2 && M >= t3);
}

int main() {
double ax, ay, bx, by, px, py, qx, qy;
cin >> ax >> ay >> bx >> by >> px >> py >> qx >> qy;
double d;
if (Order(ax, px, qx, bx) && Order(py, ay, by, qy))
    d = min(abs(ay-py) + abs(by-py), abs(qy-ay) + abs(qy-by))+ abs(ax-bx);
else if (Order(ay, py, qy, by) && Order(px, ax, bx, qx))
    d = min(abs(ax-px) + abs(bx-px), abs(qx-ax) + abs(qx-bx))+ abs(ay-by);
else
    d = abs(ax-bx) + abs(ay-by);
cout << fixed << showpoint << setprecision(4) << d << endl;

return 0;
}
