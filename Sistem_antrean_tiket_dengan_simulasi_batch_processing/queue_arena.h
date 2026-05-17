#ifndef QUEUE_ARENA_H
#define QUEUE_ARENA_H

#include "arena.h"

// Struktur data untuk merepresentasikan elemen (node) di dalam antrean
// Menyimpan data identitas pengguna dan nilai offset untuk menunjuk elemen berikutnya
typedef struct {
    int fan_id;       // Atribut untuk menyimpan data identitas unik dari pengguna/fans
    int next_offset;  // Nilai offset penunjuk posisi memori elemen selanjutnya di dalam Arena
} QueueNode;

// Fungsi untuk memasukkan elemen baru (fan_id) ke posisi paling belakang di dalam antrean Arena
void enqueue(Arena *arena, int *front_offset, int *rear_offset, int fan_id);

// Fungsi untuk mengambil dan mengeluarkan elemen dari posisi terdepan antrean, lalu mengembalikan nilai ID-nya
int dequeue(Arena *arena, int *front_offset, int *rear_offset);

// Fungsi untuk memproses sejumlah elemen antrean sekaligus secara bertahap sesuai kapasitas loket yang dibuka
void process_batch(Arena *arena, int *front_offset, int *rear_offset, int batch_size);

// Fungsi untuk menampilkan seluruh sisa elemen yang saat ini masih berada di dalam antrean secara berurutan
void display_queue(Arena *arena, int front_offset);

#endif