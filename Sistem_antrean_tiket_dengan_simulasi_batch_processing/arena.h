#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

// Deklarasi tipe data (opaque struct) untuk menyembunyikan detail implementasi dari pengguna luar
typedef struct Arena Arena;

// Fungsi untuk menginisialisasi sistem Arena dan mengalokasikan memori utama sesuai kapasitas yang diminta
Arena* arena_create(size_t size);

// Fungsi untuk mengalokasikan blok memori baru di dalam Arena dan mengembalikan nilai offset posisinya
int arena_alloc(Arena *arena, size_t size);

// Fungsi untuk mendapatkan alamat pointer fisik secara spesifik berdasarkan nilai offset yang diberikan
void* arena_get(Arena *arena, int offset);

// Fungsi untuk mereset posisi offset kembali ke 0 tanpa melakukan dealokasi memori fisik pada sistem
void arena_reset(Arena *arena);

// Fungsi untuk menampilkan representasi data mentah (raw memory) dari Arena dalam format heksadesimal
void arena_dump(Arena *arena);

// Fungsi untuk membebaskan seluruh alokasi memori fisik Arena agar dikembalikan kepada sistem operasi
void arena_destroy(Arena *arena);

#endif