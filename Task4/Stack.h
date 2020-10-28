/** @file */

#include <sys/types.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#ifdef TYPE

#ifndef __RANDVALUE1
#define __RANDVALUE1

#define CAT(X,Y) X##_##Y
#define TEMPLATE(X,Y) CAT(X,Y)


#define PRINT(TYPE) PrintValue_##TYPE 

#define PRINTTYPE(TYPE) PrintTypename_##TYPE


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

const DATA_PROTECTOR_TYPE DATA_PROTECTOR_VALUE  = 0x0DEADBEEFBADF00D;

typedef uint32_t HASH_TYPE;


static uint8_t first_call = 1;

const char *state_table[] = {"STACK_OK", "BAD_CAPACITY", "BAD_SIZE", "BAD_DATA", "BAD_STRUCT_TOP_PROTECTOR", "BAD_STRUCT_BOTTOM_PROTECTOR", 
                            "BAD_DATA_TOP_PROTECTOR", "BAD_DATA_BOTTOM_PROTECTOR", "SIZE_GREATER_CAPACITY", "WRONG_STRUCT_HASH", "WRONG_DATA_HASH"};


HASH_TYPE crc(uint8_t *data, uint32_t bytes_num) {
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



void PrintValue_int(int value) {
    fprintf(stderr, "%d\n", value);
}

void PrintValue_char(char value) {
    fprintf(stderr, "%c\n", value);
}

void PrintValue_short(short value) {
    fprintf(stderr, "%hu\n", value);
}

void PrintValue_double(double value) {
    fprintf(stderr, "%lf\n", value);
}


void PrintValue_uint64_t(uint64_t value) {
    fprintf(stderr, "%lu\n", value);
}


void PrintValue_int64_t(int64_t value) {
    fprintf(stderr, "%ld\n", value);
}


void PrintValue_uint32_t(uint32_t value) {
    fprintf(stderr, "%u\n", value);
}

void PrintTypename_double() {
    fprintf(stderr, "stack dump [TYPE = double]");
}

void PrintTypename_int() {
    fprintf(stderr, "stack dump [TYPE = int]");
}

void PrintTypename_short() {
    fprintf(stderr, "stack dump [TYPE = short]");
}

void PrintTypename_char() {
    fprintf(stderr, "stack dump [TYPE = char]");
}


void PrintTypename_uint64_t() {
    fprintf(stderr, "stack dump [TYPE = uint64_t]");
}


void PrintTypename_int64_t() {
    fprintf(stderr, "stack dump [TYPE = int64_t]");
}

void PrintTypename_uint32_t() {
    fprintf(stderr, "stack dump [TYPE = uint32_t]");
}

/*!
* Dumps the state of the stack on stderr
*/

#ifdef STACK_CHECK
#define STACKDUMP(stack, TYPE, state) \
{\
    PRINTTYPE(TYPE)();\
    if (state != STACK_OK) {\
        fprintf(stderr, "(not ok) ERROR:%s", state_table[state]);\
        if (stack.data != NULL) {\
            fprintf(stderr, "[%p]", stack.data);\
        }\
    } else {\
        fprintf(stderr, "(ok)[%p]", stack.data);\
    }\
    fprintf(stderr, "[%s:%d in func %s] {\n", __FILE__, __LINE__, __func__);\
    fprintf(stderr, "    size = %ld\n    capacity = %ld\n", stack.size, stack.capacity);\
    if (stack.data != NULL) {\
        fprintf(stderr, "    data[%p] {\n", stack.data);\
        for (ssize_t i = 0; i < stack.size; ++i) {\
            fprintf(stderr, "        *[%ld] = ", i);\
            if (stack.data + i != NULL) {\
                PRINT(TYPE)(stack.data[i]); \
            } else {\
                fprintf(stderr, "ERROR\n");\
            }\
        }\
        fprintf(stderr, "    }\n}\n");\
    }\
}
#endif


#endif

/*!
* Stack for elements that are of type TYPE 
*/
typedef struct TEMPLATE(Stack, TYPE) {
#ifdef STACK_CANARY
    DATA_PROTECTOR_TYPE top_canary;
#endif
#ifdef STACK_HASH
    HASH_TYPE struct_hash;
    HASH_TYPE data_hash;
#endif
    ssize_t size;
    ssize_t capacity;
    TYPE *data;
#ifdef STACK_CANARY
    DATA_PROTECTOR_TYPE bottom_canary;
#endif
} TEMPLATE(Stack, TYPE);



#ifdef STACK_CHECK
/*!
 * Checks stack status
 * @param [in] stack 
 * @return not 0 if stack is OK, else 0
 */
int TEMPLATE(CheckStack, TYPE)(TEMPLATE(Stack, TYPE) *stack) {
    if (stack->capacity < 0) {
        return BAD_CAPACITY;
    }
    if (stack->size < 0) {
        return BAD_SIZE;
    }
    if (stack->data == NULL) {
        return BAD_DATA;
    }
    if (stack->size > stack->capacity) {
        return SIZE_GREATER_CAPACITY;
    }
#ifdef STACK_CANARY
    if (stack->top_canary != DATA_PROTECTOR_VALUE) {
        return BAD_STRUCT_TOP_PROTECTOR;
    }
    if (stack->bottom_canary != DATA_PROTECTOR_VALUE) {
        return BAD_STRUCT_BOTTOM_PROTECTOR;
    }
    if (*((DATA_PROTECTOR_TYPE *)stack->data - 1) != DATA_PROTECTOR_VALUE) {
        return BAD_DATA_TOP_PROTECTOR;
    }
    if (*(DATA_PROTECTOR_TYPE *)(stack->data + stack->capacity) != DATA_PROTECTOR_VALUE) {
        return BAD_DATA_BOTTOM_PROTECTOR;
    
    }
#ifdef STACK_HASH
    if (stack->struct_hash != crc((uint8_t *)stack + 2 * sizeof(stack->struct_hash) + sizeof(stack->top_canary), 
                             sizeof(stack->data) + sizeof(stack->size) + sizeof(stack->capacity))) {
        return WRONG_STRUCT_HASH;
    }
    if (stack->data_hash != crc((uint8_t *)stack->data, stack->size * sizeof(*stack->data))) {
        return WRONG_DATA_HASH;
    }
#endif
#endif
    return STACK_OK;

}
#endif

/*!
 * Fills stack fields and allocates memory for data
 * @param [in, out] stack
 * @param [in] capacity allocated memory size
 */
void TEMPLATE(StackConstructor, TYPE)(TEMPLATE(Stack, TYPE) *stack, ssize_t capacity) {
    stack->capacity = capacity;
    stack->size     = 0; 
#ifdef STACK_CANARY
    void *data                         = calloc(capacity * sizeof(TYPE) + 2 * sizeof(DATA_PROTECTOR_TYPE), sizeof(uint8_t)); 
    DATA_PROTECTOR_TYPE *top_canary    = (DATA_PROTECTOR_TYPE *)data;
    DATA_PROTECTOR_TYPE *bottom_canary = (DATA_PROTECTOR_TYPE *)((uint8_t *)data + sizeof(DATA_PROTECTOR_TYPE) + capacity * sizeof(TYPE));
    *top_canary                        = DATA_PROTECTOR_VALUE;
    *bottom_canary                     = DATA_PROTECTOR_VALUE;
    stack->data                        = (TYPE *)((DATA_PROTECTOR_TYPE *)data + 1);
    stack->top_canary                  = DATA_PROTECTOR_VALUE;
    stack->botdebug tom_canary               = DATA_PROTECTOR_VALUE;
#ifdef STACK_HASH
    stack->struct_hash = crc((uint8_t *)stack + 2 * sizeof(stack->struct_hash) + sizeof(stack->top_canary), 
                             sizeof(stack->data) + sizeof(stack->size) + sizeof(stack->capacity));
    stack->data_hash = crc((uint8_t *)stack->data, stack->size * sizeof(*stack->data));

#endif   
#else
    stack->data = (TYPE *)calloc(capacity, sizeof(TYPE));
#endif                 
#ifdef STACK_CHECK
    int state;   
    if ((state = TEMPLATE(CheckStack, TYPE)(stack)) != STACK_OK) {
        TEMPLATE(Stack, TYPE) tmp = *stack;
        STACKDUMP(tmp, TYPE, state);
        assert(!"Bad stack");
        exit(-1);
    }
#endif
}

/*!
 * Frees stack memory and corrupt fields
 * @param [in] stack
 */
void TEMPLATE(StackDestructor, TYPE)(TEMPLATE(Stack, TYPE) *stack) {
#ifdef STACK_CHECK
    int state;
    if ((state = TEMPLATE(CheckStack, TYPE)(stack)) != STACK_OK) {
        TEMPLATE(Stack, TYPE) tmp = *stack;
        STACKDUMP(tmp, TYPE, state);
        assert(!"Bad stack");
        exit(-1);
    }
#endif
#ifdef STACK_CANARY
    free((DATA_PROTECTOR_TYPE *)stack->data - 1);
#else
    free(stack->data);
#endif
    stack->data     = NULL;
    stack->capacity = -1;
    stack->size     = -1;
}

/*!
 * Create copy of old_stack
 * @param [in] old_stack
 * @return new stack which is a copy of old_stack
 */
TEMPLATE(Stack, TYPE) TEMPLATE(StackCopyConstructor, TYPE)(TEMPLATE(Stack, TYPE) *old_stack) {
#ifdef STACK_CHECK
    int state;
    if ((state = TEMPLATE(CheckStack, TYPE)(old_stack)) != STACK_OK) {
        TEMPLATE(Stack, TYPE) tmp = *old_stack;
        STACKDUMP(tmp, TYPE, state);
        assert(!"Bad stack");
        exit(-1);
    }
#endif
    TEMPLATE(Stack,TYPE) new_stack;
    new_stack.capacity                 = old_stack->capacity;
    new_stack.size                     = old_stack->size;
#ifdef STACK_CANARY
    void *data                         = calloc(old_stack->capacity * sizeof(TYPE) + 2 * sizeof(DATA_PROTECTOR_TYPE), sizeof(uint8_t)); 
    DATA_PROTECTOR_TYPE *top_canary    = (DATA_PROTECTOR_TYPE *)data;
    DATA_PROTECTOR_TYPE *bottom_canary = (DATA_PROTECTOR_TYPE *)((uint8_t *)data + sizeof(DATA_PROTECTOR_TYPE) + old_stack->capacity * sizeof(TYPE));
    *top_canary                        = DATA_PROTECTOR_VALUE;
    *bottom_canary                     = DATA_PROTECTOR_VALUE;
    new_stack.data                     = (TYPE *)((DATA_PROTECTOR_TYPE *)data + 1);
    new_stack.top_canary               = old_stack->top_canary;
    new_stack.bottom_canary            = old_stack->bottom_canary;
#ifdef STACK_HASH
    new_stack.struct_hash = crc((uint8_t *)&new_stack + sizeof(new_stack.top_canary) + 2 * sizeof(new_stack.struct_hash),
                                sizeof(new_stack.data) + sizeof(new_stack.size) + sizeof(new_stack.capacity));
    new_stack.data_hash   = crc((uint8_t *)new_stack.data, sizeof(*(new_stack.data)) * new_stack.size);
#endif
#else
    new_stack.data                     = (TYPE *)calloc(old_stack->capacity, sizeof(TYPE));
#endif
#ifdef STACK_CHECK
    if ((state = TEMPLATE(CheckStack, TYPE)(&new_stack)) != STACK_OK) {
        STACKDUMP(new_stack, TYPE, state);
        assert(!"Bad stack");
        exit(-1);
    }
#endif
    return new_stack;
}

/*!
 * Adds an item to the stack
 * @param [in, out] stack stack to which the item will be added
 * @param [in] value value of the element to be added
 */
void TEMPLATE(Push, TYPE)(TEMPLATE(Stack, TYPE) *stack, TYPE value) {
#ifdef STACK_CHECK
    int state;
    if ((state = TEMPLATE(CheckStack, TYPE)(stack)) != STACK_OK) {
        TEMPLATE(Stack, TYPE) tmp = *stack;
        STACKDUMP(tmp, TYPE, state);
        assert(!"Bad stack");
        exit(-1);
    }
#endif
    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
#ifdef STACK_CANARY
        void *data = realloc((DATA_PROTECTOR_TYPE *)stack->data - 1, stack->capacity * sizeof(TYPE) + 2 * sizeof(DATA_PROTECTOR_TYPE));
#else
        TYPE *data = (TYPE *)realloc(stack->data, stack->capacity * sizeof(*stack->data));
#endif
        if (!data) {
            printf("Cannot realloc new space for stack\n");
            assert(!"Reallocation error");
            exit(-1);
        } else {
#ifdef STACK_CANARY
            DATA_PROTECTOR_TYPE *top_canary    = (DATA_PROTECTOR_TYPE *)data;
            DATA_PROTECTOR_TYPE *bottom_canary = (DATA_PROTECTOR_TYPE *)((uint8_t *)data + sizeof(DATA_PROTECTOR_TYPE) + stack->capacity * sizeof(TYPE));
            *top_canary                        = DATA_PROTECTOR_VALUE;
            *bottom_canary                     = DATA_PROTECTOR_VALUE;
            stack->data                        = (TYPE *)((DATA_PROTECTOR_TYPE *)data + 1);
#else
            stack->data = data;
#endif
        }
    }
    stack->data[stack->size++] = value;
#ifdef STACK_HASH
    stack->struct_hash = crc((uint8_t *)stack + 2 * sizeof(stack->struct_hash) + sizeof(stack->top_canary), 
                             sizeof(stack->data) + sizeof(stack->size) + sizeof(stack->capacity));
    stack->data_hash = crc((uint8_t *)stack->data, stack->size * sizeof(*stack->data));
#endif
}

