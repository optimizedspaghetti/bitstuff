#include <stdio.h>
#include <limits.h>
#include <string.h>

/* --- PRINTF_BYTE_TO_BINARY macro's --- */
/* from stackoverflow "Is there a printf converter to print in binary format?" */
#define PRINTF_BINARY_PATTERN_INT8 "%c%c%c%c%c%c%c%c"
#define PRINTF_BYTE_TO_BINARY_INT8(i)    \
    (((i) & 0x80ll) ? '1' : '0'), \
    (((i) & 0x40ll) ? '1' : '0'), \
    (((i) & 0x20ll) ? '1' : '0'), \
    (((i) & 0x10ll) ? '1' : '0'), \
    (((i) & 0x08ll) ? '1' : '0'), \
    (((i) & 0x04ll) ? '1' : '0'), \
    (((i) & 0x02ll) ? '1' : '0'), \
    (((i) & 0x01ll) ? '1' : '0')

#define PRINTF_BINARY_PATTERN_INT16 \
    PRINTF_BINARY_PATTERN_INT8              PRINTF_BINARY_PATTERN_INT8
#define PRINTF_BYTE_TO_BINARY_INT16(i) \
    PRINTF_BYTE_TO_BINARY_INT8((i) >> 8),   PRINTF_BYTE_TO_BINARY_INT8(i)
#define PRINTF_BINARY_PATTERN_INT32 \
    PRINTF_BINARY_PATTERN_INT16             PRINTF_BINARY_PATTERN_INT16
#define PRINTF_BYTE_TO_BINARY_INT32(i) \
    PRINTF_BYTE_TO_BINARY_INT16((i) >> 16), PRINTF_BYTE_TO_BINARY_INT16(i)
#define PRINTF_BINARY_PATTERN_INT64    \
    PRINTF_BINARY_PATTERN_INT32             PRINTF_BINARY_PATTERN_INT32
#define PRINTF_BYTE_TO_BINARY_INT64(i) \
    PRINTF_BYTE_TO_BINARY_INT32((i) >> 32), PRINTF_BYTE_TO_BINARY_INT32(i)
/* --- end macros --- */

//create empty string, concatenate bit filled to string
//floats can't be bit-shifted, so this doesn't work
/*
const char* float_bits(float a, const char* s) {
	s = "";

	for (int i = 0; i < 31; i++) {
		char ch;
		ch = (a >> 31-i) & 1;
		strncat(s, &ch, 1);
	}

	return s;
}
*/


int main() {

	union Data {
		int i;
		float f;
	} a, b, c, d, e;

	a.i = 0xdeadbeef;
	b.i = INT_MAX;
	c.i = INT_MIN;
	d.i = 0;
	e.i = 42;

	printf("a: "
			PRINTF_BINARY_PATTERN_INT32 "\n",
			PRINTF_BYTE_TO_BINARY_INT32(a.i));
	printf("b: "
			PRINTF_BINARY_PATTERN_INT32 "\n",
			PRINTF_BYTE_TO_BINARY_INT32(b.i));
	
	printf("c: "
			PRINTF_BINARY_PATTERN_INT32 "\n",
			PRINTF_BYTE_TO_BINARY_INT32(c.i));
	
	printf("d: "
			PRINTF_BINARY_PATTERN_INT32 "\n",
			PRINTF_BYTE_TO_BINARY_INT32(d.i));

	printf("e: "
			PRINTF_BINARY_PATTERN_INT32 "\n",
			PRINTF_BYTE_TO_BINARY_INT32(e.i));

	printf("signed ints:\n");
	printf("%d %d %d %d %d\n\n", a.i, b.i, c.i, d.i, e.i);

	printf("floats:\n");
	printf("%f %f %f %f %f\n\n", a.f, b.f, c.f, d.f, e.f);

	printf("ints cast as floats:\n");
	printf("%f %f %f %f %f\n\n", (float) a.i, (float) b.i, (float) c.i, (float) d.i, (float) e.i);

	printf("ints as floats, no cast:\n");
	printf("%f %f %f %f %f\n\n", a.i, b.i, c.i, d.i, e.i);

	printf("floats cast as ints:\n");
	printf("%d %d %d %d %d\n\n", (int) a.f, (int) b.f, (int) c.f, (int) d.f, (int) e.f);

	printf("floats as ints, no cast:\n");
	printf("%d %d %d %d %d\n\n", a.f, b.f, c.f, d.f, e.f);

	/* ---arithmetic and logic checks--- */
	printf("arithmetic: ");
	printf("%d %d %d %d %d\n\n", b.i + b.i, b.i + 1, c.i + b.i, c.i - c.i, c.i - 1);
	printf("bitwise: ");
	printf("%d %d %d %d %d\n\n", a.i & b.i, a.i & c.i, b.i ^ c.i, a.i | d.i, b.i & e.i);
	printf("logical: ");
	printf("%d %d %d %d %d\n\n", a.i && b.i, a.i && c.i, b.i || c.i, a.i || d.i, b.i && e.i);


	return 0;
}
