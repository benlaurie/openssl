#include <openssl/bio.h>
#include <openssl/cms.h>

int LLVMFuzzerTestOneInput(uint8_t *buf, size_t len) {
    BIO *in = BIO_new(BIO_s_mem());
    BIO_write(in, buf, len);
    CMS_ContentInfo *i = d2i_CMS_bio(in, NULL);
    CMS_ContentInfo_free(i);
    BIO_free(in);
    return 0;
}

