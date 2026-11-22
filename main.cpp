#include <iostream>
#include <windows.h>
#include "data.h"

using namespace std;

int main() {
    system("cls");

    setupGame();

    // Pengaturan kecepatan permainan
    const DWORD jedaBola = 90;
    const DWORD jedaGambar = 16;

    DWORD waktuBola = GetTickCount();
    DWORD waktuGambar = GetTickCount();

    while (true) {

        // Membaca input pemain secara terus-menerus
        inputPlayer();

        DWORD sekarang = GetTickCount();

        // Bola hanya bergerak setiap 90 milidetik
        if (sekarang - waktuBola >= jedaBola) {
            updateLogic();
            waktuBola = sekarang;
        }

        // Tampilan diperbarui setiap 20 milidetik
        if (sekarang - waktuGambar >= jedaGambar) {
            drawGame();
            waktuGambar = sekarang;
        }

        // Kondisi kalah
        if (gameOver) {
            drawGame();

            cout << "\n==============================\n";
            cout << "   GAME OVER! SKOR AKHIR: "
                 << skor << "\n";
            cout << "==============================\n";

            break;
        }

        // Kondisi menang
        if (hitungBalok() == 0) {
            drawGame();

            cout << "\n==============================\n";
            cout << "  SELAMAT! KAMU MENANG! SKOR: "
                 << skor << "\n";
            cout << "==============================\n";

            break;
        }

        // Memberi jeda kecil agar CPU tidak bekerja berlebihan
        Sleep(1);
    }

    return 0;
}