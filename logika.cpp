#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "data.h"

using namespace std;

// ==============================
// VARIABEL GAME
// ==============================

bool balok[BARIS][KOLOM];

int skor = 0;
int nyawa = 3;
bool gameOver = false;

Posisi bola;
Posisi arahBola;

int posisiPaddle;
int lebarPaddle = 5;


// ==============================
// MENGISI DAN MENGHITUNG BALOK
// ==============================

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


// ==============================
// MENGHANCURKAN BALOK
// ==============================

void hancurkanBalok(int baris, int kolom) {

    if (baris >= 0 && baris < BARIS &&
        kolom >= 0 && kolom < KOLOM) {

        if (balok[baris][kolom]) {

            balok[baris][kolom] = false;

            // Mencoba memunculkan item
            buatItem(kolom * 3 + 1, baris);
        }
    }
}


// ==============================
// MENAMPILKAN BALOK
// ==============================

void tampilBalok() {

    for (int i = 0; i < BARIS; i++) {

        for (int j = 0; j < KOLOM; j++) {

            if (balok[i][j]) {
                cout << "[B]";
            }
            else {
                cout << "   ";
            }
        }

        cout << endl;
    }
}


// ==============================
// RESET POSISI BOLA
// ==============================

void resetPosisiBola() {

    posisiPaddle = (LEBAR_LAYAR - lebarPaddle) / 2;

    bola.x = LEBAR_LAYAR / 2;
    bola.y = TINGGI_LAYAR - 3;

    arahBola.x = 1;
    arahBola.y = -1;
}


// ==============================
// SETUP GAME
// ==============================

void setupGame() {

    skor = 0;
    nyawa = 3;
    gameOver = false;

    lebarPaddle = 5;

    srand(static_cast<unsigned>(time(nullptr)));

    isiBalok();

    resetItem();

    resetPosisiBola();
}


// ==============================
// MENGGAMBAR GAME
// ==============================

void drawGame() {

    COORD cursorPosition;

    cursorPosition.X = 0;
    cursorPosition.Y = 0;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        cursorPosition
    );

    // Menampilkan skor dan nyawa
    cout << "SKOR: " << skor
         << " | NYAWA: " << nyawa
         << " | SISA BALOK: " << hitungBalok()
         << "                    \n";

    // Batas atas arena
    for (int x = 0; x < LEBAR_LAYAR + 2; x++) {
        cout << "#";
    }

    cout << "\n";

    // Isi arena permainan
    for (int y = 0; y < TINGGI_LAYAR; y++) {

        cout << "#";

        for (int x = 0; x < LEBAR_LAYAR; x++) {

            // Menggambar bola
            if (x == bola.x && y == bola.y) {
                cout << "O";
            }

            // Menggambar item
            else if (itemAktif &&
                     x == item.x && y == item.y) {
                cout << "*";
            }

            // Menggambar paddle
            else if (y == TINGGI_LAYAR - 1 &&
                     x >= posisiPaddle &&
                     x < posisiPaddle + lebarPaddle) {
                cout << "=";
            }

            // Menggambar balok
            else if (y < BARIS &&
                     x < KOLOM * 3 &&
                     balok[y][x / 3]) {

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

            // Area kosong
            else {
                cout << " ";
            }
        }

        cout << "#\n";
    }

    // Batas bawah arena
    for (int x = 0; x < LEBAR_LAYAR + 2; x++) {
        cout << "#";
    }

    cout << "\n";

    // Informasi kontrol
    cout << "Kontrol: A / Panah Kiri"
         << " | D / Panah Kanan"
         << " | X Keluar\n";
}


// ==============================
// KONTROL PADDLE
// ==============================

void inputPlayer() {

    static DWORD waktuGerakTerakhir = 0;

    const DWORD jedaGerak = 10;

    DWORD sekarang = GetTickCount();

    // Keluar dari permainan
    if (GetAsyncKeyState('X') & 0x8000) {
        gameOver = true;
        return;
    }

    // Membaca tombol kiri
    bool kiri =
        (GetAsyncKeyState(VK_LEFT) & 0x8000) ||
        (GetAsyncKeyState('A') & 0x8000);

    // Membaca tombol kanan
    bool kanan =
        (GetAsyncKeyState(VK_RIGHT) & 0x8000) ||
        (GetAsyncKeyState('D') & 0x8000);

    if (sekarang - waktuGerakTerakhir < jedaGerak) {
        return;
    }

    // Bergerak ke kiri
    if (kiri && !kanan) {

        posisiPaddle -= 1;

        if (posisiPaddle < 0) {
            posisiPaddle = 0;
        }

        waktuGerakTerakhir = sekarang;
    }

    // Bergerak ke kanan
    else if (kanan && !kiri) {

        posisiPaddle += 1;

        if (posisiPaddle + lebarPaddle > LEBAR_LAYAR) {
            posisiPaddle = LEBAR_LAYAR - lebarPaddle;
        }

        waktuGerakTerakhir = sekarang;
    }
}


// ==============================
// LOGIKA PERGERAKAN BOLA
// ==============================

void updateLogic() {

    if (gameOver) {
        return;
    }

    // Menggerakkan bola
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

    // Pemeriksaan tabrakan balok
    bool kenaBalok = false;

    if (bola.y >= 0 && bola.y < BARIS &&
        bola.x >= 0 && bola.x < KOLOM * 3) {

        int kolomBalok = bola.x / 3;
        int barisBalok = bola.y;

        if (balok[barisBalok][kolomBalok]) {

            hancurkanBalok(barisBalok, kolomBalok);

            skor += 10;

            arahBola.y = -arahBola.y;

            kenaBalok = true;
        }
    }

    // Pantulan dinding atas
    if (!kenaBalok && bola.y <= 0) {

        bola.y = 0;
        arahBola.y = 1;
    }

    // Pantulan paddle
    if (bola.y == TINGGI_LAYAR - 1 &&
        arahBola.y > 0 &&
        bola.x >= posisiPaddle &&
        bola.x < posisiPaddle + lebarPaddle) {

        arahBola.y = -1;

        if (bola.x < posisiPaddle + lebarPaddle / 2) {
            arahBola.x = -1;
        }
        else {
            arahBola.x = 1;
        }
    }

    // Pemeriksaan bola jatuh
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

    // Memperbarui sistem item
    updateItem();
}