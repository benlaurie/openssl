#include <assert.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    struct stat st;
    stat(argv[1], &st);
    FILE *f = fopen(argv[1], "r");
    char *buf = malloc(st.st_size);
    size_t s = fread(buf, 1, st.st_size, f);
    assert(s == st.st_size);
    LLVMFuzzerTestOneInput(buf, s);
    free(buf);
    fclose(f);
    return 0;
}

