#include <string>
#include <iostream>
#include <stdlib.h>

void ShowStrings()
{
	// The reason const is added to c-style strings is because strings are immutable
	// Immutable meaning it's a fixed allocated block of memory, you can't just make it larger
	// A string begins at the pointer and continues on untill it gets null-terminated by a null termination characted
	// Hey is 3 letters + the null termination character at the end (which we don't see) makes it a char[4] string
	const char* _cStyleString{ "Hey" };
	// this is the equivalent of the above string
	const char _proofOfConcept[4] = { 'H', 'e', 'y', '\0' }; // '\0' or 0 or 0x00 or 0b00000000, etc.
	std::string _modernCppStyleString{ "Hey" }; // std::string has a const char* constructor
	std::cout << "My string size is: " << _modernCppStyleString.size() << std::endl;

	// Wide character or 2-bytes / character string, basically an unsigned short
	// Note the L prefix which makes it a wide string literal
	//'H' = 48 00, 'E' = 65 00, 'Y' = 79 00, '\0' = 00 00
	const wchar_t* wideCharacterString{L"Hey"};
	//48 65 79 00
	const char8_t* string1{ u8"Hey" };
	//Just like wchar_t, char16_t = 2 bytes / char
	//48 00 65 00 79 00 00 00
	const char16_t* string2{ u"Hey" };
	//char32_t = 4 bytes / char
	//48 00 00 00 65 00 00 00 79 00 00 00 00 00 00 00
	const char32_t* string3{ U"Hey" };
	
	using namespace std::string_literals;
	// Note the s suffix's, we need string literals for this
	std::string string4{ "Hey"s };
	std::wstring string5{ L"Hey"s };

	// Ignore escape characters prefix
	const char* string6 {R"(H
e
y)"};

	std::cout << string6 << std::endl;

	// DONT PASS STRINGS BY COPY FOR READ-ONLY OPERATIONS, THEY'RE EXPENSIVE
	// Pass by const std::string& instead
}