#include <iostream>
#include <conio.h>   // Untuk _kbhit() dan _getch() (input keyboard tanpa Enter)
#include <windows.h> // Untuk mengatur posisi kursor agar layar tidak berkedip parah
#include "data.h"

using namespace std;

// Definisi variabel global
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
    if (baris >= 0 && baris < BARIS && kolom >= 0 && kolom < KOLOM) {
        balok[baris][kolom] = false;
    }
}

void tampilBalok() {
    for (int i = 0; i < BARIS; i++) {
        for (int j = 0; j < KOLOM; j++) {
            if (balok[i][j]) cout << "[B]";
            else cout << "   ";
        }
        cout << endl;
    }
}

// ===============================
// BAGIAN 2: LOGIKA UTAMA GAME
// ===============================
void resetPosisiBola() {
    posisiPaddle = (LEBAR_LAYAR / 2) - (lebarPaddle / 2);
    bola.x = LEBAR_LAYAR / 2;
    bola.y = TINGGI_LAYAR - 3;
    arahBola.x = 1;  // Bergerak ke kanan
    arahBola.y = -1; // Bergerak ke atas
}

void setupGame() {
    skor = 0;
    nyawa = 3;
    gameOver = false;
    isiBalok();
    resetPosisiBola();
}

void drawGame() {
    // Mengembalikan kursor ke pojok kiri atas (lebih mulus daripada system("cls"))
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    cout << "SKOR: " << skor << "  |  NYAWA: " << nyawa << "  |  SISA BALOK: " << hitungBalok() << "   \n";

    // Bingkai Atas
    for (int x = 0; x < LEBAR_LAYAR + 2; x++) cout << "#";
    cout << "\n";

    // Isi Arena
    for (int y = 0; y < TINGGI_LAYAR; y++) {
        cout << "#"; // Dinding Kiri
        for (int x = 0; x < LEBAR_LAYAR; x++) {
            // 1. Cek apakah koordinat ini adalah Bola
            if (x == bola.x && y == bola.y) {
                cout << "O";
            }
            // 2. Cek apakah koordinat ini adalah Paddle (di baris paling bawah - 1)
            else if (y == TINGGI_LAYAR - 1 && x >= posisiPaddle && x < posisiPaddle + lebarPaddle) {
                cout << "=";
            }
            // 3. Cek apakah koordinat ini adalah Balok (di 5 baris teratas, 1 balok lebarnya 3 karakter)
            else if (y < BARIS && balok[y][x / 3]) {
                if (x % 3 == 0) cout << "[";
                else if (x % 3 == 1) cout << "B";
                else cout << "]";
            }
            // 4. Ruang kosong
            else {
                cout << " ";
            }
        }
        cout << "#\n"; // Dinding Kanan
    }

    // Bingkai Bawah
    for (int x = 0; x < LEBAR_LAYAR + 2; x++) cout << "#";
    cout << "\nKontrol: [A] Kiri | [D] Kanan | [X] Keluar\n";
}

void inputPlayer() {
    if (_kbhit()) { // Cek apakah ada tombol yang ditekan
        char tombol = _getch();
        if (tombol == 'a' || tombol == 'A' || tombol == 75) { // 75 = Panah Kiri
            if (posisiPaddle > 0) {
                posisiPaddle -= 2; // Geser kiri
                if (posisiPaddle < 0) posisiPaddle = 0;
            }
        }
        else if (tombol == 'd' || tombol == 'D' || tombol == 77) { // 77 = Panah Kanan
            if (posisiPaddle + lebarPaddle < LEBAR_LAYAR) {
                posisiPaddle += 2; // Geser kanan
                if (posisiPaddle + lebarPaddle > LEBAR_LAYAR) {
                    posisiPaddle = LEBAR_LAYAR - lebarPaddle;
                }
            }
        }
        else if (tombol == 'x' || tombol == 'X') {
            gameOver = true;
        }
    }
}

void updateLogic() {
    // Gerakkan bola
    bola.x += arahBola.x;
    bola.y += arahBola.y;

    // 1. Pantulan dinding kiri & kanan
    if (bola.x <= 0) {
        bola.x = 0;
        arahBola.x = -arahBola.x;
    } else if (bola.x >= LEBAR_LAYAR - 1) {
        bola.x = LEBAR_LAYAR - 1;
        arahBola.x = -arahBola.x;
    }

    // 2. Pantulan atap
    if (bola.y <= 0) {
        bola.y = 0;
        arahBola.y = -arahBola.y;
    }

    // 3. Cek tabrakan dengan Balok
    if (bola.y >= 0 && bola.y < BARIS) {
        int kolomBalok = bola.x / 3;
        if (balok[bola.y][kolomBalok]) {
            hancurkanBalok(bola.y, kolomBalok);
            skor += 10;
            arahBola.y = -arahBola.y; // Pantulkan bola ke bawah
        }
    }

    // 4. Pantulan dengan Paddle
    if (bola.y == TINGGI_LAYAR - 1 && bola.x >= posisiPaddle && bola.x < posisiPaddle + lebarPaddle) {
        arahBola.y = -1; // Pantulkan ke atas
        // Ubah arah horizontal sedikit jika mengenai ujung paddle
        if (bola.x < posisiPaddle + (lebarPaddle / 2)) {
            arahBola.x = -1;
        } else {
            arahBola.x = 1;
        }
    }

    // 5. Cek jika bola jatuh melewati bawah layar
    if (bola.y >= TINGGI_LAYAR) {
        nyawa--;
        if (nyawa <= 0) {
            gameOver = true;
        } else {
            Sleep(500);
            resetPosisiBola();
        }
    }
}
 