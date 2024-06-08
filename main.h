#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#define MAX_LEN 100

// Define your structures here
typedef struct satu {
    char nama[MAX_LEN];
    char alamat[MAX_LEN];
    char kota[MAX_LEN];
    char loc_lahir[MAX_LEN];
    char tgl_lahir[MAX_LEN];
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

typedef struct data {
    struct satu* satu;
    struct dua* dua;
    struct tiga* tiga;
} data;

// Function prototypes
void insert(data* data, char* filename, void* new_node);
void remove_newline(char* str);
void parse(char* filename, data* data);
void save(char* filename, data* data);
void print_satu(data* data);
void print_dua(data* data);
void print_tiga(data* data);
void crud_ket_pasien(data* data);
void display_kontrol(data* data);


#endif
