#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

// Fungsi untuk mencari pasien berdasarkan ID dalam linked list dua
int findPasien(data* data, const char* id) {
    dua* current = data->dua;
    int index = 0;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;  
}

// Fungsi untuk mencari pasien berdasarkan ID dalam linked list satu
satu* findPasienInSatu(data* data, const char* id) {
    satu* current = data->satu;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;  
}

// Fungsi untuk mendapatkan biaya tindakan berdasarkan tindakan dalam linked list tiga
int getBiayaTindakan(data* data, const char* tindakan) {
    tiga* current = data->tiga;
    while (current != NULL) {
        if (strcmp(current->aktivitas, tindakan) == 0) {
            return current->biaya;
        }
        current = current->next;
    }
    return 0; 
}

// Fungsi untuk menambahkan entry ke linked list dua
void addEntry(data* data) {
    char id[MAX_LEN];
    printf("Masukkan ID pasien: ");
    fgets(id, MAX_LEN, stdin);
    strtok(id, "\n");

    satu* pasien = findPasienInSatu(data, id);
    if (pasien == NULL) {
        printf("Pasien dengan ID %s belum pernah mendaftar di klinik X\n", id);
        return;
    }

    char tanggal[MAX_LEN], diagnosis[MAX_LEN], tindakan[MAX_LEN];
    int biaya_tindakan = 0;

    printf("Silahkan menambah riwayat medis pasien\n");
    printf("Tanggal kedatangan pasien di klinik X (dd mon yyyy): ");
    fgets(tanggal, MAX_LEN, stdin);
    strtok(tanggal, "\n");

    printf("Diagnosis yang dimiliki pasien:\n1. Dehidrasi\n2. Pusing\n3. Masuk Angin\n4. Keseleo\nPilih (1-4): ");
    int diag_choice;
    scanf("%d", &diag_choice);
    getchar();  // Consume newline

    switch (diag_choice) {
        case 1: strcpy(diagnosis, "Dehidrasi"); break;
        case 2: strcpy(diagnosis, "Pusing"); break;
        case 3: strcpy(diagnosis, "Masuk Angin"); break;
        case 4: strcpy(diagnosis, "Keseleo"); break;
        default: strcpy(diagnosis, ""); break;
    }

    printf("Tindakan yang diberikan kepada pasien:\n1. Vaksinasi\n2. Cek gula darah\n3. Pemasangan infus\n4. Pengobatan\nPilih (1-4): ");
    int tindakan_choice;
    scanf("%d", &tindakan_choice);
    getchar();  // Consume newline

    switch (tindakan_choice) {
        case 1: strcpy(tindakan, "Vaksinasi"); break;
        case 2: strcpy(tindakan, "Cek gula darah"); break;
        case 3: strcpy(tindakan, "Pemasangan infus"); break;
        case 4: strcpy(tindakan, "Pengobatan"); break;
        default: strcpy(tindakan, ""); break;
    }

    biaya_tindakan = getBiayaTindakan(data, tindakan);

    char kontrol[MAX_LEN] = "01-Jan-23"; // Set kontrol date to "01-Jan-23"

    int biaya_total = 140000 + biaya_tindakan;

    // Membuat node baru untuk linked list dua
    dua* new_entry = (dua*)malloc(sizeof(dua));
    if (!new_entry) {
        printf("Gagal menambahkan entry baru, tidak cukup memori.\n");
        return;
    }
    strncpy(new_entry->tanggal, tanggal, MAX_LEN);
    strncpy(new_entry->id, id, MAX_LEN);
    strncpy(new_entry->diagnosis, diagnosis, MAX_LEN);
    strncpy(new_entry->tindakan, tindakan, MAX_LEN);
    strncpy(new_entry->kontrol, kontrol, MAX_LEN);
    new_entry->biaya = biaya_total;
    new_entry->next = NULL;

    // Menambahkan entry baru ke linked list dua
    dua* current = data->dua;
    if (current == NULL) {
        data->dua = new_entry;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_entry;
    }

    printf("Entry berhasil ditambahkan.\n");
}

