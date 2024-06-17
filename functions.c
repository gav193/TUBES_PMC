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

void parse_tanggal(dua* node) {
    // Handle different date formats
    if (strstr(node->tanggal, "Januari")) {
        sscanf(node->tanggal, "%d Januari %d", &node->hari, &node->tahun);
        node->bulan = 1;
    } else if (strstr(node->tanggal, "Februari")) {
        sscanf(node->tanggal, "%d Februari %d", &node->hari, &node->tahun);
        node->bulan = 2;
    } else if (strstr(node->tanggal, "Maret")) {
        sscanf(node->tanggal, "%d Maret %d", &node->hari, &node->tahun);
        node->bulan = 3;
    } else if (strstr(node->tanggal, "April")) {
        sscanf(node->tanggal, "%d April %d", &node->hari, &node->tahun);
        node->bulan = 4;
    } else if (strstr(node->tanggal, "Mei")) {
        sscanf(node->tanggal, "%d Mei %d", &node->hari, &node->tahun);
        node->bulan = 5;
    } else if (strstr(node->tanggal, "Juni")) {
        sscanf(node->tanggal, "%d Juni %d", &node->hari, &node->tahun);
        node->bulan = 6;
    } else if (strstr(node->tanggal, "Juli")) {
        sscanf(node->tanggal, "%d Juli %d", &node->hari, &node->tahun);
        node->bulan = 7;
    } else if (strstr(node->tanggal, "Agustus")) {
        sscanf(node->tanggal, "%d Agustus %d", &node->hari, &node->tahun);
        node->bulan = 8;
    } else if (strstr(node->tanggal, "September")) {
        sscanf(node->tanggal, "%d September %d", &node->hari, &node->tahun);
        node->bulan = 9;
    } else if (strstr(node->tanggal, "Oktober")) {
        sscanf(node->tanggal, "%d Oktober %d", &node->hari, &node->tahun);
        node->bulan = 10;
    } else if (strstr(node->tanggal, "November")) {
        sscanf(node->tanggal, "%d November %d", &node->hari, &node->tahun);
        node->bulan = 11;
    } else if (strstr(node->tanggal, "Desember")) {
        sscanf(node->tanggal, "%d Desember %d", &node->hari, &node->tahun);
        node->bulan = 12;
    } else {
        // Handle format "DD-MMM-YY"
        char month_str[4];
        sscanf(node->tanggal, "%2d-%3s-%2d", &node->hari, month_str, &node->tahun);
        if (node->tahun < 100) {
            node->tahun += 2000; // Adjust year
        }
        if (strcmp(month_str, "Jan") == 0) node->bulan = 1;
        else if (strcmp(month_str, "Feb") == 0) node->bulan = 2;
        else if (strcmp(month_str, "Mar") == 0) node->bulan = 3;
        else if (strcmp(month_str, "Apr") == 0) node->bulan = 4;
        else if (strcmp(month_str, "May") == 0) node->bulan = 5;
        else if (strcmp(month_str, "Jun") == 0) node->bulan = 6;
        else if (strcmp(month_str, "Jul") == 0) node->bulan = 7;
        else if (strcmp(month_str, "Aug") == 0) node->bulan = 8;
        else if (strcmp(month_str, "Sep") == 0) node->bulan = 9;
        else if (strcmp(month_str, "Oct") == 0) node->bulan = 10;
        else if (strcmp(month_str, "Nov") == 0) node->bulan = 11;
        else if (strcmp(month_str, "Dec") == 0) node->bulan = 12;
    }
}

