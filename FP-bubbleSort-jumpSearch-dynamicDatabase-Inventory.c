/*
 +------------------------------+
 PROGRAM INVENTORY GENSHIN IMPACT
 +------------------------------+
 Implemantasi Materi:
 - Bubble Sort
 - Jump Search
 - File Ops
 - Function
 - Loop
 - String & Array
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

#define DATABASE 10

// Struktur untuk menyimpan data item
typedef struct {
    char name[50];
    char category[30];
    int quantity;
} Inventory;

// Tampilan data item
void printData(Inventory item[], int n) {
	printf(" +-------------------------------+---------------------------+------------+\n");
	printf(" | %-28s  | %-25s | %-10s |\n", "Items", "Category", "Quantity");
	printf(" +-------------------------------+---------------------------+------------+\n");
	for (int i = 0; i < n; i++) {
	    printf(" | %-29s | %-25s | %-10d |\n", item[i].name, item[i].category, item[i].quantity);
	    }
	printf(" +-------------------------------+---------------------------+------------+\n");
}

// Fungsi untuk save database ke file
void saveDatabase(Inventory item[], int n, const char *filename) {
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
	    printf("\n File error...\n");
	    return;
	}
	for (int i = 0; i < n; i++) {
	    fprintf(file, "%s,%s,%d\n", item[i].name, item[i].category, item[i].quantity);
	}
	fclose(file);
	printf("\n Data tersimpan ke %s...\n", filename);
}

// Fungsi untuk load database dari file
int loadDatabase(Inventory item[], const char *filename) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
	    printf("\n File error...\n");
	    return 0;
	}
	int count = 0;
	while (fscanf(file, "%[^,],%[^,],%d\n", item[count].name, item[count].category, &item[count].quantity) != EOF) {
	    count++;
	    if (count >= DATABASE) break; // Mencegah overflow
	}
	fclose(file);
	printf("\n Data %d loaded dari %s...\n", count, filename);
	return count;
}

// Fungsi untuk sorting data item berdasarkan kriteria
void bubbleSort(Inventory item[], int n, int kriteria, int ascending) {
	for (int i = 0; i < n - 1; i++) {
	    for (int j = 0; j < n - i - 1; j++) {
	        int condition = 0;
	
	        // Pilih kriteria perbandingan
	        if (kriteria == 1) { // Berdasarkan Nama
	            condition = strcmp(item[j].name, item[j + 1].name) < 0;
	        } else if (kriteria == 2) { // Berdasarkan Kategori
	            condition = strcmp(item[j].category, item[j + 1].category) < 0;
	        } else if (kriteria == 3) { // Berdasarkan Quantity
	            condition = item[j].quantity < item[j + 1].quantity;
	        }
	
	        // kondisi untuk ascending/descending
	        if ((!ascending && condition) || (ascending && !condition)) {
	            Inventory temp = item[j];
	            item[j] = item[j + 1];
	            item[j + 1] = temp;
	        }
	    }
	}
}

int jumpSearchString(Inventory item[], int n, const char *query, int kriteria) {
	int step = sqrt(n); // Panjang langkah
	int prev = 0;
	
	// Jump sampai elemen lebih besar atau sama dengan query
	while (1) {
	    int index = (step < n ? step : n) - 1;
	    int hasilJump;
	
		if (kriteria == 1) { // Berdasarkan Nama
	        hasilJump = strcmp(item[index].name, query);
	    } else if (kriteria == 2) { // Berdasarkan Kategori
	        hasilJump = strcmp(item[index].category, query);
	    } else {
	        return -1; // Kriteria tidak valid untuk pencarian string
	    }
	
	    if (hasilJump >= 0) {
	        break; // Ditemukan blok yang sesuai
	    }
	
	    prev = step;
	    step += sqrt(n);
	    if (prev >= n) {
	        return -1; // Tidak ditemukan
	    }
	}
	
	// Linear search di blok yang ditemukan
	for (int i = prev; i < step && i < n; i++) {
	    if ((kriteria == 1 && strcmp(item[i].name, query) == 0) ||
	        (kriteria == 2 && strcmp(item[i].category, query) == 0)) {
	        return i; // Elemen ditemukan
	    }
	}
	
	return -1; // Tidak ditemukan
}

// Fungsi Jump Search untuk Quantity
int jumpSearchQTY(Inventory item[], int n, int query) {
    int step = sqrt(n);
    int prev = 0;
       
	// Lompat hingga elemen lebih besar atau sama dengan query
	while (item[(step < n ? step : n) - 1].quantity < query) {
    	prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1; // Tidak ditemukan
        }
    }

    // Linear search di blok yang ditemukan
    for (int i = prev; i < step && i < n; i++) {
        if (item[i].quantity == query) {
            return i; // Elemen ditemukan
        }
    }

    return -1; // Tidak ditemukan
}

int main() {
	
    // Data item
    Inventory item[DATABASE] = {
        {"Anemoculus", "Oculi", 131},
        {"Dendroculus", "Oculi", 211},
        {"Electroculus", "Oculi", 246},
        {"Geoculus", "Oculi", 186},
        {"Teyvat's Egg", "Food", 1000},
        {"Resin", "Consumable", 160},
        {"Primogems", "Gacha", 189},
        {"Pizza Eula", "Food", 23},
        {"Widhsith", "Weapon", 11},
        {"Claymore", "Weapon", 189}
    };

    int jumlahItem = DATABASE;
    int kriteria, ascending, opsi;
    char searchQuery[50];
    int searchQTY;
    const char *filename = "Inventory-Genshin.txt";
    int nameSorted = 0;     // 0 = belum disortir berdasarkan nama
	int categorySorted = 0; // 0 = belum disortir berdasarkan kategori
	int quantitySorted = 0; // 0 = belum disortir berdasarkan kuantitas



    do {
    	printf("\n +-----------------------------+\n");
        printf(" |        GENSHIN IMPACT       |");
        printf("\n +-----------------------------+\n");
        printf(" | ==== I N V E N T O R Y ==== |");
        printf("\n +---+-------------------------+\n");
        printf(" | 1 | Open Inventory          |\n");
        printf(" | 2 | Sort Item               |\n");
        printf(" | 3 | Find Item               |\n");
        printf(" | 4 | Save Database           |\n");
        printf(" | 5 | Load Database           |\n");
        printf(" | 6 | Exit                    |");
        printf("\n +---+-------------------------+\n");
        printf("\n Select option: ");
        scanf("%d", &opsi);

        switch (opsi) {
        	
        case 1:
            printf("\n Inventory:\n");
            printData(item, jumlahItem);
            break;
            
        case 2:
            printf("\n Pilih Kriteria Sortir:\n");
            printf(" 1. Name\n");
            printf(" 2. Category\n");
            printf(" 3. Quantity\n");
            printf("\n Masukkan opsi (1-3): ");
            scanf("%d", &kriteria);

            printf("\n Pilih Urutan: \n");
            printf(" 1. Ascending\n");
            printf(" 2. Descending\n");
            printf("\n Masukkan opsi (1-2): ");
            scanf("%d", &ascending);

            bubbleSort(item, jumlahItem, kriteria, ascending == 1);
		    // Set status sorting
		    if (kriteria == 1) {
		        nameSorted = 1;
		        categorySorted = 0; // Reset status kategori
		        quantitySorted = 0; // Reset status kuantitas
		    } else if (kriteria == 2) {
		        nameSorted = 0; // Reset status nama
		        categorySorted = 1;
		        quantitySorted = 0; // Reset status kuantitas
		    } else if (kriteria == 3) {
		        nameSorted = 0;	// Reset status nama
		        categorySorted = 0; // Reset status kategori
		        quantitySorted = 1;
		    }
            printf("\n Inventory setelah di-sortir:\n");
            printData(item, jumlahItem);
            break;
            
    	case 3:
		    // Pastikan data sudah di-sortir berdasarkan kriteria
		    if ((kriteria == 1 && !nameSorted) ||
		        (kriteria == 2 && !categorySorted) ||
		        (kriteria == 3 && !quantitySorted)) {
		        printf("\n Data belum disortir... Silakan sortir terlebih dahulu!\n");
		        break;
		    }
		    printf("\n Pilih Kriteria Pencarian:\n");
		    printf(" 1. Name\n");
		    printf(" 2. Category\n");
		    printf(" 3. Quantity\n");
		    printf("\n Masukkan opsi (1-3): ");
		    scanf("%d", &kriteria);
		
		    /* Pastikan data sudah di-sortir 
			(Jika data ditemukan sebelum di-sortir, artinya linear search...) */
		    bubbleSort(item, jumlahItem, kriteria, 1);
		
		    if (kriteria == 3) {
		        printf("\n Masukkan quantity yang ingin dicari: ");
		        scanf("%d", &searchQTY);
		        int found = 0; // Flag apakah ada item ditemukan
				printf("\n Item yang ditemukan:\n");
				for (int i = 0; i < jumlahItem; i++) {
    				if (item[i].quantity == searchQTY) {
        				printData(&item[i], 1);
        				found = 1; // flag 1 jika item ditemukan
    				}
				}
				if (!found) {
	    			printf("\n Item dengan quantity %d tidak ditemukan.\n", searchQTY);
				}

		        
		    } else {
		    	while (getchar() != '\n'); 
		        printf("\n Masukkan keyword yang ingin dicari: ");
		        scanf("%[^\n]", searchQuery); // %[^\n] agar bisa cari nama item yang lebih dari 1 kata
		        int found = 0; // Flag apakah ada item ditemukan
		        printf("\n Item yang ditemukan:\n");
		        for (int i = 0; i < jumlahItem; i++) {
		            if ((kriteria == 1 && strcmp(item[i].name, searchQuery) == 0) ||
		                (kriteria == 2 && strcmp(item[i].category, searchQuery) == 0)) {
		                printData(&item[i], 1);
		                found = 1; // flag 1 jika item ditemukan
		            }
		        }
		        if (!found) {
		            printf("\n Item dengan keyword '%s' tidak ditemukan.\n", searchQuery);
		        }
		    }
		    break;

        case 4:
        	saveDatabase(item, jumlahItem, filename);
            break;
            
        case 5: 
    		jumlahItem = loadDatabase(item, filename);
    		break;

        case 6:
            printf("\n Keluar...\n");
            break;
            
        default:
            printf("\n Opsi invalid...\n");
        }
        
    } while (opsi != 6);

    return 0;
}
