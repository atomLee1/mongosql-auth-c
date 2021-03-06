/*
 * Copyright 2014 MongoDB, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef MONGOC_SCRAM_H
#define MONGOC_SCRAM_H

#include "mongoc-misc.h"
#include "mongoc-crypto-private.h"

#define MONGOC_SCRAM_HASH_SIZE 20

typedef struct _mongoc_scram_t {
   my_bool done;
   int step;
   char *user;
   char *pass;
   uint8_t salted_password[MONGOC_SCRAM_HASH_SIZE];
   char encoded_nonce[48];
   int32_t encoded_nonce_len;
   uint8_t *auth_message;
   uint32_t auth_messagemax;
   uint32_t auth_messagelen;
   mongoc_crypto_t crypto;
} mongoc_scram_t;

void
_mongoc_scram_startup ();

void
_mongoc_scram_init (mongoc_scram_t *scram);

void
_mongoc_scram_set_pass (mongoc_scram_t *scram, const char *pass);

void
_mongoc_scram_set_user (mongoc_scram_t *scram, const char *user);
void
_mongoc_scram_destroy (mongoc_scram_t *scram);

my_bool
_mongoc_scram_step (mongoc_scram_t *scram,
                    const uint8_t *inbuf,
                    uint32_t inbuflen,
                    uint8_t *outbuf,
                    uint32_t outbufmax,
                    uint32_t *outbuflen,
                    bson_error_t *error);

#endif /* MONGOC_SCRAM_H */
