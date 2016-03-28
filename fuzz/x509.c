#include <stdio.h>
#include <openssl/asn1.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

int LLVMFuzzerTestOneInput(uint8_t *buf, size_t len) {
    const uint8_t *b = buf;
    X509 *x = d2i_X509(NULL, &b, len);
    X509_free(x);
    return 0;
}
