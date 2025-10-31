#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

// Funkcja sortująca (sortowanie bąbelkowe)
void sort_bubble(int* tablica, int rozmiar) {
    for (int i = 0; i < rozmiar - 1; i++) {
        for (int j = 0; j < rozmiar - i - 1; j++) {
            if (tablica[j] > tablica[j + 1]) {
                swap(tablica[j], tablica[j + 1]);
            }
        }
    }
}

// Tworzenie tablicy dynamicznej lub statycznej
int* utworzTablice(int rozmiar, bool dynamiczna) {
    if (dynamiczna) {
        cout << "Tworze tablice dynamiczna ... " << endl;
        return new int[rozmiar];
    }
    else {
        cout << "Tworze tablice statyczna ... " << endl;
        static int tablica[100000]; // Zwiększaj rozmiar do testu Stack Overflow
        return tablica;
    }
}

// Test poprawności danych
bool czyTablicaPoprawna(int* tablica, int rozmiar, int MIN, int MAX) {
    if (!tablica) return false;
    for (int i = 0; i < rozmiar; i++) {
        if (tablica[i] < MIN || tablica[i] > MAX) return false;
    }
    return true;
}

// Test sortowania
bool czyTablicaPosortowana(int* tablica, int rozmiar) {
    for (int i = 1; i < rozmiar; i++) {
        if (tablica[i - 1] > tablica[i]) return false;
    }
    return true;
}

// Test funkcjonalny
bool testFunkcjonalny(int* tablica, int rozmiar, int MIN, int MAX) {
    return czyTablicaPoprawna(tablica, rozmiar, MIN, MAX) &&
        czyTablicaPosortowana(tablica, rozmiar);
}

// Pomiar czasu sortowania
void testSortowania(int rozmiar, bool dynamiczna, int MIN, int MAX) {
    int* tablica = utworzTablice(rozmiar, dynamiczna);

    srand(time(nullptr));
    for (int i = 0; i < rozmiar; i++)
        tablica[i] = rand() % (MAX + 1);

    auto start = high_resolution_clock::now();
    sort_bubble(tablica, rozmiar);
    auto end = high_resolution_clock::now();

    long long czas = duration_cast<microseconds>(end - start).count();
    cout << "Czas sortowania: " << czas << " mikrosekund" << endl;

    if (testFunkcjonalny(tablica, rozmiar, MIN, MAX))
        cout << "✓ Test funkcjonalny zaliczony" << endl;
    else
        cout << "✗ Test funkcjonalny niezaliczony" << endl;

    if (dynamiczna) delete[] tablica;
}


int main() {
    testSortowania(10000, true, 0, 1000);   // dynamiczna
    testSortowania(10000, false, 0, 1000);  // statyczna
    return 0;
}