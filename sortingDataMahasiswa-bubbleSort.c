#include <stdio.h>
#include <string.h>

#define MAX_MAHASISWA 5

// Struktur untuk menyimpan data mahasiswa
typedef struct {
    char npm[15];
    char nama[50];
    char prodi[30];
    float ipk;
} Mahasiswa;

// Tampilan data mahasiswa
void printData(Mahasiswa mhs[], int n) {
    printf("---------------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-15s | %-5s |\n", "NPM", "Nama", "Prodi", "IPK");
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
    int kriteria, ascending;

    // Data mahasiswa sebelum sorting
    printf("Data Mahasiswa Sebelum di-sortir:\n");
    printData(mhs, jumlahMahasiswa);

    // Memilih kriteria sorting
    printf("\nPilih Kriteria Sortir:\n");
    printf("1. NPM\n2. Nama\n3. Prodi\n4. IPK\n");
    printf("Masukkan pilihan (1-4): ");
    scanf("%d", &kriteria);

    // ascending/descending
    printf("Pilih Urutan:\n1. Ascending\n2. Descending\n");
    printf("Masukkan pilihan (1-2): ");
    scanf("%d", &ascending);

    // Sorting data dengan user input
    bubbleSort(mhs, jumlahMahasiswa, kriteria, ascending == 1);

    // Data mahasiswa setelah sorting
    printf("\nData Mahasiswa Setelah di-sortir:\n");
    printData(mhs, jumlahMahasiswa);

    return 0;
}
