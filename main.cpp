#include <ncurses.h>

int main() {
    // 1. Inisialisasi layar ncurses
    initscr();

    // 2. Menulis teks ke *buffer* layar
    printw("hallo ini merupakan program pertama saya");

    // 3. Memperbarui layar agar teks muncul
    refresh();

    // 4. Menunggu pengguna menekan tombol apapun sebelum keluar
    getch();

    // 5. Membersihkan memori dan mengembalikan terminal ke mode normal
    endwin();

    return 0;
}