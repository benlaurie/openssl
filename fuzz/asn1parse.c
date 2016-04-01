#include <stdio.h>
#include <openssl/asn1.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <FuzzerInterface.h>

int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len) {
    static BIO *bio_out;

    if (bio_out == NULL)
        bio_out = BIO_new_file("/dev/null", "w");

    ASN1_parse_dump(bio_out, buf, len, 0, 0);
    return 0;
}
