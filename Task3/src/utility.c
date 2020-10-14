#include "utility.h"

static uint8_t first_call = 1;

const char *state_table[] = {"STACK_OK", "BAD_CAPACITY", "BAD_SIZE", "BAD_DATA", "BAD_STRUCT_TOP_PROTECTOR", "BAD_STRUCT_BOTTOM_PROTECTOR", 
                            "BAD_DATA_TOP_PROTECTOR", "BAD_DATA_BOTTOM_PROTECTOR", "SIZE_GREATER_CAPACITY", "WRONG_STRUCT_HASH", "WRONG_DATA_HASH"};


const DATA_PROTECTOR_TYPE DATA_PROTECTOR_VALUE  = 0x0DEADBEEFBADF00D;


HASH_TYPE crc(uint8_t *data, uint32_t bytes_num) {
    //TODO one create of table
	if (bytes_num == 0) {
		return 0;
	}
	static uint32_t crc_table[256];
	uint32_t crc;
	if (first_call) {
		for (int i = 0; i < 256; i++)
		{
			crc = i;
			for (int j = 0; j < 8; j++) {
				crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
        	}
			crc_table[i] = crc;
		}
		first_call = 0;
	}
	crc = 0xFFFFFFFFu;
	while (bytes_num--) {
	    crc = crc_table[(crc ^ *data++) & 0xFF] ^ (crc >> 8);
    }
	return ~crc;
}