PHP_ARG_ENABLE(lgv_rdrand, whether to enable lgv_rdrand support,
[ --enable-lgv_rdrand   Enable lgv_rdrand support])

if test "$PHP_LGV_RDRAND" = "yes"; then
    AC_DEFINE(HAVE_LGV_RDRAND, 1, [Whether you have lgv_rdrand])
    PHP_NEW_EXTENSION(lgv_rdrand, lgv_rdrand.c rdrand.c, $ext_shared)
fi
