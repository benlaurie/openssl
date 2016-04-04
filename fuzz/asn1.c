#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <openssl/asn1.h>
#include <openssl/asn1t.h>
#include <openssl/ec.h>
#include <openssl/pkcs12.h>
#include <openssl/x509v3.h>
#include <FuzzerInterface.h>

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
    else if(!strcmp(cmd, "ECPARAMETERS"))
        item_type = ASN1_ITEM_rptr(ECPARAMETERS);
    else if(!strcmp(cmd, "ECPKPARAMETERS"))
        item_type = ASN1_ITEM_rptr(ECPKPARAMETERS);
    else if (!strcmp(cmd, "GENERAL_NAME"))
        item_type = ASN1_ITEM_rptr(GENERAL_NAME);
    else if (!strcmp(cmd, "GENERAL_SUBTREE"))
        item_type = ASN1_ITEM_rptr(GENERAL_SUBTREE);
    else if (!strcmp(cmd, "NAME_CONSTRAINTS"))
        item_type = ASN1_ITEM_rptr(NAME_CONSTRAINTS);
    else if (!strcmp(cmd, "PKCS12_AUTHSAFES"))
        item_type = ASN1_ITEM_rptr(PKCS12_AUTHSAFES);
    else if (!strcmp(cmd, "PKCS12_SAFEBAGS"))
        item_type = ASN1_ITEM_rptr(PKCS12_SAFEBAGS);
    else if (!strcmp(cmd, "POLICY_CONSTRAINTS"))
        item_type = ASN1_ITEM_rptr(POLICY_CONSTRAINTS);
    else if (!strcmp(cmd, "POLICY_MAPPINGS"))
        item_type = ASN1_ITEM_rptr(POLICY_MAPPINGS);
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
