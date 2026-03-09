#include <stdio.h>
#include <stdlib.h>
#include "tinyexpr.h"

int main(int argc, char **argv) {
    if (argc != 2) return 1;

    FILE *f = fopen(argv[1], "rb");
    if (!f) return 1;

    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
    long size = ftell(f);
    if (size < 0) { fclose(f); return 1; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

    char *buf = malloc((size_t)size + 1);
    if (!buf) { fclose(f); return 1; }

    size_t n = fread(buf, 1, (size_t)size, f);
    fclose(f);
    buf[n] = '\0';

    te_expr *expr = te_compile(buf, 0, 0, 0);
    if (expr) te_free(expr);

    free(buf);
    return 0;
}
