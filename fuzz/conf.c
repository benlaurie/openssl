#include <openssl/conf.h>

int LLVMFuzzerTestOneInput(uint8_t *buf, size_t len) {
    CONF *conf = NCONF_new(NULL);
    BIO *in = BIO_new(BIO_s_mem());
    long eline;

    BIO_write(in, buf, len);
    NCONF_load_bio(conf, in, &eline);
    //NCONF_dump_fp(conf, stdout);
    NCONF_free(conf);
    BIO_free(in);

    return 0;
}
