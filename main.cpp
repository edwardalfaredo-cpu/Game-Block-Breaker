#include "tampilan.h"
#include "data.h"

// Dibuat oleh Orang A: pintu masuk program (menu utama)

int main() {
    mulaiTampilan();

    // ----- DATA CONTOH untuk tes tampilan High Score (HAPUS NANTI) -----
    namaTop[0] = "Budi";  skorTop[0] = 250;
    namaTop[1] = "Sari";  skorTop[1] = 180;
    // --------------------------------------------------------------------

    bool jalan = true;
    while (jalan) {
        int pilih = menuUtama();

        switch (pilih) {
            case MENU_MULAI:
                // NANTI: ganti dengan fungsi game dari Orang C
                // Sementara: tampilkan layar Game Over contoh
                skor = 120;
                tampilGameOver(true);
                // TES SEMENTARA: ketik nama, lalu lihat di menu High Score
                namaTop[2] = mintaNama();
                skorTop[2] = skor;
                break;
            case MENU_SKOR:
                tampilHighScore();
                break;
            case MENU_CARA:
                tampilHowToPlay();
                break;
            case MENU_KELUAR:
                jalan = false;
                break;
        }
    }

    akhiriTampilan();
    return 0;
}