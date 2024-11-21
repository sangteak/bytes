/// @file SharedBytes.h
/// @author stkwon (sangtakeg@gmail.com)
/// @brief 공유 가능한 불변(immutable) 바이트 배열을 나타냅니다.
/// @version 0.1
/// @date 2024-11-21
///
/// @copyright Copyright (c) 2024
///
#ifndef BYTES_SHAREDBYTES_H_
#define BYTES_SHAREDBYTES_H_

#include <memory>
#include "BytesView.h"

namespace bytes {
/// @brief 불변 데이터를 공유 할 수 있는 기능을 포함합니다.
/// @details
/// 해당 클래스는 불변 데이터를 참조 카운터(std::shared_ptr)를 이용하여 여러 쓰레드에 불변 데이터를
/// 안전하게 공유하고, BytesView를 통해 해당 데이터를 안전하게 읽도록 도와줍니다.
template <EndianKind kind>
class SharedBytes {
public:
	SharedBytes() = delete;
	~SharedBytes() = default;

	explicit SharedBytes(const uint8_t* data, size_t length)
		: data_(new uint8_t[length], std::default_delete<uint8_t[]>())
		, length_(length) {
		memcpy(data_.get(), data, length);
	}

	SharedBytes(const SharedBytes& other) = default;
	SharedBytes(SharedBytes&& other) noexcept = default;

	SharedBytes& operator=(const SharedBytes& other) = default;
	SharedBytes& operator=(SharedBytes&& other) noexcept = default;

	/// @brief 읽기 데이터를 BytesView에 담아 반환합니다.
	BytesView<kind> AsRef() {
		if (data_ == nullptr) {
			return BytesView<kind>();
		}

		return BytesView<kind>(data_.get(), length_);
	}

private:
	size_t length_ = 0;
	std::shared_ptr<uint8_t> data_; // 원본만 가지고 있고
};
} // namespace bytes

#endif // end BYTES_SHAREDBYTES_H_