#include <stdio.h>
#include <openssl/asn1.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

// Change GENERAL_NAME to whatever you want to fuzz

int LLVMFuzzerTestOneInput(uint8_t *buf, size_t len) {
    const uint8_t *b = buf;
    ASN1_VALUE *o = ASN1_item_d2i(NULL, &b, len,
                                  ASN1_ITEM_rptr(GENERAL_NAME));
    ASN1_item_free(o, ASN1_ITEM_rptr(GENERAL_NAME));
    return 0;
}
