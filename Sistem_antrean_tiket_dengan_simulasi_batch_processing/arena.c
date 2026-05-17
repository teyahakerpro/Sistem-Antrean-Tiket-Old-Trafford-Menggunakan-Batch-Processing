#include "arena.h"
#include <stdio.h>
#include <stdlib.h>

// Struktur data untuk merepresentasikan Arena Allocator
// Menyimpan pointer ke blok memori utama, total kapasitas, dan posisi offset saat ini
struct Arena {
    char *buffer;
    size_t capacity;
    size_t offset;
};

// Fungsi untuk membuat dan menginisialisasi sistem Arena
Arena* arena_create(size_t size) {
    Arena *arena = (Arena*) malloc(sizeof(Arena));
    arena->buffer = (char*) malloc(size);
    arena->capacity = size;
    arena->offset = 0; // Mengatur offset pemakaian memori awal pada indeks 0
    return arena;
}

// Fungsi untuk memesan blok memori di dalam Arena
int arena_alloc(Arena *arena, size_t size) {
    // Mengecek apakah ukuran memori yang diminta melebihi sisa kapasitas Arena
    // Jika melebihi kapasitas, proses ditolak dan mengembalikan status error (-1)
    if (arena->offset + size > arena->capacity) {
        printf("Arena penuh!\n");
        return -1;
    }

    // Menyimpan nilai offset saat ini sebelum diperbarui
    int off = arena->offset;
    // Menambahkan ukuran alokasi baru ke offset arena
    arena->offset += size;
    return off;
}

// Fungsi untuk menerjemahkan nilai offset menjadi alamat pointer memori fisik
void* arena_get(Arena *arena, int offset) {
    return arena->buffer + offset;
}

// Fungsi untuk mereset pemakaian Arena
void arena_reset(Arena *arena) {
    // Mengembalikan penunjuk offset ke 0 tanpa menghapus data secara fisik
    arena->offset = 0;
}

// Fungsi untuk mencetak isi memori Arena dalam format Hex Dump 2D
void arena_dump(Arena *arena) {
    printf("\n--- VISUALISASI MEMORI ARENA (HEX DUMP 2D GRID) ---\n");
    printf("Kapasitas: %zu bytes | Terpakai: %zu bytes\n", arena->capacity, arena->offset);

    // Iterasi untuk mencetak baris, setiap baris mewakili 16 byte memori
    for (size_t i = 0; i < arena->capacity; i += 16) {
        printf("[%04zu] ", i); 

        // Iterasi untuk mencetak nilai heksadesimal per byte dalam satu baris
        for (size_t j = 0; j < 16; j++) {
            // Memastikan pembacaan memori tidak melewati batas total kapasitas Arena
            if (i + j < arena->capacity) {
                // Mengecek apakah indeks memori saat ini merupakan area yang sudah terpakai (dialokasikan)
                if (i + j < arena->offset) {
                    unsigned char *raw_memory = (unsigned char *)arena->buffer;
                    // Mencetak nilai memori mentah dalam format heksadesimal dua digit (huruf kapital)
                    printf("%02X ", raw_memory[i + j]);
                } else {
                    // Jika memori belum dialokasikan, cetak penanda visual kosong
                    printf("-- ");
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Fungsi untuk menghancurkan Arena dan membebaskan alokasi memori
void arena_destroy(Arena *arena) {
    free(arena->buffer);
    free(arena);
}