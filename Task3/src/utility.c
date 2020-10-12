#include "utility.h"


const DATA_PROTECTOR_TYPE DATA_PROTECTOR_VALUE  = 0x0DEADBEEFBADF00D;


// HASH_TYPE crc(void *data, int bytes_num) {
//     uint8_t *data_begin = (uint8_t *)data + sizeof(DATA_PROTECTOR_TYPE);
//     uint8_t *data_end =   (uint8_t *)data + bytes_num - sizeof(DATA_PROTECTOR_TYPE);
//     HASH_TYPE hash_sum = 0;
//     return hash_sum;
// }