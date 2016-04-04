#include <assert.h>
#include <stdio.h>
#include <openssl/bn.h>
#include <FuzzerInterface.h>

int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len) {
    int success = 1;
    static BN_CTX *ctx;
    static BIGNUM *b1;
    static BIGNUM *b2;
    static BIGNUM *b3;
    static BIGNUM *b4;
    if (ctx == NULL) {
        b1 = BN_new();
        b2 = BN_new();
        b3 = BN_new();
        b4 = BN_new();
        ctx = BN_CTX_new();
    }
    size_t l1 = 0, l2 = 0;
    if (len > 0) {
        l1 = (buf[0] * (len - 1)) / 255;
        ++buf;
        l2 = len - 1 - l1;
    }
    BN_bin2bn(buf, l1, b1);
    BN_bin2bn(buf + l1, l2, b2);

    // divide by 0 is an error undefined
    if (BN_is_zero(b2))
        goto done;

    assert(BN_div(b3, b4, b1, b2, ctx));
    assert(BN_mul(b3, b3, b2, ctx));
    assert(BN_add(b3, b3, b4));

    success = BN_cmp(b3, b1) == 0;
    if (!success) {
        BN_print_fp(stdout, b1);
        putchar('\n');
        BN_print_fp(stdout, b2);
        putchar('\n');
        BN_print_fp(stdout, b3);
        putchar('\n');
        BN_print_fp(stdout, b4);
        putchar('\n');
    }

 done:
    assert(success);

    return 0;
}
