#include "data.h"
#include "bola.h"

const int RITME_BOLA = 2;   // bola bergerak tiap 2 putaran (makin besar = makin lambat)

// Taruh 1 bola di atas paddle, bola lain nonaktif (P4: for, P6: array)
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
    itemAktif = false;          // item yang lagi jatuh ikut hilang
}

// Geser semua bola yang aktif (P4: for, P6: array)
// Pantulan dan tabrakan diurus di tabrakan.cpp (cekTabrakan)
void updateBola() {
    static int hitung = 0;
    hitung++;
    if (hitung % RITME_BOLA != 0) {
        return;                 // putaran ini bola diam, biar lebih lambat
    }

    for (int i = 0; i < JUMLAH_BOLA; i++) {
        if (bolaAktif[i]) {
            bolaX[i] = bolaX[i] + arahX[i];
            bolaY[i] = bolaY[i] + arahY[i];
        }
    }
}

// P4: loop, P8: fungsi yang mengembalikan nilai
bool semuaBolaJatuh() {
    for (int i = 0; i < JUMLAH_BOLA; i++) {
        if (bolaAktif[i]) {
            return false;       // masih ada yang main
        }
    }
    return true;
}

// P6: array, P8: fungsi yang mengembalikan nilai (jumlah bola baru)
int aktifkanMultiBall() {
    int sumber = -1;            // cari 1 bola yang masih aktif
    for (int i = 0; i < JUMLAH_BOLA; i++) {
        if (bolaAktif[i]) {
            sumber = i;
            break;
        }
    }
    if (sumber == -1) {
        return 0;               // tidak ada bola, tidak bisa multi-ball
    }

    int baru = 0;
    for (int j = 0; j < JUMLAH_BOLA; j++) {
        if (!bolaAktif[j]) {
            bolaAktif[j] = true;
            bolaX[j] = bolaX[sumber];
            bolaY[j] = bolaY[sumber];
            arahX[j] = (baru % 2 == 0) ? -1 : 1;   // satu ke kiri, satu ke kanan
            arahY[j] = -1;
            baru++;
        }
    }
    return baru;
}