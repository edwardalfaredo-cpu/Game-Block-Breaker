#include <iostream>
#include <cstdlib>
#include "data.h"

using namespace std;

// Variabel khusus sistem item
Posisi item;
bool itemAktif = false;

// Pengaturan efek item
const int LEBAR_PADDLE_NORMAL = 5;
const int LEBAR_PADDLE_BESAR = 9;
const int DURASI_EFEK = 180;

// Variabel penghitung waktu
static int penghitungJatuh = 0;
static int sisaDurasi = 0;
static bool efekAktif = false;

// ===============================
// RESET SISTEM ITEM
// ===============================

void resetItem() {
    itemAktif = false;
    penghitungJatuh = 0;
    sisaDurasi = 0;
    efekAktif = false;

    lebarPaddle = LEBAR_PADDLE_NORMAL;
}

// ===============================
// MEMBUAT ITEM
// ===============================

void buatItem(int x, int y) {

    // Jika masih ada item, jangan membuat item baru
    if (itemAktif) {
        return;
    }

    // Peluang item muncul sebesar 20%
    if (rand() % 100 < 20) {

        item.x = x;
        item.y = y;

        itemAktif = true;
        penghitungJatuh = 0;
    }
}

// ===============================
// UPDATE PERGERAKAN ITEM
// ===============================

void updateItem() {

    // Menghitung durasi efek paddle
    if (efekAktif) {

        sisaDurasi--;

        if (sisaDurasi <= 0) {

            lebarPaddle = LEBAR_PADDLE_NORMAL;

            if (posisiPaddle + lebarPaddle > LEBAR_LAYAR) {
                posisiPaddle = LEBAR_LAYAR - lebarPaddle;
            }

            efekAktif = false;
        }
    }

    // Jika tidak ada item, hentikan proses
    if (!itemAktif) {
        return;
    }

    // Item jatuh setiap 3 putaran game
    penghitungJatuh++;

    if (penghitungJatuh >= 3) {
        item.y++;
        penghitungJatuh = 0;
    }

    // Periksa apakah item ditangkap paddle
    if (
        item.y >= TINGGI_LAYAR - 1 &&
        item.x >= posisiPaddle &&
        item.x < posisiPaddle + lebarPaddle
    ) {

        // Aktifkan efek paddle besar
        lebarPaddle = LEBAR_PADDLE_BESAR;

        if (posisiPaddle + lebarPaddle > LEBAR_LAYAR) {
            posisiPaddle = LEBAR_LAYAR - lebarPaddle;
        }

        efekAktif = true;
        sisaDurasi = DURASI_EFEK;

        itemAktif = false;
    }

    // Item hilang jika jatuh melewati paddle
    else if (item.y >= TINGGI_LAYAR) {
        itemAktif = false;
    }
}