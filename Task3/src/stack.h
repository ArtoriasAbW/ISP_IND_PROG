/** @file */

#include <sys/types.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "templates.h"
#include "utility.h"
#ifdef TYPE


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


/*!
 * Checks stack status
 * @param [in] stack 
 * @return not 0 if stack is OK, else 0
 */
int TEMPLATE(CheckStack, TYPE)(TEMPLATE(Stack, TYPE) *stack);


/*!
 * Fills stack fields and allocates memory for data
 * @param [in, out] stack
 * @param [in] capacity allocated memory size
 */
void TEMPLATE(StackConstructor, TYPE)(TEMPLATE(Stack, TYPE) *stack, ssize_t capacity);


/*!
 * Frees stack memory and corrupt fields
 * @param [in] stack
 */
void TEMPLATE(StackDestructor, TYPE)(TEMPLATE(Stack, TYPE) *stack);
/*!
 * Create copy of old_stack
 * @param [in] old_stack
 * @return new stack which is a copy of old_stack
 */
TEMPLATE(Stack, TYPE) TEMPLATE(StackCopyConstructor, TYPE)(TEMPLATE(Stack, TYPE) *old_stack);

/*!
 * Adds an item to the stack
 * @param [in, out] stack stack to which the item will be added
 * @param [in] value value of the element to be added
 */
void TEMPLATE(Push, TYPE)(TEMPLATE(Stack, TYPE) *stack, TYPE value);

/*!
 * Retrieves the last added item
 * @param [in, out] stack stack from which to retrieve
 * @return value of the retrieved item
 */
TYPE TEMPLATE(Pop, TYPE)(TEMPLATE(Stack, TYPE) *stack);

/*!
 * Shows value of the last added item
 * @param [in, out] stack stack last element of which will be shown
 * @return value value of the last added item
 */
TYPE TEMPLATE(ShowLast, TYPE)(TEMPLATE(Stack, TYPE) *stack);
#endif