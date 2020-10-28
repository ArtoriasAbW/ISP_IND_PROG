#include "mmap_file.h"

char *mmap_file(char *path, size_t *size) {
    assert(path != NULL && size != NULL);
    struct stat file_info;
    if (stat(path, &file_info) == -1) {
        fprintf(stderr, "Error :%s\n", strerror(errno));
        exit(1);
    }
    *size = file_info.st_size;
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error : %s\n", strerror(errno));
        exit(1);
    }

    char *intructions = (char *)mmap(0 , *size, PROT_READ, MAP_SHARED, fd, 0);
    if (intructions == MAP_FAILED) {
        fprintf(stderr, "Error :%s\n", strerror(errno));
        exit(1);
    }
    if (close(fd) == -1) {
        fprintf(stderr, "Error :%s\n", strerror(errno));
        exit(1);
    }
    return intructions;
    
}