#include "optional/error_or_value.h"
#include "gtest/gtest.h"

TEST(error_or_value_case, value_test)
{
	optional::ErrorOrValue<int> val(10);
	ASSERT_EQ(10, val.value());
}

TEST(error_or_value_case, error_test)
{
	std::string error_text = "some error";

	try
	{
		optional::ErrorOrValue<int> val(std::make_exception_ptr(std::runtime_error(error_text.c_str())));
		ASSERT_EQ(error_text, val.what());
		val.value();
	}
	catch (std::exception& ex)
	{
		ASSERT_EQ(error_text, ex.what());
	}
}
