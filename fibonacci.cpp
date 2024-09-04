#include <iostream>
#include <pthread.h>
#include <vector>

struct FibonacciData {
    int limit;
    std::vector<int> fibonacciNumbers;
    int sum;
};

void* calculateFibonacci(void* arg) {
    FibonacciData* data = (FibonacciData*)arg;
    int a = 0, b = 1, next = 0;
    data->fibonacciNumbers.push_back(a);
    data->fibonacciNumbers.push_back(b);

    while (next <= data->limit) {
        next = a + b;
        if (next > data->limit) break;
        data->fibonacciNumbers.push_back(next);
        a = b;
        b = next;
    }

    data->sum = 0;
    for (int num : data->fibonacciNumbers) {
        data->sum += num;
    }

    pthread_exit(NULL);
}

int main() {
    int limit;
    std::cout << "Ingrese un numero entre 0 y 100: ";
    std::cin >> limit;

    if (limit < 0 || limit > 100) {
        std::cerr << "El numero debe estar entre 0 y 100." << std::endl;
        return 1;
    }

    FibonacciData data;
    data.limit = limit;

    pthread_t thread;
    pthread_create(&thread, NULL, calculateFibonacci, (void*)&data);
    pthread_join(thread, NULL);

    std::cout << "Numeros de la serie Fibonacci hasta " << limit << ":" << std::endl;
    for (size_t i = 0; i < data.fibonacciNumbers.size(); ++i) {
        std::cout << "F" << i << " = " << data.fibonacciNumbers[i] << std::endl;
    }

    std::cout << "Suma total de los numeros de Fibonacci encontrados: " << data.sum << std::endl;

    return 0;
}