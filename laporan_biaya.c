#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "main.h"

// Fungsi untuk membuat format rupiah
void FormatRupiah(int Harga, char* mata_uang) {
    char temp[MAX_LEN];
    sprintf(temp, "%d", Harga);

    int len = strlen(temp);
    int count = 0;

    strcpy(mata_uang, "Rp"); // Menambahkan rupiah

    for (int i = 0; i < len; i++) {
        if (count > 0 && count % 3 == 0) { // Menambahkan titik pemisah
            strcat(mata_uang, ".");
        }
        strncat(mata_uang, &temp[len - i - 1], 1);
        count++;
    }

    len = strlen(mata_uang); // Membalikkan hasil
    for (int i = 2; i < len / 2 + 1; i++) {
        char temp2 = mata_uang[i];
        mata_uang[i] = mata_uang[len - i + 1];
        mata_uang[len - i + 1] = temp2;
    }
}

// Fungsi untuk membaca file CSV dan untuk memasukkannya ke struct dua
dua* ReadFileDua(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("File tidak dapat dibuka");
        exit(EXIT_FAILURE);
    }

    dua* head = NULL;
    dua* current = NULL;

    char line[512];

    fgets(line, sizeof(line), file); // Membiarkan headernya

    while (fgets(line, sizeof(line), file)) { // Membaca tiap baris
        dua* data_pasien = (dua*)malloc(sizeof(dua));
        if (!data_pasien) {
            perror("Gagal mengalokasi memori");
            exit(EXIT_FAILURE);
        }

        // Parsing
        char str_tanggal[20];
        char nama_bulan[20];
        int hari, tahun;
        sscanf(line, "%*d;%19[^;];%19[^;];%19[^;];%19[^;];%19[^;];%d",
            str_tanggal, data_pasien->id, data_pasien->diagnosis, data_pasien->tindakan,
            data_pasien->kontrol, &data_pasien->biaya);

        // Mengubah tanggal menjadi hari, bulan, dan tahun
        if (sscanf(str_tanggal, "%d-%3s-%2d", &hari, nama_bulan, &tahun) == 3) {
            // Menjadikan tahun dua digit menjadi 4 digit
            if (tahun < 100) {
                tahun += 2000;
            }
            if (strcmp(nama_bulan, "Jan") == 0) data_pasien->bulan = 1;
            else if (strcmp(nama_bulan, "Feb") == 0) data_pasien->bulan = 2;
            else if (strcmp(nama_bulan, "Mar") == 0) data_pasien->bulan = 3;
            else if (strcmp(nama_bulan, "Apr") == 0) data_pasien->bulan = 4;
            else if (strcmp(nama_bulan, "Mei") == 0) data_pasien->bulan = 5;
            else if (strcmp(nama_bulan, "Jun") == 0) data_pasien->bulan = 6;
            else if (strcmp(nama_bulan, "Jul") == 0) data_pasien->bulan = 7;
            else if (strcmp(nama_bulan, "Agu") == 0) data_pasien->bulan = 8;
            else if (strcmp(nama_bulan, "Sep") == 0) data_pasien->bulan = 9;
            else if (strcmp(nama_bulan, "Okt") == 0) data_pasien->bulan = 10;
            else if (strcmp(nama_bulan, "Nov") == 0) data_pasien->bulan = 11;
            else if (strcmp(nama_bulan, "Des") == 0) data_pasien->bulan = 12;
        }
        else if (sscanf(str_tanggal, "%d %19[^ ] %d", &hari, nama_bulan, &tahun) == 3) {
            if (strcmp(nama_bulan, "Januari") == 0) data_pasien->bulan = 1;
            else if (strcmp(nama_bulan, "Februari") == 0) data_pasien->bulan = 2;
            else if (strcmp(nama_bulan, "Maret") == 0) data_pasien->bulan = 3;
            else if (strcmp(nama_bulan, "April") == 0) data_pasien->bulan = 4;
            else if (strcmp(nama_bulan, "Mei") == 0) data_pasien->bulan = 5;
            else if (strcmp(nama_bulan, "Juni") == 0) data_pasien->bulan = 6;
            else if (strcmp(nama_bulan, "Juli") == 0) data_pasien->bulan = 7;
            else if (strcmp(nama_bulan, "Agustus") == 0) data_pasien->bulan = 8;
            else if (strcmp(nama_bulan, "September") == 0) data_pasien->bulan = 9;
            else if (strcmp(nama_bulan, "Oktober") == 0) data_pasien->bulan = 10;
            else if (strcmp(nama_bulan, "November") == 0) data_pasien->bulan = 11;
            else if (strcmp(nama_bulan, "Desember") == 0) data_pasien->bulan = 12;
        }
        else {
            fprintf(stderr, "Gagal parsing: %s\n", str_tanggal);
            free(data_pasien);
            continue;
        }

        strcpy(data_pasien->tanggal, str_tanggal);
        data_pasien->hari = hari;
        data_pasien->tahun = tahun;
        data_pasien->next = NULL;

        if (head == NULL) {
            head = data_pasien;
            current = data_pasien;
        }
        else {
            current->next = data_pasien;
            current = data_pasien;
        }
    }

    fclose(file);
    return head;
}

