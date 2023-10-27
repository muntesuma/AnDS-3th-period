#include <iostream>
#include <math.h>
using namespace std;

struct complex {
    double re, im;

    void output();
    void input();
    
    bool eql(complex);
    bool neql(complex);
 
    double modd();
    
    complex sum(complex);
    complex sub(complex);
    complex mult(complex);
    complex divv(complex);
};
    
complex complex::sum(complex sum) {
    complex res;
    
    res.re = re + sum.re;
    res.im = im + sum.im;
    
    return res;
}

complex complex::sub(complex sub) {
    complex res;
    
    res.re = re - sub.re;
    res.im = im - sub.im;
    
    return res;
}

complex complex::mult(complex mult) {
    complex res;
    
    res.re = re*mult.re - im*mult.im;
    res.im = re*mult.im + im*mult.re;
    
    return res;
}

complex complex::divv(complex divv) {
    complex res;
    
    res.re = (re*divv.re + im*divv.im) / (divv.re*divv.re + divv.im*divv.im);
    res.im = (im*divv.re - re*divv.im) / (divv.re*divv.re + divv.im*divv.im);
    
    return res;
}

bool complex::eql(complex eql) {
    bool res = false;
    
    if ((re == eql.re) && (im == eql.im)) {
        res = true;
        cout << re << " + i*(" << im << ") == " << eql.re << " + i*(" << eql.im << ")\n";
    } else {
        cout << re << " + i*(" << im << ") =! " << eql.re << " + i*(" << eql.im << ")\n";
    }
    
    return res;
}

bool complex::neql(complex neql) {
    bool res = false;
    
    if ((re != neql.re) || (im != neql.im)) {
        res = true;
        cout << re << " + i*(" << im << ") =! " << neql.re << " + i*(" << neql.im << ")\n";
    } else {
        cout << re << " + i*(" << im << ") == " << neql.re << " + i*(" << neql.im << ")\n";
    }
    
    return res;
}

double complex::modd() {
        double res = sqrt (re*re + im*im);
        
        cout << "|x|: " << res << "\n";
        
        return res;
}

void complex::input() {
        cout << "input re: ";
        cin >> re;
    
        cout << "input im: ";
        cin >> im;
        
        cout << "complex: " << re << " + i*(" << im << ")\n";
}

void complex::output() {
    cout << "(" << re << ") + i*(" << im <<")\n";
}

int main() {
    complex x;
        x.input();
    
    char sign;
        cout << "sign select (+ | - | * | / | = | ! | m): ";
        cin >> sign;
    
    if (sign != 'm') {
        complex y;
        y.input();
        
        switch(sign) {
            case '+': {
                complex sum = x.sum(y);
                sum.output();
                    break;
            }
            case '-': {
                complex sub = x.sub(y);
                sub.output();
                    break;
            }
            case '*': {
                complex mult = x.mult(y);
                mult.output();
                    break;
            }
            case '/': {
                complex divv = x.divv(y);
                divv.output();
                    break;
            }
            case '=': {
                bool eql = x.eql(y);
                if (eql == true) {
                    cout << "yes, they are equal";
                } else {
                    cout << "no, they aren't equal";
                }
                    break;
            }
            case '!': {
                bool neql = x.neql(y);
                if (neql == true) {
                    cout << "yes, they are notequal";
                } else {
                    cout << "no, they aren't notequal";
                }
                    break;
            }
        }
    } else {
        cout << "mod (" << x.re << " + i*(" << x.im << ")) = ";
            double modd = x.modd();
    }
    
    return 0;
}