void parse(char* filename, data* data) {
    FILE* stream = fopen(filename, "r");
    if (!stream) {
        printf("Unable to open file");
        return;
    }
    char line[1024];
    int row = 0;

    while (fgets(line, sizeof(line), stream)) {
        if (row == 0) {
            row++;
            continue;
        }

        remove_newline(line);
        char* val = strtok(line, ";");

        if (strcmp(filename, "satu.csv") == 0) {
            val = strtok(NULL, ";");
            satu* new_satu = (satu*)malloc(sizeof(satu));
            strcpy(new_satu->nama, val); val = strtok(NULL, ";");
            strcpy(new_satu->alamat, val); val = strtok(NULL, ";");
            strcpy(new_satu->kota, val); val = strtok(NULL, ";");
            strcpy(new_satu->loc_lahir, val); val = strtok(NULL, ";");
            strcpy(new_satu->tgl_lahir, val); val = strtok(NULL, ";");
            new_satu->umur = atoi(val); val = strtok(NULL, ";");
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
            parse_tanggal(new_dua);
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

void report_disease_frequency(data* data) {
    typedef struct frequency {
        char diagnosis[MAX_LEN];
        int count;
        int month;
        int year;
        struct frequency* next;
    } frequency;

    frequency* head = NULL;

    dua* current = data->dua;
    while (current != NULL) {
        frequency* f = head;
        int found = 0;
        while (f != NULL) {
            if (strcmp(f->diagnosis, current->diagnosis) == 0 && f->month == current->bulan && f->year == current->tahun) {
                f->count++;
                found = 1;
                break;
            }
            f = f->next;
        }

        if (!found) {
            frequency* new_f = (frequency*)malloc(sizeof(frequency));
            strcpy(new_f->diagnosis, current->diagnosis);
            new_f->count = 1;
            new_f->month = current->bulan;
            new_f->year = current->tahun;
            new_f->next = head;
            head = new_f;
        }

        current = current->next;
    }

    
    typedef struct month_frequency {
        int month;
        int year;
        int total_count;
        frequency* diseases;
        struct month_frequency* next;
    } month_frequency;

    month_frequency* month_head = NULL;

    frequency* f = head;
    while (f != NULL) {
        month_frequency* mf = month_head;
        int found = 0;
        while (mf != NULL) {
            if (mf->month == f->month && mf->year == f->year) {
                frequency* disease = (frequency*)malloc(sizeof(frequency));
                strcpy(disease->diagnosis, f->diagnosis);
                disease->count = f->count;
                disease->next = mf->diseases;
                mf->diseases = disease;
                mf->total_count += f->count;
                found = 1;
                break;
            }
            mf = mf->next;
        }

        if (!found) {
            month_frequency* new_mf = (month_frequency*)malloc(sizeof(month_frequency));
            new_mf->month = f->month;
            new_mf->year = f->year;
            new_mf->total_count = f->count;
            new_mf->diseases = (frequency*)malloc(sizeof(frequency));
            strcpy(new_mf->diseases->diagnosis, f->diagnosis);
            new_mf->diseases->count = f->count;
            new_mf->diseases->next = NULL;
            new_mf->next = month_head;
            month_head = new_mf;
        }

        f = f->next;
    }

    // Sort the month frequencies by total_count within each year
    month_frequency* sorted_months = NULL;
    while (month_head) {
        month_frequency** indirect = &sorted_months;
        while (*indirect && ((*indirect)->year < month_head->year || ((*indirect)->year == month_head->year && (*indirect)->total_count >= month_head->total_count))) {
            indirect = &(*indirect)->next;
        }
        month_frequency* next = month_head->next;
        month_head->next = *indirect;
        *indirect = month_head;
        month_head = next;
    }

    
    printf("Diagnosis Frequency Report:\n");
    int current_year = -1;
    month_frequency* print_month = sorted_months;
    while (print_month != NULL) {
        if (print_month->year != current_year) {
            if (current_year != -1) {
                printf("\n"); 
            }
            printf("Tahun %d:\n", print_month->year);
            current_year = print_month->year;
        }
        printf("  %02d/%d: %d penyakit\n", print_month->month, print_month->year, print_month->total_count);
        frequency* print_disease = print_month->diseases;
        while (print_disease != NULL) {
            printf("    %s: %d kali\n", print_disease->diagnosis, print_disease->count);
            print_disease = print_disease->next;
        }
        print_month = print_month->next;
    }

    
    while (sorted_months) {
        month_frequency* temp_month = sorted_months;
        sorted_months = sorted_months->next;
        frequency* disease = temp_month->diseases;
        while (disease) {
            frequency* temp_disease = disease;
            disease = disease->next;
            free(temp_disease);
        }
        free(temp_month);
    }

    while (head) {
        frequency* temp = head;
        head = head->next;
        free(temp);
    }
}
