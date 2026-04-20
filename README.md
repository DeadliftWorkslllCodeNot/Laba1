# Лабораторная работа №1

**Выполнила:** Пермякова Екатерина Алексеевна, ИДБ-25-02

---

## 📋 Содержание

1. [Проверка наличия элемента](#1-проверка-наличия-элемента-в-массиве)
2. [Поиск второго максимального элемента](#2-поиск-второго-максимального-элемента-массива)
3. [Бинарный поиск](#3-бинарный-поиск)
4. [Таблица умножения](#4-построение-таблицы-умножения)
5. [Поразрядная сортировка](#5-поразрядная-сортировка-radix-sort)

---

## 1. Проверка наличия элемента в массиве

**Алгоритмическая сложность:** O(n)

### 📊 Результаты тестирования

| Размер массива | Искомый элемент | Результат | Время (сек) |
|---------------|----------------|-----------|-------------|
| 10            | 42             | found     | 0.00000200  |
| 100           | 42             | found     | 0.00001500  |
| 1000          | 42             | not found | 0.00012000  |
| 10000         | 42             | not found | 0.00120000  |

> **Вывод:** Время растет линейно с увеличением размера массива.

### 💻 Код функции

```c
bool find_el(int* mass, int size, int num) {
    for (int i = 0; i < size; i++) {
        if (mass[i] == num) return true;
    }
    return false;
}

## 2. Поиск второго максимального элемента массива
Алгоритмическая сложность: O(n)

Результаты тестирования
Размер массива	Второй максимум	Время (сек)
10	998	0.00000100
100	999	0.00000800
1000	997	0.00008000
10000	999	0.00080000
1000000	999	0.08000000
Вывод: Алгоритм проходит по массиву один раз, время растет линейно O(n).

Код функции
c
int find_sec_max(int* mass, int size) {
    int max1 = mass[0], max2 = mass[0];
    for (int i = 0; i < size; i++) {
        if (mass[i] > max1) {
            max2 = max1;
            max1 = mass[i];
        }
        else if (mass[i] > max2 && mass[i] != max1) {
            max2 = mass[i];
        }
    }
    return max2;
}

## 3. Бинарный поиск

**Алгоритмическая сложность:** O(log(n))

### 📊 Результаты тестирования

 Size         | Total time
--------------|---------------
 10           | 1.00000000
 100          | 1.00000000
 1000         | 1.00000000

 **Вывод:** Время растет линейно с увеличением размера массива.

### 💻 Код функции

```c
bool binary_search(int* mass, int l, int r, int el) {
	while (l <= r) {
		int mid = l + (r - l) / 2;

		if (mass[mid] == el)
			return true;

		else if (mass[mid] < el)
			l = mid + 1;

		else r = mid - 1;
	}
	return false;
}

## 4. Построение таблицы умножения

**Алгоритмическая сложность:** O(n^2)

### 📊 Результаты тестирования

 Size         | Total time
--------------|---------------
 10*10        | 2.00000000
 100*100      | 3.00000000
 1000 * 10000 | 55.0

 **Вывод:** Время растет линейно с увеличением размера массива.

### 💻 Код функции

```c
void create_table(int n) {
	for (int i = 1; i <= n;i++) {
		for ( int j = 1; j <= n ;j++) {
			printf("%3d ", i*j);
		}
		printf("\n");
    }
}

## 5. Поразрядная сортировка (Radix Sort)

**Алгоритмическая сложность:** O(n × k), где k — количество разрядов

### 📊 Результаты тестирования

| Размер массива | Время (сек) | Память (байт) | Количество разрядов (k) |
|----------------|-------------|---------------|-------------------------|
| 10             | 0.000003    | 80            | 3                       |
| 100            | 0.000025    | 440           | 3                       |
| 1 000          | 0.000250    | 4 040         | 4                       |
| 10 000         | 0.002800    | 40 040        | 5                       |
| 100 000        | 0.035000    | 400 040       | 6                       |
| 1 000 000      | 0.420000    | 4 000 040     | 7                       |

> **Вывод:** Время растет линейно O(n). При увеличении размера массива в 10 раз, время увеличивается примерно в 10 раз. Память также растет линейно O(n).

### 💻 Код функции
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
