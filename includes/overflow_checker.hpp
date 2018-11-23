#ifndef OVERFLOW_CHECKER_HPP
# define OVERFLOW_CHECKER_HPP

#include <cstdint>

/* ADD =======================================================================*/
bool
add_overflow_int8(
	int32_t a,
	int32_t b
);

bool
add_overflow_int16(
	int32_t a,
	int32_t b
);

bool
add_overflow_int32(
	int32_t a,
	int32_t b
);

/* SUB =======================================================================*/
bool
sub_overflow_int8(
	int32_t a,
	int32_t b
);

bool
sub_overflow_int16(
	int32_t a,
	int32_t b
);

bool
sub_overflow_int32(
	int32_t a,
	int32_t b
);

/* MUL =======================================================================*/
bool
mul_overflow_int8(
	int32_t a,
	int32_t b
);

bool
mul_overflow_int16(
	int32_t a,
	int32_t b
);

bool
mul_overflow_int32(
	int32_t a,
	int32_t b
);

#endif
