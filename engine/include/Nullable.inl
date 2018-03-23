#pragma once

#include "Nullable.h"

template<typename T>
inline seng::Nullable<T>::Nullable()
{
	_hasValue = false;
}

template<typename T>
inline seng::Nullable<T>::Nullable(T value)
{
	_value = value;
	_hasValue = true;
}

template<typename T>
inline T seng::Nullable<T>::getValue()
{
	return _value;
}

template<typename T>
inline void seng::Nullable<T>::setNull()
{
	_hasValue = false;
}

template<typename T>
inline bool seng::Nullable<T>::hasValue()
{
	return _hasValue;
}

template<typename T>
inline seng::Nullable<T>::operator T() const
{
	return _value;
}
