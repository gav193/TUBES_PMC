#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "crud_ket_pasien.c"
#include "display_kontrol.c"
#include "keuangan_klinik.c"
#include "functions.c"
#include "fungsiDataPasien.c"

int main() {

    //input bla2
    data data = {NULL, NULL, NULL};
    parse("satu.csv", &data);
    parse("dua.csv", &data);
    parse("tiga.csv", &data);

    //opsi menu ubah aja sesuai kerapihan sama bagusnya gimana nanti
    printf("Daftar fungsi yang dapat dilakukan:\n1. fungsi no.1\n2. fungsi no.2\n3. fungsi no.3\n4. fungsi no.4\n5. fungsi no.5\n6. fungsi no.6\nPilihan: ");
    int choice; char string[MAX_LEN];
    scanf("%d", &choice);
    getchar();  // Consume newline

    switch (choice) {
        case 1: 
            printf("Pilih operasi:\n1. Cari data pasien\n2. Tambah data pasien\n3. Ubah data pasien\n4. Hapus data pasien\nPilihan: ");
            scanf("%d", &choice);
            {switch (choice) {
                case 1: 
                    printf("Masukkan ID pasien yang ingin dicari: ");
                    scanf(" %[^\r\n]%*c", string);
                    search(&data, string); break;
                case 2: insertEnd(&data); break; //Tambah pasien
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
                }
            } break;
        case 2: crud_ket_pasien(&data); break;
        case 3: break;
        case 4: laporan_keuangan(); break;
        case 5: break;
        case 6: display_kontrol(&data); break;
        default: printf("PILIHAN ANDA NGASAL!\n"); break; //sori gakepikiran yang lain
    }
    
    save("satu.csv", &data);
    save("dua.csv", &data);
    save("tiga.csv", &data);

    return 0;
}
