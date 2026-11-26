#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>

const int MAX_HIGH_SCORE = 100;

struct DataHighScore {
    std::string nama;
    int skor;
};

int muatHighScore(
    DataHighScore data[],
    int kapasitas
);

bool simpanHighScore(
    const std::string& nama,
    int skor
);

void urutkanHighScore(
    DataHighScore data[],
    int jumlah
);

int cariPemain(
    DataHighScore data[],
    int jumlah,
    const std::string& nama
);

#endif