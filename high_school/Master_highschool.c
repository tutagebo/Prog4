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

// return data count
int loadHighSchoolData(HighSchool *highschool, FILE *rfp) {
    char line[512];
    int count = 0;
    while (fgets(line, sizeof(line), rfp)!= NULL) {
        sscanf(line, "%[^,],%d,%d,%[^,],%[^\n]", highschool[count].ID, &highschool[count].prefecture, &highschool[count].type, highschool[count].name, highschool[count].address);
        count++;
    }
    return count;
}

void searchHighSchool(HighSchool *highschool, int count, char *search) {
    for (int i = 0; i < count; i++) {
        if (strcmp(highschool[i].ID, search) == 0 || strcmp(highschool[i].name, search) == 0 || strcmp(highschool[i].address, search) == 0 ) {
            printf("ID: %s\n", highschool[i].ID);
            printf("Prefecture: %d\n", highschool[i].prefecture);
            printf("Type: %d\n", highschool[i].type);
            printf("Name: %s\n", highschool[i].name);
            printf("Address: %s\n", highschool[i].address);
            return;
        }
    }
    printf("High school not found.\n");
}

int main (int argc, char *argv[]) {
    FILE *rfp, *wfp;
    char *mode = argv[1];
    HighSchool highschool[10000];
    char *readFile = argv[2];
    // open read file
    rfp = fopen(readFile, "r");
    if (rfp == NULL) {
        printf("ReadFile open error\n");
        return 1;
    }
    int count = loadHighSchoolData(highschool, rfp);
    if(strcmp(mode, "load-only") == 0) {
        for(int i = 0; i < count; i++) {
            printf("%s %s %d %d %s\n", highschool[i].name, highschool[i].ID, highschool[i].prefecture, highschool[i].type, highschool[i].address);
        }
    }
    if(strcmp(mode, "output-only") == 0) {
        char *outputFile = argv[3];
        // open write file
        wfp = fopen(outputFile, "w");
        if (wfp == NULL) {
            printf("WriteFile open error\n");
            return 1;
        }
        for(int i = 0; i < count; i++) {
            fprintf(wfp,"%s %s %d %d %s\n", highschool[i].name, highschool[i].ID, highschool[i].prefecture, highschool[i].type, highschool[i].address);
        }
        fclose(wfp);
    }
    if(strcmp(mode, "sort") == 0) {
        char *outputFile = argv[3];
        // open write file
        wfp = fopen(outputFile, "w");
        if (wfp == NULL) {
            printf("WriteFile open error\n");
            return 1;
        }
        int type = atoi(argv[4]);
        switchSort(highschool, count, type);
        for(int i = 0; i < count; i++) {
            fprintf(wfp,"%s %s %d %d %s\n", highschool[i].name, highschool[i].ID, highschool[i].prefecture, highschool[i].type, highschool[i].address);
        }
        fclose(wfp);
    }
    if(strcmp(mode, "search") == 0) {
        char *search = argv[3];
        searchHighSchool(highschool, count, search);
    }
    fclose(rfp);
    return 0;
}
