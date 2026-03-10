// 12S25007 - Tongam Prozona Manurung 

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Untuk exit()

#define MAX_SEATS_EKONOMI 11
#define MAX_SEATS_EKSEKUTIF 15
#define MAX_STRING_LEN 50
#define TOLL_FARE 20000

// Struktur untuk menyimpan informasi kursi
struct Seat {
    int number;
    int is_booked;
    char passenger_name[MAX_STRING_LEN];
};

// Fungsi untuk inisialisasi kursi
void initialize_seats(struct Seat seats[], int capacity) {
    for (int i = 0; i < capacity; i++) {
        seats[i].number = i + 1;
        seats[i].is_booked = 0;
        strcpy(seats[i].passenger_name, "");
    }
}

// Fungsi untuk menampilkan ketersediaan kursi
void display_seats(struct Seat seats[], int capacity, const char* type) {
    printf("\nKetersediaan Kursi %s (%d Kursi):\n", type, capacity);
    for (int i = 0; i < capacity; i++) {
        printf("Kursi %2d: %s\n", seats[i].number, seats[i].is_booked ? "[Terisi]" : "[Kosong]");
    }
}

// Fungsi untuk memilih dan memesan kursi
int book_seat(struct Seat seats[], int capacity, const char* passenger_name) {
    int seat_choice;
    while (1) {
        printf("Pilih nomor kursi (1-%d): ", capacity);
        // Memastikan input adalah angka
        if (scanf("%d", &seat_choice) != 1) {
            printf("Input tidak valid. Harap masukkan angka.\n");
            while (getchar() != '\n'); // Bersihkan buffer input
            continue;
        }
        while (getchar() != '\n'); // Bersihkan buffer input setelah angka

        if (seat_choice < 1 || seat_choice > capacity) {
            printf("Nomor kursi tidak valid. Silakan coba lagi.\n");
        } else if (seats[seat_choice - 1].is_booked) {
            printf("Kursi %d sudah terisi. Silakan pilih kursi lain.\n", seat_choice);
        } else {
            seats[seat_choice - 1].is_booked = 1;
            strcpy(seats[seat_choice - 1].passenger_name, passenger_name);
            return seat_choice;
        }
    }
}

// Fungsi utama program
int main() {
    struct Seat ekonomi_seats[MAX_SEATS_EKONOMI];
    struct Seat eksekutif_seats[MAX_SEATS_EKSEKUTIF];

    initialize_seats(ekonomi_seats, MAX_SEATS_EKONOMI);
    initialize_seats(eksekutif_seats, MAX_SEATS_EKSEKUTIF);

    char passenger_name[MAX_STRING_LEN];
    int service_type; // 1: Ekonomi, 2: Eksekutif
    int route_choice;
    int selected_seat_number = 0;
    char vehicle_type[MAX_STRING_LEN];
    char route_name[MAX_STRING_LEN];
    double total_price = 0;
    char use_toll; // 'Y' atau 'T' untuk pilihan tol

    printf("Selamat Datang di Sistem Ticketing KBT (Koperasi Bintang Tapanuli)\n");
    printf("------------------------------------------------------------------\n");

    // Input nama penumpang
    printf("Masukkan nama penumpang: ");
    scanf(" %[^\n]s", passenger_name); // Membaca string dengan spasi
    while (getchar() != '\n'); // Bersihkan buffer

    // Pilih jenis layanan
    while (1) {
        printf("\nPilih Jenis Layanan:\n");
        printf("1. Ekonomi\n");
        printf("2. Eksekutif\n");
        printf("Pilihan Anda: ");
        if (scanf("%d", &service_type) != 1) {
            printf("Input tidak valid. Harap masukkan angka 1 atau 2.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (service_type == 1) {
            strcpy(vehicle_type, "Ekonomi");
            break;
        } else if (service_type == 2) {
            strcpy(vehicle_type, "Eksekutif");
            break;
        } else {
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }

    // Pilih rute
    while (1) {
        printf("\nPilih Rute %s:\n", vehicle_type);
        if (service_type == 1) { // Ekonomi
            printf("1. Medan-Balige (Rp 90.000)\n");
            printf("2. Siantar-Balige (Rp 70.000)\n");
            printf("3. Medan-Sibolga (Rp 150.000)\n");
        } else { // Eksekutif
            printf("1. Medan-Balige (Rp 120.000)\n");
            printf("2. Siantar-Balige (Rp 90.000)\n");
            printf("3. Medan-Sibolga (Rp 200.000)\n");
        }
        printf("Pilihan Anda: ");
        if (scanf("%d", &route_choice) != 1) {
            printf("Input tidak valid. Harap masukkan angka rute.\n");
            while (getchar() != '\n');
            total_price = 0; // Reset untuk loop
            continue;
        }
        while (getchar() != '\n');

        switch (service_type) {
            case 1: // Ekonomi
                if (route_choice == 1) { strcpy(route_name, "Medan-Balige"); total_price = 90000; break; }
                if (route_choice == 2) { strcpy(route_name, "Siantar-Balige"); total_price = 70000; break; }
                if (route_choice == 3) { strcpy(route_name, "Medan-Sibolga"); total_price = 150000; break; }
                break;
            case 2: // Eksekutif
                if (route_choice == 1) { strcpy(route_name, "Medan-Balige"); total_price = 120000; break; }
                if (route_choice == 2) { strcpy(route_name, "Siantar-Balige"); total_price = 90000; break; }
                if (route_choice == 3) { strcpy(route_name, "Medan-Sibolga"); total_price = 200000; break; }
                break;
        }

        if (total_price > 0) { // Jika rute valid
            break;
        } else {
            printf("Pilihan rute tidak valid. Silakan coba lagi.\n");
        }
    }

    // Tanya penggunaan tol setelah rute dipilih
    while (1) {
        printf("Apakah penumpang ingin menggunakan rute tol? (Y/T): ");
        if (scanf(" %c", &use_toll) != 1) { // Perhatikan spasi di depan %c untuk mengabaikan newline
            printf("Input tidak valid. Harap masukkan Y atau T.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n'); // Bersihkan buffer

        if (use_toll == 'Y' || use_toll == 'y') {
            total_price += TOLL_FARE;
            strcat(route_name, " (via Tol)"); // Menambahkan informasi tol pada nama rute
            break;
        } else if (use_toll == 'T' || use_toll == 't') {
            break;
        } else {
            printf("Pilihan tidak valid. Silakan masukkan Y untuk Ya atau T untuk Tidak.\n");
        }
    }

    // Cek dan pilih kursi
    if (service_type == 1) { // Ekonomi
        display_seats(ekonomi_seats, MAX_SEATS_EKONOMI, "Ekonomi");
        selected_seat_number = book_seat(ekonomi_seats, MAX_SEATS_EKONOMI, passenger_name);
    } else { // Eksekutif
        display_seats(eksekutif_seats, MAX_SEATS_EKSEKUTIF, "Eksekutif");
        selected_seat_number = book_seat(eksekutif_seats, MAX_SEATS_EKSEKUTIF, passenger_name);
    }

    printf("\n--- Struk Pembelian Tiket ---\n");
    printf("Nama Penumpang : %s\n", passenger_name);
    printf("Rute           : %s\n", route_name);
    printf("Jenis Kendaraan: %s\n", vehicle_type);
    printf("Nomor Kursi    : %d\n", selected_seat_number);
    printf("Total Harga    : Rp %.2f\n", total_price);
    printf("-----------------------------\n");
    printf("Terima kasih telah menggunakan layanan KBT!\n");

    return 0;
}
