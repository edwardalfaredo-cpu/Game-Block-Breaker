#ifndef TAMPILAN_H
#define TAMPILAN_H

// Dibuat oleh Orang A (file tampilan.h / tampilan.cpp)

#include <string>
using namespace std;

// Nomor pilihan yang dikembalikan menuUtama()
const int MENU_MULAI  = 1;
const int MENU_SKOR   = 2;
const int MENU_CARA   = 3;
const int MENU_KELUAR = 4;

void mulaiTampilan();    // nyalakan ncurses + buat jendela arena
void akhiriTampilan();   // matikan ncurses (wajib sebelum program selesai)
void gambarSemua();      // gambar ulang seluruh layar permainan 1 kali

int  menuUtama();                      // tampilkan menu, kembalikan 1..4
void tampilHowToPlay();                // layar cara bermain
void tampilPesan(const char *teks);    // layar pesan singkat + tunggu tombol
void tampilGameOver(bool waktuHabis);  // true = waktu habis, false = nyawa habis
void tampilHighScore();                // tabel 5 skor tertinggi
string mintaNama();                    // layar ketik nama, kembalikan nama (maks 10 huruf)

#endif