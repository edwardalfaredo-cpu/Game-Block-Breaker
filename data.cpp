#include "data.h"

// Definisi variabel bersama (nilai awal). Pemilik file: Orang C.

int paddleX = 0;

int  bolaX[JUMLAH_BOLA]      = {0, 0, 0};
int  bolaY[JUMLAH_BOLA]      = {0, 0, 0};
int  arahX[JUMLAH_BOLA]      = {1, 1, 1};
int  arahY[JUMLAH_BOLA]      = {-1, -1, -1};
bool bolaAktif[JUMLAH_BOLA]  = {false, false, false};

int balok[BARIS_BALOK][KOLOM_BALOK];

int  itemX = 0;
int  itemY = 0;
int  itemJenis = 0;
bool itemAktif = false;

int skor = 0;
int nyawa = NYAWA_AWAL;
int waktuSisa = WAKTU_AWAL;

string namaTop[JUMLAH_TOP];
int    skorTop[JUMLAH_TOP] = {0, 0, 0, 0, 0};