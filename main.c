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
            if (row < MAX_ROWS) {
                strncpy(temp, val, MAX_LEN - 1);
                temp[MAX_LEN - 1] = '\0';
                if (strcmp(filename, "satu.csv") == 0 && col < MAX_COLS_1) {
                    strcpy(satu[row - 1][col], temp);
                } else if (strcmp(filename, "dua.csv") == 0 && col < MAX_COLS_2) {
                    strcpy(dua[row - 1][col], temp);
                } else if (strcmp(filename, "tiga.csv") == 0 && col < MAX_COLS_3) {
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
            for (int j = 0; j < MAX_COLS_1; j++) {
                printf("%s/", satu[i][j]);
            }
            printf("\n");
        }
    } else if (strcmp(filename, "dua.csv") == 0) {
        for (int i = 0; i < row - 1; i++) {
            for (int j = 0; j < MAX_COLS_2; j++) {
                printf("%s/", dua[i][j]);
            }
            printf("\n");
        }
    } else if (strcmp(filename, "tiga.csv") == 0) {
        for (int i = 0; i < row - 1; i++) {
            for (int j = 0; j < MAX_COLS_3; j++) {
                printf("%s/", tiga[i][j]);
            }
            printf("\n");
        }
    }
}

void save(char filename[]) {
    FILE *stream = fopen(filename, "w");
    if (!stream) {
        printf("File not found!\n");
        return;
    }
    
    int num_cols;
    char (*data)[MAX_LEN];

    // write header
    if (strcmp(filename, "satu.csv") == 0) {
        fprintf(stream, "No;Nama Lengkap;Alamat;Kota;Tempat Lahir;Tanggal Lahir;Umur (th);No BPJS;ID Pasien\n");
        data = (char (*)[MAX_LEN])satu;
        num_cols = MAX_COLS_1;
    } else if (strcmp(filename, "dua.csv") == 0) {
        fprintf(stream, "No;Tanggal;ID Pasien;Diagnosis;Tindakan;Kontrol;Biaya (Rp)\n");
        data = (char (*)[MAX_LEN])dua;
        num_cols = MAX_COLS_2;
    } else if (strcmp(filename, "tiga.csv") == 0) {
        fprintf(stream, "No;Aktivitas;Biaya (Rp)\n");
        data = (char (*)[MAX_LEN])tiga;
        num_cols = MAX_COLS_3;
    } else {
        fclose(stream);
        return;
    }

    // write data
    for (int row = 0; row < MAX_ROWS; ++row) {
        if (data[row * num_cols][0] == '\0'){
            break; // row is empty
        }
        for (int col = 0; col < num_cols; ++col) {
            fprintf(stream, "%s;", data[row * num_cols + col]);
        }
        fprintf(stream, "\n");
    }
    fclose(stream);
}

int main() {
    printf("Data CSV pertama : \n");
    parse("satu.csv");
    printf("\n\nData CSV kedua : \n");
    parse("dua.csv");
    printf("\n\nData CSV ketiga : \n");
    parse("tiga.csv");
    
    // testing untuk save (cek di file apakah berubah)
    //strcpy(satu[4][2],"percobaan"); 

    // buat manggil fungsi nomor 2 dari file crud_ket_pasien.c
    crud_ket_pasien();
    
    // operasi fungsi pada data yang dibaca (misalkan dihapus / ditambah data baru)
    save("satu.csv");
    save("dua.csv");
    save("tiga.csv");
    // note : ini matrix satu,dua,tiga udah dioperasikan jadi isinya udah teredit (bukan data yang murni setelah parsing)
    return 0;
}
