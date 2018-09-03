#include "php.h"
#include "drng.h"

#define RDRAND_CUTOFF 10

#define LGV_RDRAND_MAX 386786400
#define LGV_RDRAND_LIMIT 4254650400 // MAX * 11

#define PHP_MY_EXTENSION_VERSION "1.0"
#define PHP_MY_EXTENSION_EXTNAME "lgv_rdrand"

PHP_FUNCTION(lgv_rdrand_uint32);

extern zend_module_entry lgv_rdrand_module_entry;

#define phpext_my_extension_ptr &lgv_rdrand_module_entry

static zend_function_entry lgv_rdrand_functions[] = {
    PHP_FE(lgv_rdrand_uint32, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry lgv_rdrand_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_MY_EXTENSION_EXTNAME,
    lgv_rdrand_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_MY_EXTENSION_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(lgv_rdrand)

PHP_FUNCTION(lgv_rdrand_uint32)
{
    int r, i;
    uint32_t n;
    uint32_t data[RDRAND_CUTOFF] = {0};

    if (RdRand_isSupported()) {
        r = rdrand_get_n_32(RDRAND_CUTOFF, data);
        if (r == DRNG_SUCCESS) {
            for (i = 0; i < RDRAND_CUTOFF; i++) {
                n = data[i];

                if (n > LGV_RDRAND_LIMIT) {
                    continue;
                }

                RETURN_LONG(n % LGV_RDRAND_MAX);
            }
        }
    }

    RETURN_LONG(0);
}
