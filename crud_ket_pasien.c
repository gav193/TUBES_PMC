#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROWS 1000
#define MAX_COLS_1 9
#define MAX_COLS_2 7
#define MAX_COLS_3 3
#define MAX_LEN 100

extern char satu[MAX_ROWS][MAX_COLS_1][MAX_LEN];
extern char dua[MAX_ROWS][MAX_COLS_2][MAX_LEN];
extern char tiga[MAX_ROWS][MAX_COLS_3][MAX_LEN];


int findPasien(const char* id) {
    for (int i = 0; i < MAX_ROWS; ++i) {
        if (strcmp(dua[i][2], id) == 0) {
            return i;
        }
    }
    return -1;  
}

int findPasienInSatu(const char* id) {
    for (int i = 0; i < MAX_ROWS; ++i) {
        if (strcmp(satu[i][8], id) == 0) { 
            return i;
        }
    }
    return -1;  
}

int getBiayaTindakan(const char* tindakan) {
    for (int i = 0; i < MAX_ROWS; ++i) {
        if (strcmp(tiga[i][1], tindakan) == 0) {
            return atoi(tiga[i][2]);
        }
    }
    return 0; 
}

//fungsi add
void addEntry() {
    char id[MAX_LEN];
    printf("Masukkan ID pasien: ");
    fgets(id, MAX_LEN, stdin);
    strtok(id, "\n");

    int pasienIndex = findPasienInSatu(id);
    if (pasienIndex == -1) {
        printf("Pasien dengan ID %s belum pernah mendaftar di klinik X\n", id);
        return;
    }

    int i;
    for (i = 0; i < MAX_ROWS; ++i) {
        if (dua[i][0][0] == '\0') {
            break;
        }
    }
    if (i == MAX_ROWS) {
        printf("Informasi Pasien sudah terisi, tidak bisa ditambahkan.\n");
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

    biaya_tindakan = getBiayaTindakan(tindakan);

    char kontrol[MAX_LEN] = "01-Jan-23"; // Set kontrol date to "01-Jan-23"

    int biaya_total = 140000 + biaya_tindakan;

    snprintf(dua[i][0], MAX_LEN, "%d", i + 1);
    strncpy(dua[i][1], tanggal, MAX_LEN);
    strncpy(dua[i][2], id, MAX_LEN);
    strncpy(dua[i][3], diagnosis, MAX_LEN);
    strncpy(dua[i][4], tindakan, MAX_LEN);
    strncpy(dua[i][5], kontrol, MAX_LEN);
    snprintf(dua[i][6], MAX_LEN, "%d", biaya_total);

    printf("Entry berhasil ditambahkan.\n");
}


//funfsi ubah
void updateEntry() {
    char id[MAX_LEN];
    printf("Masukkan ID pasien: ");
    fgets(id, MAX_LEN, stdin);
    strtok(id, "\n");

    int row = findPasien(id);
    if (row == -1) {
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
                strncpy(dua[row][1], tanggal, MAX_LEN);
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
                strncpy(dua[row][3], diagnosis, MAX_LEN);
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
                strncpy(dua[row][4], tindakan, MAX_LEN);
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
    int biaya_total = 15000 + 125000 + biaya_tindakan;
    snprintf(dua[row][6], MAX_LEN, "%d", biaya_total);

    printf("Entry telah diupdate.\n");
}

//fungsi delete
void deleteEntry() {
    char id[MAX_LEN];
    printf("Masukkan ID pasien: ");
    fgets(id, MAX_LEN, stdin);
    strtok(id, "\n");

    int rows[MAX_ROWS];
    int count = 0;

    // Cari semua baris dengan ID pasien yang sesuai
    for (int i = 0; i < MAX_ROWS; ++i) {
        if (strcmp(dua[i][2], id) == 0) {
            rows[count++] = i;
        }
    }

    if (count == 0) {
        printf("ID Pasien tidak ditemukan.\n");
        return;
    }

    // Tampilkan semua tanggal riwayat kedatangan untuk pasien yang sesuai
    printf("Pilih tanggal riwayat kedatangan pasien:\n");
    for (int i = 0; i < count; ++i) {
        printf("%d. %s\n", i + 1, dua[rows[i]][1]);
    }

    // Minta pengguna memilih tanggal
    int choice;
    printf("Pilih opsi (1-%d): ", count);
    scanf("%d", &choice);
    getchar();  // Konsumsi newline

    if (choice < 1 || choice > count) {
        printf("Opsi tidak valid.\n");
        return;
    }

    int row = rows[choice - 1];

    // Hapus semua kolom kecuali kolom 0 (nomor)
    for (int i = 1; i < MAX_COLS_2; ++i) {
        dua[row][i][0] = '\0';
    }

    printf("Entry untuk ID pasien %s pada tanggal %s telah dihapus.\n", id, dua[row][1]);
}


//fungsi display
void displayEntry() {
    char id[MAX_LEN];
    printf("Masukkan ID pasien: ");
    fgets(id, MAX_LEN, stdin);
    strtok(id, "\n");

    int row = findPasien(id);
    if (row == -1) {
        printf("ID Pasien tidak ditemukan.\n");
        return;
    }

    printf("RIWAYAT PASIEN %s\n", id);
    printf("Pasien datang di klinik X pada tanggal : %s\n", dua[row][1]);
    printf("Diagnosis yang dimiliki pasien: %s\n", dua[row][3]);
    printf("Tindakan yang diberikan ke pasien: %s\n", dua[row][4]);
    printf("Tanggal kontrol: %s\n", dua[row][5]);
}

//main dari file ini
void crud_ket_pasien() {
    printf("Pilih operasi apa yang akan dilakukan:\n1. Penambahan\n2. Pengubahan\n3. Penghapusan\n4. Menampilkan informasi\nPilihan: ");
    int choice;
    scanf("%d", &choice);
    getchar();  // Consume newline

    switch (choice) {
        case 1: addEntry(); break;
        case 2: updateEntry(); break;
        case 3: deleteEntry(); break;
        case 4: displayEntry(); break;
        default: printf("Operasi tidak valid.\n"); break;
    }
}
