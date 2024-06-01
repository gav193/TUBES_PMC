#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROWS 1000
#define MAX_COLS_1 9
#define MAX_LEN 100
#define MAX_COLS_2 7
#define MAX_COLS_3 3

char satu[MAX_ROWS][MAX_COLS_1][MAX_LEN];
char dua[MAX_ROWS][MAX_COLS_2][MAX_LEN];
char tiga[MAX_ROWS][MAX_COLS_3][MAX_LEN];

void remove_newline(char *str) {
    char *pos;
    if ((pos = strchr(str, '\n')) != NULL) {
        *pos = '\0';
    }
}

void parse(char filename[]) {
    FILE* stream = fopen(filename, "r"); // open filename in read mode
    if (!stream) {
        printf("File not found!\n");
        return;
    }

    char temp[1024]; // temporary line
    int row = 0, col = 0;
    while (fgets(temp, sizeof(temp), stream)) { // first iteration to find dimension of csv
        col = 0;
        row++;
        if (row == 1) {
            continue;  // skip the header row
        }
        char* val = strtok(temp, ";");
        while (val) {
            val = strtok(NULL, ";");
            col++; // find number of columns 
        }
    }
    rewind(stream);
    row = 0;
    col = 0; // reset row and column
    char line[1024];
    while (fgets(line, sizeof(line), stream)) { // second iteration to save data and finalize
        col = 0;
        if (row == 0) {
            row++;  // skip the header row
            continue;
        }
        char* val = strtok(line, ";");
        while (val) {
            remove_newline(val); // remove newline
            if (col < MAX_COLS_1 && row < MAX_ROWS) {
                strncpy(temp, val, MAX_LEN - 1);
                temp[MAX_LEN - 1] = '\0';
                if (strcmp(filename, "satu.csv") == 0) {
                    strcpy(satu[row - 1][col], temp);
                } else if (strcmp(filename, "dua.csv") == 0) {
                    strcpy(dua[row - 1][col], temp);
                } else if (strcmp(filename, "tiga.csv") == 0) {
                    strcpy(tiga[row - 1][col], temp);
                }
            }
            val = strtok(NULL, ";");
            col++;
        }
        row++;
    }
    fclose(stream);

    // print out for debugging
    if (strcmp(filename, "satu.csv") == 0) {
        for (int i = 0; i < row - 1; i++) {
            for (int j = 0; j < col; j++) {
                printf("%s/", satu[i][j]);
            }
            printf("\n");
        }
    } else if (strcmp(filename, "dua.csv") == 0) {
        for (int i = 0; i < row - 1; i++) {
            for (int j = 0; j < col; j++) {
                printf("%s/", dua[i][j]);
            }
            printf("\n");
        }
    } else if (strcmp(filename, "tiga.csv") == 0) {
        for (int i = 0; i < row - 1; i++) {
            for (int j = 0; j < col; j++) {
                printf("%s/", tiga[i][j]);
            }
            printf("\n");
        }
    }
}

