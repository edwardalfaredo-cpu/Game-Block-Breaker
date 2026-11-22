#ifndef DATA_H
#define DATA_H

#include <string>
using namespace std;

// ============================================================
// data.h - DAFTAR VARIABEL BERSAMA (DIBEKUKAN)
// Jangan ganti nama / tipe / arti. Mau tambah? Lewat grup,
// lalu Orang C yang menambahkan.
//
// Aturan koordinat:
// - (0,0) = pojok kiri atas DI DALAM arena (bukan layar)
// - x = kolom (0 .. LEBAR_ARENA-1), y = baris (0 .. TINGGI_ARENA-1)
// - paddle berada di baris paling bawah: y = TINGGI_ARENA-1
// - balok baris ke-r berada di y = r + 1
// - balok kolom ke-k mulai dari x = k * LEBAR_BALOK
// ============================================================

// ---------- KONSTANTA ----------
const int KOLOM_BALOK  = 8;
const int BARIS_BALOK  = 4;
const int LEBAR_BALOK  = 5;
const int LEBAR_ARENA  = 40;   // = KOLOM_BALOK * LEBAR_BALOK
const int TINGGI_ARENA = 20;
const int LEBAR_PADDLE = 7;
const int JUMLAH_BOLA  = 3;
const int JUMLAH_TOP   = 5;    // jumlah high score yang disimpan

const int NYAWA_AWAL        = 3;
const int PUTARAN_PER_DETIK = 20;                  // Sleep(50) tiap putaran
const int WAKTU_AWAL        = 60 * PUTARAN_PER_DETIK;   // 60 detik
const int WAKTU_TAMBAHAN    = 10 * PUTARAN_PER_DETIK;   // item +Waktu = 10 detik

// ---------- ISI ARRAY BALOK & JENIS ITEM ----------
// 0 = balok hancur / kosong
// 1 = balok biasa
// 2 = balok berisi item +Waktu
// 3 = balok berisi item Multi-Ball
// itemJenis memakai angka yang sama (2 atau 3)

// ---------- PADDLE ----------
extern int paddleX;            // kolom paling kiri paddle

// ---------- BOLA (3 bola) ----------
extern int  bolaX[JUMLAH_BOLA];
extern int  bolaY[JUMLAH_BOLA];
extern int  arahX[JUMLAH_BOLA];      // hanya -1 atau 1
extern int  arahY[JUMLAH_BOLA];      // hanya -1 atau 1
extern bool bolaAktif[JUMLAH_BOLA];  // true = bola sedang main

// ---------- BALOK ----------
extern int balok[BARIS_BALOK][KOLOM_BALOK];

// ---------- ITEM (satu item saja dalam satu waktu) ----------
extern int  itemX;
extern int  itemY;
extern int  itemJenis;     // 2 = +Waktu, 3 = Multi-Ball
extern bool itemAktif;

// ---------- STATUS GAME ----------
extern int skor;
extern int nyawa;          // awal NYAWA_AWAL
extern int waktuSisa;      // dalam putaran, awal WAKTU_AWAL

// ---------- HIGH SCORE ----------
extern string namaTop[JUMLAH_TOP];
extern int    skorTop[JUMLAH_TOP];

#endif