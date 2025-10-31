#include <iostream>
#include <vector>
#include <chrono> // do mierzenia czasu
#include <cstdlib> // do losowania liczb
using namespace std;
int main() {
	cout << "Porownanie sortowania babelkowego: indeksy vs wskazniki\n";
	const int N = 1000; // liczba elementów
	vector<int> dane(N);
	srand(123); // stałe ziarno losowania
	for (int i = 0; i < N; i++) {
		dane[i] = rand() % 10000;
	}
	vector<int> dane_kopia = dane; // kopia dla drugiego testu
	auto start1 = chrono::high_resolution_clock::now();
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N - 1 - i; j++) {
			if (dane[j] > dane[j + 1]) {
				int temp = dane[j];
				dane[j] = dane[j + 1];
				dane[j + 1] = temp;
			}
		}
	}
	auto stop1 = chrono::high_resolution_clock::now();
	auto czas1 = chrono::duration_cast<chrono::milliseconds>(stop1 - start1).count();
	cout << "Czas sortowania (indeksy): " << czas1 << " ms\n";
	int* tab = dane_kopia.data(); // wskaźnik do pierwszego elementu
	auto start2 = chrono::high_resolution_clock::now();
	for (int i = 0; i < N - 1; i++) {
		for (int* p = tab; p < tab + (N - 1 - i); p++) {
			if (*p > *(p + 1)) {
				int temp = *p;
				*p = *(p + 1);
				*(p + 1) = temp;
			}
		}
	}
	auto stop2 = chrono::high_resolution_clock::now();
	auto czas2 = chrono::duration_cast<chrono::milliseconds>(stop2 - start2).count();
	cout << "Czas sortowania (wskazniki): " << czas2 << " ms\n";
	cout << "Koniec programu." << endl;
	return 0;
}