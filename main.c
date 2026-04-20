#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>


## 1. Проверка наличия элемента в массиве

**Алгоритмическая сложность:** \( O(n) \)

### Код функции:
```С
bool find_el(int* mass, int size, int num) {
	for (int i = 0; i < size; i++) {
		if (mass[i] == num) return true;
	}
	return false;
}

---
## 2. Поиск второго максимального элемента массива

**Алгоритмическая сложность:** \( O(n) \)

### Код функции:
```С

int find_sec_max(int *mass, int size) {
	int max1 = mass[0], max2 = mass[0];
	for (int i = 0; i < size;i++) {
		if (mass[i] > max1) {
			max2=max1;
			max1 = mass[i];
		}
		else if (mass[i]>max2 && mass[i]!=max1) {
			max2 = mass[i];
		}
	}
	return max2;
}


## 3. Бинарный поиск

**Алгоритмическая сложность:** \( O(log(n)) \)

### Код функции:
```С
void fill_sort_rand(int* mass, int size, int min, int max) {
    mass[0] = min + rand() % ((max - min) / 2 + 1);

    for (int i = 1; i < size; i++) {
        int step = 1 + rand() % ((max - mass[i - 1]) / (size - i + 1) + 1);
        mass[i] = step + mass[i - 1];
        if (mass[i] > max) {
            mass[i] = max - rand() % (max / (size - i + 1));
        }
    }
}

bool binary_search(int* mass, int l, int r, int el) {
    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (mass[mid] == el)
            return true;
        else if (mass[mid] < el)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return false;
}

## 4. Построение таблицы умножения

**Алгоритмическая сложность:** \( O(n^2) \)

### Код функции:
```С
void table(int n) {
    int t;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            t= i * j;
        }
    }
}


## 5. Radix sort

**Алгоритмическая сложность:** \( O(n*k) \)

### Код функции:
```С
int find_max(int* mass, int size) {
    int max = mass[0];
    for (int i = 1; i < size; i++) {
        if (mass[i] > max) {
            max = mass[i];
        }
    }
    return max;
}

void counting_sort_by_digit(int* mass, int size, int exp) {
    int* output = (int*)malloc(size * sizeof(int));
    int count[10] = { 0 };

    for (int i = 0; i < size; i++) {
        int digit = (mass[i] / exp) % 10;
        count[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        int digit = (mass[i] / exp) % 10;
        output[count[digit] - 1] = mass[i];
        count[digit]--;
    }

    for (int i = 0; i < size; i++) {
        mass[i] = output[i];
    }

    free(output);
}

void radix_sort(int* mass, int size) {
    if (size <= 1) return;

    int max_val = find_max(mass, size);

    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        counting_sort_by_digit(mass, size, exp);
    }
}


void measure_radix_sort(int* mass, int size) {
    
    clock_t start = clock();
    radix_sort(mass, size);
    clock_t end = clock();

    double time_sec = (double)(end - start) / CLOCKS_PER_SEC;

    size_t memory_bytes = size * sizeof(int) + 40;

    printf("| %-10d | %-15.8f | %-15zu |\n", size, time_sec, memory_bytes);
}


## функция автоматического заполнения
```С
void fill_rand(int arr[], int size, int min, int max) {
	for (int i = 0; i < size; i++) {
		arr[i] = min + rand() % (max - min + 1);
	}
## функция подсчета времени
```С
double measure_time(int* mass, int size, int num, bool* result) {
	clock_t start = clock();
	*result = function;
	clock_t end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC;
}

## main
```С
int main() {
	int sizes[] = { 10, 100, 1000, 10000 };
	int num_s = sizeof(sizes) / sizeof(*sizes);

	srand(time(NULL));

	printf("| %-10s | %-15s | %-15s |\n", "Size", "Time (sec)", "Memory (bytes)");
   	printf("|------------|-----------------|-----------------|\n");

	for (int i = 0; i < num_s; i++) {
		int size = sizes[i];
		int* mass = (int*)malloc(size * sizeof(int));
		if (mass == NULL) {
			printf("Memory allocation error for size %d\n", size);
			continue;
		}

		fill_rand();
		bool found;
		double search_time = measure_time();

		
		free(mass);
	}
}
