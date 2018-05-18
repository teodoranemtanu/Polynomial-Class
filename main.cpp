#include<iostream>
#include <fstream>
#include "Polinom.h"
using namespace std;
ifstream fin("..\\date.in");
ofstream fout("..\\date.out");

int main() {

    Polinom <float> a(2);
    Polinom <float> b(a);
    Polinom <double> c;
    fin >> a >> c;
    b = a + a;
    fout << c;

    return 0;
}