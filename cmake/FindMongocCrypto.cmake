IF(APPLE)
    MESSAGE(STATUS "Using Common Crypto for mongoc crypto")
    set (MONGOC_ENABLE_CRYPTO_COMMON_CRYPTO 1)
    set (MONGOC_CRYPTO_LIBS "-framework CoreFoundation -framework Security")
ELSEIF(WIN32)
    MESSAGE(STATUS "Using CNG for mongoc crypto")
    set (MONGOC_ENABLE_CRYPTO_CNG 1)
    set(MONGOC_CRYPTO_LIBS crypt32.lib Bcrypt.lib)
ELSE()
    MESSAGE(STATUS "Using OpenSSL for mongoc crypto")
    set (MONGOC_ENABLE_CRYPTO_LIBCRYPTO 1)
    include(FindOpenSSL)
    if (OPENSSL_FOUND)
        set(MONGOC_CRYPTO_LIBS ${OPENSSL_LIBRARIES})
        include_directories(${OPENSSL_INCLUDE_DIR})
        MESSAGE(STATUS "Found OpenSSL libraries")
        MESSAGE(STATUS "OpenSSL include path: ${OPENSSL_INCLUDE_DIR}")
    else()
        MESSAGE(FATAL_ERROR "Could not find OpenSSL libraries")
    endif()
ENDIF()

MESSAGE(STATUS "using mongoc crypto library: ${MONGOC_CRYPTO_LIBS}")