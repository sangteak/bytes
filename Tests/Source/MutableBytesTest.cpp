#include <tuple>
#include <gtest/gtest.h>
#include <Bytes/MutableBytes.h>

TEST(MutableBytesTests, PutI8) {
	int8_t value = 0x02;

	bytes::MutableBytes<bytes::EndianKind::Big> buf(10);
	EXPECT_EQ(buf.IsEmpty(), true);

	buf.PutI8(value);
	EXPECT_EQ(buf.Length(), sizeof(value));

	bytes::BytesView view = buf.AsRef();
	EXPECT_EQ(view.GetI8(), value);

	buf.Advance(sizeof(value));
	EXPECT_EQ(buf.IsEmpty(), true);
}

TEST(MutableBytesTests, PutU8) {
	uint8_t value = 0xFF;

	bytes::MutableBytes<bytes::EndianKind::Big> buf(10);
	EXPECT_EQ(buf.IsEmpty(), true);

	buf.PutU8(value);
	EXPECT_EQ(buf.Length(), sizeof(value));

	bytes::BytesView view = buf.AsRef();
	EXPECT_EQ(view.GetU8(), value);

	buf.Advance(sizeof(value));
	EXPECT_EQ(buf.IsEmpty(), true);
}

TEST(MutableBytesTests, PutI16) {
	int16_t value = -10000;

	bytes::MutableBytes<bytes::EndianKind::Big> buf(10);
	EXPECT_EQ(buf.IsEmpty(), true);

	buf.PutI16(value);
	EXPECT_EQ(buf.Length(), sizeof(value));

	bytes::BytesView view = buf.AsRef();
	EXPECT_EQ(view.GetI16(), value);

	buf.Advance(sizeof(value));
	EXPECT_EQ(buf.IsEmpty(), true);
}

TEST(MutableBytesTests, PutU16) {
	uint16_t value = 10000;

	bytes::MutableBytes<bytes::EndianKind::Big> buf(10);
	EXPECT_EQ(buf.IsEmpty(), true);

	buf.PutU16(value);
	EXPECT_EQ(buf.Length(), sizeof(value));

	bytes::BytesView view = buf.AsRef();
	EXPECT_EQ(view.GetU16(), value);

	buf.Advance(sizeof(value));
	EXPECT_EQ(buf.IsEmpty(), true);
}

TEST(MutableBytesTests, PutI32) {
	int32_t value = -10000000;

	bytes::MutableBytes<bytes::EndianKind::Big> buf(10);
	EXPECT_EQ(buf.IsEmpty(), true);

	buf.PutI32(value);
	EXPECT_EQ(buf.Length(), sizeof(value));

	bytes::BytesView view = buf.AsRef();
	EXPECT_EQ(view.GetI32(), value);

	buf.Advance(sizeof(value));
	EXPECT_EQ(buf.IsEmpty(), true);
}

TEST(MutableBytesTests, PutU32) {
	uint32_t value = 10000000;

	bytes::MutableBytes<bytes::EndianKind::Big> buf(10);
	EXPECT_EQ(buf.IsEmpty(), true);

	buf.PutU32(value);
	EXPECT_EQ(buf.Length(), sizeof(value));

	bytes::BytesView view = buf.AsRef();
	EXPECT_EQ(view.GetU32(), value);

	buf.Advance(sizeof(value));
	EXPECT_EQ(buf.IsEmpty(), true);
}

TEST(MutableBytesTests, PutI64) {
	int64_t value = -10000000000;

	bytes::MutableBytes<bytes::EndianKind::Big> buf(10);
	EXPECT_EQ(buf.IsEmpty(), true);

	buf.PutI64(value);
	EXPECT_EQ(buf.Length(), sizeof(value));

	bytes::BytesView view = buf.AsRef();
	EXPECT_EQ(view.GetI64(), value);

	buf.Advance(sizeof(value));
	EXPECT_EQ(buf.IsEmpty(), true);
}

TEST(MutableBytesTests, PutU64) {
	uint64_t value = 10000000000;

	bytes::MutableBytes<bytes::EndianKind::Big> buf(10);
	EXPECT_EQ(buf.IsEmpty(), true);

	buf.PutU64(value);
	EXPECT_EQ(buf.Length(), sizeof(value));

	bytes::BytesView view = buf.AsRef();
	EXPECT_EQ(view.GetU64(), value);

	buf.Advance(sizeof(value));
	EXPECT_EQ(buf.IsEmpty(), true);
}

TEST(MutableBytesTests, PutFloat) {
	float value = -30.123f;

	bytes::MutableBytes<bytes::EndianKind::Big> buf(10);
	EXPECT_EQ(buf.IsEmpty(), true);

	buf.PutFloat(value);
	EXPECT_EQ(buf.Length(), sizeof(value));

	bytes::BytesView view = buf.AsRef();
	EXPECT_EQ(view.GetFloat(), value);

	buf.Advance(sizeof(value));
	EXPECT_EQ(buf.IsEmpty(), true);
}

TEST(MutableBytesTests, PutDouble) {
	double value = -30.123f;

	bytes::MutableBytes<bytes::EndianKind::Big> buf(10);
	EXPECT_EQ(buf.IsEmpty(), true);

	buf.PutDouble(value);
	EXPECT_EQ(buf.Length(), sizeof(value));

	bytes::BytesView view = buf.AsRef();
	EXPECT_EQ(view.GetDouble(), value);

	buf.Advance(sizeof(value));
	EXPECT_EQ(buf.IsEmpty(), true);
}

TEST(MutableBytesTests, PutMultipleValues) {
	auto values = std::make_tuple(int32_t(30), int64_t(9800));

	bytes::MutableBytes<bytes::EndianKind::Big> buf(10);
	EXPECT_EQ(buf.IsEmpty(), true);

	buf.PutI32(std::get<0>(values));
	EXPECT_EQ(buf.Length(), 4);

	buf.PutI64(std::get<1>(values));
	EXPECT_EQ(buf.Length(), 12);
}

TEST(MutableBytesTests, Compact) {
	bytes::MutableBytes<bytes::EndianKind::Big> buf(10);
	EXPECT_EQ(buf.Capacity(), 10);
	EXPECT_EQ(buf.IsEmpty(), true);
	EXPECT_EQ(buf.Length(), 0);

	buf.PutI32(int32_t(10));
	EXPECT_EQ(buf.Capacity(), 10);
	EXPECT_EQ(buf.IsEmpty(), false);
	EXPECT_EQ(buf.Length(), 4);

	buf.Advance(4); // 4byte를 읽은 후 읽기 위치 전진한 상태이며, 현재 단편화 공간 4가 남아있는 상태에서 8바이트를 입력한다.

	buf.PutI64(int64_t(30));
	EXPECT_EQ(buf.Capacity(), 10);
	EXPECT_EQ(buf.IsEmpty(), false);
	EXPECT_EQ(buf.Length(), 8);

	buf.PutI32(int32_t(10));
	EXPECT_TRUE(buf.Capacity() > 10);
	EXPECT_EQ(buf.IsEmpty(), false);
	EXPECT_EQ(buf.Length(), 12);
}