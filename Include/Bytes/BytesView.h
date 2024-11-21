/// @file BytesView.h
/// @author stkwon (sangtakeg@gmail.com)
/// @brief 불변(immutable) 바이트 배열을 나타냅니다.
/// @version 0.1
/// @date 2024-11-21
///
/// @copyright Copyright (c) 2024
///
#ifndef BYTES_BYTES_H_
#define BYTES_BYTES_H_

#include <vector>
#include <array>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <boost/endian/conversion.hpp>
#include <fmt/format.h>

namespace bytes {
/// @brief 불변(immutable) 바이트 배열을 나타냅니다.
/// @details
/// MutableBytes와 SharedBytes의 데이터를 안전하게 읽기 위한 기능을 포함합니다.
///
/// @warning
/// 이 클레스는 쓰레드 안전하지 않습니다.
class BytesView {
public:
	BytesView() = default;
	~BytesView() = default;

	/// @brief 주어진 인수를 이용해 BytesView를 생성합니다.
	/// @param data 데이터 포인터
	/// @param length 데이터 길이
	/// @warning
	/// 내부적으로 복사 없이 전달된 data 인수를 참조하여 사용합니다. 그러므로 BytesView 사용이 끝나기 전까지 해당 포인터를
	/// 해제해서는 안됩니다.
	explicit BytesView(uint8_t* data, size_t length)
		: pointer_(data)
		, length_(length) {
	}

	/// @brief 읽을 수 있는 데이터 길이를 반환합니다.
	/// @return 읽을 수 있는 데이터 길이
	size_t Remaining() {
		static const size_t min_value = 0;
		return std::max(min_value, length_ - pos_);
	}

	/// @brief 시작 위치를 기준으로 pos로 이동합니다.
	/// @param pos offset
	/// @throw 주어진 pos가 유효 범위를 벗어난 경우 std::runtime_error를 throw 합니다.
	void Seek(size_t pos) {
		if (pos < 0 || length_ < pos) {
			throw std::runtime_error(fmt::format("the requested position ({}) exceeds the total length ({})", Remaining(), pos));
		}

		pos_ = pos;
	}

	/// @brief 현재 읽기 위치를 기준으로 cnt 만큼 이동시킵니다.
	/// @param pos offset
	/// @throw 주어진 cnt가 유효 범위를 벗어난 경우 std::runtime_error를 throw 합니다.
	void Advance(size_t cnt) {
		if (Remaining() < cnt) {
			throw std::runtime_error(fmt::format("the number of requested bytes ({}) exceeds the number of remaning bytes ({})", Remaining(), cnt));
		}

		pos_ += cnt;
	}

	/// @brief 1바이트를 읽고, Endian을 변경 후 uint8_t 값을 반환합니다.
	uint8_t GetU8() {
		return Get<uint8_t>();
	}

	/// @brief 1바이트를 읽고, Endian을 변경 후 int8_t 값을 반환합니다.
	int8_t GetI8() {
		return Get<int8_t>();
	}

	/// @brief 2바이트를 읽고, Endian을 변경 후 uint16_t 값을 반환합니다.
	uint16_t GetU16() {
		return Get<uint16_t>();
	}

	/// @brief 2바이트를 읽고, Endian을 변경 후 int16_t 값을 반환합니다.
	int16_t GetI16() {
		return Get<int16_t>();
	}

	/// @brief 4바이트를 읽고, Endian을 변경 후 uint32_t 값을 반환합니다.
	uint32_t GetU32() {
		return Get<uint32_t>();
	}

	/// @brief 4바이트를 읽고, Endian을 변경 후 int32_t 값을 반환합니다.
	int32_t GetI32() {
		return Get<int32_t>();
	}

	/// @brief 8바이트를 읽고, Endian을 변경 후 uint64_t 값을 반환합니다.
	uint64_t GetU64() {
		return Get<uint64_t>();
	}

	/// @brief 8바이트를 읽고, Endian을 변경 후 int64_t 값을 반환합니다.
	int64_t GetI64() {
		return Get<int64_t>();
	}

	/// @brief 4바이트를 읽고, Endian을 변경 후 float 값을 반환합니다.
	float_t GetFloat() {
		auto u32_value = GetU32();
		return *reinterpret_cast<float_t*>(&u32_value);
	}

	/// @brief 8바이트를 읽고, Endian을 변경 후 double 값을 반환합니다.
	double_t GetDouble() {
		auto u64_value = GetU64();
		return *reinterpret_cast<double_t*>(&u64_value);
	}

	/// @brief 읽기 위치 포인터를 반환합니다.
	const uint8_t* GetData() const {
		return pointer_ + pos_;
	}

private:
	template <typename T>
	typename std::enable_if_t<std::is_integral_v<T>, T> Get() {
		if (Remaining() < sizeof(T)) {
			throw std::runtime_error(fmt::format("the number of requested bytes ({}) exceeds the number of remaining bytes ({})", Remaining(), sizeof(T)));
		}
		T value = boost::endian::big_to_native(*reinterpret_cast<T*>(pointer_ + pos_));

		Advance(sizeof(T));

		return value;
	}

	uint8_t* pointer_ = nullptr;
	const size_t length_ = 0;
	size_t pos_ = 0;
};
} // namespace bytes

// 생성자를 통해 데이터를 받는다.

#endif