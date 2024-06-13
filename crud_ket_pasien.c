#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

int isTanggalExists(data* data, const char* id, const char* tanggal) {
    dua* current = data->dua;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0 && strcmp(current->tanggal, tanggal) == 0) {
            return 1;  // Tanggal ditemukan
        }
        current = current->next;
    }
    return 0;  // Tanggal tidak ditemukan
}

void convertTanggal(const char* input, char* output, int format_type) {
    int day, month, year;
    sscanf(input, "%d-%d-%d", &day, &month, &year);

    const char* bulan_indonesia[] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni",
        "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };

    const char* bulan_inggris[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    if (format_type == 1) {
        sprintf(output, "%02d %s %04d", day, bulan_indonesia[month - 1], year);
    } else {
        sprintf(output, "%02d-%s-%02d", day, bulan_inggris[month - 1], year % 100);
    }
}


int selectTanggalKedatangan(data* data, const char* id) {
    dua* current = data->dua;
    int index = 0;
    int selected_index = -1;

    printf("Tanggal kedatangan yang tersedia untuk ID pasien %s:\n", id);
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            printf("%d. %s\n", index + 1, current->tanggal);
            index++;
        }
        current = current->next;
    }

    if (index == 0) {
        printf("Tidak ada tanggal kedatangan yang ditemukan untuk ID pasien %s\n", id);
        return -1;
    }

    printf("Pilih tanggal kedatangan (1-%d): ", index);
    scanf("%d", &selected_index);
    getchar();  // Consume newline

    if (selected_index < 1 || selected_index > index) {
        printf("Pilihan tidak valid.\n");
        return -1;
    }

    return selected_index - 1;
}

// Fungsi nyari ID pasien di linked list "satu"
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

// Fungsi nyari ID pasien di linked list "dua"
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

// Fungsi biaya tindakan berdasarkan tindakan di linked list "tiga"
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

// Fungsi buat nambahin entry ke linked list yang "dua"
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

    char tanggal_input[MAX_LEN], tanggal_converted[MAX_LEN];
    char diagnosis[MAX_LEN], tindakan[MAX_LEN];
    int biaya_tindakan = 0;

    printf("Silahkan menambah riwayat medis pasien\n");
    printf("Tanggal kedatangan pasien di klinik X (dd-mm-yyyy): ");
    fgets(tanggal_input, MAX_LEN, stdin);
    strtok(tanggal_input, "\n");

    convertTanggal(tanggal_input, tanggal_converted, 1);  // Format Indonesia (e.g., 24 Juli 2022)

    if (isTanggalExists(data, id, tanggal_converted)) {
        printf("Tanggal kedatangan %s sudah terdaftar untuk pasien dengan ID %s.\n", tanggal_converted, id);
        return;
    }

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

    // Asumsikan kontrol tanggal adalah 3 hari setelah tanggal kedatangan
    char kontrol[MAX_LEN];
    // Anda perlu menambahkan logika untuk menambah 3 hari ke tanggal kedatangan dan menangani akhir bulan dan tahun kabisat.

    int biaya_total = 140000 + biaya_tindakan;

    dua* new_entry = (dua*)malloc(sizeof(dua));
    if (!new_entry) {
        printf("Gagal menambahkan entry baru, tidak cukup memori.\n");
        return;
    }
    strncpy(new_entry->tanggal, tanggal_converted, MAX_LEN);
    strncpy(new_entry->id, id, MAX_LEN);
    strncpy(new_entry->diagnosis, diagnosis, MAX_LEN);
    strncpy(new_entry->tindakan, tindakan, MAX_LEN);
    strncpy(new_entry->kontrol, kontrol, MAX_LEN);
    new_entry->biaya = biaya_total;
    new_entry->next = NULL;

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


