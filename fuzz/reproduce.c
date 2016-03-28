#include <stdio.h>

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "r");
    char buf[4096];
    size_t s = fread(buf, 1, sizeof buf, f);
    LLVMFuzzerTestOneInput(buf, s);
    return 0;
}

