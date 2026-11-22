#include <iostream>
#include <conio.h>
#include <windows.h>
#include "data.h"

using namespace std;

// ===============================
// DEFINISI VARIABEL GLOBAL
// ===============================

bool balok[BARIS][KOLOM];

int skor = 0;
int nyawa = 3;
bool gameOver = false;

Posisi bola;
Posisi arahBola;

int posisiPaddle;
int lebarPaddle = 5;

// ===============================
// BAGIAN 1: ISI DAN RESET BALOK
// ===============================

void isiBalok() {
    for (int i = 0; i < BARIS; i++) {
        for (int j = 0; j < KOLOM; j++) {
            balok[i][j] = true;
        }
    }
}

void resetBalok() {
    isiBalok();
}

int hitungBalok() {
    int jumlah = 0;

    for (int i = 0; i < BARIS; i++) {
        for (int j = 0; j < KOLOM; j++) {
            if (balok[i][j]) {
                jumlah++;
            }
        }
    }

    return jumlah;
}

void hancurkanBalok(int baris, int kolom) {
    if (baris >= 0 && baris < BARIS &&
        kolom >= 0 && kolom < KOLOM) {

        balok[baris][kolom] = false;
    }
}

void tampilBalok() {
    for (int i = 0; i < BARIS; i++) {
        for (int j = 0; j < KOLOM; j++) {
            if (balok[i][j]) {
                cout << "[B]";
            } else {
                cout << "   ";
            }
        }
        cout << endl;
    }
}

// ===============================
// BAGIAN 2: RESET POSISI BOLA
// ===============================

void resetPosisiBola() {
    posisiPaddle = (LEBAR_LAYAR - lebarPaddle) / 2;

    bola.x = LEBAR_LAYAR / 2;
    bola.y = TINGGI_LAYAR - 3;

    arahBola.x = 1;
    arahBola.y = -1;
}

// ===============================
// BAGIAN 3: PERSIAPAN GAME
// ===============================

void setupGame() {
    skor = 0;
    nyawa = 3;
    gameOver = false;

    lebarPaddle = 5;

    isiBalok();
    resetPosisiBola();
}

// ===============================
// BAGIAN 4: MENAMPILKAN GAME
// ===============================

void drawGame() {
    COORD cursorPosition;

    cursorPosition.X = 0;
    cursorPosition.Y = 0;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        cursorPosition
    );

    cout << "SKOR: " << skor
         << " | NYAWA: " << nyawa
         << " | SISA BALOK: " << hitungBalok()
         << "                    \n";

    // Bingkai atas
    for (int x = 0; x < LEBAR_LAYAR + 2; x++) {
        cout << "#";
    }
    cout << "\n";

    // Isi arena
    for (int y = 0; y < TINGGI_LAYAR; y++) {

        cout << "#";

        for (int x = 0; x < LEBAR_LAYAR; x++) {

            // Bola
            if (x == bola.x && y == bola.y) {
                cout << "O";
            }

            // Paddle
            else if (
                y == TINGGI_LAYAR - 1 &&
                x >= posisiPaddle &&
                x < posisiPaddle + lebarPaddle
            ) {
                cout << "=";
            }

            // Balok
            else if (
                y < BARIS &&
                x < KOLOM * 3 &&
                balok[y][x / 3]
            ) {
                if (x % 3 == 0) {
                    cout << "[";
                }
                else if (x % 3 == 1) {
                    cout << "B";
                }
                else {
                    cout << "]";
                }
            }

            // Ruang kosong
            else {
                cout << " ";
            }
        }

        cout << "#\n";
    }

    // Bingkai bawah
    for (int x = 0; x < LEBAR_LAYAR + 2; x++) {
        cout << "#";
    }

    cout << "\nKontrol: A / Panah Kiri"
         << " | D / Panah Kanan"
         << " | X Keluar\n";
}

// ===============================
// BAGIAN 5: INPUT PEMAIN
// ===============================

void inputPlayer() {

    if (_kbhit()) {

        int tombol = _getch();

        // Memeriksa tombol panah kiri atau kanan
        if (tombol == 0 || tombol == 224) {
            tombol = _getch();
        }

        // Tombol panah kiri atau huruf A
        if (tombol == 75 || tombol == 'a' || tombol == 'A') {

            posisiPaddle -= 2;

            if (posisiPaddle < 0) {
                posisiPaddle = 0;
            }
        }

        // Tombol panah kanan atau huruf D
        else if (tombol == 77 || tombol == 'd' || tombol == 'D') {

            posisiPaddle += 2;

            if (posisiPaddle + lebarPaddle > LEBAR_LAYAR) {
                posisiPaddle = LEBAR_LAYAR - lebarPaddle;
            }
        }

        // Tombol X untuk keluar
        else if (tombol == 'x' || tombol == 'X') {
            gameOver = true;
        }
    }
}

// ===============================
// BAGIAN 6: LOGIKA PERGERAKAN BOLA
// ===============================

void updateLogic() {
    cout << "Posisi bola: x = " << bola.x
         << " | Y = " << bola.y << endl;

    if (gameOver) {
        return;
    }

    // Gerakkan bola
    bola.x += arahBola.x;
    bola.y += arahBola.y;

    // Pantulan dinding kiri
    if (bola.x <= 0) {
        bola.x = 0;
        arahBola.x = 1;
    }

    // Pantulan dinding kanan
    else if (bola.x >= LEBAR_LAYAR - 1) {
        bola.x = LEBAR_LAYAR - 1;
        arahBola.x = -1;
    }

    // Cek tabrakan dengan balok
    bool kenaBalok = false;

    if (
        bola.y >= 0 &&
        bola.y < BARIS &&
        bola.x >= 0 &&
        bola.x < KOLOM * 3
    ) {

        int kolomBalok = bola.x / 3;
        int barisBalok = bola.y;

        if (balok[barisBalok][kolomBalok]) {

            hancurkanBalok(barisBalok, kolomBalok);

            skor += 10;

            arahBola.y = -arahBola.y;

            kenaBalok = true;
        }
    }

    // Pantulan atap jika tidak sedang mengenai balok
    if (!kenaBalok && bola.y <= 0) {
        bola.y = 0;
        arahBola.y = 1;
    }

    // Pantulan paddle
    if (
        bola.y == TINGGI_LAYAR - 1 &&
        arahBola.y > 0 &&
        bola.x >= posisiPaddle &&
        bola.x < posisiPaddle + lebarPaddle
    ) {

        arahBola.y = -1;

        // Mengenai sisi kiri paddle
        if (bola.x < posisiPaddle + lebarPaddle / 2) {
            arahBola.x = -1;
        }

        // Mengenai sisi kanan paddle
        else {
            arahBola.x = 1;
        }
    }

    // Bola jatuh melewati paddle
    if (bola.y >= TINGGI_LAYAR) {

        nyawa--;

        if (nyawa <= 0) {
            gameOver = true;
        }
        else {
            Sleep(500);
            resetPosisiBola();
        }
    }
}