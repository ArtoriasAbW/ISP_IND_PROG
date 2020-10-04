#include "templates.h"
#include "defines.h"

#ifdef TYPE 
#undef TYPE 
#endif

#define TYPE int
#include "stack.c"
#undef TYPE

#define TYPE double
#include "stack.c"
#undef TYPE

#define TYPE short
#include "stack.c"
#undef TYPE

#define TYPE char
#include "stack.c"