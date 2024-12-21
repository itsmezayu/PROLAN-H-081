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
void merge(Mahasiswa mhs[], int left, int mid, int right, int kriteria, int ascending) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Mahasiswa L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = mhs[left + i];
    for (int j = 0; j < n2; j++) R[j] = mhs[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        int condition;
        if (kriteria == 1) {
            condition = strcmp(L[i].npm, R[j].npm) <= 0;
        } else if (kriteria == 2) {
            condition = strcmp(L[i].nama, R[j].nama) <= 0;
        } else if (kriteria == 3) {
            condition = strcmp(L[i].prodi, R[j].prodi) <= 0;
        } else {
            condition = L[i].ipk <= R[j].ipk;
        }

        if ((ascending && condition) || (!ascending && !condition)) {
            mhs[k++] = L[i++];
        } else {
            mhs[k++] = R[j++];
        }
    }

    while (i < n1) mhs[k++] = L[i++];
    while (j < n2) mhs[k++] = R[j++];
}

void mergeSort(Mahasiswa mhs[], int left, int right, int kriteria, int ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(mhs, left, mid, kriteria, ascending);
        mergeSort(mhs, mid + 1, right, kriteria, ascending);
        merge(mhs, left, mid, right, kriteria, ascending);
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
    mergeSort(mhs, 0, jumlahMahasiswa - 1, kriteria, ascending == 1);

    // Data mahasiswa setelah sorting
    printf("\nData Mahasiswa Setelah di-sortir:\n");
    printData(mhs, jumlahMahasiswa);

    return 0;
}
