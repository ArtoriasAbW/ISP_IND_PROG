/** @file */

#include "Output.h"

void WriteInFile(MyStringViews data, char *file_name) {
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Cannot open file %s", file_name);
        exit(1);
    }
    for (int i = 0; i < data.size; ++i) {
        fprintf(file, "%s\n", data.data[i].str);
    }
    fclose(file);
}
