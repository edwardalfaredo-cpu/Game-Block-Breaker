#include "data.h"
#include "bola.h"
#include "tabrakan.h"

int hitungItem = 0;     // penghitung putaran untuk mengatur kecepatan jatuh item

// ---------------- balok (array 2 dimensi) ----------------

// Mengisi balok: 1 = biasa, 2 = item +Waktu, 3 = item Multi-Ball
void initBalok() {
    for (int i = 0; i < BARIS_BALOK; i++) {
        for (int j = 0; j < KOLOM_BALOK; j++) {
            int kode = (i * 3 + j) % 7;
            if (kode == 2) {
                balok[i][j] = 2;
            } else if (kode == 5) {
                balok[i][j] = 3;
            } else {
                balok[i][j] = 1;
            }
        }
    }
}

// true kalau semua balok sudah hancur
bool blokHabis() {
    for (int i = 0; i < BARIS_BALOK; i++) {
        for (int j = 0; j < KOLOM_BALOK; j++) {
            if (balok[i][j] > 0) {
                return false;
            }
        }
    }
    return true;
}

// ---------------- fungsi pembantu (parameter + nilai balik) ----------------

// true kalau posisi x berada di atas paddle
bool diAtasPaddle(int x) {
    return x >= paddleX && x < paddleX + LEBAR_PADDLE;
}

// true kalau di baris dan kolom itu masih ada balok
bool adaBalok(int baris, int kolom) {
    bool ada = false;
    if (baris >= 0 && baris < BARIS_BALOK && kolom >= 0 && kolom < KOLOM_BALOK) {
        if (balok[baris][kolom] > 0) {
            ada = true;
        }
    }
    return ada;
}

// ---------------- balok hancur ----------------

// Balok hancur, skor naik, kalau balok bertanda (2 atau 3) munculkan item
void hancurkanBalok(int baris, int kolom) {
    int jenis = balok[baris][kolom];

    if (jenis >= 2 && !itemAktif) {
        itemAktif = true;
        itemJenis = jenis;
        itemX = kolom * LEBAR_BALOK + 2;    // tengah balok
        itemY = baris + 1;                  // aturan data.h: y = baris + 1
    }
    balok[baris][kolom] = 0;
    skor = skor + 10;
}

// ---------------- pantulan ----------------

// Pantul di dinding kiri, kanan, dan atas
void pantulDinding(int i) {
    if (bolaX[i] < 0 || bolaX[i] >= LEBAR_ARENA) {
        arahX[i] = -arahX[i];
        bolaX[i] = bolaX[i] + 2 * arahX[i];     // dipantulkan balik ke dalam arena
    }
    if (bolaY[i] < 0) {
        arahY[i] = -arahY[i];
        bolaY[i] = bolaY[i] + 2 * arahY[i];
    }
}

// Pantul di paddle (nested if), atau bola jatuh kalau lewat paddle
void pantulPaddle(int i) {
    int yPaddle = TINGGI_ARENA - 1;

    if (bolaY[i] == yPaddle && arahY[i] > 0) {
        if (diAtasPaddle(bolaX[i])) {
            arahY[i] = -1;
            bolaY[i] = yPaddle - 1;
            if (bolaX[i] < paddleX + LEBAR_PADDLE / 3) {
                arahX[i] = -1;                  // ujung kiri paddle -> ke kiri
            } else if (bolaX[i] >= paddleX + 2 * LEBAR_PADDLE / 3) {
                arahX[i] = 1;                   // ujung kanan paddle -> ke kanan
            }
        }
    } else if (bolaY[i] > yPaddle) {
        bolaAktif[i] = false;                   // bola jatuh
    }
}

// ---------------- tabrakan dengan balok ----------------

void tabrakBalok(int i) {
    int baris = bolaY[i] - 1;
    int kolom = bolaX[i] / LEBAR_BALOK;

    if (adaBalok(baris, kolom)) {
        hancurkanBalok(baris, kolom);
        arahY[i] = -arahY[i];
        bolaY[i] = bolaY[i] + arahY[i];         // balik ke posisi sebelum nabrak
    }
}

// ---------------- item jatuh ----------------

void gerakItem() {
    if (itemAktif) {
        hitungItem++;
        if (hitungItem % 4 == 0) {              // item lebih lambat dari bola
            itemY++;
            if (itemY >= TINGGI_ARENA - 1) {
                if (diAtasPaddle(itemX)) {
                    if (itemJenis == 3) {
                        aktifkanMultiBall();
                    } else {
                        waktuSisa = waktuSisa + 5 * PUTARAN_PER_DETIK;   // +Waktu
                    }
                }
                itemAktif = false;
            }
        }
    }
}

// ---------------- dipanggil tiap putaran ----------------

void cekTabrakan() {
    for (int i = 0; i < JUMLAH_BOLA; i++) {
        if (bolaAktif[i]) {
            pantulDinding(i);
            pantulPaddle(i);
            if (bolaAktif[i]) {
                tabrakBalok(i);
            }
        }
    }
    gerakItem();
}