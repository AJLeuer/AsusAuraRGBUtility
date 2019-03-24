#pragma once

#include <string>
#include <iostream>

template <typename CharType, typename StringLike>
bool contains(std::basic_string<CharType> & string, StringLike & substring)
{
	return string.find(substring) != std::basic_string<CharType>::npos;
}