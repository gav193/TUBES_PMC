#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "main.h"

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
void insertEnd(data *database) {
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
    
    ptr->hari = 0; ptr->bulan = 0; ptr->tahun = 0;
    printf("Masukkan umur pasien: "); scanf("%d", &num); ptr->umur = num;
    printf("Masukkan nomor BPJS pasien: "); scanf(" %[^\r\n]%*c", ptr->bpjs);
    convertTanggalSatu(ptr);
    
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
        id = id_number(temp) + 1;
       
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
void search(data *database, char *data) {
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
        }
    }

    //Jika data tidak ditemukan
    if (!found) {
        printf("Data dengan ID %s tidak ditemukan.\n", data);
    }
}

//Search & print list berdasarkan id
//Kalo mau berdasarkan nama atau bpjs bisa tambahin 'type' di switch case
void updateData(data *database, char *data) {
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
void hapusData(data *database, char *data) {
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

//Informasi pasien dan riwayat medisnya di klinik X
//Input nama/ID pasien -> iterasi ke dataset dua, print every diagnosis of ID that matches
//void riwayatPasien (char ), modif dari search

//Search & print list
void riwayatPasien(data *database, char *data) {
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
