 #include <stdio.h>

void bubbleSort(int data[6]) {
    for (int i = 0; i < 6 - 1; i++) {
        for (int j = 0; j < 6 - i - 1; j++) {
            if (data[j] < data[j + 1]) { /* ubah '>' untuk ascending, dan '<' untuk descending */
                int temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

void printData(int data[6]) {
    for (int i = 0; i < 6; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int main() {
    int data[6] = {22, 10, 15, 3, 8, 2};

    printf("Data sebelum di-sort: ");
    printData(data);

    bubbleSort(data);

    printf("Data setelah di-sort: ");
    printData(data);

    return 0;
}
