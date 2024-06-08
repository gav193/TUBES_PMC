#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert(data* data, char* filename, void* new_node) {
    if (strcmp(filename, "satu.csv") == 0) {
        satu* new_satu = (satu*)new_node;
        if (data->satu == NULL) {
            data->satu = new_satu;
        } else {
            satu* temp = data->satu;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_satu;
        }
    } else if (strcmp(filename, "dua.csv") == 0) {
        dua* new_dua = (dua*)new_node;
        if (data->dua == NULL) {
            data->dua = new_dua;
        } else {
            dua* temp = data->dua;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_dua;
        }
    } else if (strcmp(filename, "tiga.csv") == 0) {
        tiga* new_tiga = (tiga*)new_node;
        if (data->tiga == NULL) {
            data->tiga = new_tiga;
        } else {
            tiga* temp = data->tiga;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_tiga;
        }
    }
}

void remove_newline(char* str) {
    char* pos;
    if ((pos = strchr(str, '\n')) != NULL) {
        *pos = '\0';
    }
}

void parse(char* filename, data* data) {
    FILE* stream = fopen(filename, "r"); // open filename in read mode
    if (!stream) {
        printf("Unable to open file");
        return;
    }
    char line[1024]; // temporary line
    int row = 0;

    while (fgets(line, sizeof(line), stream)) { // read each line
        if (row == 0) {
            row++;  // skip the header row
            continue;
        }
        
        remove_newline(line); // remove newline
        char* val = strtok(line, ";");

        if (strcmp(filename, "satu.csv") == 0) {
            val = strtok(NULL, ";");
            satu* new_satu = (satu*)malloc(sizeof(satu));
            strcpy(new_satu->nama, val); val = strtok(NULL, ";");
            strcpy(new_satu->alamat, val); val = strtok(NULL, ";");
            strcpy(new_satu->kota, val); val = strtok(NULL, ";");
            strcpy(new_satu->loc_lahir, val); val = strtok(NULL, ";");
            strcpy(new_satu->tgl_lahir, val); val = strtok(NULL, ";");
            new_satu->umur= atoi(val); val = strtok(NULL, ";");
            strcpy(new_satu->bpjs, val); val = strtok(NULL, ";");
            strcpy(new_satu->id, val);
            new_satu->next = NULL;
            insert(data, filename, new_satu);
        } else if (strcmp(filename, "dua.csv") == 0) {
            val = strtok(NULL, ";");
            dua* new_dua = (dua*)malloc(sizeof(dua));
            strcpy(new_dua->tanggal, val); val = strtok(NULL, ";");
            strcpy(new_dua->id, val); val = strtok(NULL, ";");
            strcpy(new_dua->diagnosis, val); val = strtok(NULL, ";");
            strcpy(new_dua->tindakan, val); val = strtok(NULL, ";");
            strcpy(new_dua->kontrol, val); val = strtok(NULL, ";");
            new_dua->biaya = atoi(val);
            new_dua->next = NULL;
            insert(data, filename, new_dua);
        } else if (strcmp(filename, "tiga.csv") == 0) {
            val = strtok(NULL, ";");
            tiga* new_tiga = (tiga*)malloc(sizeof(tiga));
            strcpy(new_tiga->aktivitas, val); val = strtok(NULL, ";");
            new_tiga->biaya = atoi(val);
            new_tiga->next = NULL;
            insert(data, filename, new_tiga);
        }
        row++;
    }
    fclose(stream);
}

void save(char* filename, data* data) {
    FILE* stream = fopen(filename, "w");
    if (!stream) {
        printf("Error opening file for writing: %s\n", filename);
        perror("fopen");
        return;
    }
    
    // Write header and data based on filename
    if (strcmp(filename, "satu.csv") == 0) {
        printf("Saving data to satu.csv\n");
        fprintf(stream, "No;Nama Lengkap;Alamat;Kota;Tempat Lahir;Tanggal Lahir;No BPJS;ID Pasien\n");
        satu* current = data->satu;
        int row = 1;
        while (current != NULL) {
            fprintf(stream, "%d;%s;%s;%s;%s;%s;%d;%s;%s", row, current->nama, current->alamat, current->kota, current->loc_lahir,  current->tgl_lahir,current->umur, current->bpjs, current->id);
            current = current->next;
            row++;
            if (current != NULL) {
                fprintf(stream,"\n");
            }
        }
    } else if (strcmp(filename, "dua.csv") == 0) {
        printf("Saving data to dua.csv\n");
        fprintf(stream, "No;Tanggal;ID Pasien;Diagnosis;Tindakan;Kontrol;Biaya (Rp)\n");
        dua* current = data->dua;
        int row = 1;
        while (current != NULL) {
            fprintf(stream, "%d;%s;%s;%s;%s;%s;%d", row, current->tanggal,current->id, current->diagnosis, current->tindakan, current->kontrol, current->biaya);
            current = current->next;
            row++;
            if (current != NULL) {
                fprintf(stream, "\n");
            }
        }
    } else if (strcmp(filename, "tiga.csv") == 0) {
        printf("Saving data to tiga.csv\n");
        fprintf(stream, "No;Aktivitas;Biaya (Rp)\n");
        tiga* current = data->tiga;
        int row = 1;
        while (current != NULL) {
            fprintf(stream, "%d;%s;%d", row, current->aktivitas, current->biaya * 1000);
            current = current->next;
            row++;
            if (current != NULL) {
                fprintf(stream,"\n");
            }
        }
    } else {
        printf("Unknown filename: %s\n", filename);
        fclose(stream);
        return;
    }

    fclose(stream);
}

void print_satu(data* data) {
    printf("Data Satu:\n");
    satu* current = data->satu;
    int count = 1;
    while (current != NULL) {
        printf("%d. ",count);
        printf("Nama: %s, Alamat: %s, Kota: %s, Tempat Lahir: %s, Tanggal Lahir: %s, Umur : %d, No BPJS: %s, ID: %s\n",current->nama, current->alamat, current->kota, current->loc_lahir,current->tgl_lahir,current->umur, current->bpjs, current->id);
        current = current->next;
        count++;
    }
}

void print_dua(data* data) {
    printf("Data Dua:\n");
    dua* current = data->dua;
    int count = 1;
    while (current != NULL) {
        printf("%d. ",count);
        printf("Tanggal: %s, ID: %s, Diagnosis: %s, Tindakan: %s, Kontrol: %s, Biaya: %d\n",current->tanggal,current->id, current->diagnosis, current->tindakan, current->kontrol, current->biaya);
        current = current->next;
        count++;
    }
}

void print_tiga(data* data) {
    printf("Data Tiga:\n");
    tiga* current = data->tiga;
    int count = 1;
    while (current != NULL) {
        printf("%d. ",count);
        printf("Aktivitas: %s, Biaya: %d\n",current->aktivitas, current->biaya * 1000);
        current = current->next;
        count++;
    }
}
