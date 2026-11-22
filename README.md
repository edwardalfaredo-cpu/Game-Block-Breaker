# Brick Breaker (Game-Block-Breaker)

Game **Brick Breaker** berbasis terminal, dibuat dengan **C++** dan library **ncurses**.
Proyek akhir mata kuliah **Dasar Pemrograman dan Algoritma** (S1 Sistem Informasi, Universitas Lampung).

> GAME BLOCK BREAKER.

## Anggota Kelompok

| Nama | NPM | Tugas |
|---|---|---|
|Alfaredo Edward Sarip | 2617052009 | Tampilan, menu, dan main.cpp |
|Syifa Dhiya Rahmadani | 2617052008 | Gerak bola dan tabrakan |
|Ardian Dhani Sefa | 2667052001 | Logika game, item, dan high score |

## Tentang Game

Pemain menggerakkan **paddle** untuk memantulkan bola dan menghancurkan **balok**.
Tujuannya mengumpulkan **skor setinggi mungkin** dalam waktu **60 detik** dan diberikan nyawa sebanyak **3 hati** apabila sebelum waktu **60 detik** nyawa yang diberikan sudah habis karena bola jatuh sebanyak 3 kali maka game selesai dan **game over**.dan yang mendapatkan Skor tertinggi akan masuk ke tabel **High Score**.

### Aturan

- Waktu bermain: **60 detik**
- Nyawa: **3**. Nyawa berkurang 1 saat bola jatuh.
- Skor: **10 poin** per balok yang hancur
- Kalau bola ada banyak (Multi-Ball), nyawa baru berkurang saat **semua bola** sudah jatuh
- Game selesai kalau **waktu habis** atau **nyawa habis**
- Kalau semua balok hancur, balok **diisi ulang** supaya skor bisa terus naik

### Item

Beberapa balok bertanda menjatuhkan item. Tangkap item dengan paddle.

| Balok | Item | Efek |
|---|---|---|
| `[ T ]` | +Waktu | Tambah 10 detik |
| `[ M ]` | Multi-Ball | Bola menjadi 3 |

### Kontrol

| Tombol | Fungsi |
|---|---|
| Panah kiri / kanan | Geser paddle |
| Panah atas / bawah | Pilih menu |
| Enter | Pilih menu |

## Persyaratan

- Windows 11
- Compiler **g++ (MinGW)**
- Library **ncurses**
- Terminal yang cukup besar (minimal sekitar 50 kolom x 28 baris)

## Cara Compile dan Menjalankan

Buka terminal di folder proyek, lalu:

```
g++ *.cpp -lncurses -o brickbreaker
brickbreaker.exe
```

Catatan:

- Pastikan tidak ada file percobaan yang punya `main()` lain (misalnya `tes.cpp`) di folder ini, karena akan menyebabkan error `multiple definition of main`.
- Kalau muncul `Permission denied` saat compile, tutup dulu program yang sedang berjalan, atau ganti nama file keluaran.

## Struktur File

```
Game-Block-Breaker/
├── main.cpp          Pintu masuk program dan menu (Orang A)
├── tampilan.h/.cpp   Menggambar arena, menu, dan layar (Orang A)
├── bola.h/.cpp       Gerak bola (Orang B)
├── tabrakan.h/.cpp   Pantulan dan tabrakan (Orang B)
├── logika.h/.cpp     Game loop, timer, item (Orang C)
├── highscore.h/.cpp  Simpan dan urutkan skor (Orang C)
├── data.h/.cpp       Variabel bersama (Orang C)
└── README.md
```

### Variabel bersama (`data.h`)

`data.h` berisi variabel yang dipakai bersama oleh semua anggota (posisi paddle, bola, balok, item, skor, nyawa, waktu).
File ini **dibekukan**: nama, tipe, dan arti variabel tidak boleh diubah sendiri.
Kalau butuh variabel baru, sepakati di grup, lalu Orang C yang menambahkannya.

## Materi Perkuliahan yang Dipakai

| Modul | Dipakai untuk |
|---|---|
| Pertemuan 2 | Tipe data, variabel, operator, cara compile |
| Pertemuan 3 | Percabangan `if` dan `switch-case` |
| Pertemuan 4 | Perulangan `for`, `while`, nested loop, `break` |
| Pertemuan 6 | Array (balok, bola, high score) |
| Pertemuan 7 | Bubble sort untuk urutan high score |
| Pertemuan 8 | Function (pembagian tugas per fungsi) |
| Pertemuan 10 | File teks untuk menyimpan `highscore.txt` |
| Pertemuan 11 | Dasar ncurses: input, tampilan, tombol panah |
| Pertemuan 12 | Jendela (`newwin`, `box`), warna, `Sleep` |

Tambahan kecil di luar modul: `nodelay()` (input tanpa menunggu), `werase()`, serta `extern`, `const`, dan `#ifndef` untuk membagi variabel antar file.

## Cara Kerja Tim (Git)

Tiap anggota bekerja di branch masing-masing:

- `fitur-tampilan` **Alfaredo**
- `fitur-bola` **Syifa**
- `fitur-logika` **Ardian**

Alur: **commit** dan **push** di branch sendiri, lalu buka **Pull Request** ke `main`.
Gabungkan ke `main` hanya kalau kode sudah bisa dikompilasi.