// Fungsi untuk menghitung rerata biaya per tahun
void RerataTahun(data* dataPasien) {
    int tahun_sum[MAX_YEAR] = {0};
    int tahun_count[MAX_YEAR] = {0};

    dua* current = dataPasien->dua;
    while (current != NULL) {
        tahun_sum[current->tahun] += current->biaya;
        tahun_count[current->tahun]++;
        current = current->next;
    }

    printf("Rerata biaya per tahun:\n");
    for (int i = 0; i < MAX_YEAR; i++) {
        if (tahun_count[i] != 0) {
            float mean = (float)tahun_sum[i] / tahun_count[i];
            char mata_uang[MAX_LEN];
            FormatRupiah((int)mean, mata_uang);
            printf("Tahun %d: %s\n", i, mata_uang);
        }
    }
}

// Fungsi untuk menghitung total biaya per bulan tiap tahunnya
void TotalPerBulan(data* dataPasien) {
    int bulan_sum[MAX_YEAR][12] = {0};

    dua* current = dataPasien->dua;
    while (current != NULL) {
        bulan_sum[current->tahun][current->bulan - 1] += current->biaya;
        current = current->next;
    }

    printf("\nTotal biaya per bulan untuk tiap tahun:\n");
    for (int i = 0; i < MAX_YEAR; i++) {
        for (int j = 0; j < 12; j++) {
            if (bulan_sum[i][j] != 0) {
                char mata_uang[MAX_LEN];
                FormatRupiah(bulan_sum[i][j], mata_uang);
                printf("Tahun %d, Bulan %d: %s\n", i, j + 1, mata_uang);
            }
        }
    }
}

// Fungsi untuk menghitung total biaya per tahun
void TotalPerTahun(data* dataPasien) {
    int tahun_sum[MAX_YEAR] = {0};

    dua* current = dataPasien->dua;
    while (current != NULL) {
        tahun_sum[current->tahun] += current->biaya;
        current = current->next;
    }

    printf("\nTotal biaya per tahun:\n");
    for (int i = 0; i < MAX_YEAR; i++) {
        if (tahun_sum[i] != 0) {
            char mata_uang[MAX_LEN];
            FormatRupiah(tahun_sum[i], mata_uang);
            printf("Tahun %d: %s\n", i, mata_uang);
        }
    }
}

void laporan_biaya() {
    data data_obj;
    data_obj.dua = ReadFileDua("dua.csv");

    RerataTahun(&data_obj);
    TotalPerBulan(&data_obj);
    TotalPerTahun(&data_obj);

    dua* current = data_obj.dua;
    dua* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}