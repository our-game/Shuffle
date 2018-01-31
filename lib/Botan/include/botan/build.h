
#ifndef BOTAN_BUILD_CONFIG_H__
#define BOTAN_BUILD_CONFIG_H__

/*
* This file was automatically generated Fri Feb 17 17:49:25 2017 UTC by
* abtre@chizesheng running 'configure.py --cc=msvc --cpu=X86 --enable-debug'
*
* Target
*  - Compiler: cl /MDd /Od /Zi /DDEBUG 
*  - Arch: x86_32/x86_32
*  - OS: windows
*/

#define BOTAN_VERSION_MAJOR 1
#define BOTAN_VERSION_MINOR 10
#define BOTAN_VERSION_PATCH 15
#define BOTAN_VERSION_DATESTAMP 0

#define BOTAN_VERSION_VC_REVISION "unknown"

#define BOTAN_DISTRIBUTION_INFO "unspecified"

#ifndef BOTAN_DLL
  #define BOTAN_DLL __declspec(dllimport)
#endif

/* Chunk sizes */
#define BOTAN_DEFAULT_BUFFER_SIZE 4096
#define BOTAN_MEM_POOL_CHUNK_SIZE 64*1024
#define BOTAN_BLOCK_CIPHER_PAR_MULT 4

/* BigInt toggles */
#define BOTAN_MP_WORD_BITS 32
#define BOTAN_KARAT_MUL_THRESHOLD 32
#define BOTAN_KARAT_SQR_THRESHOLD 32

/* PK key consistency checking toggles */
#define BOTAN_PUBLIC_KEY_STRONG_CHECKS_ON_LOAD 1
#define BOTAN_PRIVATE_KEY_STRONG_CHECKS_ON_LOAD 0
#define BOTAN_PRIVATE_KEY_STRONG_CHECKS_ON_GENERATE 1

/*
* RNGs will automatically poll the system for additional
* seed material after producing this many bytes of output.
*/
#define BOTAN_RNG_MAX_OUTPUT_BEFORE_RESEED 512
#define BOTAN_RNG_RESEED_POLL_BITS 128

/* Should we use GCC-style inline assembler? */
#if !defined(BOTAN_USE_GCC_INLINE_ASM) && defined(__GNUG__)
  #define BOTAN_USE_GCC_INLINE_ASM 1
#endif

#if !defined(BOTAN_USE_GCC_INLINE_ASM)
  #define BOTAN_USE_GCC_INLINE_ASM 0
#endif

#ifdef __GNUC__
  #define BOTAN_GCC_VERSION \
     (__GNUC__ * 100 + __GNUC_MINOR__ * 10 + __GNUC_PATCHLEVEL__)
#else
  #define BOTAN_GCC_VERSION 0
#endif

/* Target identification and feature test macros */
#define BOTAN_TARGET_OS_IS_WINDOWS
#define BOTAN_TARGET_OS_HAS_GMTIME_S
#define BOTAN_TARGET_OS_HAS_LOADLIBRARY
#define BOTAN_TARGET_OS_HAS_WIN32_GET_SYSTEMTIME
#define BOTAN_TARGET_OS_HAS_WIN32_VIRTUAL_LOCK

#define BOTAN_TARGET_ARCH_IS_X86_32
#define BOTAN_TARGET_CPU_IS_LITTLE_ENDIAN
#define BOTAN_TARGET_CPU_IS_X86_FAMILY
#define BOTAN_TARGET_UNALIGNED_MEMORY_ACCESS_OK 1

#if defined(BOTAN_TARGET_CPU_IS_LITTLE_ENDIAN) || \
    defined(BOTAN_TARGET_CPU_IS_BIG_ENDIAN)
  #define BOTAN_TARGET_CPU_HAS_KNOWN_ENDIANNESS
#endif

#define BOTAN_BUILD_COMPILER_IS_MSVC

#if defined(_MSC_VER)
  // 4250: inherits via dominance (diamond inheritence issue)
  // 4251: needs DLL interface (STL DLL exports)
  #pragma warning(disable: 4250 4251)
#endif

/*
* Compile-time deprecatation warnings
*/
#if !defined(BOTAN_NO_DEPRECATED_WARNINGS)

  #if defined(__clang__)
    #define BOTAN_DEPRECATED(msg) __attribute__ ((deprecated))

  #elif defined(_MSC_VER)
    #define BOTAN_DEPRECATED(msg) __declspec(deprecated(msg))

  #elif defined(__GNUG__)

    #if BOTAN_GCC_VERSION >= 450 && !defined(__INTEL_COMPILER)
      #define BOTAN_DEPRECATED(msg) __attribute__ ((deprecated(msg)))
    #else
      #define BOTAN_DEPRECATED(msg) __attribute__ ((deprecated))
    #endif

  #endif

