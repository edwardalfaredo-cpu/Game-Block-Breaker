#include "data.h"
#include "bola.h"

const int RITME_BOLA = 2;   // bola bergerak tiap 2 putaran (makin besar = makin lambat)
int hitungBola = 0;         // penghitung putaran untuk mengatur kecepatan bola

// Mencari bola yang masih aktif.
// Mengembalikan nomor bolanya, atau -1 kalau tidak ada.
int cariBolaAktif() {
    for (int i = 0; i < JUMLAH_BOLA; i++) {
        if (bolaAktif[i]) {
            return i;
        }
    }
    return -1;
}

// Taruh 1 bola di atas paddle, bola lain nonaktif
void resetBola() {
    for (int i = 0; i < JUMLAH_BOLA; i++) {
        bolaAktif[i] = false;
        bolaX[i] = 0;
        bolaY[i] = 0;
        arahX[i] = 1;
        arahY[i] = -1;
    }
    bolaAktif[0] = true;
    bolaX[0] = paddleX + LEBAR_PADDLE / 2;
    bolaY[0] = TINGGI_ARENA - 2;
    itemAktif = false;      // item yang lagi jatuh ikut hilang
}

// Geser semua bola yang aktif.
// Pantulan dan tabrakan diurus di tabrakan.cpp (cekTabrakan)
void updateBola() {
    hitungBola++;
    if (hitungBola % RITME_BOLA == 0) {     // bola hanya bergerak di putaran tertentu
        for (int i = 0; i < JUMLAH_BOLA; i++) {
            if (bolaAktif[i]) {
                bolaX[i] = bolaX[i] + arahX[i];
                bolaY[i] = bolaY[i] + arahY[i];
            }
        }
    }
}

// Cek apakah semua bola sudah jatuh (fungsi dengan nilai balik)
bool semuaBolaJatuh() {
    for (int i = 0; i < JUMLAH_BOLA; i++) {
        if (bolaAktif[i]) {
            return false;       // masih ada bola yang main
        }
    }
    return true;
}

// Mengaktifkan bola yang belum aktif, dimulai dari posisi bola yang sedang main.
// Mengembalikan jumlah bola baru.
int aktifkanMultiBall() {
    int baru = 0;
    int sumber = cariBolaAktif();

    if (sumber != -1) {
        for (int j = 0; j < JUMLAH_BOLA; j++) {
            if (!bolaAktif[j]) {
                bolaAktif[j] = true;
                bolaX[j] = bolaX[sumber];
                bolaY[j] = bolaY[sumber];
                arahX[j] = (baru % 2 == 0) ? -1 : 1;    // satu ke kiri, satu ke kanan
                arahY[j] = -1;
                baru++;
            }
        }
    }
    return baru;
}