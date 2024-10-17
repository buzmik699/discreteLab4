#include <iostream>
#include <set>
#include <vector>
using namespace std;


// функция для вывода мультимножества на экран (вспомогательная)
void print_set(vector<int> lst) {
    for (int item : lst) cout << item << " "; cout << endl;
}




// функция для нахождения наибольший индекса i, такого что a[i] < a[i + 1] (вспомогательная)
int maxIndexI(const vector<int> lst) {
    int size = lst.size();
    for (int i = size - 1; i >= 1; --i) {
        if (lst[i] > lst[i - 1]) return i-1;
    } return -1;
}

// функция для нахождения наибольшего индекса j, такого что j > i и a[i] < a[j] (вспомогательная)
int maxIndexJ(const vector<int> lst, const int index_i) {
    int size = lst.size();
    if (index_i == -1) return -1;
    for (int j = size - 1; j > index_i; --j) {
        if (lst[index_i] < lst[j]) return j;
    }
}

// функция для разворота последовательности (вспомогательная)
void reverse(int index_i, vector<int> &lst) {
    int size = lst.size();
    vector<int> result_lst;
    for (int i = 0; i <= index_i; ++i) result_lst.push_back(lst[i]);
    for (int i = size-1; i > index_i; --i) result_lst.push_back(lst[i]);
    lst = result_lst;
}

// Функция для определения знака перестановки
int sign_of_permutation(const vector<int>& P) {
    int n = P.size();
    vector<bool> isNew(n, true); // Массив для отслеживания новых элементов
    int s = 1; // Начальный знак перестановки (1 - чётная, -1 - нечётная)

    // Проходим по каждому элементу
    for (int i = 0; i < n; i++) {
        if (isNew[i]) { // Если элемент не был использован в предыдущих циклах
            int j = P[i] - 1; // Запускаем цикл, начиная с элемента P[i]
            isNew[i] = false;  // Помечаем элемент как обработанный
            while (j != i) {
                isNew[j] = false; // Помечаем следующий элемент как обработанный
                s = -s;           // Инвертируем знак
                j = P[j] - 1;     // Переходим к следующему элементу цикла
            }
        }
    }
    return s; // Возвращаем знак перестановки
}

// главная функция для нахождения все перестановок
void permutation(multiset<int> list) {
    vector<int> copy_list;
    for (int item : list) copy_list.push_back(item);
    print_set(copy_list);
    int index_i = maxIndexI(copy_list);
    int index_j = maxIndexJ(copy_list, index_i);
    while (index_j != -1) {
        swap(copy_list[index_i], copy_list[index_j]);
        reverse(index_i, copy_list);
        cout << "Permutation: ";
        print_set(copy_list);
        cout << "Sign: " << sign_of_permutation(copy_list) << endl;
        index_i = maxIndexI(copy_list);
        index_j = maxIndexJ(copy_list, index_i);
    }
}



int main()
{
    multiset<int> list;
    int item{};
    while (cin >> item) list.insert(item);
    permutation(list); 
}

