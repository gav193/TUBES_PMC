#ifndef MAIN_H
#define MAIN_H

#define MAX_LEN 100
#define MAX_YEAR 2024 // Tahun hingga sampai 2024

// Define your structures here
typedef struct satu {
    char nama[MAX_LEN];
    char alamat[MAX_LEN];
    char kota[MAX_LEN];
    char loc_lahir[MAX_LEN];
    char tgl_lahir[MAX_LEN];
    int hari;
    int bulan; 
    int tahun;
    int umur;
    char bpjs[MAX_LEN];
    char id[MAX_LEN];
    struct satu* next;
} satu;

typedef struct dua {
    char tanggal[MAX_LEN];
    int hari;
    int bulan;
    int tahun;
    char id[MAX_LEN];
    char diagnosis[MAX_LEN];
    char tindakan[MAX_LEN];
    char kontrol[MAX_LEN];
    int biaya;
    struct dua* next;
} dua;

typedef struct tiga {
    char aktivitas[MAX_LEN];
    int biaya;
    struct tiga* next;
} tiga;

typedef struct Data {
    struct satu* satu;
    struct dua* dua;
    struct tiga* tiga;
} Data;

// Function prototypes
void insert(Data* data, char* filename, void* new_node);
void remove_newline(char* str);
void parse_tanggal(dua* node);
void parse(char* filename, Data* data);
void save(char* filename, Data* data);
void print_satu(Data* data);
void print_dua(Data* data);
void print_tiga(Data* data);
void insertEnd(Data *database);
void search(Data *database, char *data);
void updateData(Data *database, char *data);
void hapusData(Data *database, char *data);
void riwayatPasien(Data *database, char *data);
void crud_ket_pasien(Data* data);
void display_kontrol(Data* data);
void laporan_keuangan();
void report_disease_frequency(Data* data);

#endif
