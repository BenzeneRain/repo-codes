#ifndef _H_TINYPRP_
#define _H_TINYPRP_

#define KEYSIZE_16  8 /* Count in 16 bits */
#define RCON_COUNT_16 10 /* See the paper */
#define KEYSIZE_32  4 /* Count in 32 bits */
#define RCON_COUNT_32 6 /* See the paper */

void encrypt_16(uint16_t  *expandedKey, uint8_t a[2]);
void decrypt_16(uint16_t  *expandedKey, uint8_t a[2]);
inline void ExpandKey_16(uint16_t key[KEYSIZE_16], uint16_t *expandedKey);

void encrypt_32(uint32_t  *expandedKey, uint8_t a[4]);
void decrypt_32(uint32_t  *expandedKey, uint8_t a[4]);
inline void ExpandKey_32(uint32_t key[KEYSIZE_32], uint32_t *expandedKey);
#endif /* _H_TINYPRP_ */
