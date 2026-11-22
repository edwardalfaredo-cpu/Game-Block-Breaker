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

    // ----- WARNA (P12): pasangan nomor = (warna tulisan, warna latar) -----
    start_color();
    init_pair(1, COLOR_CYAN,    COLOR_BLACK);   // balok biasa
    init_pair(2, COLOR_GREEN,   COLOR_BLACK);   // balok / item +Waktu
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);   // balok / item Multi-Ball
    init_pair(4, COLOR_YELLOW,  COLOR_BLACK);   // paddle
    init_pair(5, COLOR_RED,     COLOR_BLACK);   // bola

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
                wattron(winArena, COLOR_PAIR(1));
                mvwprintw(winArena, y + 1, x + 1, "[===]");
                wattroff(winArena, COLOR_PAIR(1));
            } else if (balok[r][k] == 2) {
                wattron(winArena, COLOR_PAIR(2));
                mvwprintw(winArena, y + 1, x + 1, "[ T ]");
                wattroff(winArena, COLOR_PAIR(2));
            } else if (balok[r][k] == 3) {
                wattron(winArena, COLOR_PAIR(3));
                mvwprintw(winArena, y + 1, x + 1, "[ M ]");
                wattroff(winArena, COLOR_PAIR(3));
            }
            // 0 = hancur: tidak digambar
        }
    }
}

void gambarPaddle() {
    int y = TINGGI_ARENA - 1;
    wattron(winArena, COLOR_PAIR(4));
    for (int i = 0; i < LEBAR_PADDLE; i++) {
        mvwprintw(winArena, y + 1, paddleX + i + 1, "=");
    }
    wattroff(winArena, COLOR_PAIR(4));
}

void gambarBola() {
    wattron(winArena, COLOR_PAIR(5));
    for (int i = 0; i < JUMLAH_BOLA; i++) {
        if (bolaAktif[i]) {
            mvwprintw(winArena, bolaY[i] + 1, bolaX[i] + 1, "O");
        }
    }
    wattroff(winArena, COLOR_PAIR(5));
}

void gambarItem() {
    if (itemAktif) {
        if (itemJenis == 2) {
            wattron(winArena, COLOR_PAIR(2));
            mvwprintw(winArena, itemY + 1, itemX + 1, "T");
            wattroff(winArena, COLOR_PAIR(2));
        } else {
            wattron(winArena, COLOR_PAIR(3));
            mvwprintw(winArena, itemY + 1, itemX + 1, "M");
            wattroff(winArena, COLOR_PAIR(3));
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

// ============================================================
// MENU & LAYAR LAIN
// ============================================================

int menuUtama() {
    nodelay(stdscr, FALSE);    // menu menunggu tombol (tidak jalan sendiri)

    string pilihan[4] = {"Mulai Main", "High Score", "How to Play", "Keluar"};
    int sorot = 0;             // 0..3 = pilihan yang sedang ditandai
    int ch;

    while (true) {
        clear();
        mvprintw(2, 10, "=== BRICK BREAKER ===");

        for (int i = 0; i < 4; i++) {
            if (i == sorot) {
                mvprintw(5 + i * 2, 12, "> %s", pilihan[i].c_str());
            } else {
                mvprintw(5 + i * 2, 12, "  %s", pilihan[i].c_str());
            }
        }
        mvprintw(15, 6, "Panah atas/bawah = pilih, Enter = oke");
        refresh();

        ch = getch();
        if (ch == KEY_UP && sorot > 0) {
            sorot--;
        } else if (ch == KEY_DOWN && sorot < 3) {
            sorot++;
        } else if (ch == '\n' || ch == KEY_ENTER || ch == '\r') {
            return sorot + 1;
        }
    }
}

void tampilHowToPlay() {
    clear();
    mvprintw(2, 5, "=== CARA BERMAIN ===");
    mvprintw(4, 5, "Panah kiri/kanan : geser paddle");
    mvprintw(5, 5, "Pukul balok pakai bola, tiap balok = 10 poin");
    mvprintw(6, 5, "Waktu bermain 60 detik, nyawa 3");
    mvprintw(8, 5, "Balok [ T ] : jatuh item +Waktu (tangkap pakai paddle)");
    mvprintw(9, 5, "Balok [ M ] : jatuh item Multi-Ball (bola jadi 3)");
    mvprintw(11, 5, "Bola jatuh = nyawa berkurang");
    mvprintw(12, 5, "(kalau bola ada banyak, nyawa berkurang saat semuanya jatuh)");
    mvprintw(14, 5, "Tekan tombol apa saja untuk kembali...");
    refresh();
    getch();
}

void tampilPesan(const char *teks) {
    clear();
    mvprintw(5, 5, "%s", teks);
    mvprintw(7, 5, "Tekan tombol apa saja untuk kembali...");
    refresh();
    getch();
}

void tampilGameOver(bool waktuHabis) {
    nodelay(stdscr, FALSE);    // layar ini menunggu tombol
    flushinp();                // buang tombol panah yang masih tertahan

    clear();
    mvprintw(4, 10, "=== GAME OVER ===");
    if (waktuHabis) {
        mvprintw(6, 10, "Waktu habis!");
    } else {
        mvprintw(6, 10, "Nyawa habis!");
    }
    mvprintw(8, 10, "Skor kamu: %d", skor);
    mvprintw(11, 10, "Tekan tombol apa saja untuk kembali...");
    refresh();
    getch();
}

void tampilHighScore() {
    nodelay(stdscr, FALSE);
    flushinp();

    clear();
    mvprintw(2, 8, "=== HIGH SCORE ===");
    for (int i = 0; i < JUMLAH_TOP; i++) {
        if (skorTop[i] > 0) {
            mvprintw(4 + i, 8, "%d. %-12s %5d", i + 1, namaTop[i].c_str(), skorTop[i]);
        } else {
            mvprintw(4 + i, 8, "%d. ---", i + 1);
        }
    }
    mvprintw(11, 8, "Tekan tombol apa saja untuk kembali...");
    refresh();
    getch();
}