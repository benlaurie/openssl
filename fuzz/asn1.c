#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <openssl/asn1.h>
#include <openssl/asn1t.h>
#include <openssl/x509v3.h>
#include <FuzzerInterface.h>

// Change GENERAL_NAME to whatever you want to fuzz

static const ASN1_ITEM *item_type;

int LLVMFuzzerInitialize(int *argc, char ***argv) {
    const char *cmd;
    assert(*argc > 1);

    cmd = (*argv)[1];
    (*argv)[1] = (*argv)[0];
    ++*argv;
    --*argc;
    if(!strcmp(cmd, "ASN1_SEQUENCE"))
        item_type = ASN1_ITEM_rptr(ASN1_SEQUENCE);
    else if(!strcmp(cmd, "BIGNUM"))
        item_type = ASN1_ITEM_rptr(BIGNUM);
    else if (!strcmp(cmd, "GENERAL_NAME"))
        item_type = ASN1_ITEM_rptr(GENERAL_NAME);
    else if(!strcmp(cmd, "X509"))
        item_type = ASN1_ITEM_rptr(X509);
    else
        assert(!"Bad type");

    return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len) {
    const uint8_t *b = buf;
    ASN1_VALUE *o = ASN1_item_d2i(NULL, &b, len, item_type);
    ASN1_item_free(o, item_type);
    return 0;
}
