/*
[1, 1, 1] -> [1, 1, 1]
[1, 2, 1, null, 2] -> [1, 2, 1, 1, 2]
[1, 2, null] -> [1, 2, 1]
[1, 2, -1] -> [1, 2, 1]
[1, 1, 1, null] -> [1, 1, 1, 1]

counter:
                [0, 1, 2] - уникальные значений
[0, 1, 2, 1] -> [1, 2, 1] - сколько раз уникальное значение встретилось
                {0: 1, 1: 2, 2: 1}
                [1, 2, 1]

1. Что будем вставлять
2. Куда будем вставлять

*/
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

// ! const int arr[] - почему нельзя
std::vector<int> impute(const unsigned char arr[], const int size) {
    // 4 * size + 4 байта

    // 1. Что будем вставлять
    // [1, 1, 0, 0, 0], от 0 до 5 [0, 1, 2, 3, 4]
    // число -> кол-во повторений
    std::vector<int> counter(120, 0); // [0, 0, 0, 0, ..., 0] (120)  // 24 + 120 * 4 байт

    for (int i = 0; i < size; i++) {
        // 4 байта (i)
        int counter_index = arr[i];  // берем значение из массива, где i - ключ // 4 байта
        counter[counter_index]++;  // По индексу увеличиваем значение counter
    }

    // Найти число, которое встречается наибольшее число раз
    int max_index = 0;  // Число  4 байта
    int max_count = 0;  // сколько раз число max_index встретилось  4 байта
    for (int i = 1; i < size; i++) {
        // 4 байта
        if (counter[i] > max_count) {
            max_index = i;
            max_count = counter[i];
        }
    }

    // 2. Что будем вставлять
    std::vector<int> out(size);  // 4 * size + 24 байта
    for (int i = 0; i < size; i++) {
        // 4 байта
        if (arr[i] > 0) {
            out[i] = arr[i];
        } else {
            out[i] = max_index;
        }
    }

    // 4 * size + 4 байта
    // + 24 + 120 * 4 байт
    // + 8
    // + 4 * size + 24 байта
    // ==

    return out;
}

bool compare_vector(const std::vector<int> &arr, const std::vector<int> &out) {
    return std::equal(arr.begin(), arr.end(), out.begin());
}

void print_vector(std::string prefix, const std::vector<int> &vec) {
    std::cout << prefix;
    for (auto val : vec) {
        std::cout << " " << val;
    }
    std::cout << std::endl;
}


int main() {
    int n = 8;
    const unsigned char arr[] = {8,5,1,0,4,2,0,2};

    vector<int> a = impute(arr, n);
    print_vector("a", a);
    return 0;
}