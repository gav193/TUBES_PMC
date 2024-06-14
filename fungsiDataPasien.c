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

void printData(satu *start) {
    satu *ptr;
    ptr = start;
    printf("%-25s| %-15s| %-15s| %-15s| %-15s| %-5d| %-5d| %-5d| %-5d| %-15s| %-7s|\n", 
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
    printf("%-3s| %-25s| %-15s| %-15s| %-15s| %-15s| %-5s| %-5s| %-5s| %-5s| %-15s| %-7s\n",
           "No.", "Nama", "Alamat", "Kota", "Lok. Lahir", "Tanggal Lahir", "Hari", "Bln", "Thn", "Umur", "BPJS", "ID");

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
        printf("%-25s| %-15s| %-15s| %-15s| %-15s| %-5s| %-5s| %-5s| %-5s| %-15s| %-7s\n",
           "Nama", "Alamat", "Kota", "Lok. Lahir", "Tanggal Lahir", "Hari", "Bln", "Thn", "Umur", "BPJS", "ID");
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
void updateData(satu *start, char *data) {
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
        char nama[MAX_LEN]; char alamat[MAX_LEN]; char kota[MAX_LEN];
        char loc_lahir[MAX_LEN]; char tgl_lahir[MAX_LEN];
        int hari; int bulan; int tahun; int umur;
        char bpjs[MAX_LEN]; char id[MAX_LEN];
        int done = 0; char ans;

        while (!done) {
        printf("Masukkan nama pasien: "); scanf(" %[^\r\n]%*c", ptr->nama);
        printf("Masukkan alamat pasien: "); scanf(" %[^\r\n]%*c", ptr->alamat);
        printf("Masukkan kota domisili: "); scanf(" %[^\r\n]%*c", ptr->kota);
        printf("Masukkan kota lahir pasien: "); scanf(" %[^\r\n]%*c", ptr->loc_lahir);
        printf("Masukkan tanggal lahir: "); scanf(" %[^\r\n]%*c", ptr->tgl_lahir);
        // parse_tanggal(satu* start, char * filename);
        printf("Masukkan umur pasien: "); scanf("%d", ptr->umur);
        printf("Masukkan nomor BPJS pasien: "); scanf(" %[^\r\n]%*c", ptr->bpjs);

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
satu *hapusData(satu *start, char *data) {
    satu *temp, *ptr;

    //Jika list kosong
    if (start == NULL) {
        printf("Database kosong!\n");
        return NULL;
    }

    //Jika data head
    if (strcmp(start->id, data) == 0) {
        temp = start;
        start = start->next;
        free(temp);
        return start;
    }

    //Jika data bukan node start/head
    ptr = start;
    while (ptr->next != NULL) {
        if (strcmp(ptr->next->id, data) == 0) {
            temp = ptr->next;
            ptr->next = temp->next;
            free(temp);
            return start;
        }
        ptr = ptr->next;
    }

    //Jika data tidak ditemukan
    printf("Data dengan ID %s tidak ditemukan", data);
    return start;
}

//Informasi pasien dan riwayat medisnya di klinik X
//Input nama/ID pasien -> iterasi ke dataset dua, print every diagnosis of ID that matches
//void riwayatPasien (char ), modif dari search

/*
//Search & print list
void search(satu *start, char *data) {
    satu *ptr;
    int found = 0;

    //Jika list kosong
    if (start == NULL) {
        printf("Database kosong.\n");
        return;
    }
    else {
        printf("[ Search Pasien ]");
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
*/

// int main() {
//     //input bla2
//     data data = {NULL, NULL, NULL};
//     parse("satu.csv", &data);
//     parse("dua.csv", &data);
//     parse("tiga.csv", &data);

//     //opsi menu ubah aja sesuai kerapihan sama bagusnya gimana nanti
//     printf("Daftar fungsi yang dapat dilakukan:\n1. fungsi no.1\n2. fungsi no.2\n3. fungsi no.3\n4. fungsi no.4\n5. fungsi no.5\n6. fungsi no.6\nPilihan: ");
//     int choice; char string[MAX_LEN];
//     scanf("%d", &choice);
//     getchar();  // Consume newline

//     switch (choice) {
//         case 1: //Menambah (V), ubah, hapus, cari data pasien
//             printf("Pilih operasi:\n1. Cari data pasien\n2. Tambah data pasien\n3.Ubah data pasien\n4. Hapus data pasien\nPilihan:");
//             scanf("%d", &choice);
//             {switch (choice) {
//                 case 1: //search(&data); break;
//                 case 2: //insertEnd(&data); break; //Tambah pasien
//                 case 3: 
//                     printf("Masukkan ID pasien yang datanya ingin di-update: ");
//                     scanf(" %[^\r\n]%*c", string);
//                     //updateData(&data, string);
//                     break;
//                 case 4:
//                     printf("Masukkan ID pasien yang datanya ingin dihapus: ");
//                     scanf(" %[^\r\n]%*c", string);
//                     //Update node satu (first struct in data)
//                     //satu = hapusData(satu, string);
//                     break;
//                 }
//             }
//         //case 2: crud_ket_pasien(&data); break;
//         case 3: break;
//         //case 4: laporan_biaya(); break;
//         case 5: break;
//         //case 6: display_kontrol(&data); break;
//         default: printf("PILIHAN ANDA NGASAL!\n"); break; //sori gakepikiran yang lain
//     }
    
//     save("satu.csv", &data);
//     save("dua.csv", &data);
//     save("tiga.csv", &data);

//     return 0;
// }
