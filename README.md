# Sistem-Antrean-Tiket-Old-Trafford-Menggunakan-Batch-Processing
"A high-performance ticket queue simulation using a custom Arena Allocator in C. Features $O(1)$ memory allocation, zero fragmentation, raw memory Hex Dump visualization, and Round-Robin batch processing."

# 🏟️ Arena Allocator Ticket Queue System

Sistem simulasi antrean tiket (tema: Server Old Trafford Manchester United) yang dikembangkan menggunakan bahasa C dengan mengimplementasikan arsitektur **Arena Allocator** untuk manajemen memori tingkat rendah (*low-level memory management*).

Proyek ini dibangun untuk mendemonstrasikan efisiensi alokasi memori dinamis tanpa menggunakan fungsi `free()` secara individual, sehingga mengeliminasi risiko fragmentasi memori dan menurunkan *overhead* komputasi menjadi $O(1)$.

## ✨ Fitur Utama

- **Arena Allocator:** Manajemen memori tersentralisasi berbasis *offset* yang aman dari *buffer overflow*.
- **Queue Tanpa Pointer Tradisional:** Struktur data *First In, First Out* (FIFO) yang direpresentasikan menggunakan *integer offset* untuk menjaga memori tetap kontigu.
- **Visualisasi Hex Dump:** Fitur untuk membaca *raw memory* (memori mentah) dalam format heksadesimal 2D (*Little-Endian*) untuk membuktikan bahwa data tersimpan tanpa celah/pajak memori.
- **Round-Robin Batch Processing:** Distribusi beban pelayanan tiket ke beberapa loket secara bergiliran.
- **Edge-Cases Protected:** Algoritma yang kebal terhadap *stress test* kapasitas, *odd batching*, hingga penarikan antrean kosong.

## 🛠️ Teknologi yang Digunakan
- **Bahasa Pemrograman:** C
- **Paradigma:** Modular Programming, Low-level Memory Manipulation

## 🚀 Cara Menjalankan Program
Compile seluruh file *source code* menggunakan GCC:
```bash
gcc main.c arena.c queue_arena.c -o program
.\program.exe
