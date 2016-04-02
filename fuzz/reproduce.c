#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <FuzzerInterface.h>

__attribute__((weak)) int LLVMFuzzerInitialize(int *argc, char ***argv);

int main(int argc, char **argv) {
    if (LLVMFuzzerInitialize)
        LLVMFuzzerInitialize(&argc, &argv);

    struct stat st;
    stat(argv[1], &st);
    FILE *f = fopen(argv[1], "r");
    unsigned char *buf = malloc(st.st_size);
    size_t s = fread(buf, 1, st.st_size, f);
    assert(s == (size_t)st.st_size);
    LLVMFuzzerTestOneInput(buf, s);
    free(buf);
    fclose(f);
    return 0;
}
