#include "utility.h"



const char *state_table[] = {"STACK_OK", "BAD_CAPACITY", "BAD_SIZE", "BAD_DATA", "BAD_STRUCT_TOP_PROTECTOR", "BAD_STRUCT_BOTTOM_PROTECTOR", 
                            "BAD_DATA_TOP_PROTECTOR", "BAD_DATA_BOTTOM_PROTECTOR", "SIZE_GREATER_CAPACITY", "WRONG_STACK_HASH", "WRONG_DATA_HASH"};


const DATA_PROTECTOR_TYPE DATA_PROTECTOR_VALUE  = 0x0DEADBEEFBADF00D;


// HASH_TYPE crc(void *data, int bytes_num) {
//     uint8_t *data_begin = (uint8_t *)data + sizeof(DATA_PROTECTOR_TYPE);
//     uint8_t *data_end =   (uint8_t *)data + bytes_num - sizeof(DATA_PROTECTOR_TYPE);
//     HASH_TYPE hash_sum = 0;
//     return hash_sum;
// }