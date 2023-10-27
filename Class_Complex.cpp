
#include <iostream>
#include <cmath>
using namespace std;

class complex {
	double re, im; // Задание 2ух вещественных переменных для комплексного числа

	public: // Задание типа доступа для общедоступных член-данных и член-функций
		// По умолчанию (то есть без спользования типов доступа) используется private

		complex(double Re = 0, double Im = 0); // Оператор задания комплексного числа

		void input(); // 
		void output();
 //

		double getRe() { // Оператор просмотра действительного числа
		    return re;
		} 
		void setRe(double); // Оператор смены действительного числа

		double getIm() { // Оператор просмотра мнимо числа
		    return im;
		} 
		void setIm(double); // Оператор смены мнимого числа

		bool operator == (complex); // Оператор сравнения на равенство
		bool operator != (complex); // Оператор сравнения на неравенство

		double mod() { // Модуль комплексного числа
		    return sqrt(re * re + im * im);
		} 

		complex operator + (const complex &x);// Оператор сложения комплексных чисел
		complex operator - (const complex &); // Оператор вычитания комплексных чисел
		complex operator * (const complex &); // Оператор умножения комплексных чисел
		complex operator / (const complex &); // Оператор деления комплексных чисел

		friend ostream &operator << (ostream &st, const complex &x) { // Вывод комплексного числа
			if (x.im > 0) st << x.re << " + " << x.im << " * i";
        		else if (x.im < 0) st << x.re << " - " << -1 * x.im << " * i";
        		else st << x.re;

        		return st;
		};

		friend istream &operator >> (istream &st, complex &x) { // Ввод коплексного числа 
			st >> x.re;
        		st >> x.im;

        		return st;
		};
};

complex :: complex (double Re, double Im) { // Задание комплексного числа
    	re = Re;
    	im = Im;
}

void complex :: setRe (double Re) {re = Re;} // Смена действительного числа
void complex :: setIm (double Im) {im = Im;} // Смена мнимого числа



bool complex :: operator == (complex x) { // Сравнение на равенство
	if (re == x.re && im == x.im) return true;
    	return false;
}

bool complex ::operator != (complex x) { // Сравнение на неравенство
	if (re != x.re || im != x.im) return true;
    	return false;
}

complex complex::operator + (const complex &x) { // Разность комплексных чисел
    	complex res;
    	res.re = re + x.re;
    	res.im = im + x.im;

    	return res;
}

complex complex::operator - (const complex &x) { // Разность комплексных чисел
    	complex res;
    	res.re = re - x.re;
    	res.im = im - x.im;

    	return res;
}

complex complex::operator * (const complex &x) { // Умножение коплексных чисел
    	complex res;
    	res.re = re * x.re - im * x.im;
    	res.im = re * x.im + re * x.re;

    	return res;
}

complex complex::operator / (const complex &x) { // Деление коплексных чисел
    	complex res;
    	res.re = (re * x.re + im * x.im) / (x.re * x.re + x.im * x.im);
    	res.im = (im * x.re - re * x.im) / (x.re * x.re + x.im * x.im);

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

int main() { // Основная функция
    	complex x, y;

    	x.input();
	    y.input();

    	if (x == y) cout << "\nThey are equal";
    	if (x != y) cout << "\nThey aren't equal";

    	x.setRe(10);
    	y.setIm(10);

    	cout << "\nx re change:" << x.getRe();
	cout << "\ny im change:" << y.getIm();

    	cout << "\nx mod:" << x.mod(); 
	cout << "\ny mod:" << y.mod();

    	cout << "\nx + y:" << x + y;
    	cout << "\nx - y:" << x - y;
    	cout << "\nx * y:" << x * y;
    	cout << "\nx / y:" << x / y;

	return 0;
}