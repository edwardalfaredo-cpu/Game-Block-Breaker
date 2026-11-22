#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <string>
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

        if   (balok[baris][kolom]) { 

            balok[baris][kolom] = false;
            // Coba munculkan item dari balok 
            buatItem(kolom * 3 + 1, baris);

        }
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

    srand(static_cast<unsigned>(time(nullptr)));

    isiBalok();
    resetItem();
    resetPosisiBola();
}

// ===============================
// BAGIAN 4: MENAMPILKAN GAME
// ===============================

void drawGame() {
    // Mengatur posisi tampilan agar bergeser ke tengah
    const int OFFSET_KIRI = 15;
    string geser(OFFSET_KIRI, ' ');

    // Mengembalikan kursor ke pojok kiri atas
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        cursorPosition
    );

    // Menampilkan informasi permainan
    cout << geser;
    cout << "SKOR: " << skor
         << " | NYAWA: " << nyawa
         << " | SISA BALOK: " << hitungBalok()
         << "                    \n";

    // Batas atas arena
    cout << geser;
    for (int x = 0; x < LEBAR_LAYAR + 2; x++) {
        cout << "#";
    }
    cout << "\n";

    // Menggambar isi arena
    for (int y = 0; y < TINGGI_LAYAR; y++) {
        cout << geser;
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
    cout << geser;
    for (int x = 0; x < LEBAR_LAYAR + 2; x++) {
        cout << "#";
    }
    cout << "\n";

    // Informasi kontrol
    cout << geser;
    cout << "Kontrol: A / Panah Kiri"
         << " | D / Panah Kanan"
         << " | X Keluar\n";
}

// ===============================
// BAGIAN 5: INPUT PEMAIN
// ===============================

void inputPlayer() {

    static DWORD waktuGerakTerakhir = 0;
    const DWORD jedaGerak = 12;

    DWORD sekarang = GetTickCount();

    // Tombol X untuk keluar
    if (GetAsyncKeyState('X') & 0x8000) {
        gameOver = true;
        return;
    }

    // Membaca tombol kiri dan kanan
    bool kiri = (GetAsyncKeyState(VK_LEFT) & 0x8000) ||
                (GetAsyncKeyState('A') & 0x8000);

    bool kanan = (GetAsyncKeyState(VK_RIGHT) & 0x8000) ||
                 (GetAsyncKeyState('D') & 0x8000);

    // Mengatur jeda gerakan
    if (sekarang - waktuGerakTerakhir < jedaGerak) {
        return;
    }

    // Gerakan ke kiri
    if (kiri && !kanan) {
        posisiPaddle -= 1;

        if (posisiPaddle < 0) {
            posisiPaddle = 0;
        }

        waktuGerakTerakhir = sekarang;
    }

    // Gerakan ke kanan
    else if (kanan && !kiri) {
        posisiPaddle += 1;

        if (posisiPaddle + lebarPaddle > LEBAR_LAYAR) {
            posisiPaddle = LEBAR_LAYAR - lebarPaddle;
        }

        waktuGerakTerakhir = sekarang;
    }
}

// ===============================
// BAGIAN 6: LOGIKA PERGERAKAN BOLA
// ===============================

void updateLogic() {
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

    updateItem();
}