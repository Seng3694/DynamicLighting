#pragma once

#include "Nullable.h"

template<typename T>
inline Nullable<T>::Nullable()
{
	_hasValue = false;
}

template<typename T>
inline Nullable<T>::Nullable(T value)
{
	_value = value;
	_hasValue = true;
}

template<typename T>
inline T Nullable<T>::getValue()
{
	return _value;
}

template<typename T>
inline void Nullable<T>::setNull()
{
	_hasValue = false;
}

template<typename T>
inline bool Nullable<T>::hasValue()
{
	return _hasValue;
}

template<typename T>
inline Nullable<T>::operator T() const
{
	return _value;
}
