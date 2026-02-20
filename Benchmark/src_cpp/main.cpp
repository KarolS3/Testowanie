#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <limits>


std::vector<int> load_data_from_csv(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Nie mogę otworzyć pliku: " + filename);
    }

    std::vector<int> data;
    std::string line;


    if (!std::getline(in, line)) {
        throw std::runtime_error("Plik pusty lub brak nagłówka: " + filename);
    }


    while (std::getline(in, line)) {
        if (line.empty()) continue;
        int value = std::stoi(line);
        data.push_back(value);
    }

    if (data.empty()) {
        throw std::runtime_error("Brak danych w pliku: " + filename);
    }

    return data;
}


bool is_sorted_non_decreasing(const std::vector<int>& v) {
    return std::is_sorted(v.begin(), v.end());
}


void benchmark_sort(
    const std::string& language,
    const std::string& algorithm_name,
    const std::string& filename,
    int repetitions
) {

    std::vector<int> original_data = load_data_from_csv(filename);
    const std::size_t data_size = original_data.size();

    std::vector<double> times_ms;
    times_ms.reserve(repetitions);

    for (int i = 0; i < repetitions; ++i) {
        std::vector<int> data = original_data;

        auto start = std::chrono::high_resolution_clock::now();


        std::sort(data.begin(), data.end());

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> diff = end - start;
        times_ms.push_back(diff.count());

        if (!is_sorted_non_decreasing(data)) {
            std::cerr << "BŁĄD: Dane nie są posortowane poprawnie w powtórzeniu "
                      << i << " dla pliku: " << filename << std::endl;
            return;
        }
    }

 
    double sum = 0.0;
    double min_t = std::numeric_limits<double>::max();
    double max_t = std::numeric_limits<double>::lowest();

    for (double t : times_ms) {
        sum += t;
        if (t < min_t) min_t = t;
        if (t > max_t) max_t = t;
    }

    double avg = sum / static_cast<double>(repetitions);


    std::cout << language << ";"
              << algorithm_name << ";"
              << data_size << ";"
              << avg << ";"
              << repetitions << ";"
              << min_t << ";"
              << max_t
              << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Użycie: " << argv[0]
                  << " <plik_csv_z_danymi> [liczba_powtórzeń]" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    int repetitions = 5;

    if (argc >= 3) {
        repetitions = std::stoi(argv[2]);
        if (repetitions <= 0) {
            std::cerr << "Liczba powtórzeń musi być > 0" << std::endl;
            return 1;
        }
    }

    try {
        benchmark_sort("C++", "sort", filename, repetitions);
    } catch (const std::exception& ex) {
        std::cerr << "Wyjątek: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
