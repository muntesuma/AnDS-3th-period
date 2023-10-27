#include <iostream>
#include <cmath>
using namespace std;

class route { // класс маршрут
    int *r, n; // r – массив, представляющий маршрут; n – количество городов
    public:
        route(int num = 0); // заполнение массива числами от 1 до n
        route(const route &); // конструктор копирования
        route &operator=(const route &); // оператор присваивания
        ~route() { // деструктор
            if (r) delete[]r;
            r = NULL;
        } 
        int route_price(int **); // вычисление стоимоити маршрута по матрице стоимости
        bool next_route(); // вычисление следующего маршрута с использованием алгоритма Дейкстры
        friend ostream &operator<<(ostream &, const route &); // вывод маршрута
};

route::route(int num) { // заполние массива числами от 1 до n
    n = num;
    r = new int[num];
    for (int i = 0; i < num; i++) r[i] = i + 1; 
}

route::route(const route &arr) { // копирование длины маршрута
    n = arr.n;
    r = new int[arr.n];
    for (int i = 0; i < arr.n; i++) r[i] = arr.r[i];
}

route& route::operator=(const route &x) { // оператор присваивания
    if(this == &x) return *this;
    delete(r);
    n = x.n; // присваевание длины маршрута
    r = new int [x.n];
    for(int i = 0; i < x.n; i++) r[i] = x.r[i];
    return *this;
}

int route::route_price(int **arr) { // подсчёт матрицы стоимости
    int sum = 0, b;
    for(int i = 0; i < n - 1; i++) {
        b = r[i+1]; // 2й город
        sum += arr[r[i]-1][b-1]; // заносим стоимость пути i в второй
    }
    b = r[0];
    sum += arr[r[n-1]-1][b-1]; // путь из последнего в первый для цикла
    return sum;
}

bool route::next_route() {
    int i;
    int j;
    bool flag = false;
    for(i = n - 2; i > - 1; i--) { // поиск i
        if(r[i] < r[i+1]) {
            flag = true;
            break;
        }
    } 
    if(flag) {
        for(j = n - 1; j > i; j--) if(r[i] < r[j]) break; // поиск j

        int c;
        c = r[i];
        r[i] = r[j];
        r[j] = c;

        if(i < n - 2) { // инвертирование хвоста
            int left = i + 1;
            int right = n - 1;
            while(left < right) {
                c = r[left];
                r[left] = r[right];
                r[right] = c;
                left++;
                right--;
            }
        } 
        if(r[0] != 1) flag = false; // все пути !=1 можно не расматривать, так как пути цикличны
        return flag;
    }
    else return flag;
}

ostream &operator<<(ostream &p, const route &x) { // дружественная функция вывода
    for (int i = 0; i < x.n; i++) p << x.r[i] << " ";
    return p;
}

route task(int num) { // решение задачи коммивояжера
    int**matrix = new int* [num]; // выделение памяти под столбцы
    for (int i = 0; i < num; i++) matrix[i] = new int [num]; // выделение памяти под строки
    for(int i = 0; i < num; i++) {
        for(int j = 0; j < num; j++) {
            matrix[i][j] = rand() % 9 + 1; // заполнение матрицы
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    route r(num); // начальный путь по возрастанию
    route final_r = r; // создание конечного значения
    int sum = r.route_price(matrix); // стоймость начального пути
    cout << r << " = " << sum << endl; // вывод начального пути и его стоимость
    while(r.next_route()) {
        int new_sum = r.route_price(matrix); // стоимость следующего пути
        cout << r << " = " << new_sum << endl; // вывод следующего пути и его стоимость
        if(sum > new_sum && new_sum > 0) { // если путь дешевле выбираем его
            sum = new_sum;
            final_r = r;
        }
    }
    cout << "\nBest route : ";
    return final_r; // возвращение лучшего пути
}

int main() {
    cout << "N = ";
    int n;
    cin >> n;
    cout << task(n);
    return 0;
}