// Fungsi update
void updateEntry(data* data) {
    char id[MAX_LEN];
    printf("Masukkan ID pasien: ");
    fgets(id, MAX_LEN, stdin);
    strtok(id, "\n");

    int selected_index = selectTanggalKedatangan(data, id);
    if (selected_index == -1) {
        return;
    }

    dua* entry = data->dua;
    int index = 0;
    while (entry != NULL) {
        if (strcmp(entry->id, id) == 0) {
            if (index == selected_index) {
                break;
            }
            index++;
        }
        entry = entry->next;
    }

    if (entry == NULL) {
        printf("ID Pasien atau tanggal kedatangan tidak ditemukan.\n");
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
                char tanggal_input[MAX_LEN], tanggal_converted[MAX_LEN];
                printf("Tanggal kedatangan pasien (dd-mm-yyyy): ");
                fgets(tanggal_input, MAX_LEN, stdin);
                strtok(tanggal_input, "\n");

                convertTanggal(tanggal_input, tanggal_converted, 1);  // Format Indonesia (e.g., 24 Juli 2022)

                if (isTanggalExists(data, id, tanggal_converted)) {
                    printf("Tanggal kedatangan %s sudah terdaftar untuk pasien dengan ID %s.\n", tanggal_converted, id);
                } else {
                    strncpy(entry->tanggal, tanggal_converted, MAX_LEN);
                }
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



// Fungsi buat hapus entry dari linked list yang "dua"
void deleteEntry(data* data) {
    char id[MAX_LEN];
    printf("Masukkan ID pasien: ");
    fgets(id, MAX_LEN, stdin);
    strtok(id, "\n");

    int selected_index = selectTanggalKedatangan(data, id);
    if (selected_index == -1) {
        return;
    }

    dua* prev = NULL;
    dua* current = data->dua;
    int index = 0;

    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            if (index == selected_index) {
                if (prev == NULL) {
                    data->dua = current->next;
                } else {
                    prev->next = current->next;
                }
                free(current);
                printf("Entry untuk ID pasien %s pada tanggal %s telah dihapus.\n", id, current->tanggal);
                return;
            }
            index++;
        }
        prev = current;
        current = current->next;
    }

    printf("ID Pasien atau tanggal kedatangan tidak ditemukan.\n");
}


// Fungsi buat nampilin entry dari linked list "dua"
void displayEntry(data* data) {
    char id[MAX_LEN];
    printf("Masukkan ID pasien: ");
    fgets(id, MAX_LEN, stdin);
    strtok(id, "\n");

    int selected_index = selectTanggalKedatangan(data, id);
    if (selected_index == -1) {
        return;
    }

    dua* entry = data->dua;
    int index = 0;
    while (entry != NULL) {
        if (strcmp(entry->id, id) == 0) {
            if (index == selected_index) {
                printf("RIWAYAT PASIEN %s\n", id);
                printf("Pasien datang di klinik X pada tanggal : %s\n", entry->tanggal);
                printf("Diagnosis yang dimiliki pasien: %s\n", entry->diagnosis);
                printf("Tindakan yang diberikan ke pasien: %s\n", entry->tindakan);
                printf("Tanggal kontrol: %s\n", entry->kontrol);
                return;
            }
            index++;
        }
        entry = entry->next;
    }

    printf("ID Pasien atau tanggal kedatangan tidak ditemukan.\n");
}


// Fungsi utama untuk menjalankan CRUD
void crud_ket_pasien(data* data) {
    printf("Pilih operasi apa yang akan dilakukan:\n1. Penambahan\n2. Pengubahan\n3. Penghapusan\n4. Menampilkan informasi\nPilihan: ");
    int choice;
    scanf("%d", &choice);
    getchar();  // Consume newline
    
    // pilihan menu
    switch (choice) {
        case 1: addEntry(data); break;
        case 2: updateEntry(data); break;
        case 3: deleteEntry(data); break;
        case 4: displayEntry(data); break;
        default: printf("Operasi tidak valid.\n"); break;
    }
}
