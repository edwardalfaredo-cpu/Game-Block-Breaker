#include "data.h"
#include "bola.h"

// ---------------- inisialisasi ----------------
void initBalok() {
    for (int r = 0; r < BARIS_BALOK; r++) {
        for (int k = 0; k < KOLOM_BALOK; k++) {
            int kode = (r * 3 + k) % 7;
            if (kode == 2)      balok[r][k] = 2;   // +Waktu
            else if (kode == 5) balok[r][k] = 3;   // Multi-Ball
            else                balok[r][k] = 1;   // biasa
        }
    }
}

void resetBola() {
    for (int i = 0; i < JUMLAH_BOLA; i++) {
        bolaAktif[i] = false;
        bolaX[i] = 0;
        bolaY[i] = 0;
        bolaDX[i] = 1;
        bolaDY[i] = -1;
    }
    bolaAktif[0] = true;
    bolaX[0] = paddleX + LEBAR_PADDLE / 2;
    bolaY[0] = TINGGI_ARENA - 2;
    itemAktif = false;
}

// ---------------- tabrakan balok ----------------
// balok hancur -> skor naik -> kalau bertanda (2/3) munculkan item
static void hancurkanBalok(int r, int k) {
    int jenis = balok[r][k];
    if (jenis >= 2 && !itemAktif) {
        itemAktif = true;
        itemJenis = jenis;
        itemX = k * LEBAR_BALOK + 2;   // tengah balok
        itemY = r + 1;                 // aturan data.h: y = r + 1
    }
    balok[r][k] = 0;
    skor += 10;
}

// ---------------- gerak satu bola ----------------
static void gerakBola(int i) {
    int yPaddle = TINGGI_ARENA - 1;
    int nx = bolaX[i] + bolaDX[i];
    int ny = bolaY[i] + bolaDY[i];

    // dinding kiri / kanan
    if (nx < 0 || nx >= LEBAR_ARENA) {
        bolaDX[i] = -bolaDX[i];
        nx = bolaX[i] + bolaDX[i];
    }
    // dinding atas
    if (ny < 0) {
        bolaDY[i] = -bolaDY[i];
        ny = bolaY[i] + bolaDY[i];
    }

    // paddle atau jatuh (nested if)
    if (ny == yPaddle && bolaDY[i] > 0) {
        if (nx >= paddleX && nx < paddleX + LEBAR_PADDLE) {
            bolaDY[i] = -1;
            if (nx < paddleX + LEBAR_PADDLE / 3)               bolaDX[i] = -1;
            else if (nx >= paddleX + 2 * LEBAR_PADDLE / 3)     bolaDX[i] = 1;
            ny = bolaY[i] + bolaDY[i];
        }
    } else if (ny > yPaddle) {
        bolaAktif[i] = false;   // bola jatuh
        return;
    }

    // balok
    int r = ny - 1;
    int k = nx / LEBAR_BALOK;
    if (r >= 0 && r < BARIS_BALOK && k >= 0 && k < KOLOM_BALOK) {
        if (balok[r][k] > 0) {
            hancurkanBalok(r, k);
            bolaDY[i] = -bolaDY[i];
            ny = bolaY[i] + bolaDY[i];
            if (ny < 0) ny = 0;
        }
    }

    bolaX[i] = nx;
    bolaY[i] = ny;
}

// ---------------- multi-ball ----------------
int aktifkanMultiBall() {
    int sumber = -1;
    for (int i = 0; i < JUMLAH_BOLA; i++) {
        if (bolaAktif[i]) { sumber = i; break; }
    }
    if (sumber == -1) return 0;

    int baru = 0;
    for (int j = 0; j < JUMLAH_BOLA; j++) {
        if (!bolaAktif[j]) {
            bolaAktif[j] = true;
            bolaX[j] = bolaX[sumber];
            bolaY[j] = bolaY[sumber];
            bolaDX[j] = (baru % 2 == 0) ? -1 : 1;
            bolaDY[j] = -1;
            baru++;
        }
    }
    return baru;
}

// ---------------- item jatuh ----------------
static void gerakItem() {
    static int hitung = 0;
    if (!itemAktif) return;
    hitung++;
    if (hitung % 2 != 0) return;       // item jatuh lebih lambat dari bola
    itemY++;
    if (itemY >= TINGGI_ARENA - 1) {
        if (itemX >= paddleX && itemX < paddleX + LEBAR_PADDLE) {
            if (itemJenis == 3) aktifkanMultiBall();
            else                waktuSisa += 5 * PUTARAN_PER_DETIK;  // +Waktu (hapus kalau bukan bagianmu)
        }
        itemAktif = false;
    }
}

// ---------------- pengecekan ----------------
bool semuaBolaJatuh() {
    for (int i = 0; i < JUMLAH_BOLA; i++) {
        if (bolaAktif[i]) return false;
    }
    return true;
}

bool blokHabis() {
    for (int r = 0; r < BARIS_BALOK; r++)
        for (int k = 0; k < KOLOM_BALOK; k++)
            if (balok[r][k] > 0) return false;
    return true;
}

// ---------------- dipanggil tiap putaran ----------------
void updateBola() {
    for (int i = 0; i < JUMLAH_BOLA; i++) {
        if (bolaAktif[i]) gerakBola(i);
    }
    gerakItem();
}