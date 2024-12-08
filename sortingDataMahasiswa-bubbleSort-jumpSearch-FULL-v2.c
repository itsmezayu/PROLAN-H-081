#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_MAHASISWA 5

// Struktur untuk menyimpan data mahasiswa
typedef struct {
    char npm[20];
    char nama[50];
    char prodi[30];
    float ipk;
} Mahasiswa;

// Tampilan data mahasiswa
void printData(Mahasiswa mhs[], int n) {
    printf("---------------------------------------------------------------\n");
    printf("| %-10s  | %-20s | %-15s | %-5s|\n", "NPM", "Nama", "Prodi", "IPK");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("| %-10s | %-20s | %-15s | %.2f |\n", 
               mhs[i].npm, mhs[i].nama, mhs[i].prodi, mhs[i].ipk);
    }
    printf("---------------------------------------------------------------\n");
}

// Fungsi untuk sorting data mahasiswa berdasarkan kriteria
void bubbleSort(Mahasiswa mhs[], int n, int kriteria, int ascending) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int condition = 0;

            // Pilih kriteria perbandingan
            if (kriteria == 1) { // Berdasarkan NPM
                condition = strcmp(mhs[j].npm, mhs[j + 1].npm) < 0;
            } else if (kriteria == 2) { // Berdasarkan Nama
                condition = strcmp(mhs[j].nama, mhs[j + 1].nama) < 0;
            } else if (kriteria == 3) { // Berdasarkan Prodi
                condition = strcmp(mhs[j].prodi, mhs[j + 1].prodi) < 0;
            } else if (kriteria == 4) { // Berdasarkan IPK
                condition = mhs[j].ipk < mhs[j + 1].ipk;
            }

            // kondisi untuk ascending/descending
            if ((!ascending && condition) || (ascending && !condition)) {
                Mahasiswa temp = mhs[j];
                mhs[j] = mhs[j + 1];
                mhs[j + 1] = temp;
            }
        }
    }
}

// Fungsi Jump Search untuk string
int jumpSearchString(Mahasiswa mhs[], int n, const char *query, int kriteria) {
    int step = sqrt(n); // Panjang langkah
    int prev = 0;

    // Jump sampai elemen lebih besar atau sama dengan query
    while (strcmp((kriteria == 1 ? mhs[(step < n ? step : n) - 1].npm :
                   kriteria == 2 ? mhs[(step < n ? step : n) - 1].nama :
                   mhs[(step < n ? step : n) - 1].prodi), query) < 0) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1; // Tidak ditemukan
        }
    }

    // Linear search di blok yang ditemukan
    for (int i = prev; i < step && i < n; i++) {
        if (strcmp((kriteria == 1 ? mhs[i].npm :
                    kriteria == 2 ? mhs[i].nama :
                    mhs[i].prodi), query) == 0) {
            return i; // Elemen ditemukan
        }
    }

    return -1; // Tidak ditemukan
}

// Fungsi Jump Search untuk IPK
int jumpSearchFloat(Mahasiswa mhs[], int n, float query) {
    int step = sqrt(n);
    int prev = 0;

    // Lompat hingga elemen lebih besar atau sama dengan query
    while (mhs[(step < n ? step : n) - 1].ipk < query) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1; // Tidak ditemukan
        }
    }

    // Linear search di blok yang ditemukan
    for (int i = prev; i < step && i < n; i++) {
        if (mhs[i].ipk == query) {
            return i; // Elemen ditemukan
        }
    }

    return -1; // Tidak ditemukan
}

int main() {
    // Data mahasiswa
    Mahasiswa mhs[MAX_MAHASISWA] = {
        {"23081010209", "Shahzada Hartanto", "Informatika", 4.00},
        {"23081010035", "Muthmainnah Az Zahra", "Informatika", 3.80},
        {"23081010223", "Christian Cimo", "Theologi", 3.75},
        {"23081010215", "Nana Febbyna", "Psikologi", 3.90},
        {"23081010077", "Qiqi binti Baizhu", "Kedokteran", 3.45}
    };

    int jumlahMahasiswa = MAX_MAHASISWA;
    int kriteria, ascending, opsi;
    char searchQuery[50];
    float searchIpk;

    do {
        printf("\n===== Menu =====\n");
        printf("1. Tampilkan Data Mahasiswa\n");
        printf("2. Sorting Data Mahasiswa\n");
        printf("3. Pencarian Mahasiswa\n");
        printf("4. Keluar\n");
        printf("Masukkan opsi: ");
        scanf("%d", &opsi);

        switch (opsi) {
        case 1:
            printf("\nData Mahasiswa:\n");
            printData(mhs, jumlahMahasiswa);
            break;
        case 2:
            printf("\nPilih Kriteria Sortir:\n");
            printf("1. NPM\n2. Nama\n3. Prodi\n4. IPK\n");
            printf("Masukkan opsi (1-4): ");
            scanf("%d", &kriteria);

            printf("Pilih Urutan:\n1. Ascending\n2. Descending\n");
            printf("Masukkan opsi (1-2): ");
            scanf("%d", &ascending);

            bubbleSort(mhs, jumlahMahasiswa, kriteria, ascending == 1);
            printf("\nData Mahasiswa Setelah di-sortir:\n");
            printData(mhs, jumlahMahasiswa);
            break;
        case 3:
            printf("\nPilih Kriteria Pencarian:\n");
            printf("1. NPM\n2. Nama\n3. Prodi\n4. IPK\n");
            printf("Masukkan opsi (1-4): ");
            scanf("%d", &kriteria);

            // Pastikan data sudah diurutkan
            bubbleSort(mhs, jumlahMahasiswa, kriteria, 1);

            if (kriteria == 4) {
                printf("\nMasukkan IPK yang ingin dicari: ");
                scanf("%f", &searchIpk);
                int hasil = jumpSearchFloat(mhs, jumlahMahasiswa, searchIpk);
                if (hasil != -1) {
                    printf("\nMahasiswa ditemukan:\n");
                    printData(&mhs[hasil], 1);
                } else {
                    printf("\nMahasiswa dengan IPK %.2f tidak ditemukan.\n", searchIpk);
                }
            } else {
                printf("\nMasukkan kata kunci yang ingin dicari: ");
                scanf(" %[^\n]", searchQuery);
                int hasil = jumpSearchString(mhs, jumlahMahasiswa, searchQuery, kriteria);
                if (hasil != -1) {
                    printf("\nMahasiswa ditemukan:\n");
                    printData(&mhs[hasil], 1);
                } else {
                    printf("\nMahasiswa dengan kriteria '%s' tidak ditemukan.\n", searchQuery);
                }
            }
            break;
        case 4:
            printf("Keluar...\n");
            break;
        default:
            printf("Opsi invalid.\n");
        }
    } while (opsi != 4);

    return 0;
}
