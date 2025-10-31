#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std::chrono;


void fill_random(int* tab, int n, unsigned int seed) {
	srand(seed);
	for (int i = 0; i < n; i++) {
		tab[i] = rand() % 1000;
	}
}
void fill_sorted(int* tab, int n) {
	for (int i = 0; i < n; i++) {
		tab[i] = i;
	}
}
void fill_reversed(int* tab, int n) {
	for (int i = 0; i < n; i++) {
		tab[i] = n - i;
	}
}

void bubble_sort(int* tab, int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (tab[j] > tab[j + 1]) {
				std::swap(tab[j], tab[j + 1]);
			}
		}
	}
}

long long measure_time(int* tab, int n) {
	auto start = high_resolution_clock::now();
	bubble_sort(tab, n);
	auto end = high_resolution_clock::now();
	return duration_cast<microseconds>(end - start).count();
}

int main() {
	const int N = 5000;
	int* tab = new int[N];
	fill_sorted(tab, N);
	std::cout << "Posortowana: " << measure_time(tab, N) << " us\n";
	fill_reversed(tab, N);
	std::cout << "Odwrotnie: " << measure_time(tab, N) << " us\n";
	fill_random(tab, N, 300);
	std::cout << "Losowa: " << measure_time(tab, N) << " us\n";
	delete[] tab;
}