#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum SortMode {
    ASCENDING = 1,
    DESCENDING = -1
};

enum SortType {
    SORT_BY_NAME = 0,
    SORT_BY_ADDRESS = 1,
    SORT_BY_ID = 2
};

typedef struct {
    char ID[16];
    int prefecture;
    int type;
    char name[128];
    char address[128];
} HighSchool;

void sortByName (HighSchool highschoolArray[], int array_size, int mode);
void swapHighschool (HighSchool *a, HighSchool *b);

// 1: ascending, -1: descending
void sortByName (HighSchool highschoolArray[], int array_size, int mode) {
    int i, j;
    for (i = 0; i < array_size - 1; i++){
        for (j = array_size - 1; j >= i + 1; j--){
            if (strcmp(highschoolArray[j].name, highschoolArray[j-1].name)*mode < 0) {
                swapHighschool(&highschoolArray[j], &highschoolArray[j-1]);
            }
        }
    }
}

// 1: ascending, -1: descending
void sortByAddress (HighSchool highschoolArray[], int array_size, int mode) {
    int i, j;
    for (i = 0; i < array_size - 1; i++){
        for (j = array_size - 1; j >= i + 1; j--){
            if (strcmp(highschoolArray[j].address, highschoolArray[j-1].address)*mode < 0) {
                swapHighschool(&highschoolArray[j], &highschoolArray[j-1]);
            }
        }
    }
}

void sortByID (HighSchool highschoolArray[], int array_size, int mode) {
    int i, j;
    for (i = 0; i < array_size - 1; i++){
        for (j = array_size - 1; j >= i + 1; j--){
            long long ID_tmp1, ID_tmp2;
            sscanf(highschoolArray[j].ID, "D%lld", &ID_tmp1);
            sscanf(highschoolArray[j-1].ID, "D%lld", &ID_tmp2);
            if ((ID_tmp1-ID_tmp2)*mode < 0) {
                swapHighschool(&highschoolArray[j], &highschoolArray[j-1]);
            }
        }
    }
}

void swapHighschool (HighSchool *a, HighSchool *b) {
    HighSchool tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void switchSort (HighSchool highschoolArray[], int array_size, int type) {
    switch (type/2) {
        case SORT_BY_NAME:
            if(type%2 == 0) sortByName(highschoolArray, array_size, ASCENDING);
            else sortByName(highschoolArray, array_size, DESCENDING);
            break;
        case SORT_BY_ADDRESS:
            if(type%2 == 0) sortByAddress(highschoolArray, array_size, ASCENDING);
            else sortByAddress(highschoolArray, array_size, DESCENDING);
            break;
        case SORT_BY_ID:
            if(type%2 == 0) sortByID(highschoolArray, array_size, ASCENDING);
            else sortByID(highschoolArray, array_size, DESCENDING);
            break;
        default:
            printf("Invalid sort type\n");
            break;
    }
}

int main (int argc, char *argv[]) {
    FILE *rfp, *wfp;
    printf("HighSchool Data\n");
    if (argc != 3) {
        printf("Usage: %s <csv_file> <output_file>\n", argv[0]);
        return 1;
    }
    char *targetreadcsv = argv[1];
	rfp = fopen(targetreadcsv, "r");
    if (rfp == NULL) {
        printf("ReadFile open error\n");
        return 1;
    }
    char *outputFile = argv[2];
	wfp = fopen(outputFile, "w");
    if (wfp == NULL) {
        printf("WriteFile open error\n");
        return 1;
    }
    char line[512];
    char ID_tmp[16];
    int count = 0;
    HighSchool highschool[10000];
    while (fgets(line, sizeof(line), rfp)!= NULL) {
        sscanf(line, "%[^,],%d,%d,%[^,],%[^\n]", highschool[count].ID, &highschool[count].prefecture, &highschool[count].type, highschool[count].name, highschool[count].address);
        count++;
    }
    sortByName(highschool, count, -1);
    for(int i = 0; i < count; i++) {
        fprintf(wfp,"%s %s %d %d %s\n", highschool[i].name, highschool[i].ID, highschool[i].prefecture, highschool[i].type, highschool[i].address);
    }
    fclose(rfp);
    fclose(wfp);
    return 0;
}
