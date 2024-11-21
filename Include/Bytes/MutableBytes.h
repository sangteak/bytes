/// @file MutableBytes.h
/// @author stkwon (sangtakeg@gmail.com)
/// @brief 가변(Mutable) 바이트 배열을 나타냅니다.
/// @version 0.1
/// @date 2024-11-21
///
/// @copyright Copyright (c) 2024
///
#ifndef BYTES_MUTABLEBYTES_H_
#define BYTES_MUTABLEBYTES_H_

#include <vector>
#include <type_traits>
#include <boost/endian/conversion.hpp>
#include <fmt/format.h>
#include "BytesView.h"

namespace bytes {
/// @brief 가변(Mutable) 바이트 배열을 나타냅니다.
///
/// MutableBytes는 네트워크 송/수신에 필요한 데이터를 안정적이고, 효율적으로 만들 수 있도록 하기 위한 기능을 포함합니다.
///
/// [특징]
/// - 안전성
/// 내부 메모리를 완벽하게 캡슐화하였으며, 만일 데이터를 읽어야 할 경우 얕은 복사를 제공하는 BytesView가 제공됩니다.. 이를 통해
/// 메모리에 데이터를 쓰거나, 데이터를 읽을 경우 안전한 메모리 접근이 가능합니다.
///
/// - 효율성
/// 읽기 위치와 쓰기 위치를 관리하도록 하였습니다. 데이터를 읽더라도 데이터를 이동하지 않고, 읽기 위치를 조정하여 비용을 절약하였으며,
/// 쓰기 시 메모리가 부족할 경우 Compact 기능을 호출하여 단편화된 블록을 제거하도록 하였습니다. 이를 통해 메모리 블록을 효율적으로 운영합니다.
template <EndianKind kind>
class MutableBytes {
public:
	MutableBytes() = default;
	~MutableBytes() = default;

	/// @brief 버퍼의 용량을 설정합니다.
	/// @param capacity
	MutableBytes(const size_t capacity) {
		buf_.reserve(capacity);
	}

	/// @brief 현재 버퍼의 용량을 반환합니다.
	size_t Capacity() {
		return buf_.capacity();
	}

	/// @brief 버퍼가 비어있는지 확인합니다.
	bool IsEmpty() {
		return Length() == 0;
	}

	/// @brief 데이터 길이를 반환합니다.
	size_t Length() {
		return rear_pos_ - front_pos_;
	}

	/// @brief 주어진 인수를 Big Endian으로 변환 후 버퍼에 씁니다.
	void PutI8(const int8_t& value) {
		put(value);
	}

	/// @brief 주어진 인수를 Big Endian으로 변환 후 버퍼에 씁니다.
	void PutU8(const uint8_t& value) {
		put(value);
	}

	/// @brief 주어진 인수를 Big Endian으로 변환 후 버퍼에 씁니다.
	void PutI16(const int16_t& value) {
		put(value);
	}

	/// @brief 주어진 인수를 Big Endian으로 변환 후 버퍼에 씁니다.
	void PutU16(const uint16_t& value) {
		put(value);
	}

	/// @brief 주어진 인수를 Big Endian으로 변환 후 버퍼에 씁니다.
	void PutI32(const int32_t& value) {
		put(value);
	}

	/// @brief 주어진 인수를 Big Endian으로 변환 후 버퍼에 씁니다.
	void PutU32(const uint32_t& value) {
		put(value);
	}

	/// @brief 주어진 인수를 Big Endian으로 변환 후 버퍼에 씁니다.
	void PutI64(const int64_t& value) {
		put(value);
	}

	/// @brief 주어진 인수를 Big Endian으로 변환 후 버퍼에 씁니다.
	void PutU64(const uint64_t& value) {
		put(value);
	}

	/// @brief 주어진 인수를 Big Endian으로 변환 후 버퍼에 씁니다.
	void PutFloat(const float& value) {
		uint32_t convert_value;
		memcpy(&convert_value, &value, sizeof(value));

		put(convert_value);
	}

	/// @brief 주어진 인수를 Big Endian으로 변환 후 버퍼에 씁니다.
	void PutDouble(const double& value) {
		uint64_t convert_value;
		memcpy(&convert_value, &value, sizeof(value));

		put(convert_value);
	}

	/// @brief 주어진 인수를 버퍼에 씁니다.
	void PutBytes(const uint8_t* data, size_t length) {
		Compact(length);

		buf_.insert(buf_.end(), data, data + length);

		rear_pos_ += length;
	}

	/// @brief 현재 읽기 위치를 기준으로 count 만큼 이동합니다.
	/// @throw 범위를 벗어난 경우 std::runtime_error를 throw 합니다.
	void Advance(size_t count) {
		const size_t len = Length();
		if (len < count) {
			throw std::runtime_error(fmt::format("the number of requested bytes ({}) exceeds the number of remaning bytes ({})", len, count));
		}

		front_pos_ += count;
	}

	/// @brief 읽기 데이터를 BytesView에 담아 반환합니다.
	BytesView<kind> AsRef() {
		return BytesView<kind>(&buf_[front_pos_], Length());
	}

private:
	template <typename T>
	typename std::enable_if_t<std::is_integral_v<T>> put(const T& value) {
		// 필요할 경우 단편화를 제거하여 공간을 확보한다.
		Compact(sizeof(value));

		auto endian_value = to_endian<T, kind>(value);
		// auto endian_value = boost::endian::native_to_big(value);
		uint8_t* pointer = reinterpret_cast<uint8_t*>(&endian_value);
		constexpr size_t count = sizeof(value);
		buf_.insert(buf_.end(), pointer, pointer + count);

		rear_pos_ += count;
	}

	void Compact(size_t count) {
		size_t len = Length();
		if (len <= 0) {
			front_pos_ = 0;
			rear_pos_ = 0;
			buf_.resize(0);
		}
		else {
			// 쓰기 공간이 충분한지 확인한다.
			size_t writable = buf_.capacity() - rear_pos_;
			if (writable >= count) {
				return;
			}

			// 쓰기 공간이 부족하다면 단편화를 제거하는 작업을 수행한다.
			memmove(buf_.data(), &buf_[front_pos_], len);
			buf_.resize(len);
			front_pos_ = 0;
			rear_pos_ = len;
		}
	}

	std::vector<uint8_t> buf_;
	size_t front_pos_ = 0;
	size_t rear_pos_ = 0;
};
} // namespace bytes

#endif // end BYTES_MUTABLEBYTES_H_