#ifndef __DEFINES_H
#define __DEFINES_H

#define OPENSSL_NO_STDIO 1
#define OPENSSL_NO_FP_API 1
#define NO_STRINGS_H 1
#define OPENSSL_NO_SYS_TYPES_H 1
#define OPENSSL_NO_SYS_PARAM_H 1
#define THREADS 1
#define L_ENDIAN 1
#define NCOMPAT 1

#define OPENSSL_NO_BIO 1

#define OPENSSL_NO_OCSP 1
//#define OPENSSL_NO_LHASH 1
/* define if necessary */
#undef OPENSSL_NO_DES
#undef OPENSSL_NO_RSA
#undef OPENSSL_NO_DSA
#undef OPENSSL_NO_BF
#undef OPENSSL_NO_CAST
#undef OPENSSL_NO_DH
#undef OPENSSL_NO_IDEA
#undef OPENSSL_NO_RC2
#undef OPENSSL_NO_RC4
#undef OPENSSL_NO_RC5
#undef OPENSSL_NO_MD2
#undef OPENSSL_NO_MD4
#undef OPENSSL_NO_MD5
#undef OPENSSL_NO_RIPEMD
#undef OPENSSL_NO_MDC2
#undef OPENSSL_NO_SHA
#undef OPENSSL_NO_HMAC

#endif /* __DEFINES_H */
