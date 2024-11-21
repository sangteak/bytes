#include <array>
#include <gtest/gtest.h>
#include <Bytes/BytesView.h>
#include "DataGenerator.h"

TEST(BytesViewTest, GetI8) {
	int8_t value = 100;
	bytes::BytesView<bytes::EndianKind::Big> view(reinterpret_cast<uint8_t*>(&value), sizeof(value));
	auto result_value = view.GetI8();
	EXPECT_EQ(result_value, value);
}

TEST(BytesViewTest, GetU8) {
	uint8_t value = 200;
	bytes::BytesView<bytes::EndianKind::Big> view(&value, sizeof(value));
	auto result_value = view.GetU8();
	EXPECT_EQ(result_value, value);
}

TEST(BytesViewTest, GetI16) {
	auto buf = MakeTestData<int16_t>(-10000);
	bytes::BytesView<bytes::EndianKind::Big> view(buf.data(), buf.size());
	auto result_value = view.GetI16();
	EXPECT_EQ(result_value, -10000);
}

TEST(BytesViewTest, GetU16) {
	auto buf = MakeTestData<uint16_t>(20000);
	bytes::BytesView<bytes::EndianKind::Big> view(buf.data(), buf.size());
	auto result_value = view.GetU16();
	EXPECT_EQ(result_value, 20000);
}

TEST(BytesViewTest, GetI32) {
	auto buf = MakeTestData<int32_t>(-99999999);
	bytes::BytesView<bytes::EndianKind::Big> view(buf.data(), buf.size());
	auto result_value = view.GetI32();
	EXPECT_EQ(result_value, -99999999);
}

TEST(BytesViewTest, GetU32) {
	auto buf = MakeTestData<uint32_t>(99999999);
	bytes::BytesView<bytes::EndianKind::Big> view(buf.data(), buf.size());
	auto result_value = view.GetU32();
	EXPECT_EQ(result_value, 99999999);
}

TEST(BytesViewTest, GetI64) {
	auto buf = MakeTestData<int64_t>(-9999999999999);
	bytes::BytesView<bytes::EndianKind::Big> view(buf.data(), buf.size());
	auto result_value = view.GetI64();
	EXPECT_EQ(result_value, -9999999999999);
}

TEST(BytesViewTest, GetU64) {
	auto buf = MakeTestData<uint64_t>(9999999999999);
	bytes::BytesView<bytes::EndianKind::Big> view(buf.data(), buf.size());
	auto result_value = view.GetU64();
	EXPECT_EQ(result_value, 9999999999999);
}

TEST(BytesViewTest, GetFloat) {
	float value = 30.321f;
	uint32_t convert_value;
	memcpy(&convert_value, &value, sizeof(value));

	auto buf = MakeTestData(convert_value);
	bytes::BytesView<bytes::EndianKind::Big> view(buf.data(), buf.size());
	auto result_value = view.GetFloat();
	EXPECT_EQ(result_value, 30.321f);
}

TEST(BytesViewTest, GetDouble) {
	double value = -40.321f;
	uint64_t convert_value;
	memcpy(&convert_value, &value, sizeof(value));

	auto buf = MakeTestData(convert_value);
	bytes::BytesView<bytes::EndianKind::Big> view(buf.data(), buf.size());
	auto result_value = view.GetDouble();
	EXPECT_EQ(result_value, -40.321f);
}

TEST(BytesViewTest, GetData) {
	auto buf = MakeTestData(10, 20);
	bytes::BytesView<bytes::EndianKind::Big> view(buf.data(), buf.size());

	const uint8_t* data = view.GetData();
	EXPECT_EQ(view.Remaining(), 8);

	std::pair<int32_t, int32_t> values;
	memcpy(&values.first, data, sizeof(int32_t));
	memcpy(&values.second, data + sizeof(int32_t), sizeof(int32_t));

	EXPECT_EQ(boost::endian::big_to_native(values.first), 10);
	EXPECT_EQ(boost::endian::big_to_native(values.second), 20);
}

TEST(BytesViewTest, Advence) {
	auto buf = MakeTestData<uint32_t, int32_t>(10000, -10000);
	bytes::BytesView<bytes::EndianKind::Big> view(buf.data(), buf.size());

	view.Advance(sizeof(uint32_t));

	auto result_value = view.GetI32();
	EXPECT_EQ(result_value, -10000);

	EXPECT_THROW(view.Advance(sizeof(int32_t)), std::runtime_error);
}

TEST(BytesViewTest, Seek) {
	auto buf = MakeTestData<uint32_t, int32_t>(10000, -10000);
	bytes::BytesView<bytes::EndianKind::Big> view(buf.data(), buf.size());
	view.Seek(sizeof(uint32_t));
	EXPECT_EQ(view.GetI32(), -10000);
	EXPECT_EQ(view.Remaining(), 0);

	view.Seek(0);
	EXPECT_EQ(view.GetU32(), 10000);
	EXPECT_EQ(view.Remaining(), sizeof(int32_t));
}