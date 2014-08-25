#include "utfstring.h"

int main()
{
	utf::u8string s = "Hello World";

	s += ", How are you?";
	s += " Not too shabby";
	s += ", if I must say!";

	std::cout << s << std::endl;

	utf::u32string s1 = "Hello World";
	utf::u16string s2 = "Hello World";
	utf::u8string s3 = "Hi";

	std::cout <<s3<<std::endl;

	bool eq = (s1 == s2);
	bool neq = (s1 != s2);

	std::cout << "EQ: " << eq << std::endl;
	std::cout << "NEQ: " << neq << std::endl;

	//std::cout << "to_string(): " << std::to_string(s2) << std::endl;

	s2 += "Foo";

	std::cout << s1 << std::endl;
	std::cout << s2 << std::endl;

	//for (auto ch : s) {
	//	std::cout << ch << ", ";
	//}
	//std::cout << std::endl;

	return 0;
}
