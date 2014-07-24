#if defined(DOUBLE)

#define REAL real8
#define INTEGER int8
#define COMPILED_TYPE (double_precision)
#define WORD_SIZE 8

#elif defined(SINGLE)

#define REAL real4
#define INTEGER int4
#define COMPILED_TYPE  (single_precision)
#define WORD_SIZE 4

#endif
