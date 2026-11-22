#include "data.h"
#include "bola.h"
#include "tabrakan.h"

// ---------------- balok (P6: array 2D) ----------------
void initBalok() {
    for (int r = 0; r < BARIS_BALOK; r++) {
        for (int k = 0; k < KOLOM_BALOK; k++) {
            int kode = (r * 3 + k) % 7;
            if (kode == 2)      balok[r][k] = 2;   // +Waktu     [ T ]
            else if (kode == 5) balok[r][k] = 3;   // Multi-Ball [ M ]
            else                balok[r][k] = 1;   // biasa
        }
    }
}

bool blokHabis() {                                  // P8: return nilai
    for (int r = 0; r < BARIS_BALOK; r++) {
        for (int k = 0; k < KOLOM_BALOK; k++) {
            if (balok[r][k] > 0) {
                return false;
            }
        }
    }
    return true;
}

// balok hancur -> skor naik -> kalau bertanda (2/3) munculkan item (P3: if)
static void hancurkanBalok(int r, int k) {
    int jenis = balok[r][k];
    if (jenis >= 2 && !itemAktif) {
        itemAktif = true;
        itemJenis = jenis;
        itemX = k * LEBAR_BALOK + 2;                // tengah balok
        itemY = r + 1;                              // aturan data.h: y = r + 1
    }
    balok[r][k] = 0;
    skor += 10;
}

// ---------------- pantulan (P3: if, nested if) ----------------

// dinding kiri, kanan, atas
static void pantulDinding(int i) {
    if (bolaX[i] < 0 || bolaX[i] >= LEBAR_ARENA) {
        arahX[i] = -arahX[i];
        bolaX[i] = bolaX[i] + 2 * arahX[i];         // dipantulkan balik ke dalam arena
    }
    if (bolaY[i] < 0) {
        arahY[i] = -arahY[i];
        bolaY[i] = bolaY[i] + 2 * arahY[i];
    }
}

// paddle, atau bola jatuh kalau lewat paddle
static void pantulPaddle(int i) {
    int yPaddle = TINGGI_ARENA - 1;

    if (bolaY[i] == yPaddle && arahY[i] > 0) {
        if (bolaX[i] >= paddleX && bolaX[i] < paddleX + LEBAR_PADDLE) {   // nested if
            arahY[i] = -1;
            bolaY[i] = yPaddle - 1;
            if (bolaX[i] < paddleX + LEBAR_PADDLE / 3) {
                arahX[i] = -1;                      // ujung kiri paddle -> ke kiri
            } else if (bolaX[i] >= paddleX + 2 * LEBAR_PADDLE / 3) {
                arahX[i] = 1;                       // ujung kanan paddle -> ke kanan
            }
        }
    } else if (bolaY[i] > yPaddle) {
        bolaAktif[i] = false;                       // bola jatuh
    }
}

// ---------------- tabrakan balok ----------------
static void tabrakBalok(int i) {
    int r = bolaY[i] - 1;
    int k = bolaX[i] / LEBAR_BALOK;

    if (r >= 0 && r < BARIS_BALOK && k >= 0 && k < KOLOM_BALOK) {
        if (balok[r][k] > 0) {
            hancurkanBalok(r, k);
            arahY[i] = -arahY[i];
            bolaY[i] = bolaY[i] + arahY[i];         // balik ke posisi sebelum nabrak
        }
    }
}

// ---------------- item jatuh ----------------
static void gerakItem() {
    static int hitung = 0;
    if (!itemAktif) return;

    hitung++;
    if (hitung % 4 != 0) return;                    // item lebih lambat dari bola

    itemY++;
    if (itemY >= TINGGI_ARENA - 1) {
        if (itemX >= paddleX && itemX < paddleX + LEBAR_PADDLE) {
            if (itemJenis == 3) {
                aktifkanMultiBall();                // Multi-Ball (P8)
            } else {
                waktuSisa += 5 * PUTARAN_PER_DETIK; // +Waktu (hapus kalau bukan bagianmu)
            }
        }
        itemAktif = false;
    }
}

// ---------------- dipanggil tiap putaran ----------------
void cekTabrakan() {
    for (int i = 0; i < JUMLAH_BOLA; i++) {         // P4: for
        if (bolaAktif[i]) {
            pantulDinding(i);
            pantulPaddle(i);
            if (bolaAktif[i]) {
                tabrakBalok(i);
            }
        }
    }
    gerakItem();
}