#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "functions.c"

int main() {

    //input bla2
    Data data = {NULL, NULL, NULL};
    parse("satu.csv", &data);
    parse("dua.csv", &data);
    parse("tiga.csv", &data);

    //opsi menu ubah aja sesuai kerapihan sama bagusnya gimana nanti
    int choice = 0; 
    int choice_2 = 0;
    do {
        printf("Daftar fungsi yang dapat dilakukan:\n1. Daftar Pasien\n2. Daftar Riwayat\n3. Cari Riwayat Pasien\n4. fungsi no.4\n5. Data jumlah pasien dan penyakit keseluruhan (per bulan dan per tahun)\n6. fungsi no.6\n7. Exit program\nPilihan: ");
        char string[MAX_LEN];
        scanf("%d", &choice);
        getchar();  // Consume newline
        parse("satu.csv", &data);
        parse("dua.csv", &data);
        switch (choice) {
            case 1: 
                printf("Pilih operasi:\n1. Cari data pasien\n2. Tambah data pasien\n3. Ubah data pasien\n4. Hapus data pasien\n5. Back\nPilihan: ");
                scanf("%d", &choice_2);
                {switch (choice_2) {
                    case 1: 
                        printf("Masukkan ID pasien yang ingin dicari: ");
                        scanf(" %[^\r\n]%*c", string);
                        search(&data, string); 
                        break;
                    case 2: 
                        insertEnd(&data); 
                        break; //Tambah pasien
                    case 3: 
                        printf("Masukkan ID pasien yang datanya ingin di-update: ");
                        scanf(" %[^\r\n]%*c", string);
                        updateData(&data, string);
                        break;
                    case 4:
                        printf("Masukkan ID pasien yang datanya ingin dihapus: ");
                        scanf(" %[^\r\n]%*c", string);
                        //Update node satu (first struct in data)
                        hapusData(&data, string);
                        break;
                    case 5: 
                        printf("Kembali ke halaman awal\n");
                        break;
                    default:
                        printf("Input tidak valid, kembali ke halaman awal\n");
                        break;
                    }
                } break;
            case 2: crud_ket_pasien(&data); break;
            case 3: 
                printf("Masukkan ID pasien: ");
                scanf(" %[^\r\n]%*c", string);
                riwayatPasien(&data, string);
                break;
            case 4: laporan_keuangan(); break;
            case 5: report_disease_frequency(&data); break;
            case 6: display_kontrol(&data); break;
            case 7: 
                printf("Exiting system...\n");
                save("satu.csv", &data);
                save("dua.csv", &data);
                save("tiga.csv", &data);
                break;
            default: printf("Pilihan tidak valid, ulangi input!\n"); break; //sori gakepikiran yang lain
        }
        save("satu.csv", &data);
        save("dua.csv", &data);
    } while (choice != 7);

    return 0;
}
