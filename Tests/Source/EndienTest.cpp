#include <gtest/gtest.h>
#include <Bytes/Endian.h>

TEST(EndianTests, ToEndian_None) {
	int32_t input = 10;
	auto value = bytes::to_endian<int32_t, bytes::EndianKind::None>(input);
	EXPECT_EQ(value, 10);
}

TEST(EndianTests, ToEndian_Big) {
	int32_t input = 10;
	auto value = bytes::to_endian<int32_t, bytes::EndianKind::Big>(input);

	int32_t origin_value = boost::endian::big_to_native(value);
	EXPECT_EQ(origin_value, 10);
}

TEST(EndianTests, ToEndian_Little) {
	int32_t input = 10;
	auto value = bytes::to_endian<int32_t, bytes::EndianKind::Little>(input);

	int32_t origin_value = boost::endian::little_to_native(value);
	EXPECT_EQ(origin_value, 10);
}

TEST(EndianTests, FromEndian_None) {
	int32_t input = 10;
	auto value = bytes::from_endian<int32_t, bytes::EndianKind::None>(input);
	EXPECT_EQ(value, 10);
}

TEST(EndianTests, FromEndian_Big) {
	int32_t input = 10;
	input = boost::endian::native_to_big(input);

	auto value = bytes::from_endian<int32_t, bytes::EndianKind::Big>(input);
	EXPECT_EQ(value, 10);
}

TEST(EndianTests, FromEndian_Little) {
	int32_t input = 10;
	input = boost::endian::native_to_little(input);

	auto value = bytes::from_endian<int32_t, bytes::EndianKind::Little>(input);
	EXPECT_EQ(value, 10);
}