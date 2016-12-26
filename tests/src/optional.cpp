#include "optional/optional.h"
#include "gtest/gtest.h"
#include <string>
#include <memory>

struct Parent
{
	virtual int fun() { return 5; }
};

struct Child : Parent
{
	int fun() override { return 10; }
};

TEST(optional_case, literal_test)
{
	optional::OptionalValue<int> val;
	ASSERT_FALSE(val);
	val = 10;
	ASSERT_EQ(10, val.value());
}

TEST(optional_case, inherite_test)
{
	optional::OptionalValue<std::shared_ptr<Parent>> val;
	val = std::make_shared<Child>();
	ASSERT_EQ(10, val.value()->fun());
}

TEST(optional_case, move_test)
{
	std::string data = "data";
	optional::OptionalValue<std::string> val;
	ASSERT_FALSE(val);
	val = std::move(data);
	ASSERT_TRUE(data.empty());
	ASSERT_EQ(std::string("data"), val.value());
}

TEST(optional_case, copy_test)
{
	std::string data = "data";
	optional::OptionalValue<std::string> val;
	ASSERT_FALSE(val);
	val = data;
	ASSERT_EQ(data, val.value());
}

TEST(optional_case, ctr_test)
{
	optional::OptionalValue<int> val1(10);
	ASSERT_EQ(10, val1.value());

	optional::OptionalValue<std::string> val2("data");
	ASSERT_EQ(std::string("data"), val2.value());
}

TEST(optional_case, move_ctr_test)
{
	std::vector<unsigned int> val{ 1, 2, 3 };

	optional::OptionalValue<std::vector<unsigned int>> optional_value1(val);
	optional::OptionalValue<std::vector<unsigned int>> optional_value2(std::move(optional_value1));

	ASSERT_FALSE(optional_value1);
	ASSERT_EQ(val, optional_value2.value());
}

TEST(optional_case, move_ctr_empty_test)
{
	optional::OptionalValue<std::vector<unsigned int>> optional_value1;
	optional::OptionalValue<std::vector<unsigned int>> optional_value2(std::move(optional_value1));

	ASSERT_FALSE(optional_value1);
	ASSERT_FALSE(optional_value2);
}

TEST(optional_case, emplace_test)
{
	optional::OptionalValue<std::vector<unsigned int>> optional_value;
	optional_value.emplace(10);

	ASSERT_TRUE(optional_value);
	ASSERT_EQ(10, optional_value.value().size());
}

TEST(optional_case, init_init_move_assign_test)
{
	std::vector<unsigned int> val1{ 1, 2, 3 };
	std::vector<unsigned int> val2{ 1, 2, 3, 4 };

	optional::OptionalValue<std::vector<unsigned int>> optional_value1(val1);
	optional::OptionalValue<std::vector<unsigned int>> optional_value2(val2);
	optional_value2 = std::move(optional_value1);

	ASSERT_FALSE(optional_value1);
	ASSERT_EQ(val1, optional_value2.value());
}

TEST(optional_case, empty_init_move_assign_test)
{
	std::vector<unsigned int> val{ 1, 2, 3 };

	optional::OptionalValue<std::vector<unsigned int>> optional_value1;
	optional::OptionalValue<std::vector<unsigned int>> optional_value2(val);
	optional_value2 = std::move(optional_value1);

	ASSERT_FALSE(optional_value1);
	ASSERT_FALSE(optional_value2);
}

TEST(optional_case, init_empty_move_assign_test)
{
	std::vector<unsigned int> val{ 1, 2, 3 };

	optional::OptionalValue<std::vector<unsigned int>> optional_value1(val);
	optional::OptionalValue<std::vector<unsigned int>> optional_value2;
	optional_value2 = std::move(optional_value1);

	ASSERT_FALSE(optional_value1);
	ASSERT_EQ(val, optional_value2.value());
}

TEST(optional_case, empty_empty_move_assign_test)
{
	optional::OptionalValue<std::vector<unsigned int>> optional_value1;
	optional::OptionalValue<std::vector<unsigned int>> optional_value2;
	optional_value2 = std::move(optional_value1);

	ASSERT_FALSE(optional_value1);
	ASSERT_FALSE(optional_value2);
}

TEST(optional_case, copy_ctr_test)
{
	std::vector<unsigned int> val{ 1, 2, 3 };

	optional::OptionalValue<std::vector<unsigned int>> optional_value1(val);
	optional::OptionalValue<std::vector<unsigned int>> optional_value2(optional_value1);

	ASSERT_EQ(val, optional_value1.value());
	ASSERT_EQ(val, optional_value2.value());
}

TEST(optional_case, copy_ctr_empty_test)
{
	optional::OptionalValue<std::vector<unsigned int>> optional_value1;
	optional::OptionalValue<std::vector<unsigned int>> optional_value2(optional_value1);

	ASSERT_FALSE(optional_value1);
	ASSERT_FALSE(optional_value2);
}

TEST(optional_case, init_init_copy_assign_test)
{
	std::vector<unsigned int> val1{ 1, 2, 3 };
	std::vector<unsigned int> val2{ 1, 2, 3, 4 };

	optional::OptionalValue<std::vector<unsigned int>> optional_value1(val1);
	optional::OptionalValue<std::vector<unsigned int>> optional_value2(val2);
	optional_value2 = optional_value1;

	ASSERT_EQ(val1, optional_value1.value());
	ASSERT_EQ(val1, optional_value2.value());
}

TEST(optional_case, empty_init_copy_assign_test)
{
	std::vector<unsigned int> val{ 1, 2, 3 };

	optional::OptionalValue<std::vector<unsigned int>> optional_value1;
	optional::OptionalValue<std::vector<unsigned int>> optional_value2(val);
	optional_value2 = optional_value1;

	ASSERT_FALSE(optional_value1);
	ASSERT_FALSE(optional_value2);
}

TEST(optional_case, init_empty_copy_assign_test)
{
	std::vector<unsigned int> val{ 1, 2, 3 };

	optional::OptionalValue<std::vector<unsigned int>> optional_value1(val);
	optional::OptionalValue<std::vector<unsigned int>> optional_value2;
	optional_value2 = optional_value1;

	ASSERT_EQ(val, optional_value1.value());
	ASSERT_EQ(val, optional_value2.value());
}

TEST(optional_case, empty_empty_copy_assign_test)
{
	optional::OptionalValue<std::vector<unsigned int>> optional_value1;
	optional::OptionalValue<std::vector<unsigned int>> optional_value2;
	optional_value2 = optional_value1;

	ASSERT_FALSE(optional_value1);
	ASSERT_FALSE(optional_value2);
}
