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
/**
 * @brief 불변(immutable) 바이트 배열을 나타냅니다.
 * @details
 * 주로 읽기 전용 데이터에 사용되며, 메모리에서 효율적으로 공유할 수 있도록 설계되었습니다.
 *
 * 특징
 * - 불변성: Bytes는 생성된 후 변경할 수 없습니다. 이는 쓰레드 안정성을 확보하고, 완성된 데이터에 대한
 * 변경을 차단하여 데이터를 안전하게 사용할 수 있도록 합니다.
 * - 메모리 공유: Bytes가 대입될 경우 데이터를 복제하지 않고 참조 카운트를 통해 얕은 복사를 수행합니다.
 * 이를 통해 여러 쓰레드에 공유되었을 경우에도 메모리 사용을 최적화할 수 있습니다.
 */
class BytesView {
public:
	BytesView() = default;
	~BytesView() = default;

	explicit BytesView(uint8_t* data, size_t length)
		: pointer_(data)
		, length_(length) {
	}

	size_t Remaining() {
		static const size_t min_value = 0;
		return std::max(min_value, length_ - pos_);
	}

	void Seek(size_t pos) {
		if (length_ < pos) {
			throw std::runtime_error(fmt::format("the requested position ({}) exceeds the total length ({})", Remaining(), pos));
		}

		pos_ = pos;
	}

	void Advance(size_t cnt) {
		if (Remaining() < cnt) {
			throw std::runtime_error(fmt::format("the number of requested bytes ({}) exceeds the number of remaning bytes ({})", Remaining(), cnt));
		}

		pos_ += cnt;
	}

	uint8_t GetU8() {
		return Get<uint8_t>();
	}

	int8_t GetI8() {
		return Get<int8_t>();
	}

	uint16_t GetU16() {
		return Get<uint16_t>();
	}

	int16_t GetI16() {
		return Get<int16_t>();
	}

	uint32_t GetU32() {
		return Get<uint32_t>();
	}

	int32_t GetI32() {
		return Get<int32_t>();
	}

	uint64_t GetU64() {
		return Get<uint64_t>();
	}

	int64_t GetI64() {
		return Get<int64_t>();
	}

	float_t GetFloat() {
		auto u32_value = GetU32();
		return *reinterpret_cast<float_t*>(&u32_value);
	}

	double_t GetDouble() {
		auto u64_value = GetU64();
		return *reinterpret_cast<double_t*>(&u64_value);
	}

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