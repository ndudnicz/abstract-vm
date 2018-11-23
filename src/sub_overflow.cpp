#include <cstdint>

bool
sub_overflow_int8(
	int32_t a,
	int32_t b
) {
	int8_t	result;
	return __builtin_sub_overflow(a, b, &result);
}

bool
sub_overflow_int16(
	int32_t a,
	int32_t b
) {
	int16_t	result;
	return __builtin_sub_overflow(a, b, &result);
}

bool
sub_overflow_int32(
	int32_t a,
	int32_t b
) {
	int32_t	result;
	return __builtin_sub_overflow(a, b, &result);
}
