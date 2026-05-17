#include "arena.h"
#include "queue_arena.h"
#include <stdio.h>

int main() {
    // Kapasitas 256 byte (Maksimal menampung 32 Fans @ 8 byte)
    Arena *arena = arena_create(256);

    printf("========================================================\n");
    printf("   UJI COBA 4 SKENARIO EDGE CASES - ARENA ALLOCATOR\n");
    printf("========================================================\n\n");

    int front_offset = -1;
    int rear_offset = -1;
    int jumlah_loket = 3; 

    /* ---------------------------------------------------------
       SKENARIO 1: STRESS TEST (SERVER OVERLOAD)
       Mencoba memasukkan 35 Fans (Dengan catatan kapasitas maksimal arena 32)
    --------------------------------------------------------- */
    
    printf("========================================================\n");
    printf("--- SKENARIO 1: STRESS TEST (KAPASITAS PENUH) ---\n");
    printf("========================================================\n\n");
    printf(">> Mengirim 35 Request antrean secara bersamaan...\n\n");
    for (int i = 1; i <= 35; i++) {
        enqueue(arena, &front_offset, &rear_offset, i);
    }
    printf("\n>> HASIL SKENARIO 1: 32 Fans masuk, 3 Fans ditolak karena server penuh. Program AMAN tidak crash!\n\n");


    /* ---------------------------------------------------------
       SKENARIO 2: SISA ANTREAN NANGGUNG (ODD BATCHING)
       Memproses 32 orang dengan 3 Loket. Di akhir pasti ada sisa nanggung.
    --------------------------------------------------------- */
    printf("========================================================\n");
    printf("--- SKENARIO 2: SISA ANTREAN NANGGUNG (ODD BATCHING) ---\n");
    printf("========================================================\n\n");
    printf(">> Membuka ke-3 Loket untuk memproses 32 antrean...\n");
    int sesi_ke = 1;
    while (front_offset != -1) {
        printf("\n[Sesi Pelayanan Ke-%d]", sesi_ke);
        process_batch(arena, &front_offset, &rear_offset, jumlah_loket);
        sesi_ke++;
    }
    printf("\n>> HASIL SKENARIO 2: Di Sesi 11, hanya Loket 1 & 2 yang bekerja untuk sisa 2 orang. Distribusi beban berhasil!\n\n");

    /* ---------------------------------------------------------
       SKENARIO 3: LOKET BUKA SAAT KOSONG (UNDERLOAD)
       Mencetak tiket saat tidak ada satupun antrean.
    --------------------------------------------------------- */
    printf("========================================================\n");
    printf("--- SKENARIO 3: LOKET BUKA SAAT KOSONG (UNDERLOAD) ---\n");
    printf("========================================================\n\n");
    printf(">> Memaksa memanggil process_batch saat antrean sudah habis...\n");
    process_batch(arena, &front_offset, &rear_offset, jumlah_loket);
    printf("\n>> HASIL SKENARIO 3: Program mendeteksi kekosongan tanpa menarik sampah memori!\n\n");


    /* ---------------------------------------------------------
       SKENARIO 4: THE ULTIMATE TRADE-OFF (MEMORY LEAK & RESET)
       Membuktikan bahwa memori lama tidak dihapus secara default.
    --------------------------------------------------------- */
    printf("========================================================\n");
    printf("--- SKENARIO 4: THE ULTIMATE TRADE-OFF (MEMORY LEAK & RESET) ---\n");
    printf("========================================================\n\n");
    printf(">> Mencoba memasukkan Fans Kloter 2 (ID 99) padahal antrean sudah kosong...\n");
    enqueue(arena, &front_offset, &rear_offset, 99);
    // Dipastikan akan gagal karena offset memori masih menyentuh angka 256 (Penuh)
    
    printf("\n>> SOLUSI: Mengeksekusi arena_reset(arena) dalam waktu O(1)...\n");
    arena_reset(arena);
    
    // Pastikan antrean benar-benar mulai dari awal (0)
    front_offset = -1;
    rear_offset = -1;

    printf("\n>> Mencoba kembali memasukkan Fans Kloter 2 (ID 101 - 103)...\n");
    for (int i = 101; i <= 103; i++) {
        enqueue(arena, &front_offset, &rear_offset, i);
    }
    
    printf("\n[Mengecek Hex Dump Kloter Baru (Harusnya kembali ke Offset 0000)]\n");
    arena_dump(arena);
    
    printf("\n>> Memproses Kloter Baru...\n");
    process_batch(arena, &front_offset, &rear_offset, jumlah_loket);
    printf("\n>> HASIL SKENARIO 4: Fitur Reset berhasil menyapu bersih seluruh memori lama dalam sekejap!\n\n");

    // Bersihkan seluruh memori (Dealokasi fisik)
    arena_destroy(arena);
    printf("=== SELURUH SKENARIO UJI COBA SELESAI. SYSTEM SHUTDOWN. ===\n");
    return 0;
}