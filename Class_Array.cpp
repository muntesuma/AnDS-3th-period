// https://www.programiz.com/cpp-programming/online-compiler/ - ссылка на онлайн-компилятор

#include <iostream>
#include <chrono> // библиотека для измерения скорости выполнения участка кода

using namespace std;

class Array {
	int *a, n; 	// *a - динамический массив, n - размер 
public:
	// конструктор (конструктор с целым аргументом будет выделять память под массив с заданным кол-вом элементов, если не будет указан аргумент, то по умолчанию выделяется память под массив из 1 элемента) 
    	Array(int len = 1, int t = 1, int d = 10) { 		// len – число элементов в массиве
        	a = new int[len];
        	n = len; 					// len – число элементов в массиве
        	if (t == 1) { 					// t = 1 – неупорядоченный массив
            		for (int i = 0; i < n; i++) {
                		a[i] = rand() % d; 		// d – диапазон псевдослучайных чисел для неупорядоченного массива (при t = 1)
            		}
        	} else if (t == 2) { 				// t = 2 – массив, упорядоченный по неубыванию
            		a[0] = rand() % d;
            		for (int i = 1; i < n; i++) {
                		a[i] = a[i - 1] + rand() % d;	// массив по возрастанию 
            		}
        	} else if (t == 3) { 				// t = 3 – массив, упорядоченный по невозрастанию
            		a[n - 1] = rand() % d;
            		for (int i = n - 2; i >= 0; i--) {
                		a[i] = a[i + 1] + rand() % d; 	// массив по убыванию 
            		}
        	} else {
            		exit(1);
        	}
    	};

	// конструктор с двумя аргументами (*b - массив, len - размер массива) 
    	Array(int *b, int len) { 		// конструктор 2: по массиву
        	a = new int[len]; 		// выделение памяти 
        	n = len;
        	for (int i = 0; i < n; i++) { 	// заполнение элементами массива
            		a[i] = b[i];
        	}
    	};

	// конструктор копирования (необходим, т.к. массив в динамической области) 
    	Array(Array &b) { 			// конструктор копирования
        	a = new int[b.n];
        	n = b.n;
        	for (int i = 0; i < n; i++) {
            		a[i] = b.a[i];
        	}
    	};

    	~Array() { // деструктор
        	if (a) delete[]a;
        	a = NULL;
    	}

    	Array &operator=(const Array &);	// перегрузка оператора присваивания
    	int &operator[](int); 			// оператор для получения i-ого элемента

    	bool Test(); 		// проверка на упорядоченность по неубыванию
    	bool operator==(Array); // равенство элементов массивов (но не порядка)

    	void Shell_sort(); 	// СОРТИРОВКА ШЕЛЛА
    	// void Heapsort(); 	// ПИРАМИДАЛЬНАЯ СОРТИРОВКА 
    	void Hoar_sort(); 	// СОРТИРОВКА ХОАР_3 
	

    	friend istream &operator>>(istream &, Array &); 	// дружественный оператор ввода
    	friend ostream &operator<<(ostream &, Array &); 	// дружественный оператор вывода
};

Array &Array::operator=(const Array &newArr) { 	// оператор присваивания
    	if (this == &newArr) { 			// выход при совпадении, передача массива обратно
        	return *this;
	}
    	delete[] a; 				// очистка памяти
    	n = newArr.n; 				// задание новой длинны 
    	a = new int[n]; 			// выделение памяти 
    	for (int i = 0; i < n; i++) {
        	a[i] = newArr.a[i]; 		// переписывание элементов 
    	}
    	return *this;
};

int &Array::operator[](int b) { 		// оператор для получения i-ого элемента
    	if (b < 0 || b >= n) return a[0];
    	return a[b];
}

bool Array::Test() { 			// проверка массива на упорядоченность по неубыванию
    	for (int i = 1; i < n; i++) {
        	if (a[i] < a[i - 1]) { 		// если существуют эл-ты по убыванию
			cout << "\ntest result: false (the array is not sorted in non-decreasing order)" << endl;
 			return false;
		}
    	}
	cout << "\ntest result: true (the array is sorted in non-decreasing order)" << endl;	
    	return true;
}

// равенство элементов массивов (но не порядка)
bool Array::operator==(Array b) { 			// передача непосредственно данных, т.к. они будут изменяться
    	if (n != b.n) return false; 			// если длины не равны 
	int len = n; 					// временная переменная - длина массива
    	for (int i = 0; i < n; i++) {  			// проход по массиву 
        	bool ch = false;
        	for (int j = 0; j < len; j++) { 	// проход по всем эл-ам с временной переменной
            		if (a[i] == b.a[j]) { 		// поиск i-ого эл-та из массива, равного хотя бы одному j-ому из переданного	 
                		ch = true;
                		b[j] = b[len - 1];	// перемещение найденного эл-та 
                		len--; 			// уменьшение диапазона работы 
                		break;
            		}
        	}
        	if (ch == false) return false;
    	}
    	return true;
}

istream &operator>>(istream &in, Array &obj) {	// оператор ввода
    	int len; 				// создание len 
    	cout << "length: "; 			// ввод длинны (кол-ва элементов) массива 
    	in >> len; 				// подсчет длины 

    	cout << "\n array: "; 			// ввод массива 
    	int *arr; 				// создание временного массива
    	arr = new int[len]; 			// выделение памяти
    	for (int i = 0; i < len; i++) { 
        	in >> arr[i]; 			// ввод элементов 
    	}
    	obj = Array(arr, len); 			// копирование в массив
    	delete[] arr;
    	return in;
}

