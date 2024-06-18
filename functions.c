#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

// File Processing Functions
void insert(Data* data, char* filename, void* new_node) {
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
    char* token;
    char temp_tgl[MAX_LEN];
    dua* new_dua = node;
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
        printf("Format tanggal tidak valid: %s\n", new_dua->tanggal);
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
            printf("Ditemukan bulan yang tidak valid : %s\n", new_dua->tanggal);
            return;
        }
    } else {
        printf("Format tanggal tidak valid: %s\n", new_dua->tanggal);
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
        printf("Format tanggal tidak valid: %s\n", new_dua->tanggal);
        return;
    }
}

void parse(char* filename, Data* data) {
    FILE* stream = fopen(filename, "r");
    if (!stream) {
        printf("File tidak dapat dibuka");
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
            if (new_tiga->biaya < 1000) {
                new_tiga->biaya = atoi(val) * 1000;
            }
            else {new_tiga->biaya = atoi(val); }
            new_tiga->next = NULL;
            insert(data, filename, new_tiga);
        }
        row++;
    }
    fclose(stream);
}

    void save(char* filename, Data* data) {
        FILE* stream = fopen(filename, "w");
        if (!stream) {
            printf("Error opening file for writing: %s\n", filename);
            perror("fopen");
            return;
        }
        
        // Write header and data based on filename
        if (strcmp(filename, "satu.csv") == 0) {
            //printf("Saving data to satu.csv\n");
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
            //printf("Saving data to dua.csv\n");
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
            //printf("Saving data to tiga.csv\n");
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

    void print_satu(Data* data) {
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

    void print_dua(Data* data) {
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

    void print_tiga(Data* data) {
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
void freeData(Data *data) {
    // Free linked list satu
    satu *current_satu = data->satu;
    while (current_satu != NULL) {
        satu *temp = current_satu;
        current_satu = current_satu->next;
        free(temp);
    }

    // Free linked list dua
    dua *current_dua = data->dua;
    while (current_dua != NULL) {
        dua *temp = current_dua;
        current_dua = current_dua->next;
        free(temp);
    }

    // Free linked list tiga
    tiga *current_tiga = data->tiga;
    while (current_tiga != NULL) {
        tiga *temp = current_tiga;
        current_tiga = current_tiga->next;
        free(temp);
    }

    data->satu = NULL;
    data->dua = NULL;
    data->tiga = NULL;
}

// Fitur 1 (Data Pasien)
satu *getnode() {
    satu *temp;
    temp = (satu*)malloc(sizeof(satu));
    temp->next = NULL;
    return temp;
}

void printData(satu *ptr) {
    printf("%-25s| %-15s| %-18s| %-18s| %-18s| %-4d| %-4d| %-4d| %-4d| %-11s| %s\n", 
        ptr->nama, ptr->alamat, ptr->kota, ptr->loc_lahir, ptr->tgl_lahir,
        ptr->hari, ptr->bulan, ptr->tahun, ptr->umur,
        ptr->bpjs, ptr->id
        );
}

//Print semua item dalam list
void printList(satu *start) {
    satu *ptr;
    ptr = start;
    int num = 1;

    if (ptr == NULL) {
        printf("Database kosong.\n");
        return;
    }

    printf("\n[ Database Pasien ]\n");
    //%-25s| %-15s| %-18s| %-18s| %-18s| %-4d| %-4d| %-4d| %-4d| %-11s| %s
    printf("%-3s| %-25s| %-15s| %-18s| %-18s| %-18s| %-4s| %-4s| %-4s| %-4s| %-11s| %s\n",
           "No.", "Nama", "Alamat", "Kota", "Lok. Lahir", "Tanggal Lahir", "Hr", "Bln", "Thn", "Um", "BPJS", "ID");

    while (ptr != NULL) {
        printf("%-3d| ", num);
        printData(ptr);
        num += 1;
        ptr = ptr->next;
    }
}

//node->id = "KX 1230123", return only 1230123 for easy ID autoassignment
int id_number(satu *node) {
    char str[11]; char *letters; int numbers;
    strcpy(str, node->id);

    // Use strtok to split the string
    letters = strtok(str, " "); //Just in case it's needed
    numbers = atoi(strtok(NULL, " "));

    return numbers;
}

//Konversi tanggal untuk node satu
void convertTanggalSatu(satu *node){
    char* token;
    char temp_tgl[MAX_LEN];
    satu* new_satu = node;
    
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
        printf("Format tanggal tidak valid: %s\n", new_satu->tgl_lahir);
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
            printf("Ditemukan bulan yang tidak valid : %s\n", new_satu->tgl_lahir);
            return;
        }
    } else {
        printf("Format tanggal tidak valid: %s\n", new_satu->tgl_lahir);
        return;
    }

    token = strtok(NULL, separator);
    if (token) { 
        int temp = atoi(token); 
        new_satu->tahun = temp;
    } else { 
        printf("Format tanggal tidak valid: %s\n", new_satu->tgl_lahir);
        return;
    }
    node = new_satu;
}

//Masukkan data pasien baru di akhir list
void insertEnd(Data *database) {
    satu *start = database->satu;
    satu *ptr, *temp; 
    int id, num;
    ptr = getnode();

    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("\n[ Tambah Data Pasien ]\n");
    printf("Masukkan nama pasien: "); scanf(" %[^\r\n]%*c", ptr->nama);
    printf("Masukkan alamat pasien: "); scanf(" %[^\r\n]%*c", ptr->alamat);
    printf("Masukkan kota domisili: "); scanf(" %[^\r\n]%*c", ptr->kota);
    printf("Masukkan kota lahir pasien: "); scanf(" %[^\r\n]%*c", ptr->loc_lahir);
    printf("Masukkan tanggal lahir: "); scanf(" %[^\r\n]%*c", ptr->tgl_lahir);
    
    //debugging
    //printf("%s; %s; %s; %s; %s", ptr->nama, ptr->alamat, ptr->kota, ptr->loc_lahir, ptr->tgl_lahir);

    ptr->hari = 0; ptr->bulan = 0; ptr->tahun = 0;
    printf("Masukkan umur pasien: "); scanf("%d", &num); ptr->umur = num;
    printf("Masukkan nomor BPJS pasien: "); scanf(" %[^\r\n]%*c", ptr->bpjs);
    convertTanggalSatu(ptr);

    printf("ptr:\n");
    printData(ptr);
    
    if (start == NULL) {
        //Assign otomatis ID Pasien
        strcpy(ptr->id, "KX 1230001");
        printf("\nID Pasien: %s", ptr->id);

        //Update database
        start = ptr;
        database->satu = start;        
        printf("\nData Pasien telah ditambahkan!\n");

        printList(database->satu);
    }

    else {
        //Find last node
        temp = start;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        //Parse last node's ID to turn into the format KX 1230123 (KX - integer) and add one
        printf("temp:\n");
        printData(temp);
        
        id = id_number(temp) + 1;
        printf("id of temp: %d", id);
        //Put it in ptr
        sprintf(ptr->id, "KX %d", id);
        printf("\nID Pasien: %s", ptr->id);

        //Add new last node by copying ptr to temp->next
        temp->next = ptr;
        ptr->next = NULL;

        //Update the real database->satu
        database->satu = start;

        printf("\nData Pasien telah ditambahkan!\n");
        printList(database->satu);
    }
}

//Search & print list
void search(Data *database, char *data) {
    satu *start = database->satu;
    satu *ptr;
    int found = 0;

    //Jika list kosong
    if (start == NULL) {
        printf("\nDatabase kosong.\n");
        return;
    }

    else {
        printf("\n[ Search Pasien ]\n");
        printf("%-25s| %-15s| %-20s| %-20s| %-18s| %-4s| %-4s| %-4s| %-4s| %-11s| %s\n",
           "Nama", "Alamat", "Kota", "Lok. Lahir", "Tanggal Lahir", "Hr", "Bln", "Thn", "Um", "BPJS", "ID");
    }

    //Jika data head
    if (strcmp(start->id, data) == 0) {
        convertTanggalSatu(start);
        printData(start);
        found = 1;
    }

    //Jika data bukan node start/head
    ptr = start;
    while (ptr->next != NULL) {
        ptr = ptr->next;
        if (strcmp(ptr->id, data) == 0) {
            convertTanggalSatu(ptr);
            printData(ptr);
            found = 1;
        }
    }

    //Jika data tidak ditemukan
    if (!found) {
        printf("Data dengan ID %s tidak ditemukan.\n", data);
    }
}

//Search & print list berdasarkan id
//Kalo mau berdasarkan nama atau bpjs bisa tambahin 'type' di switch case
void updateData(Data *database, char *data) {
    satu *start = database->satu;
    satu *ptr;
    int found = 0;

    //Jika list kosong
    if (start == NULL) {
        printf("Database kosong.\n");
        return;
    }

    else {
        printf("\n[ Update Data Pasien ]\n");
    }

    //Jika data head
    if (strcmp(start->id, data) == 0) {
        printData(start);
        found = 1;
    }

    //Jika data bukan node start/head
    ptr = start;
    while (ptr->next != NULL) {
        ptr = ptr->next;
        if (strcmp(ptr->id, data) == 0) {
            printData(ptr);
            found = 1;
            break;
        }
    }

    //Jika data tidak ditemukan
    if (!found) {
        printf("Data dengan ID %s tidak ditemukan.\n", data);
    }

    else {
        int done = 0; char ans, pil = 0;

        while (!done) {
        printf("Pilih data yang ingin di-update:\n1. Nama pasien\n2. Alamat pasien\n3. Kota domisili pasien\n4. Kota lahir pasien\n5. Tanggal lahir pasien\n6. Umur pasien\n7. Nomor BPJS pasien\n8.Selesai\n");
        do {
            printf("Pilihan: "); scanf("%d", &pil);
            switch (pil) {
                case 1: printf("Masukkan nama pasien: "); scanf(" %[^\r\n]%*c", ptr->nama); break;
                case 2: printf("Masukkan alamat pasien: "); scanf(" %[^\r\n]%*c", ptr->alamat); break;
                case 3: printf("Masukkan kota domisili: "); scanf(" %[^\r\n]%*c", ptr->kota); break;
                case 4: printf("Masukkan kota lahir pasien: "); scanf(" %[^\r\n]%*c", ptr->loc_lahir); break;
                case 5: 
                    printf("Masukkan tanggal lahir: "); scanf(" %[^\r\n]%*c", ptr->tgl_lahir);
                    ptr->hari = 0; ptr->bulan = 0; ptr->tahun = 0;
                    convertTanggalSatu(ptr); break;
                case 6: printf("Masukkan umur pasien: "); scanf("%d", &ptr->umur); break;
                case 7: printf("Masukkan nomor BPJS pasien: "); scanf(" %[^\r\n]%*c", ptr->bpjs); break;
                case 8: break;
                default:
                    printf("Input tidak valid, kembali ke halaman awal\n");
                    break;
                }
            } while (pil != 8);
        
        printf("\nData pasien sudah diperbarui!\n");
        printData(ptr);

        do {
            printf("\nApakah data pasien sudah sesuai? (Y/N): ");
            scanf(" %c", &ans);

            if (ans == 'Y' || ans == 'y') {done = 1;}
            else if (ans == 'N' || ans == 'n') {done = 0;}
            else {printf("Jawaban tidak valid!\n");}
            } while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n');
        }
    }
}

//Hapus data pasien berdasarkan ID
void hapusData(Data *database, char *data) {
    satu *start = database->satu;
    satu *temp, *ptr; int found = 0;

    //Jika list kosong
    if (start == NULL) {
        printf("Database kosong!\n");
        return;
    }

    else {
        //Jika data head
        if (strcmp(start->id, data) == 0) {
            temp = start;
            start = start->next;
            free(temp);
            database->satu = start;
            found = 1;
        }

        //Jika data bukan node start/head
        else {
            ptr = start;
            while (ptr->next != NULL) {
                if (strcmp(ptr->next->id, data) == 0) {
                    found = 1;
                    temp = ptr->next;
                    ptr->next = temp->next;
                    free(temp);
                    break;
                }
                ptr = ptr->next;
            }
        }
    }

    //Jika data tidak ditemukan
    if (!found) {printf("Data dengan ID %s tidak ditemukan", data);}
}

// Fitur 2 (Data Riwayat)
int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month(int month, int year) {
    switch (month) {
        case 1: return 31;
        case 2: return is_leap_year(year) ? 29 : 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return 0;
    }
}

void add_days(char* input_date, char* result_date) {
    int day, month, year;
    sscanf(input_date, "%d-%d-%d", &day, &month, &year);
    
    day += 3;
    
    while (day > days_in_month(month, year)) {
        day -= days_in_month(month, year);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }

    const char* months[] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni",
        "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };
    
    sprintf(result_date, "%d %s %d", day, months[month - 1], year);
}
int isTanggalExists(Data* data, const char* id, const char* tanggal) {
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


int selectTanggalKedatangan(Data* data, const char* id) {
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
satu* findPasienInSatu(Data* data, const char* id) {
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
int findPasien(Data* data, const char* id) {
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
int getBiayaTindakan(Data* data, const char* tindakan) {
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

void addEntry(Data* data) {
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

    // Calculate control date
    char kontrol[MAX_LEN];
    add_days(tanggal_input, kontrol);

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
void updateEntry(Data* data) {
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
void deleteEntry(Data* data) {
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
void displayEntry(Data* data) {
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
void crud_ket_pasien(Data* data) {
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

// Fitur 3 (Informasi Pasien dan Riwayat Medis)
//Informasi pasien dan riwayat medisnya di klinik X
//Input nama/ID pasien -> iterasi ke dataset dua, print every diagnosis of ID that matches
//void riwayatPasien (char ), modif dari search

//Search & print list
void riwayatPasien(Data *database, char *data) {
    satu *sSatu = database->satu; 
    dua *sDua = database->dua;
    satu *ptrSatu; dua *ptrDua;
    int found = 0, exist = 0, num = 1;

    //Jika list kosong
    if (sSatu == NULL || sDua == NULL) {
        printf("Database kosong.\n");
        return;
    }

    else {
        printf("\n[ Riwayat Berobat Pasien ]\n");
    }

    //Jika data head
    if (strcmp(sSatu->id, data) == 0) {
        printf("Data Pasien:\n");
        printf("%-25s| %-15s| %-18s| %-4s| %-11s| %s\n",
               "Nama", "Alamat", "Tanggal Lahir", "Um", "BPJS", "ID");
        printf("%-25s| %-15s| %-18s| %-4d| %-11s| %s\n",
                sSatu->nama, sSatu->alamat, sSatu->tgl_lahir, 
                sSatu->umur, sSatu->bpjs, sSatu->id);
        exist = 1;
    }

    //Jika data bukan node start/head
    ptrSatu = sSatu;
    while (ptrSatu->next != NULL) {
        ptrSatu = ptrSatu->next;
        if (strcmp(ptrSatu->id, data) == 0) {
            printf("Data Pasien:\n");
            printf("%-25s| %-15s| %-18s| %-4s| %-11s| %s\n",
               "Nama", "Alamat", "Tanggal Lahir", "Um", "BPJS", "ID");
            printf("%-25s| %-15s| %-18s| %-4d| %-11s| %s\n",
                ptrSatu->nama, ptrSatu->alamat, ptrSatu->tgl_lahir, 
                ptrSatu->umur, ptrSatu->bpjs, ptrSatu->id);
            exist = 1;
            break;
        }
    }

    //Jika data tidak ditemukan
    if (!exist) {
        printf("Data pasien dengan ID %s tidak ditemukan.\n", data);
        return;
    }

    //Else search di struct dua
    else {
        printf("\nRiwayat Berobat Pasien:\n");
        printf("No. | %-18s| %-15s| %-18s| %-18s\n",
               "Tanggal", "Diagnosis", "Tindakan", "Kontrol");

        //Jika data head
        if (strcmp(sDua->id, data) == 0) {
            printf("%-4d| %-18s| %-15s| %-18s| %-18s\n",
                num, sDua->tanggal, sDua->diagnosis, sDua->tindakan, sDua->kontrol);
            found = 1; num ++;
        }

        //Jika data selain head
        ptrDua = sDua;
        while (ptrDua->next != NULL) {
            ptrDua = ptrDua->next;
            if (strcmp(ptrDua->id, data) == 0) {
                printf("%-4d| %-18s| %-15s| %-18s| %-18s\n",
                num, ptrDua->tanggal, ptrDua->diagnosis, ptrDua->tindakan, ptrDua->kontrol);
                found = 1; num ++;
            }
        }
        
        if (!found) {
            printf("Pasien dengan ID %s tidak memiliki riwayat berobat.\n", data);
        }
    }
}

// Fitur 4 (Pendapatan dan Keuangan Klinik)
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
void RerataTahun(Data* dataPasien) {
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
void TotalPerBulan(Data* dataPasien) {
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
void TotalPerTahun(Data* dataPasien) {
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

void laporan_keuangan() {
    Data data_pasien;
    data_pasien.dua = ReadFileDua("dua.csv");

    RerataTahun(&data_pasien);
    TotalPerBulan(&data_pasien);
    TotalPerTahun(&data_pasien);

    dua* current = data_pasien.dua;
    dua* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    printf("\n");
}

// Fitur 5
void report_disease_frequency(Data* data) {
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

// Fitur 6 (Display Kontrol)
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
void display_kontrol(Data* data) {
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
