#include <iostream>
#include <cstdlib>
#include "data.h"

using namespace std;

Posisi item;
bool itemAktif = false;

const int LEBAR_PADDLE_NORMAL = 5;
const int LEBAR_PADDLE_BESAR = 9;
const int DURASI_EFEK = 180;

static int penghitungJatuh = 0;
static int sisaDurasi = 0;
static bool efekAktif = false;

// Reset item
void resetItem() {

    itemAktif = false;

    penghitungJatuh = 0;
    sisaDurasi = 0;

    efekAktif = false;

    lebarPaddle = LEBAR_PADDLE_NORMAL;
}

// Membuat item
void buatItem(int x, int y) {

    if (itemAktif) {
        return;
    }

    if (rand() % 100 < 20) {

        item.x = x;
        item.y = y;

        itemAktif = true;

        penghitungJatuh = 0;
    }
}

// Memperbarui item
void updateItem() {

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

    if (!itemAktif) {
        return;
    }

    penghitungJatuh++;

    if (penghitungJatuh >= 3) {

        item.y++;

        penghitungJatuh = 0;
    }

    // Item tertangkap paddle
    if (
        item.y >= TINGGI_LAYAR - 1 &&
        item.x >= posisiPaddle &&
        item.x < posisiPaddle + lebarPaddle
    ) {

        lebarPaddle = LEBAR_PADDLE_BESAR;

        if (posisiPaddle + lebarPaddle > LEBAR_LAYAR) {
            posisiPaddle = LEBAR_LAYAR - lebarPaddle;
        }

        efekAktif = true;

        sisaDurasi = DURASI_EFEK;

        itemAktif = false;
    }

    // Item hilang jika terlewat
    else if (item.y >= TINGGI_LAYAR) {

        itemAktif = false;
    }
}