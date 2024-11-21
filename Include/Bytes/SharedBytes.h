#ifndef BYTES_SHAREDBYTES_H_
#define BYTES_SHAREDBYTES_H_

#include <memory>
#include "BytesView.h"

namespace bytes {
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

	BytesView AsRef() {
		if (data_ == nullptr) {
			return BytesView();
		}

		return BytesView(data_.get(), length_);
	}

private:
	size_t length_ = 0;
	std::shared_ptr<uint8_t> data_; // 원본만 가지고 있고
};
} // namespace bytes

#endif // end BYTES_SHAREDBYTES_H_