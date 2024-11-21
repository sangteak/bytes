#ifndef BYTES_TESTS_DATAGENERATOR_H_
#define BYTES_TESTS_DATAGENERATOR_H_

#include <boost/endian/conversion.hpp>

template <typename... Args>
auto MakeTestData(Args... args) -> std::enable_if_t<(std::is_integral_v<Args> && ...), std::array<uint8_t, (sizeof(Args) + ... + 0)>> {
	constexpr size_t totalSize = (sizeof(args) + ...);
	std::array<uint8_t, totalSize> buf{};

	size_t offset = 0;
	(([&]() {
		 using T = Args;
		 T value = args;
		 value = boost::endian::native_to_big(value);

		 memcpy(buf.data() + offset, &value, sizeof(value));
		 offset += sizeof(value);
	 }()),
	 ...);

	return buf;
}

#endif