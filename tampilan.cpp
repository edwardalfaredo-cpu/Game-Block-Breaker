#include <ncurses.h>
#include "data.h"
#include "tampilan.h"

// Jendela arena (hanya dipakai di file ini)
WINDOW *winArena;

// Letak jendela arena di layar
const int ARENA_BARIS_LAYAR = 1;
const int ARENA_KOLOM_LAYAR = 2;

void mulaiTampilan() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);              // sembunyikan kursor
    refresh();

    // +2 karena bingkai memakai 1 baris/kolom di tiap sisi
    winArena = newwin(TINGGI_ARENA + 2, LEBAR_ARENA + 2,
                      ARENA_BARIS_LAYAR, ARENA_KOLOM_LAYAR);
}

void akhiriTampilan() {
    endwin();
}

// ---------- bagian-bagian gambar ----------
// Koordinat data (x,y) dihitung dari dalam arena,
// jadi di jendela digeser +1 karena ada bingkai.

void gambarBalok() {
    for (int r = 0; r < BARIS_BALOK; r++) {
        for (int k = 0; k < KOLOM_BALOK; k++) {
            int y = r + 1;                 // aturan data.h
            int x = k * LEBAR_BALOK;
            if (balok[r][k] == 1) {
                mvwprintw(winArena, y + 1, x + 1, "[===]");
            } else if (balok[r][k] == 2) {
                mvwprintw(winArena, y + 1, x + 1, "[ T ]");
            } else if (balok[r][k] == 3) {
                mvwprintw(winArena, y + 1, x + 1, "[ M ]");
            }
            // 0 = hancur: tidak digambar
        }
    }
}

void gambarPaddle() {
    int y = TINGGI_ARENA - 1;
    for (int i = 0; i < LEBAR_PADDLE; i++) {
        mvwprintw(winArena, y + 1, paddleX + i + 1, "=");
    }
}

void gambarBola() {
    for (int i = 0; i < JUMLAH_BOLA; i++) {
        if (bolaAktif[i]) {
            mvwprintw(winArena, bolaY[i] + 1, bolaX[i] + 1, "O");
        }
    }
}

void gambarItem() {
    if (itemAktif) {
        if (itemJenis == 2) {
            mvwprintw(winArena, itemY + 1, itemX + 1, "T");
        } else {
            mvwprintw(winArena, itemY + 1, itemX + 1, "M");
        }
    }
}

void gambarStatus() {
    int detik = waktuSisa / PUTARAN_PER_DETIK;
    // spasi di belakang untuk menimpa angka lama
    mvprintw(TINGGI_ARENA + 3, ARENA_KOLOM_LAYAR,
             "Skor: %5d   Nyawa: %d   Waktu: %3d   ", skor, nyawa, detik);
}

// ---------- fungsi yang dipanggil Orang C tiap putaran ----------
void gambarSemua() {
    werase(winArena);          // bersihkan isi jendela
    box(winArena, 0, 0);       // bingkai

    gambarBalok();
    gambarPaddle();
    gambarBola();
    gambarItem();
    gambarStatus();

    refresh();                 // layar utama (status)
    wrefresh(winArena);        // jendela arena
}