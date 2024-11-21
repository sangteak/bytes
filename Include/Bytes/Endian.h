#ifndef BYTES_ENDIAN_H_
#define BYTES_ENDIAN_H_

#include <type_traits>
#include <boost/endian/conversion.hpp>

namespace bytes {
enum class EndianKind {
	None,
	Big,
	Little
};

template <typename T, EndianKind endian>
T to_endian(T value) {
	if constexpr (endian == EndianKind::Big) {
		return boost::endian::native_to_big(value);
	}
	else if constexpr (endian == EndianKind::Little) {
		return boost::endian::native_to_little(value);
	}
	return value;
}

template <typename T, EndianKind endian>
T from_endian(T value) {
	if constexpr (endian == EndianKind::Big) {
		return boost::endian::big_to_native(value);
	}
	else if constexpr (endian == EndianKind::Little) {
		return boost::endian::little_to_native(value);
	}
	return value;
}
} // namespace bytes

#endif