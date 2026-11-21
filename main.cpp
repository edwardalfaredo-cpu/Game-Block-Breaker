#include <iostream>
#include <windows.h> // Untuk fungsi Sleep()
#include "data.h"

using namespace std;

int main() {
    system("cls"); // Bersihkan terminal sekali di awal
    setupGame();

    while (true) {
        drawGame();
        inputPlayer();
        updateLogic();

        // Cek kondisi kalah
        if (gameOver) {
            drawGame();
            cout << "\n==============================\n";
            cout << "   GAME OVER! SKOR AKHIR: " << skor << "\n";
            cout << "==============================\n";
            break;
        }

        // Cek kondisi menang (semua balok habis)
        if (hitungBalok() == 0) {
            drawGame();
            cout << "\n==============================\n";
            cout << "  SELAMAT! KAMU MENANG! SKOR: " << skor << "\n";
            cout << "==============================\n";
            break;
        }

        Sleep(90); // Kecepatan game (makin kecil angka, makin cepat bola bergerak)
    }

    return 0;
}
 
