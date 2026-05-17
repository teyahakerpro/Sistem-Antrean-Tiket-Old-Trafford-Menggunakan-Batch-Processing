#include "queue_arena.h"
#include <stdio.h>

// Fungsi untuk mengalokasikan memori dan memasukkan data baru ke bagian belakang antrean
void enqueue(Arena *arena, int *front_offset, int *rear_offset, int fan_id) {
    // Meminta alokasi ruang pada memori Arena sebesar ukuran struktur QueueNode
    int new_node_offset = arena_alloc(arena, sizeof(QueueNode));
    
    // Mengecek apakah proses alokasi gagal (Arena penuh)
    // Jika nilai offset -1, maka fungsi dihentikan agar tidak terjadi akses memori ilegal
    if (new_node_offset == -1) {
        printf("Server penuh! Fans ID %d gagal masuk antrean.\n", fan_id);
        return;
    }

    // Mendapatkan alamat fisik memori untuk node baru dan mengisi datanya
    QueueNode *new_node = (QueueNode*) arena_get(arena, new_node_offset);
    new_node->fan_id = fan_id;
    new_node->next_offset = -1; // Set ke -1 karena ini adalah elemen paling akhir

    // Mengecek apakah kondisi antrean saat ini sedang kosong
    if (*rear_offset == -1) {
        // Jika antrean kosong, node baru bertindak sebagai elemen pertama sekaligus terakhir
        *front_offset = new_node_offset;
        *rear_offset = new_node_offset;
    } else {
        // Jika antrean sudah berisi, perbarui pointer dari elemen terakhir sebelumnya
        // agar menunjuk ke offset dari node yang baru saja masuk
        QueueNode *rear_node = (QueueNode*) arena_get(arena, *rear_offset);
        rear_node->next_offset = new_node_offset;
        *rear_offset = new_node_offset; // Perbarui batas akhir antrean ke node baru
    }
    printf("Fans ID %d berhasil masuk antrean Old Trafford (Offset: %d)\n", fan_id, new_node_offset);
}

// Fungsi untuk menghapus dan mengambil data dari elemen terdepan antrean
int dequeue(Arena *arena, int *front_offset, int *rear_offset) {
    // Memvalidasi apakah antrean kosong sebelum melakukan proses penarikan
    // Jika kosong, kembalikan nilai -1 sebagai indikator error
    if (*front_offset == -1) return -1; 

    // Mengambil data dari elemen terdepan sebelum pointer offset-nya digeser
    QueueNode *front_node = (QueueNode*) arena_get(arena, *front_offset);
    int id = front_node->fan_id;
    int next = front_node->next_offset;

    // Menggeser posisi pointer terdepan ke elemen selanjutnya dalam antrean
    *front_offset = next;
    
    // Mengecek apakah antrean menjadi kosong setelah elemen ditarik
    // Jika pointer terdepan menjadi -1, maka pointer akhir juga harus di-reset ke -1
    if (*front_offset == -1) {
        *rear_offset = -1; 
    }
    return id;
}

// Fungsi untuk memproses elemen antrean dalam jumlah tertentu secara berurutan (Round-Robin)
void process_batch(Arena *arena, int *front_offset, int *rear_offset, int batch_size) {
    printf("\n--- MEMPROSES BATCH TIKET (Dibuka %d Loket Old Trafford) ---\n", batch_size);
    int count = 0;
    int nomor_loket = 1; 
    
    // Iterasi memproses antrean selama batas batch belum tercapai DAN antrean belum kosong
    while (count < batch_size && *front_offset != -1) {
        int fan_id = dequeue(arena, front_offset, rear_offset);
        
        printf("[Loket %d] Tiket berhasil dicetak untuk Fans ID: %d\n", nomor_loket, fan_id);
        
        nomor_loket++;
        count++;
    }
    
    // Memvalidasi hasil proses untuk memberikan laporan operasi akhir
    if (count == 0) {
        printf("Semua loket kosong, tidak ada antrean.\n");
    } else {
        printf(">> %d fans sukses dilayani oleh loket pada sesi ini.\n", count);
    }
}

// Fungsi untuk melakukan traversal dan mencetak seluruh sisa elemen di dalam antrean
void display_queue(Arena *arena, int front_offset) {
    // Memvalidasi apabila tidak ada elemen untuk ditampilkan
    if (front_offset == -1) {
        printf("Antrean saat ini kosong.\n");
        return;
    }
    
    int current = front_offset;
    printf("Sisa Antrean: ");
    
    // Melakukan perulangan untuk menelusuri setiap node menggunakan nilai next_offset
    while (current != -1) {
        QueueNode *node = (QueueNode*) arena_get(arena, current);
        printf("[ID %d] ", node->fan_id);
        current = node->next_offset;
    }
    printf("\n");
}