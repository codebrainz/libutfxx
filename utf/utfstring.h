#ifndef __UTF_STRING_H__
#define __UTF_STRING_H__

#include "utf.h"
#include <iostream>
#include <vector>

namespace utf
{

template< typename CharT > class string;

template< typename T1, typename T2 >
void convert(const string<T1>& in, T2 out);

template< typename CharT >
class string
{
public:
	typedef CharT char_type;
	typedef std::basic_string<char_type> string_type;
	typedef typename string_type::size_type size_type;
	typedef typename string_type::iterator iterator;
	typedef typename string_type::const_iterator const_iterator;
	typedef std::vector<string<CharT> > list_type;

	template< typename T >
	string(T str) {
		utf::convert(str, s);
	}

	template< typename T >
	string& assign(T str) {
		if (&str != this)
			utf::convert(str, s);
		return *this;
	}

	template< typename T >
	string& operator=(T str) {
		return assign(str);
	}

	template< typename T >
	string& append(T str) {
		string_type tmp;
		utf::convert(str, tmp);
		s += tmp;
		return *this;
	}

	template< typename T >
	string& operator+=(T str) {
		return append(str);
	}

	template< typename T >
	bool equal(T str) const {
		string_type tmp;
		utf::convert(str, tmp);
		return (s == tmp);
	}

	template< typename T >
	bool operator==(T str) const {
		return equal(str);
	}

	template< typename T >
	bool operator!=(T str) const {
		return !equal(str);
	}

	utf::string8 to_utf8() const {
		return utf::to_utf8(s);
	}

	utf::string16 to_utf16() const {
		return utf::to_utf16(s);
	}

	utf::string32 to_utf32() const {
		return utf::to_utf32(s);
	}

	const string_type& str() const {
		return s;
	}

	string_type& str() {
		return s;
	}

	const char_type* c_str() const {
		return s.c_str();
	}

	const char_type* data() const {
		return s.data();
	}

	iterator begin() {
		return s.begin();
	}

	const_iterator begin() const {
		return s.begin();
	}

	iterator end() {
		return s.end();
	}

	const_iterator end() const {
		return s.end();
	}

	const_iterator cbegin() const {
		return s.begin();
	}

	const_iterator cend() const {
		return s.end();
	}

	char_type& at(size_t pos) {
		return s.at(pos);
	}

	const char_type& at(size_t pos) const {
		return s.at(pos);
	}

	char_type& operator[](size_t pos) {
		return s[pos];
	}

	const char_type& operator[](size_t pos) const {
		return s[pos];
	}

	char_type& back() {
		return s.back();
	}

	const char_type& back() const {
		return s.back();
	}

	char_type& front() {
		return s.front();
	}

	const char_type& front() const {
		return s.front();
	}

	size_t capacity() const {
		return s.capacity();
	}

	void clear() {
		s.clear();
	}

	template< typename T >
	int compare(T str) const {
		string_type tmp;
		utf::convert(str, tmp);
		return s.compare(tmp);
	}

	bool empty() const {
		return s.empty();
	}

	inline friend std::ostream& operator<<(std::ostream& out, const string<char_type>& str)
	{
		std::basic_string<std::ostream::char_type> out_str;
		utf::convert(str.str(), out_str);
		out << out_str.c_str();
		return out;
	}

private:
	string_type s;
};

template< typename T1, typename T2 >
void convert(const string<T1>& in, T2 out)
{
	convert(in.str(), out);
}

typedef string<char8>  u8string;
typedef string<char16> u16string;
typedef string<char32> u32string;

typedef u8string::list_type  ustring8_list;
typedef u16string::list_type ustring16_list;
typedef u32string::list_type ustring32_list;

} // namespace utf

#ifdef UTF_CXX11
namespace std {
	template< typename T >
	std::string to_string(const utf::string<T>& in)
	{
		return in.to_utf8();
	}
}
#endif

#endif // __UTF_STRING_H__
