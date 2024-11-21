#include <array>
#include <gtest/gtest.h>
#include <Bytes/SharedBytes.h>
#include "DataGenerator.h"

TEST(SharedBytesTests, Share) {
	auto buf = MakeTestData<uint32_t, int32_t>(10000, -10000);
	bytes::SharedBytes<bytes::EndianKind::Big> shared(buf.data(), buf.size());
	{
		auto shared_inner = shared;
		auto view = shared_inner.AsRef();
		EXPECT_EQ(view.Remaining(), 8);
	}

	auto view = shared.AsRef();
	EXPECT_EQ(view.Remaining(), 8);
}