/*!
 * Shows value of the last added item
 * @param [in, out] stack stack last element of which will be shown
 * @return value value of the last added item
 */
TYPE TEMPLATE(ShowLast, TYPE)(TEMPLATE(Stack, TYPE) *stack) {
#ifdef STACK_CHECK
    int state;
    if ((state = TEMPLATE(CheckStack, TYPE)(stack)) != STACK_OK) {
        TEMPLATE(Stack, TYPE) tmp = *stack;
        STACKDUMP(tmp, TYPE, state);
        assert(!"Bad stack");
        exit(-1);
    }
#endif
    if (stack->size < 1) {
        assert(!"Stack is empty");
        printf("Stack is empty. Nothing to show(pop).\n"); //for release
        return (TYPE)1;
    }
    return stack->data[stack->size - 1];
}

/*!
 * Retrieves the last added item
 * @param [in, out] stack stack from which to retrieve
 * @return value of the retrieved item
 */
TYPE TEMPLATE(Pop, TYPE)(TEMPLATE(Stack, TYPE) *stack) {
    TYPE value = TEMPLATE(ShowLast, TYPE)(stack);
    stack->size--;
#ifdef STACK_HASH
    stack->struct_hash = crc((uint8_t *)stack + 2 * sizeof(stack->struct_hash) + sizeof(stack->top_canary), 
                             sizeof(stack->data) + sizeof(stack->size) + sizeof(stack->capacity));
    stack->data_hash = crc((uint8_t *)stack->data, stack->size * sizeof(*stack->data));
#endif
    return value;
}

#endif
