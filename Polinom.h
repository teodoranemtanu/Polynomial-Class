//
// Created by teone on 12-May-18.
//

#ifndef TEMA3_POLINOM_TEMPLATE_POLINOM_H
#define TEMA3_POLINOM_TEMPLATE_POLINOM_H
using namespace std;

template<class T>
class Polinom {
    int degree;
    T *coef;
public:
    ///constructors
    /**
     * initializes a polynomial with a degree and all its coeficients with 0
     * @param n - degree of the polynomial
     */
    Polinom(int n = 0);

    /**
     * initializes the polynomial with a degree and an array of coeficients
     * @param n - degree
     * @param array - coeficients
     */
    Polinom(int n, T *array);

    /**
     * copy constructor
     * @param obj - object of class polynomial to be copied
     */
    Polinom(Polinom<T> &obj);

    //destructor
    ~Polinom();

    ///acces
    const int getDegree() const;

    T operator[](int position) {
        return coef[position];
    }

    /**
     * calculates the value of the polynomial in a given point x
     * @param x
     * @return - value calculated
     */
    T getValueInPoint(T x);

    /**
     * overload of the operators
     * @param a - the polynomial with whom the operations are made
     * @return - polynomial calculated in the overloaded functions
     */
    Polinom<T> &operator=(const Polinom<T> &a);

    Polinom<T> operator+(const Polinom<T> &a);

    Polinom<T> operator*(const Polinom<T> &a);

    /**
     * the multiplication with a scalar, implemented both as scalar * polynomial and polynomial * scalar
     * @param x - scalar
     * @param a - polynomial
     * @return - the polynomial calculated
     */

    friend Polinom<T> operator*(const T x, const Polinom<T> &a) {
        Polinom<T> c(a.degree);
        for (int i = 0; i <= a.degree; i++)
            c.coef[i] = a.coef[i] * x;
        return c;
    }

    friend Polinom<T> operator*(const Polinom<T> &a, const T x) {
        Polinom<T> c(a.degree);
        for (int i = 0; i <= a.degree; i++)
            c.coef[i] = a.coef[i] * x;
        return c;
    }

    /**
     * division of a polynomial by other polynomial
     * @param b - polynomial which divides the *this polynome
     * @return - result of the operation
     */
    Polinom<T> operator/(const Polinom<T> &b);

    /**
     * overload of the reading operator, getting all the information for a polynomial from the input file
     * @param fin - input file
     * @param a - polynomial to be read
     * @return - input file
     */
    friend ifstream &operator>>(ifstream &fin, Polinom<T> &a) {
        fin >> a.degree;
        a.coef = new T[a.degree + 1];
        for (int i = 0; i <= a.degree; i++)
            fin >> a.coef[i];
        cout << a.degree << " " << a.coef[1] << "\n";
        return fin;
    }

    /**
     * overload of the display operator, writing the information for a polynomial in the output file
     * @param fout - output file
     * @param a - polynomial to be displayed
     * @return - output file
     */
    friend ofstream &operator<<(ofstream &fout, const Polinom<T> &a) {
        fout << "Polinomul are forma ";
        for (int i = 0; i < a.degree; i++) {
            if (a.coef[i] != 0) {
                if (a.coef[i] != 1) {
                    fout << a.coef[i] << " x^" << i << " + ";
                } else {
                    fout << "x^" << i << " + ";
                }
            }
        }
        if (a.coef[a.degree] != 0) {
            if (a.coef[a.degree] != 1) {
                fout << a.coef[a.degree] << " x^" << a.degree << " ";
            } else {
                fout << "x^" << a.degree << " ";
            }
            fout << "si are gradul " << a.degree << ".\n";
        }
    }

    /**
     * adds a new term to the polynomial, in case there isn't other term of that degree already existing in the polynomial
     * if the new degree of the term exceeds the current degree, new memory is being allcated
     * @param newDegree - the degree of the new term
     * @param newCoef - the coeficient of the new term
     * @return - polynomial resulted
     */
    Polinom<T> &add(int newDegree, T newCoef);

    /**
     * deletes a term of a given degree in the polynomial
     * if the term of the biggest degree is being deleted, then it is checked whether a sequence of 0-coeficient terms are left as the terms with the biggest degrees
     * in that case, they are being deleted until a non-zero coeficient is being found
     * @param newDegree - the degree of the term which will be deleted
     * @return - resulted polynomial
     */
    Polinom<T> &remove(int newDegree);
};

