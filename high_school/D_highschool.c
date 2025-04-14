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
        fprintf(wfp,"%s %s %d %d %s\n", highschool[count].name, highschool[count].ID, highschool[count].prefecture, highschool[count].type, highschool[count].address);
        count++;
    }
    fclose(rfp);
    fclose(wfp);
    return 0;
}
