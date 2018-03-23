#include "catch.h"

#include "Nullable.h"

TEST_CASE("engine/Nullable check if hasValue() is false on construction")
{
	seng::Nullable<int> i;
		
	REQUIRE(i.hasValue() == false);
}

TEST_CASE("engine/Nullable check if hasValue() is true on implicit conversion")
{
	seng::Nullable<int> i = 10;

	REQUIRE(i.hasValue() == true);
}

TEST_CASE("engine/Nullable check for implicit backward conversion")
{
	seng::Nullable<int> i = 10;
	int a = i;

	REQUIRE(a == 10);
}

TEST_CASE("engine/Nullable check for hasValue() after setNull()")
{
	seng::Nullable<int> i = 10;
	i.setNull();

	REQUIRE(i.hasValue() == false);
}

TEST_CASE("engine/Nullable check for custom types")
{
	struct CustomType
	{
	public:
		int x;
		int y;
	};

	seng::Nullable<CustomType> i;
	REQUIRE(i.hasValue() == false);

	i = CustomType{ 10, 20 };
	REQUIRE(i.hasValue() == true);

	CustomType a = i;
	REQUIRE(a.x == 10);
	REQUIRE(a.y == 20);

	i.setNull();
	REQUIRE(i.hasValue() == false);
}