// Fungsi untuk mengupdate entry dalam linked list dua
void updateEntry(data* data) {
    char id[MAX_LEN];
    printf("Masukkan ID pasien: ");
    fgets(id, MAX_LEN, stdin);
    strtok(id, "\n");

    dua* entry = data->dua;
    while (entry != NULL) {
        if (strcmp(entry->id, id) == 0) {
            break;
        }
        entry = entry->next;
    }
    if (entry == NULL) {
        printf("ID Pasien tidak ditemukan.\n");
        return;
    }

    int biaya_tindakan = 0;
    int choice = 0;

    while (choice != 4) {
        printf("Opsi pengubahan data riwayat pasien:\n");
        printf("1. Tanggal kedatangan pasien\n");
        printf("2. Diagnosa pasien\n");
        printf("3. Tindakan yang diberikan kepada pasien\n");
        printf("4. Tidak ada pengubahan\n");
        printf("Pilih opsi (1-4): ");
        scanf("%d", &choice);
        getchar();  // Consume newline

        switch (choice) {
            case 1: {
                char tanggal[MAX_LEN];
                printf("Tanggal kedatangan pasien (dd-mm-yyyy): ");
                fgets(tanggal, MAX_LEN, stdin);
                strtok(tanggal, "\n");
                strncpy(entry->tanggal, tanggal, MAX_LEN);
                break;
            }
            case 2: {
                char diagnosis[MAX_LEN];
                printf("Diagnosis yang dimiliki pasien:\n1. Dehidrasi\n2. Pusing\n3. Masuk Angin\n4. Keseleo\nPilih (1-4): ");
                int diag_choice;
                scanf("%d", &diag_choice);
                getchar();  // Consume newline
                switch (diag_choice) {
                    case 1: strcpy(diagnosis, "Dehidrasi"); break;
                    case 2: strcpy(diagnosis, "Pusing"); break;
                    case 3: strcpy(diagnosis, "Masuk Angin"); break;
                    case 4: strcpy(diagnosis, "Keseleo"); break;
                    default: strcpy(diagnosis, ""); break;
                }
                strncpy(entry->diagnosis, diagnosis, MAX_LEN);
                break;
            }
            case 3: {
                char tindakan[MAX_LEN];
                printf("Tindakan yang diambil pasien:\n1. Vaksinasi\n2. Cek gula darah\n3. Pemasangan infus\n4. Pengobatan\nPilih (1-4): ");
                int tindakan_choice;
                scanf("%d", &tindakan_choice);
                getchar();  // Consume newline
                switch (tindakan_choice) {
                    case 1: strcpy(tindakan, "Vaksinasi"); biaya_tindakan = 100000; break;
                    case 2: strcpy(tindakan, "Cek gula darah"); biaya_tindakan = 25000; break;
                    case 3: strcpy(tindakan, "Pemasangan infus"); biaya_tindakan = 125000; break;
                    case 4: strcpy(tindakan, "Pengobatan"); biaya_tindakan = 125000; break;
                    default: strcpy(tindakan, ""); biaya_tindakan = 0; break;
                }
                strncpy(entry->tindakan, tindakan, MAX_LEN);
                break;
            }
            case 4:
                printf("Pengubahan selesai.\n");
                break;
            default:
                printf("Opsi tidak valid.\n");
                break;
        }
    }

    // Perbarui biaya total
    entry->biaya = 15000 + 125000 + biaya_tindakan;
    printf("Entry telah diupdate.\n");
}

// Fungsi untuk menghapus entry dalam linked list dua
void deleteEntry(data* data) {
    char id[MAX_LEN];
    printf("Masukkan ID pasien: ");
    fgets(id, MAX_LEN, stdin);
    strtok(id, "\n");

    dua* prev = NULL;
    dua* current = data->dua;

    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            if (prev == NULL) {
                data->dua = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Entry untuk ID pasien %s telah dihapus.\n", id);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("ID Pasien tidak ditemukan.\n");
}

// Fungsi untuk menampilkan entry dalam linked list dua
void displayEntry(data* data) {
    char id[MAX_LEN];
    printf("Masukkan ID pasien: ");
    fgets(id, MAX_LEN, stdin);
    strtok(id, "\n");

    dua* entry = data->dua;
    while (entry != NULL) {
        if (strcmp(entry->id, id) == 0) {
            printf("RIWAYAT PASIEN %s\n", id);
            printf("Pasien datang di klinik X pada tanggal : %s\n", entry->tanggal);
            printf("Diagnosis yang dimiliki pasien: %s\n", entry->diagnosis);
            printf("Tindakan yang diberikan ke pasien: %s\n", entry->tindakan);
            printf("Tanggal kontrol: %s\n", entry->kontrol);
            return;
        }
        entry = entry->next;
    }

    printf("ID Pasien tidak ditemukan.\n");
}

// Fungsi utama untuk menjalankan CRUD operasi
void crud_ket_pasien(data* data) {
    printf("Pilih operasi apa yang akan dilakukan:\n1. Penambahan\n2. Pengubahan\n3. Penghapusan\n4. Menampilkan informasi\nPilihan: ");
    int choice;
    scanf("%d", &choice);
    getchar();  // Consume newline

    switch (choice) {
        case 1: addEntry(data); break;
        case 2: updateEntry(data); break;
        case 3: deleteEntry(data); break;
        case 4: displayEntry(data); break;
        default: printf("Operasi tidak valid.\n"); break;
    }
}
