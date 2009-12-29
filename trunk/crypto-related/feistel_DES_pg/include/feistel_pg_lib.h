#include <stdint.h>

#ifndef _H_FEISTEL_PG_LIB_
#define _H_FEISTEL_PG_LIB_

#define INITIAL_VECTOR "PIRchain"
#define PERMKEYLENGTH 8

#define AINC 2
#define BINC 13

uint32_t permute(uint32_t val, uint32_t max, uint32_t a, uint32_t b,
                 uint8_t *key[], uint32_t round);
uint32_t revpermute(uint32_t val, uint32_t max, uint32_t a, uint32_t b, 
                    uint8_t *key[], uint32_t round);
void discomp_max(uint32_t max, uint32_t *a, uint32_t *b);

#endif /* _H_FEISTEL_PG_LIB_ */
