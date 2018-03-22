#pragma once

template<typename T>
struct Nullable
{
public:
	Nullable();
	Nullable(T value);

	T getValue();
	void setNull();
	bool hasValue();

	operator T() const;

private:
	T _value;
	bool _hasValue;
};

#include "Nullable.inl"