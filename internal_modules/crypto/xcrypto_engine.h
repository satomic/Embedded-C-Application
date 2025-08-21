#ifndef XCRYPTO_ENGINE_H
#define XCRYPTO_ENGINE_H

#include <stdint.h>

typedef enum {
    XCRYPTO_AES_128 = 0,
    XCRYPTO_AES_192 = 1,
    XCRYPTO_AES_256 = 2
} xcrypto_aes_key_size_t;

typedef enum {
    XCRYPTO_MODE_ECB = 0,
    XCRYPTO_MODE_CBC = 1,
    XCRYPTO_MODE_CTR = 2,
    XCRYPTO_MODE_GCM = 3
} xcrypto_cipher_mode_t;

typedef enum {
    XCRYPTO_HASH_SHA1 = 0,
    XCRYPTO_HASH_SHA256 = 1,
    XCRYPTO_HASH_SHA384 = 2,
    XCRYPTO_HASH_SHA512 = 3,
    XCRYPTO_HASH_MD5 = 4
} xcrypto_hash_type_t;

typedef enum {
    XCRYPTO_STATUS_OK = 0,
    XCRYPTO_STATUS_ERROR = 1,
    XCRYPTO_STATUS_INVALID_PARAM = 2,
    XCRYPTO_STATUS_BUSY = 3,
    XCRYPTO_STATUS_KEY_ERROR = 4,
    XCRYPTO_STATUS_AUTH_FAIL = 5
} xcrypto_status_t;

typedef struct {
    xcrypto_aes_key_size_t key_size;
    xcrypto_cipher_mode_t mode;
    uint8_t* key;
    uint8_t* iv;
    uint8_t enable_hardware_acceleration;
} xcrypto_aes_config_t;

typedef struct {
    xcrypto_hash_type_t hash_type;
    uint8_t enable_hmac;
    uint8_t* hmac_key;
    uint32_t hmac_key_length;
    uint8_t enable_hardware_acceleration;
} xcrypto_hash_config_t;

typedef struct {
    uint32_t encrypt_operations;
    uint32_t decrypt_operations;
    uint32_t hash_operations;
    uint32_t key_generations;
    uint64_t bytes_processed;
    uint32_t hardware_accelerated_ops;
    uint32_t software_ops;
    uint32_t error_count;
} xcrypto_stats_t;

typedef void* xcrypto_context_t;

int xcrypto_init(void);
int xcrypto_deinit(void);
xcrypto_context_t xcrypto_aes_create_context(const xcrypto_aes_config_t* config);
xcrypto_status_t xcrypto_aes_destroy_context(xcrypto_context_t context);
xcrypto_status_t xcrypto_aes_encrypt(xcrypto_context_t context, const uint8_t* plaintext, 
                                     uint32_t plaintext_len, uint8_t* ciphertext, uint32_t* ciphertext_len);
xcrypto_status_t xcrypto_aes_decrypt(xcrypto_context_t context, const uint8_t* ciphertext, 
                                     uint32_t ciphertext_len, uint8_t* plaintext, uint32_t* plaintext_len);
xcrypto_status_t xcrypto_aes_gcm_encrypt(xcrypto_context_t context, const uint8_t* plaintext, uint32_t plaintext_len,
                                         const uint8_t* aad, uint32_t aad_len, uint8_t* ciphertext, 
                                         uint32_t* ciphertext_len, uint8_t* tag, uint32_t tag_len);
xcrypto_status_t xcrypto_aes_gcm_decrypt(xcrypto_context_t context, const uint8_t* ciphertext, uint32_t ciphertext_len,
                                         const uint8_t* aad, uint32_t aad_len, const uint8_t* tag, uint32_t tag_len,
                                         uint8_t* plaintext, uint32_t* plaintext_len);
xcrypto_context_t xcrypto_hash_create_context(const xcrypto_hash_config_t* config);
xcrypto_status_t xcrypto_hash_destroy_context(xcrypto_context_t context);
xcrypto_status_t xcrypto_hash_update(xcrypto_context_t context, const uint8_t* data, uint32_t data_len);
xcrypto_status_t xcrypto_hash_finalize(xcrypto_context_t context, uint8_t* hash, uint32_t* hash_len);
xcrypto_status_t xcrypto_hash_compute(xcrypto_hash_type_t type, const uint8_t* data, uint32_t data_len, 
                                      uint8_t* hash, uint32_t* hash_len);
xcrypto_status_t xcrypto_generate_random(uint8_t* buffer, uint32_t length);
xcrypto_status_t xcrypto_generate_key(uint8_t* key, uint32_t key_length);
xcrypto_status_t xcrypto_derive_key(const uint8_t* password, uint32_t password_len, const uint8_t* salt, 
                                    uint32_t salt_len, uint32_t iterations, uint8_t* derived_key, uint32_t key_len);
int xcrypto_get_stats(xcrypto_stats_t* stats);
int xcrypto_reset_stats(void);
uint8_t xcrypto_is_hardware_available(void);

#endif // XCRYPTO_ENGINE_H