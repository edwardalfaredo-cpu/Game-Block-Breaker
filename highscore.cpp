#include <iostream>
#include <fstream>
#include <sstream>
#include "highscore.h"

using namespace std;

// Membaca data High Score
int muatHighScore(DataHighScore data[], int kapasitas) {

    ifstream file("highscore.txt");

    if (!file.is_open()) {
        return 0;
    }

    int jumlah = 0;
    string baris;

    while (getline(file, baris) && jumlah < kapasitas) {

        stringstream ss(baris);

        string nama;
        int nilai;

        if (getline(ss, nama, '|') && ss >> nilai) {

            data[jumlah].nama = nama;
            data[jumlah].skor = nilai;

            jumlah++;
        }
    }

    file.close();

    return jumlah;
}

// Mencari pemain berdasarkan nama
int cariPemain(
    DataHighScore data[],
    int jumlah,
    const string& nama
) {

    for (int i = 0; i < jumlah; i++) {

        if (data[i].nama == nama) {
            return i;
        }
    }

    return -1;
}

// Mengurutkan skor dari tertinggi ke terendah
void urutkanHighScore(
    DataHighScore data[],
    int jumlah
) {

    for (int i = 0; i < jumlah - 1; i++) {

        for (int j = 0; j < jumlah - i - 1; j++) {

            if (data[j].skor < data[j + 1].skor) {

                DataHighScore sementara = data[j];

                data[j] = data[j + 1];

                data[j + 1] = sementara;
            }
        }
    }
}

// Menyimpan skor pemain
bool simpanHighScore(
    const string& nama,
    int skor
) {

    if (nama.empty() || nama.find('|') != string::npos) {
        return false;
    }

    DataHighScore data[MAX_HIGH_SCORE];

    int jumlah = muatHighScore(data, MAX_HIGH_SCORE);

    int index = cariPemain(data, jumlah, nama);

    if (index != -1) {

        // Perbarui hanya jika skor baru lebih tinggi
        if (skor > data[index].skor) {
            data[index].skor = skor;
        }

    } else {

        if (jumlah >= MAX_HIGH_SCORE) {
            return false;
        }

        data[jumlah].nama = nama;
        data[jumlah].skor = skor;

        jumlah++;
    }

    urutkanHighScore(data, jumlah);

    ofstream file("highscore.txt");

    if (!file.is_open()) {
        return false;
    }

    for (int i = 0; i < jumlah; i++) {

        file << data[i].nama
             << "|"
             << data[i].skor
             << "\n";
    }

    file.close();

    return true;
}