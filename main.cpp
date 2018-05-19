#include<iostream>
#include <fstream>
#include "Polinom.h"

using namespace std;
ifstream fin("..\\date.in");
ofstream fout("..\\date.out");

int main() {

    Polinom<float> a(2);
    Polinom<float> b(a);
    Polinom<double> c;
    fin >> a >> c;
    b = a + a;
    float x = 2.5;
    /// valoarea in pct a unui polinom - exemplu: x, b
    fout << "Valoarea in punctul " << x << " a polinomului este " << b.getValueInPoint(x) << "\n";

    fout << "Gradul polinomului c este " << c.getDegree() << "\n";
    for (int i = 0; i < c.getDegree(); i++) {
        fout << c[i] << " "; // coeficientii
    }
    fout << "\n";
    fout << a;

    Polinom<float> d;
    d = a + b;
    fout << "Polinom suma: ";
    fout << d;

    fout << "Produs intre polinoame: ";
    fout << a * b;

    fout << "Produs cu scalar la stanga si dreapta: ";
    fout << x * b;
    fout << b * x;
    fout << "Polinom cat: ";
    fout << a / b;

    // adauga la polinomul q un termen de grad 10 si coeficient 15
    fout << "adaugare termen de grad dat 10 si coef x: ";
    c.add(10, x);
    fout << c;
    fout << "stergere termen de grad dat 10 ";
    fout << c.remove(10);

    return 0;
}