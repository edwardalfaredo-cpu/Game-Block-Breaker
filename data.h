#ifndef  DATA_H
#define DATA_H

// ===============================
// KONSTANTA & VARIABEL GLOBAL
// ===============================
const int BARIS = 5;
const int KOLOM = 8;

// Menggunakan 'extern' agar variabel bisa dipakai bersama di main.cpp dan logika.cpp
extern bool balok[BARIS][KOLOM];
extern int skor;
extern int nyawa;
extern bool gameOver;

 // Struktur data posisi (opsional untuk pengembangan bola & papan)
 struct Posisi {
    int x;
    int y;
 };

 // ===============================
 // PROTOTIPE FUNGSI BALOK (Sudah ada di logika.cpp)
 // ===============================
 void isiBalok();
 void resetBalok();
 int hitungBalok();
 void hancurkanBalok(int baris, int kolom);
 void tampilBalok();

 // ===============================
 // PROTOTIPE FUNGSI GAME (Rencana di main.cpp)
 // ===============================
 void setupGame();
 void drawGame();
 void inputPlayer();
 void updateLogic();

 #endif // DATA_H
