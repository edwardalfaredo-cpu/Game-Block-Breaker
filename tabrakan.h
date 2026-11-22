#ifndef TABRAKAN_H
#define TABRAKAN_H

void initBalok();       // isi array 2D balok
bool blokHabis();       // true kalau semua balok hancur
void cekTabrakan();     // dipanggil tiap putaran, SETELAH updateBola()

#endif