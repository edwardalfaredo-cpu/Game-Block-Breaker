#ifndef  DATA_H
#define DATA_H

// ===============================
// KONSTANTA & VARIABEL GLOBAL
// ===============================
const int BARIS = 5;
const int KOLOM = 8;

// Ukuran arena permainan diterminal (1 balok = lebar 3 karakter, jadi 8 * 3 = 24)
const int TINGGI_LAYAR = 20;
const int LEBAR_LAYAR = 40;

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

 extern Posisi bola;
 extern Posisi arahBola;
 extern int posisiPaddle;
 extern int lebarPaddle;

 // ===============================
 // PROTOTIPE FUNGSI BALOK 
 // ===============================
 void isiBalok();
 void resetBalok();
 int hitungBalok();
 void hancurkanBalok(int baris, int kolom);
 void tampilBalok();

 // ===============================
 // PROTOTIPE FUNGSI GAME 
 // ===============================
 void setupGame();
 void drawGame();
 void inputPlayer();
 void updateLogic();

 #endif // DATA_H
