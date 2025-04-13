#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char ID[16];
    int prefecture;
    int type;
    char name[128];
    char address[128];
} HighSchool;

void bubbleSortHighschool (HighSchool highschoolArray[], int array_size, int mode);
void swapHighschool (HighSchool *a, HighSchool *b);

void bubbleSortHighschool (HighSchool highschoolArray[], int array_size, int mode) {
    int i, j;
    for (i = 0; i < array_size - 1; i++){
        for (j = array_size - 1; j >= i + 1; j--){
            if (strcmp(highschoolArray[j].name, highschoolArray[j-1].name) < 0) {
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
    int count = 0;
    HighSchool highschool[10000];
    while (fgets(line, sizeof(line), rfp)!= NULL) {
        sscanf(line, "%[^,],%d,%d,%[^,],%[^\n]", highschool[count].ID, &highschool[count].prefecture, &highschool[count].type, highschool[count].name, highschool[count].address);
        //printf("%s %s %d %d %s\n", highschool[count].name, highschool[count].ID, highschool[count].prefecture, highschool[count].type, highschool[count].address);
        fprintf(wfp,"%s %s %d %d %s\n", highschool[count].name, highschool[count].ID, highschool[count].prefecture, highschool[count].type, highschool[count].address);
        count++;
    }
    bubbleSortHighschool(highschool, count, 0);
    for(int i = 0; i < count; i++) {
        printf("%s %s %d %d %s\n", highschool[i].name, highschool[i].ID, highschool[i].prefecture, highschool[i].type, highschool[i].address);
    }
    fclose(rfp);
    fclose(wfp);
    return 0;
}
