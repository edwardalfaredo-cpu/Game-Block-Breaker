#include <iostream>
#include <windows.h>
#include <string>

#include "data.h"
#include "highscore.h"

using namespace std;

int main() {

    system("cls");

    string nama = "Dhani";

    cout << "==============================\n";
    cout << "       BLOCK BREAKER\n";
    cout << "       PEMAIN: " << nama << "\n";
    cout << "==============================\n";

    setupGame();

    const DWORD jedaBola = 90;
    const DWORD jedaGambar = 20;

    DWORD waktuBola = GetTickCount();
    DWORD waktuGambar = GetTickCount();

    // =================================
    // PERULANGAN PERMAINAN
    // =================================

    while (true) {

        inputPlayer();

        DWORD sekarang = GetTickCount();

        if (sekarang - waktuBola >= jedaBola) {

            updateLogic();

            waktuBola = sekarang;
        }

        if (sekarang - waktuGambar >= jedaGambar) {

            drawGame();

            waktuGambar = sekarang;
        }

        // Kondisi kalah
        if (gameOver) {

            drawGame();

            cout << "\n==============================\n";
            cout << "       GAME OVER!\n";
            cout << "       PEMAIN: " << nama << "\n";
            cout << "       SKOR: " << skor << "\n";
            cout << "==============================\n";

            break;
        }

        // Kondisi menang
        if (hitungBalok() == 0) {

            drawGame();

            cout << "\n==============================\n";
            cout << "    SELAMAT! KAMU MENANG!\n";
            cout << "       PEMAIN: " << nama << "\n";
            cout << "       SKOR: " << skor << "\n";
            cout << "==============================\n";

            break;
        }

        Sleep(1);
    }

    // =================================
    // MENYIMPAN HIGHSCORE
    // =================================

    if (simpanHighScore(nama, skor)) {

        cout << "\nSkor berhasil disimpan!\n";
    }
    else {

        cout << "\nSkor gagal disimpan!\n";
    }

    // =================================
    // MENAMPILKAN HIGHSCORE
    // =================================

    DataHighScore daftar[MAX_HIGH_SCORE];

    int jumlah = muatHighScore(
        daftar,
        MAX_HIGH_SCORE
    );

    cout << "\n========== HIGH SCORE ==========\n";

    if (jumlah == 0) {

        cout << "Belum ada data High Score.\n";
    }

    for (int i = 0; i < jumlah; i++) {

        cout << i + 1 << ". "
             << daftar[i].nama
             << " - "
             << daftar[i].skor
             << "\n";
    }

    cout << "================================\n";

    system("pause");

    return 0;
}