ostream &operator<<(ostream &out, Array &a) {	// оператор вывода
   	out << "sort result: ";
    	for (int i = 0; i < a.n; i++) {
        	out << a[i] << " ";
    	}
    	out << "\n";
    	return out;
}

void Array::Shell_sort() { 								// сортировка Шела
    	for (int gap = n / 2; gap > 0; gap /= 2) { 					// разбиение на раунды
        	for (int b = 0; b < gap; b++) { 					// рассмотр 1го эл-та подмассива
            		for (int i = b + gap; i < n; i += gap) { 			// проход по следующим эл-там подмассива
                		int x = a[i];
                		int k;
                		for (k = i - gap; k >= 0 && a[k] > x; k -= gap) {	// сравнение элемента с предыдущими
                    			a[k + gap] = a[k];
                		}
                		a[k + gap] = x;
            		}
        	}
    	}
}

int change(int *A, int l, int r) { 		// функция сортировки для удобства
    	if (l >= r) { 				// выход из функции когда левая граница >= правой
        	return 0;
    	}
    	int i = l; 				// установка i = l - левая граница
    	int j = r;				// установка j = r - правая граница
   	int x = A[(l + r) / 2]; 		// установка x = A[(l + r) / 2] - опорный элемент
    	while (i <= j) { 			// пока i <= j
        	while (A[i] < x) {		// пока A[i] < x
            		i++;			// увеличиваем i на 1.
        	}
        	while (A[j] > x) {		// пока A[j] > x
            		j--;			// уменьшаем j на 1
        	}
        	if (i <= j) { 			// если i <= j
            		swap(A[i], A[j]);	// A[i] <-> A[j]
            		i++;			// увеличиваем i на 1
            		j--;			// уменьшаем j на 1
        	}
    	}

	// разбитый на две части массив, подмассивы которого сортируются рекурсивно
    	change(A, l, j); 	// вызов рекурсии для левого подмассива
    	change(A, i, r); 	// вызов рекурсии для правого подмассива

    	return 0;
}

void Array::Hoar_sort() { 	// сортировка Хоар-3
    	change(a, 0, n - 1);
}

// void Array::heapify(int n, int i) {			// функция просеивания
//     	int j = 2 * i + 1;
//     	int x = a[i];
//     	bool f = true;
//     	while (j < n && f) { 				// до выхода за пределы пока есть потомок > предок
//         	if (j + 1 < n && a[j + 1] > a[j]) j++;	// выбор потомка с максимальным значением
//         	if (a[j] > x) { 			// в случае нахождения потомка > предка то запись потомка в предка и рассмотр места потомка как нового предка
//             		a[i] = a[j];
//             		i = j;
//             		j = 2 * i + 1;
//         	} else f = false;
//     	}
//     	a[i] = x;
// }

// void Array::Heapsort() { 			// пирамидальная сортировка
//     	for (int i = n / 2 - 1; i >= 0; i--)	// создание пирамиды с максимальным значением в её вершине
//         	this->heapify(n, i);
//     	for (int i = n - 1; i > 0; i--) { 	// сортировка массива по пирамиде
//         	swap(a[0], a[i]);
//         	this->heapify(i, 0);
//     	}
// }

void test() {
    	using std::chrono::high_resolution_clock;
    	using std::chrono::duration_cast;
    	using std::chrono::duration;
    	using std::chrono::milliseconds;

    	Array t(100, 3);

    	double seconds = 0;

	Array t_shell = t;
    	auto t_start = high_resolution_clock::now(); // метод возвращающий текущую точку во времени (начальная точка во времени) 
    	t_shell.Shell_sort();
    	auto t_stop = high_resolution_clock::now(); // конечная точка во времени
    	duration<double, std::milli> ms_double = t_stop - t_start; // разница во времени
    	cout << ms_double.count() << " ms by Shell_sort" << endl;

	// Array t_heap = t;
    	// t_start = high_resolution_clock::now();
    	// t_heap.Heapsort();
    	// t_stop = high_resolution_clock::now();
    	// ms_double = t_stop - t_start;
    	// cout << ms_double.count() << " ms by Heapsort" << endl;

	Array t_hoar = t;
    	t_start = high_resolution_clock::now();
    	t_hoar.Hoar_sort();
    	t_stop = high_resolution_clock::now();
    	ms_double = t_stop - t_start;
    	cout << ms_double.count() << " ms by Hoar_sort" << endl;
}

int main() {
    	Array t;
    	cin >> t;

	bool nd = t.Test();
	if (nd == true) {
		return 0;
	}

	int sort;
	cout << "sort selection: \n for Shell_sort - 1 \n for Hoar_sort - 2 \n for Heap_sort - 3 \nchoosen sort: ";
	cin >> sort;
	if (sort == 1) {
		t.Shell_sort();
	} else if (sort == 2) {
		t.Hoar_sort();
	} else if (sort == 3) {
		// t.Heap_sort();
		return 0;
	} else {
		cout << "\nthere is no such sorting" << endl;
		return 0;
	}
    	
    	cout << t;
    	test();

    	return 0;
}

