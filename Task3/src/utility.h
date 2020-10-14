
#ifndef UTILITY_H_
#define UTILITY_H_

#include<stdint.h>


extern const char *state_table[];

enum STACK_STATE 
{
    STACK_OK,
    BAD_CAPACITY,
    BAD_SIZE,
    BAD_DATA,
    BAD_STRUCT_TOP_PROTECTOR,
    BAD_STRUCT_BOTTOM_PROTECTOR,
    BAD_DATA_TOP_PROTECTOR,
    BAD_DATA_BOTTOM_PROTECTOR,
    SIZE_GREATER_CAPACITY,
    WRONG_STRUCT_HASH,
    WRONG_DATA_HASH

};

typedef uint64_t DATA_PROTECTOR_TYPE;

typedef uint32_t HASH_TYPE;

extern const DATA_PROTECTOR_TYPE DATA_PROTECTOR_VALUE;


HASH_TYPE crc(uint8_t *data, uint32_t bytes_num);

#endif