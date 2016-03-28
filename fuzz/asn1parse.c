#include <stdio.h>
#include <openssl/asn1.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

// This one produces crashes that don't reproduce. Why? 

int LLVMFuzzerTestOneInput(uint8_t *buf, size_t len) {
    static BIO *bio_out;

    if (bio_out == NULL)
        bio_out = BIO_new_fp(stdout, BIO_NOCLOSE | BIO_FP_TEXT);

    if (!ASN1_parse_dump(bio_out, buf, len, 0, 0))
        ERR_print_errors(bio_out);
    return 0;
}
