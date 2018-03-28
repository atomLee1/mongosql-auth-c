include(FindMongocCrypto)
include(FindMongocKerberos)

# Defaults.
set (MONGOC_ENABLE_CRYPTO_COMMON_CRYPTO 0)
set (MONGOC_ENABLE_CRYPTO_LIBCRYPTO 0)
set (MONGOC_ENABLE_CRYPTO_CNG 0)
set (MONGOC_DEBUG 0)
set (MONGOSQL_AUTH_ENABLE_SASL 0)
set (MONGOSQL_AUTH_ENABLE_SASL_GSSAPI 0)
set (MONGOSQL_AUTH_ENABLE_SASL_SSPI 0)
set (MONGOSQL_AUTH_DEBUG 0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
set (CMAKE_C_FLAGS "-std=c99 ${CMAKE_C_FLAGS}")

set (PLUGIN_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongosql-auth-plugin.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongosql-auth.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongosql-auth-conversation.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/bson-md5.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-misc.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-b64.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-crypto-cng.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-crypto-common-crypto.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-crypto-openssl.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-crypto.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-memcmp.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-rand-cng.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-rand-common-crypto.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-rand-openssl.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-scram.c
)

IF(WIN32)
    set(PLUGIN_SOURCE_FILES ${PLUGIN_SOURCE_FILES} ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongosql-auth-sspi.c)
ELSE()
    set(PLUGIN_SOURCE_FILES ${PLUGIN_SOURCE_FILES} ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongosql-auth-gssapi.c)
ENDIF()

configure_file (
  "${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-config.h.in"
  "${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-config.h"
)

configure_file (
  "${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongosql-auth-config.h.in"
  "${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongosql-auth-config.h"
)

set (MONGOC_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/bson-md5.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-misc.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-b64.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-crypto-cng.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-crypto-common-crypto.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-crypto-openssl.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-crypto.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-memcmp.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-rand-cng.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-rand-common-crypto.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-rand-openssl.c
    ${PROJECT_SOURCE_DIR}/plugin/auth/mongosql-auth/mongoc/mongoc-scram.c
)

add_library(mongoc STATIC ${MONGOC_SOURCE_FILES})
target_link_libraries(mongoc ${MONGOC_CRYPTO_LIBS})

IF(UNIX)
  target_compile_options(mongoc PUBLIC "$<1:-fPIC>")
ENDIF()

MYSQL_ADD_PLUGIN(mongosql_auth ${PLUGIN_SOURCE_FILES} LINK_LIBRARIES ${MONGOC_CRYPTO_LIBS} ${MONGOC_KRB_LIBS} MODULE_ONLY TEST_ONLY)