void addnew() {
    FILE* satu = fopen("satu.csv", "r");
    if (!satu) {
        printf("Can't open file\n");
        return;
    }

    char line[1024];
    char lastID[MAX_LEN] = "KX 0";  // Default last ID
    int row = 0, col = 0;

    while (fgets(line, sizeof(line), satu)) {
        col = 0;
        row++;
        if (row == 1) {
            continue;  // Skip the header row
        }
        char* val = strtok(line, ";");
        while (val) {
            if (col == 0) {
                strncpy(lastID, val, MAX_LEN - 1);
                lastID[MAX_LEN - 1] = '\0';
            }
            val = strtok(NULL, ";");
            col++;
        }
    }

    fclose(satu);

    printf("Last ID : %s\n", lastID);

    // Extract the numeric part from the last ID
    char prefix[MAX_LEN] = "KX ";
    int numPart = 0;
    sscanf(lastID, "KX %d", &numPart);
    numPart++;
    
    char newID[MAX_LEN];
    snprintf(newID, MAX_LEN, "KX %d", numPart);

    // Input new data
    char nama[MAX_LEN], alamat[MAX_LEN], kota[MAX_LEN];
    char loclahir[MAX_LEN], datelahir[MAX_LEN], umur[MAX_LEN];
    char bpjs[MAX_LEN];

    printf("Enter Nama Lengkap: ");
    fgets(nama, MAX_LEN, stdin);
    nama[strcspn(nama, "\n")] = '\0';  // Remove newline character

    printf("Enter Alamat: ");
    fgets(alamat, MAX_LEN, stdin);
    alamat[strcspn(alamat, "\n")] = '\0';

    printf("Enter Kota: ");
    fgets(kota, MAX_LEN, stdin);
    kota[strcspn(kota, "\n")] = '\0';

    printf("Enter Tempat Lahir: ");
    fgets(loclahir, MAX_LEN, stdin);
    loclahir[strcspn(loclahir, "\n")] = '\0';

    printf("Enter Tanggal Lahir: ");
    fgets(datelahir, MAX_LEN, stdin);
    datelahir[strcspn(datelahir, "\n")] = '\0';

    printf("Enter Umur (th): ");
    fgets(umur, MAX_LEN, stdin);
    umur[strcspn(umur, "\n")] = '\0';

    printf("Enter No BPJS: ");
    fgets(bpjs, MAX_LEN, stdin);
    bpjs[strcspn(bpjs, "\n")] = '\0';

    // Append new data to the file
    FILE* add = fopen("satu.csv", "a");
    if (!add) {
        printf("Can't open file to append\n");
        return;
    }

    //fprintf(add, "%s;%s;%s;%s;%s;%s;%s;%s;%s\n", newID, nama, alamat, kota, loclahir, datelahir, umur, bpjs, newID);
    fclose(add);

    printf("Data added successfully.\n");
}

int main() {
    printf("Data CSV pertama : \n");
    parse("satu.csv");
    printf("\n\nData CSV kedua : \n");
    parse("dua.csv");
    printf("\n\nData CSV ketiga : \n");
    parse("tiga.csv");
    //addnew();
    return 0;
}

// int main() {
//     printf("Program Klinik X\n");
//     saveall(); //open and move to matrix of char
//     int pilihan = 0;
//     // while (pilihan == 0) { // prompt input user
//     //     printf("1. Tambah Pasien\n2. Ubah Data Pasien\n3. Hapus Data Pasien\n4. Riwayat Pasien\n5. Info ke Medis\n6. Laporan\n7. Daftar Pasien\nInfo Kontrol");
//     //     printf("Pilihan: ");
//     //     scanf("%d", &pilihan);
//     //     if (pilihan!= 0) {
//     //         switch(pilihan) {
//     //             case 1:
//     //                 // printf("Create selected\n");
//     //                 // printf("=================================\n");
//     //                 // create();
//     //                 pilihan = 0;
//     //                 printf("=================================\n");
//     //                 break;
//     //             case 2:
//     //                 // printf("Edit selected\n");
//     //                 // printf("=================================\n");
//     //                 // edit();
//     //                 pilihan = 0;
//     //                 printf("=================================\n");
//     //                 break;
//     //             case 3:
//     //                 // printf("Delete selected\n");
//     //                 // printf("=================================\n");
//     //                 // delete();
//     //                 pilihan = 0;
//     //                 printf("=================================\n");
//     //                 break;
//     //             case 4:
//     //                 // printf("Search selected\n");
//     //                 // printf("=================================\n");
//     //                 // search();
//     //                 pilihan = 0;
//     //                 printf("=================================\n");
//     //                 break;
//     //             case 5:
//     //                 // printf("Rata-rata selected\n");
//     //                 // printf("=================================\n");
//     //                 // nr();
//     //                 pilihan = 0;
//     //                 printf("=================================\n");
//     //                 break;
//     //             case 6:
//     //                 // printf("Standar Deviasi selected\n");
//     //                 // printf("=================================\n");
//     //                 // stdev();
//     //                 pilihan = 0;
//     //                 printf("=================================\n");
//     //                 break;
//     //             case 7:
//     //                 printf("=================================\n");
//     //                 printf("Exiting system!\n");
//     //                 break;
//     //             default: // else
//     //                 printf("Error, ulangi input\n");
//     //                 pilihan = 0; // re-loop
//     //                 break;  
//     //         }
//     //     }
//     // }

//     return 0;
// }
