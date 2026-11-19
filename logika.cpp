#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// ===============================
// BAGIAN 1: ISI DAN RESET BALOK
// ===============================

const int BARIS = 5;
const int KOLOM = 8;

bool balok[BARIS][KOLOM];

// Mengisi semua balok
void isiBalok() {
    for (int i = 0; i < BARIS; i++) {
        for (int j = 0; j < KOLOM; j++) {
            balok[i][j] = true;
        }
    }
}

// Mereset semua balok
void resetBalok() {
    for (int i = 0; i < BARIS; i++) {
        for (int j = 0; j < KOLOM; j++) {
            balok[i][j] = true;
        }
    }
}

// Menghitung jumlah balok yang tersisa
int hitungBalok() {
    int jumlah = 0;

    for (int i = 0; i < BARIS; i++) {
        for (int j = 0; j < KOLOM; j++) {
            if (balok[i][j] == true) {
                jumlah++;
            }
        }
    }

    return jumlah;
}

// Menghancurkan balok
void hancurkanBalok(int baris, int kolom) {
    if (baris >= 0 && baris < BARIS &&
        kolom >= 0 && kolom < KOLOM) {

        balok[baris][kolom] = false;
    }
}

// Menampilkan kondisi balok
void tampilBalok() {
    for (int i = 0; i < BARIS; i++) {
        for (int j = 0; j < KOLOM; j++) {
            if (balok[i][j]) {
                cout << "[B] ";
            } else {
                cout << "[ ] ";
            }
        }
        cout << endl;
    }
}