#endif

#if !defined(BOTAN_DEPRECATED)
  #define BOTAN_DEPRECATED(msg)
#endif

/*
* Module availability definitions
*/
#define BOTAN_HAS_ADLER32
#define BOTAN_HAS_AES
#define BOTAN_HAS_ALGORITHM_FACTORY
#define BOTAN_HAS_ANSI_X919_MAC
#define BOTAN_HAS_ARC4
#define BOTAN_HAS_ASN1
#define BOTAN_HAS_AUTO_SEEDING_RNG
#define BOTAN_HAS_BASE64_CODEC
#define BOTAN_HAS_BCRYPT
#define BOTAN_HAS_BIGINT
#define BOTAN_HAS_BIGINT_MATH
#define BOTAN_HAS_BIGINT_MP
#define BOTAN_HAS_BLOCK_CIPHER
#define BOTAN_HAS_BLOWFISH
#define BOTAN_HAS_BMW_512
#define BOTAN_HAS_CAMELLIA
#define BOTAN_HAS_CASCADE
#define BOTAN_HAS_CAST
#define BOTAN_HAS_CBC
#define BOTAN_HAS_CBC_MAC
#define BOTAN_HAS_CERTIFICATE_STORE
#define BOTAN_HAS_CFB
#define BOTAN_HAS_CIPHER_MODE_PADDING
#define BOTAN_HAS_CMAC
#define BOTAN_HAS_CODEC_FILTERS
#define BOTAN_HAS_COMB4P
#define BOTAN_HAS_CORE_ENGINE
#define BOTAN_HAS_CRC24
#define BOTAN_HAS_CRC32
#define BOTAN_HAS_CRYPTO_BOX
#define BOTAN_HAS_CTR_BE
#define BOTAN_HAS_CTS
#define BOTAN_HAS_DES
#define BOTAN_HAS_DIFFIE_HELLMAN
#define BOTAN_HAS_DLIES
#define BOTAN_HAS_DL_GROUP
#define BOTAN_HAS_DL_PUBLIC_KEY_FAMILY
#define BOTAN_HAS_DSA
#define BOTAN_HAS_DYNAMICALLY_LOADED_ENGINE
#define BOTAN_HAS_DYNAMIC_LOADER
#define BOTAN_HAS_EAX
#define BOTAN_HAS_ECB
#define BOTAN_HAS_ECC_GROUP
#define BOTAN_HAS_ECC_PUBLIC_KEY_CRYPTO
#define BOTAN_HAS_ECDH
#define BOTAN_HAS_ECDSA
#define BOTAN_HAS_EC_CURVE_GFP
#define BOTAN_HAS_ELGAMAL
#define BOTAN_HAS_EME1
#define BOTAN_HAS_EME_PKCS1v15
#define BOTAN_HAS_EMSA1
#define BOTAN_HAS_EMSA1_BSI
#define BOTAN_HAS_EMSA2
#define BOTAN_HAS_EMSA3
#define BOTAN_HAS_EMSA4
#define BOTAN_HAS_EMSA_RAW
#define BOTAN_HAS_ENGINES
#define BOTAN_HAS_ENGINE_SIMD
#define BOTAN_HAS_ENTROPY_SRC_CAPI
#define BOTAN_HAS_ENTROPY_SRC_HIGH_RESOLUTION_TIMER
#define BOTAN_HAS_ENTROPY_SRC_WIN32
#define BOTAN_HAS_FILTERS
#define BOTAN_HAS_FPE_FE1
#define BOTAN_HAS_GOST_28147_89
#define BOTAN_HAS_GOST_34_10_2001
#define BOTAN_HAS_GOST_34_11
#define BOTAN_HAS_HASH_ID
#define BOTAN_HAS_HAS_160
#define BOTAN_HAS_HEX_CODEC
#define BOTAN_HAS_HMAC
#define BOTAN_HAS_HMAC_RNG
#define BOTAN_HAS_IDEA
#define BOTAN_HAS_IF_PUBLIC_KEY_FAMILY
#define BOTAN_HAS_KASUMI
#define BOTAN_HAS_KDF1
#define BOTAN_HAS_KDF2
#define BOTAN_HAS_KDF_BASE
#define BOTAN_HAS_KECCAK
#define BOTAN_HAS_KEYPAIR_TESTING
#define BOTAN_HAS_LIBSTATE_MODULE
#define BOTAN_HAS_LION
#define BOTAN_HAS_LUBY_RACKOFF
#define BOTAN_HAS_MARS
#define BOTAN_HAS_MD2
#define BOTAN_HAS_MD4
#define BOTAN_HAS_MD5
#define BOTAN_HAS_MDX_HASH_FUNCTION
#define BOTAN_HAS_MGF1
#define BOTAN_HAS_MISTY1
#define BOTAN_HAS_MUTEX_NOOP
#define BOTAN_HAS_MUTEX_WIN32
#define BOTAN_HAS_MUTEX_WRAPPERS
#define BOTAN_HAS_NOEKEON
#define BOTAN_HAS_NOEKEON_SIMD
#define BOTAN_HAS_NYBERG_RUEPPEL
#define BOTAN_HAS_OFB
#define BOTAN_HAS_OID_LOOKUP
#define BOTAN_HAS_OPENPGP_CODEC
#define BOTAN_HAS_PACKAGE_TRANSFORM
#define BOTAN_HAS_PARALLEL_HASH
#define BOTAN_HAS_PASSHASH9
#define BOTAN_HAS_PASSWORD_BASED_ENCRYPTION
#define BOTAN_HAS_PBE_PKCS_V15
#define BOTAN_HAS_PBE_PKCS_V20
#define BOTAN_HAS_PBKDF1
#define BOTAN_HAS_PBKDF2
#define BOTAN_HAS_PEM_CODEC
#define BOTAN_HAS_PGPS2K
#define BOTAN_HAS_PKCS10_REQUESTS
#define BOTAN_HAS_PK_PADDING
#define BOTAN_HAS_PUBLIC_KEY_CRYPTO
#define BOTAN_HAS_PUBLIC_KEY_CRYPTO
#define BOTAN_HAS_RANDPOOL
#define BOTAN_HAS_RC2
#define BOTAN_HAS_RC5
#define BOTAN_HAS_RC6
#define BOTAN_HAS_RFC3394_KEYWRAP
#define BOTAN_HAS_RIPEMD_128
#define BOTAN_HAS_RIPEMD_160
#define BOTAN_HAS_RSA
#define BOTAN_HAS_RUNTIME_BENCHMARKING
#define BOTAN_HAS_RW
#define BOTAN_HAS_SAFER
#define BOTAN_HAS_SALSA20
#define BOTAN_HAS_SEED
#define BOTAN_HAS_SELFTESTS
#define BOTAN_HAS_SERPENT
#define BOTAN_HAS_SERPENT_SIMD
#define BOTAN_HAS_SHA1
#define BOTAN_HAS_SHA2_32
#define BOTAN_HAS_SHA2_64
#define BOTAN_HAS_SIMD_32
#define BOTAN_HAS_SIMD_SCALAR
#define BOTAN_HAS_SKEIN_512
#define BOTAN_HAS_SKIPJACK
#define BOTAN_HAS_SQUARE
#define BOTAN_HAS_SRP6
#define BOTAN_HAS_SSL3_MAC
#define BOTAN_HAS_SSL_V3_PRF
#define BOTAN_HAS_STREAM_CIPHER
#define BOTAN_HAS_TEA
#define BOTAN_HAS_THRESHOLD_SECRET_SHARING
#define BOTAN_HAS_TIGER
#define BOTAN_HAS_TLS_V10_PRF
#define BOTAN_HAS_TURING
#define BOTAN_HAS_TWOFISH
#define BOTAN_HAS_UTIL_FUNCTIONS
#define BOTAN_HAS_WHIRLPOOL
#define BOTAN_HAS_WID_WAKE
#define BOTAN_HAS_X509_CA
#define BOTAN_HAS_X509_CERTIFICATES
#define BOTAN_HAS_X509_CRL
#define BOTAN_HAS_X509_SELF_SIGNED
#define BOTAN_HAS_X509_STORE
#define BOTAN_HAS_X931_RNG
#define BOTAN_HAS_X942_PRF
#define BOTAN_HAS_XTEA
#define BOTAN_HAS_XTEA_SIMD
#define BOTAN_HAS_XTS

/*
* Local configuration options (if any) follow
*/


#endif
