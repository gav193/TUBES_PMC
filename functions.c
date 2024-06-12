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


void parse_tanggal(void* node, char* filename){
    char* token;
    char temp_tgl[MAX_LEN];
    if (strcmp(filename, "satu.csv") == 0) {
        satu* new_satu = (satu*) node;
        strcpy(temp_tgl, new_satu->tgl_lahir);
        int len = strlen(temp_tgl);
        char separator[2] = " ";
        // Detect separator
        for (int i = 0; i < len; i++) {
            if (temp_tgl[i] == '-') {
                separator[0] = '-';
                break;
            }
        }

        // Parse day
        token = strtok(temp_tgl, separator);
        if (token) {
            new_satu->hari = atoi(token);
        } else {
            printf("Format tanggal tidak valid(%s): %s\n",filename, new_satu->tgl_lahir);
            return;
        }

        // Parse month
        token = strtok(NULL, separator);
        if (token) {
            if (strcmp(token, "Januari") == 0 || strcmp(token, "januari") == 0 || strcmp(token, "Jan") == 0 || strcmp(token, "jan") == 0) {
                new_satu->bulan = 1;
            } else if (strcmp(token, "Februari") == 0 || strcmp(token, "februari") == 0 || strcmp(token, "Feb") == 0 || strcmp(token, "feb") == 0) {
                new_satu->bulan = 2;
            } else if (strcmp(token, "Maret") == 0 || strcmp(token, "maret") == 0 || strcmp(token, "Mar") == 0 || strcmp(token, "mar") == 0) {
                new_satu->bulan = 3;
            } else if (strcmp(token, "April") == 0 || strcmp(token, "april") == 0 || strcmp(token, "Apr") == 0 || strcmp(token, "apr") == 0) {
                new_satu->bulan = 4;
            } else if (strcmp(token, "Mei") == 0 || strcmp(token, "mei") == 0) {
                new_satu->bulan = 5;
            } else if (strcmp(token, "Juni") == 0 || strcmp(token, "juni") == 0 || strcmp(token, "Jun") == 0 || strcmp(token, "jun") == 0) {
                new_satu->bulan = 6;
            } else if (strcmp(token, "Juli") == 0 || strcmp(token, "juli") == 0 || strcmp(token, "Jul") == 0 || strcmp(token, "jul") == 0) {
                new_satu->bulan = 7;
            } else if (strcmp(token, "Agustus") == 0 || strcmp(token, "agustus") == 0 || strcmp(token, "Aug") == 0 || strcmp(token, "aug") == 0) {
                new_satu->bulan = 8;
            } else if (strcmp(token, "September") == 0 || strcmp(token, "september") == 0 || strcmp(token, "Sep") == 0 || strcmp(token, "sep") == 0) {
                new_satu->bulan = 9;
            } else if (strcmp(token, "Oktober") == 0 || strcmp(token, "oktober") == 0 || strcmp(token, "Okt") == 0 || strcmp(token, "okt") == 0) {
                new_satu->bulan = 10;
            } else if (strcmp(token, "November") == 0 || strcmp(token, "november") == 0 || strcmp(token, "Nov") == 0 || strcmp(token, "nov") == 0) {
                new_satu->bulan = 11;
            } else if (strcmp(token, "Desember") == 0 || strcmp(token, "desember") == 0 || strcmp(token, "Des") == 0 || strcmp(token, "des") == 0) {
                new_satu->bulan = 12;
            } else {
                printf("Ditemukan bulan yang tidak valid(%s) : %s\n",filename,new_satu->tgl_lahir);
                return;
            }
        } else {
            printf("Format tanggal tidak valid(%s): %s\n",filename, new_satu->tgl_lahir);
            return;
        }
        token = strtok(NULL, separator);
        if (token) { 
            int temp = atoi(token);
            if (temp>=2000) {
                temp-=2000;
            }   
            new_satu->tahun = temp;
        } else { 
            printf("Format tanggal tidak valid(%s): %s\n",filename, new_satu->tgl_lahir);
            return;
        }
    } else if (strcmp(filename, "dua.csv") == 0) {
        dua* new_dua = (dua*) node;
        strcpy(temp_tgl, new_dua->tanggal);
        int len = strlen(temp_tgl);
        char separator[2] = " ";
        // Detect separator
        for (int i = 0; i < len; i++) {
            if (temp_tgl[i] == '-') {
                separator[0] = '-';
                break;
            }
        }

        // Parse day
        token = strtok(temp_tgl, separator);
        if (token) {
            new_dua->hari = atoi(token);
        } else {
            printf("Format tanggal tidak valid(%s): %s\n",filename, new_dua->tanggal);
            return;
        }

        // Parse month
        token = strtok(NULL, separator);
        if (token) {
            if (strcmp(token, "Januari") == 0 || strcmp(token, "januari") == 0 || strcmp(token, "Jan") == 0 || strcmp(token, "jan") == 0) {
                new_dua->bulan = 1;
            } else if (strcmp(token, "Februari") == 0 || strcmp(token, "februari") == 0 || strcmp(token, "Feb") == 0 || strcmp(token, "feb") == 0) {
                new_dua->bulan = 2;
            } else if (strcmp(token, "Maret") == 0 || strcmp(token, "maret") == 0 || strcmp(token, "Mar") == 0 || strcmp(token, "mar") == 0) {
                new_dua->bulan = 3;
            } else if (strcmp(token, "April") == 0 || strcmp(token, "april") == 0 || strcmp(token, "Apr") == 0 || strcmp(token, "apr") == 0) {
                new_dua->bulan = 4;
            } else if (strcmp(token, "Mei") == 0 || strcmp(token, "mei") == 0) {
                new_dua->bulan = 5;
            } else if (strcmp(token, "Juni") == 0 || strcmp(token, "juni") == 0 || strcmp(token, "Jun") == 0 || strcmp(token, "jun") == 0) {
                new_dua->bulan = 6;
            } else if (strcmp(token, "Juli") == 0 || strcmp(token, "juli") == 0 || strcmp(token, "Jul") == 0 || strcmp(token, "jul") == 0) {
                new_dua->bulan = 7;
            } else if (strcmp(token, "Agustus") == 0 || strcmp(token, "agustus") == 0 || strcmp(token, "Aug") == 0 || strcmp(token, "aug") == 0) {
                new_dua->bulan = 8;
            } else if (strcmp(token, "September") == 0 || strcmp(token, "september") == 0 || strcmp(token, "Sep") == 0 || strcmp(token, "sep") == 0) {
                new_dua->bulan = 9;
            } else if (strcmp(token, "Oktober") == 0 || strcmp(token, "oktober") == 0 || strcmp(token, "Okt") == 0 || strcmp(token, "okt") == 0) {
                new_dua->bulan = 10;
            } else if (strcmp(token, "November") == 0 || strcmp(token, "november") == 0 || strcmp(token, "Nov") == 0 || strcmp(token, "nov") == 0) {
                new_dua->bulan = 11;
            } else if (strcmp(token, "Desember") == 0 || strcmp(token, "desember") == 0 || strcmp(token, "Des") == 0 || strcmp(token, "des") == 0) {
                new_dua->bulan = 12;
            } else {
                printf("Ditemukan bulan yang tidak valid(%s) : %s\n",filename, new_dua->tanggal);
                return;
            }
        } else {
            printf("Format tanggal tidak valid(%s): %s\n",filename, new_dua->tanggal);
            return;
        }
        token = strtok(NULL, separator);
        if (token) { 
            int temp = atoi(token);
            if (temp>=2000) {
                temp-=2000;
            }   
            new_dua->tahun = temp;
        } else { 
            printf("Format tanggal tidak valid(%s): %s\n",filename, new_dua->tanggal);
            return;
        }
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
            parse_tanggal(new_satu, "satu.csv");
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
            parse_tanggal(new_dua, "dua.csv");
            // for debugging
            //printf("\nd: %d, m:%d, y:%d \n", new_dua->hari, new_dua->bulan, new_dua->tahun);
            insert(data, filename, new_dua);
        } else if (strcmp(filename, "tiga.csv") == 0) {
            val = strtok(NULL, ";");
            tiga* new_tiga = (tiga*)malloc(sizeof(tiga));
            strcpy(new_tiga->aktivitas, val); val = strtok(NULL, ";");
            new_tiga->biaya = atoi(val);
            if (new_tiga->biaya < 1000) {
                new_tiga->biaya = new_tiga->biaya * 1000;
            }
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
            if (current->biaya < 1000) {
                current->biaya = current->biaya * 1000;
            }
            fprintf(stream, "%d;%s;%d", row, current->aktivitas, current->biaya);
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
