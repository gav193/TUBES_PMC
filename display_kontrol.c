#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Format 1: 7 Desember 2023
// Format 2: 10-Apr-23

// Fungsi ngeonversiin input bulan jadi format 1
const char* get_month_name(int month) {
    const char* months[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", 
                            "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    if (month >= 1 && month <= 12) {
        return months[month - 1];
    }
    return NULL;
}

// Fungsi ngonversiin input bulan jadi format 2
const char* get_month_abbr(int month) {
    const char* months_abbr[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
                                 "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    if (month >= 1 && month <= 12) {
        return months_abbr[month - 1];
    }
    return NULL;
}

// Fungsi untuk mengkonversi input tanggal menjadi format seragam
int parse_date(const char* input, int* day, int* month, int* year) {
    if (sscanf(input, "%d-%d-%d", day, month, year) == 3) {
        *year += (*year < 100) ? 2000 : 0; // Adjust year
        return 1;
    }
    return 0; // Invalid format
}

// Fungsi untuk mengkonversi tanggal ke string yang konsisten
void format_date(int day, int month, int year, char* buffer1, char* buffer2) {
    const char* month_name = get_month_name(month);
    const char* month_abbr = get_month_abbr(month);
    if (month_name && month_abbr) {
        // Format 1: 7 Desember 2023
        sprintf(buffer1, "%d %s %d", day, month_name, year);
        // Format 2: 10-Apr-23
        sprintf(buffer2, "%02d-%s-%02d", day, month_abbr, year % 100);
    }
}

// Fungsi nampilin kontrol berdasarkan tanggal
void display_kontrol(data* data) {
    char input[50];
    int day, month, year;
    char formatted_date1[30];
    char formatted_date2[15];

    //input tanggalnya dijadiin format baru ntar dikonversiin ke format yang ada
    printf("Masukkan tanggal kontrol (format: dd-mm-yy): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    if (!parse_date(input, &day, &month, &year)) {
        printf("Format tanggal tidak valid.\n");
        return;
    }

    format_date(day, month, year, formatted_date1, formatted_date2);

    printf("List pasien yang terdaftar untuk kontrol pada tanggal %s atau %s:\n", formatted_date1, formatted_date2);

    dua* current = data->dua;
    int count = 0;
    dua* found_dua[100]; 
    while (current != NULL) {
        if (strcmp(current->kontrol, formatted_date1) == 0 || strcmp(current->kontrol, formatted_date2) == 0) {
            count++;
            found_dua[count-1] = current;
            printf("%d. ID Pasien: %s\n", count, current->id);
        }
        current = current->next;
    }

    if (count == 0) {
        printf("Tidak ada pasien yang terdaftar untuk kontrol pada tanggal tersebut.\n");
        return;
    }

    printf("Lihat data pasien nomor: ");
    int choice;
    scanf("%d", &choice);
    getchar(); 

    if (choice > 0 && choice <= count) {
        current = found_dua[choice-1];
        printf("Data pasien:\n");
        printf("ID pasien: %s\n", current->id);
        printf("Tanggal: %s\n", current->tanggal);
        printf("Diagnosa pasien: %s\n", current->diagnosis);
        printf("Tindakan yang diberikan kepada pasien: %s\n", current->tindakan);
        printf("Kontrol: %s\n", current->kontrol);
        printf("Biaya: %d\n", current->biaya);
    } else {
        printf("Pilihan tidak valid.\n");
    }
}
