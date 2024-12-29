#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

int hitungRataRataIteratif(int harga[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += harga[i];
    }
    return (n == 0) ? 0 : total / n;
}

int hitungTotalRekursif(int harga[], int n) {
    if (n == 0) return 0; // Base case
    return harga[n - 1] + hitungTotalRekursif(harga, n - 1);
}

int hitungRataRataRekursif(int harga[], int n) {
    if (n == 0) return 0;
    int total = hitungTotalRekursif(harga, n);
    return total / n;
}

int main() {
    cout << "Berapa banyak harga yang mau anda buat? ";
    int amount;
    cin >> amount;

    if (amount <= 0) {
        cout << "Jumlah harga harus lebih dari 0.\n";
        return 1;
    }

    srand(time(0));
    int* priceList = new int[amount]; // Menggunakan alokasi dinamis

    for (int i = 0; i < amount; i++) {
        priceList[i] = rand() % 19001 + 1000; // Range [1000, 20000]
    }

    int iterations = 1000; // Jumlah iterasi untuk meningkatkan akurasi pengukuran waktu

    cout << "Mulai iteratif...\n";
    auto startIteratif = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        hitungRataRataIteratif(priceList, amount);
    }
    auto endIteratif = high_resolution_clock::now();
    auto durasiIteratif = duration_cast<milliseconds>(endIteratif - startIteratif);
    cout << "Iteratif selesai.\n";

    cout << "Mulai rekursif...\n";
    auto startRekursif = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        hitungRataRataRekursif(priceList, amount);
    }
    auto endRekursif = high_resolution_clock::now();
    auto durasiRekursif = duration_cast<milliseconds>(endRekursif - startRekursif);
    cout << "Rekursif selesai.\n";

    cout << fixed << setprecision(6); // Menampilkan enam angka di belakang koma
    cout << "Waktu Eksekusi Iteratif per Iterasi: " << (durasiIteratif.count() / static_cast<double>(iterations)) << " milliseconds.\n";
    cout << "Waktu Eksekusi Rekursif per Iterasi: " << (durasiRekursif.count() / static_cast<double>(iterations)) << " milliseconds.\n";

    delete[] priceList; // Membersihkan memori yang dialokasikan dinamis
    return 0;
}
