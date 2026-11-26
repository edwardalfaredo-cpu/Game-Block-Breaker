#ifndef DATA_H
#define DATA_H

const int BARIS = 5;
const int KOLOM = 8;

const int TINGGI_LAYAR = 20;
const int LEBAR_LAYAR = 40;

// Variabel permainan
extern bool balok[BARIS][KOLOM];
extern int skor;
extern int nyawa;
extern bool gameOver;

// Posisi bola, paddle, dan item
struct Posisi {
    int x;
    int y;
};

extern Posisi bola;
extern Posisi arahBola;
extern Posisi item;

extern int posisiPaddle;
extern int lebarPaddle;
extern bool itemAktif;

// Fungsi balok
void isiBalok();
void resetBalok();
int hitungBalok();
void hancurkanBalok(int baris, int kolom);
void tampilBalok();

// Fungsi permainan
void setupGame();
void resetPosisiBola();
void drawGame();
void inputPlayer();
void updateLogic();

// Fungsi item
void resetItem();
void buatItem(int x, int y);
void updateItem();

#endif