template<class T>
Polinom<T>::Polinom(int n) {
    degree = n;
    coef = new T[n + 1];
    for (int i = 0; i <= n; i++)
        coef[i] = 0;
    std::cout << "C1" << " ";
}

template<class T>
Polinom<T>::Polinom(int n, T *array) {
    degree = n;
    coef = new T[n + 1];
    for (int i = 0; i <= n; i++)
        coef[i] = array[i];
    std::cout << "C2" << " ";
}

template<class T>
Polinom<T>::Polinom(Polinom<T> &obj) {
    degree = obj.degree;
    coef = new T[degree + 1];
    for (int i = 0; i <= degree; i++)
        coef[i] = obj.coef[i];
    std::cout << "CC" << " ";
}

template<class T>
Polinom<T>::~Polinom() {
    delete[] coef;
    std::cout << "D" << " ";
}

template<class T>
const int Polinom<T>::getDegree() const {
    return degree;
}

template<class T>
T Polinom<T>::getValueInPoint(T x) {
    T power = x;
    T value = coef[0];
    for (int i = 1; i <= degree; i++) {
        value = value + coef[i] * power * x;
        power *= x;
    }
    return value;
}

template<class T>
Polinom<T> &Polinom<T>::operator=(const Polinom<T> &a) {
    if (this != &a) {
        degree = a.degree;
        delete[] coef;
        coef = new T[degree + 1];
        for (int i = 0; i <= degree; i++)
            coef[i] = a.coef[i];
    }
    return *this;
}

template<class T>
Polinom<T> Polinom<T>::operator+(const Polinom<T> &a) {
    Polinom<T> c(max(a.degree, degree));
    for (int i = 0; i <= c.degree; i++)
        if (i <= a.degree && i <= degree) {
            c.coef[i] = a.coef[i] + coef[i];
        } else if (i <= a.degree) {
            c.coef[i] = a.coef[i];
        } else {
            c.coef[i] = coef[i];
        }
    return c;
}

template<class T>
Polinom<T> Polinom<T>::operator*(const Polinom<T> &a) {
    Polinom<T> c(a.degree + degree);
    for (int i = 0; i <= degree; i++)
        for (int j = 0; j <= a.degree; j++)
            c.coef[i + j] += coef[i] * a.coef[j];
    return c;
}

template<class T>
Polinom<T> Polinom<T>::operator/(const Polinom<T> &b) {
    Polinom<T> a(*this);
    Polinom<T> c(a.degree - b.degree);
    int k = c.degree;

    while (a.degree >= b.degree) {
        if (a.degree == b.degree) {
            c.coef[k] = a.coef[a.degree] / b.coef[b.degree];  // calculates the new coeficients
        } else {
            c.coef[k] = a.coef[a.degree];
        }

        for (int i = a.degree, j = b.degree; j >= 0; i--, j--) {
            a.coef[i] = a.coef[i] - c.coef[k] * b.coef[j];
        }
        a.degree--;
        k--;
    }
    return c;
}

template<class T>
Polinom<T> &Polinom<T>::add(int newDegree, T newCoef) {
    if (newDegree >= 0) {
        if (newDegree <= degree) {
            if (!coef[newDegree]) {
                coef[newDegree] = newCoef;
            }
        } else {
            Polinom<T> aux(*this);
            degree = newDegree;
            delete[] coef;
            coef = new int[degree + 1];
            for (int i = 0; i <= degree; i++)
                coef[i] = 0;
            for (int i = 0; i <= aux.degree; i++)
                coef[i] = aux.coef[i];
            coef[newDegree] = newCoef;
        }
    }
    return *this;
}

template<class T>
Polinom<T> &Polinom<T>::remove(int newDegree) {
    if (newDegree >= 0 && newDegree < degree) {
        coef[newDegree] = 0;
    } else if (newDegree == degree) {
        Polinom<T> aux(*this);
        coef[newDegree] = 0;
        while (!coef[degree])
            degree--;
        coef = new int[degree + 1];
        for (int i = 0; i <= degree; i++)
            coef[i] = aux.coef[i];
    }
    return *this;
}


#endif //TEMA3_POLINOM_TEMPLATE_POLINOM_H
