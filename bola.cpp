// bola.cpp  --  Bagian 1: Gerak bola
#include "data.h"
#include "bola.h"

// Taruh 1 bola di atas paddle, bola lain nonaktif (P4: for, P6: array)
void resetBola() {
    for (int i = 0; i < JUMLAH_BOLA; i++) {
        bolaAktif[i] = false;
        bolaX[i] = 0;
        bolaY[i] = 0;
        bolaDX[i] = 1;
        bolaDY[i] = -1;
    }
    bolaAktif[0] = true;
    bolaX[0] = paddleX + LEBAR_PADDLE / 2;
    bolaY[0] = TINGGI_ARENA - 2;
}

// Geser semua bola yang aktif (P4: for, P6: array)
void updateBola() {
    for (int i = 0; i < JUMLAH_BOLA; i++) {
        if (bolaAktif[i]) {
            bolaX[i] = bolaX[i] + bolaDX[i];
            bolaY[i] = bolaY[i] + bolaDY[i];

            // sementara: keluar arena = jatuh (pantulan dibuat di bagian 2)
            if (bolaX[i] < 0 || bolaX[i] >= LEBAR_ARENA ||
                bolaY[i] < 0 || bolaY[i] >= TINGGI_ARENA) {
                bolaAktif[i] = false;
            }
        }
    }
}

// P4: loop, P8: fungsi yang mengembalikan nilai
bool semuaBolaJatuh() {
    for (int i = 0; i < JUMLAH_BOLA; i++) {
        if (bolaAktif[i]) {
            return false;   // masih ada yang main
        }
    }
    return true;
}

// P6: array, P8: fungsi yang mengembalikan nilai (jumlah bola baru)
int aktifkanMultiBall() {
    int sumber = -1;                       // cari 1 bola yang masih aktif
    for (int i = 0; i < JUMLAH_BOLA; i++) {
        if (bolaAktif[i]) {
            sumber = i;
            break;
        }
    }
    if (sumber == -1) {
        return 0;                          // tidak ada bola, tidak bisa multi-ball
    }

    int baru = 0;
    for (int j = 0; j < JUMLAH_BOLA; j++) {
        if (!bolaAktif[j]) {
            bolaAktif[j] = true;
            bolaX[j] = bolaX[sumber];
            bolaY[j] = bolaY[sumber];
            bolaDX[j] = (baru % 2 == 0) ? -1 : 1;   // satu ke kiri, satu ke kanan
            bolaDY[j] = -1;
            baru++;
        }
    }
    return baru;
}