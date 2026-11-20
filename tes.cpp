#include <ncurses.h>
#include "data.h"
#include "tampilan.h"

// FILE TES SAJA - tidak ikut dikirim ke GitHub
int main() {
    // isi data palsu supaya ada yang digambar
    for (int r = 0; r < BARIS_BALOK; r++) {
        for (int k = 0; k < KOLOM_BALOK; k++) {
            balok[r][k] = 1;
        }
    }
    balok[1][2] = 2;
    balok[2][5] = 3;

    paddleX = 16;
    bolaX[0] = 19;
    bolaY[0] = 12;
    bolaAktif[0] = true;
    itemAktif = true;
    itemJenis = 2;
    itemX = 10;
    itemY = 9;
    skor = 120;

    mulaiTampilan();
    gambarSemua();
    mvprintw(TINGGI_ARENA + 5, 2, "Tekan tombol apa saja untuk keluar...");
    getch();
    akhiriTampilan();
    return 0;
}