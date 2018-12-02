#include <iostream>
#include <clocale>
#include <cassert>
#include "base64.h"
#include "utf8.h"


void test1() {
	Encoder& encoder = Encoder::instance();
	Decoder& decoder = Decoder::instance();

	std::string input = "";
	std::string output = decoder.decodeToASCII(encoder.encode(input));
	assert(input == output);

	input = "a";
	output = decoder.decodeToASCII(encoder.encode(input));
	assert(input == output);

	input = "asdJSDSND\nsa";
	output = decoder.decodeToASCII(encoder.encode(input));
	assert(input == output);

	input = "SkakOOSAK039scdn\n3id90\t dji\w 32okamzxkK@)@O_)DN\n?";
	output = decoder.decodeToASCII(encoder.encode(input));
	assert(input == output);

	std::cout << "First test has been succesfully passed" << std::endl;
}


void test2() {
	Encoder& encoder = Encoder::instance();
	Decoder& decoder = Decoder::instance();

	std::string input = "aaEs0921OIJSn\n23 09\tsZZZ";
	std::string encoded_input = encoder.encode(input);
	encoded_input += "?~)";
	std::string output;
	try {
		output = decoder.decodeToASCII(encoded_input);
	}
	catch (Exception* e) {
		std::cout << e->what() << std::endl;
	}

	input = "dsjuidah\n is uh\r ad\\sis dahd\tsih 2e03e98230-9 38e03 9JZIOSXJK><k@( W*@(E&^ *(S& 7s8";
	output = decoder.decodeToASCII(encoder.encode(input));
	assert(input == output);

	std::cout << "Second test has been succesfully passed" << std::endl;
}


void test3() {
	std::setlocale(LC_ALL, "russian_russia.866");
	Encoder& encoder = Encoder::instance();
	Decoder& decoder = Decoder::instance();

	std::wstring input = L"Привет, это тесто\tвая строка, состоящая из русских и english letters!.>SX?";
	std::wstring output = decoder.decodeToUTF(encoder.encode(input));
	assert(input == output);

	input = L"ОАЫШЩ022109ьь.дльфызфыщ!!(*№>\t dsjosajismxшовОВГ\n isio)_#EX<a";
	output = decoder.decodeToUTF(encoder.encode(input));
	assert(input == output);
	//std::wcout << output << std::endl;

	std::cout << "Third test has been succesfully passed" << std::endl;
}


void test4() {
	std::setlocale(LC_ALL, "Arabic_U.AE.1256");
	Encoder& encoder = Encoder::instance();
	Decoder& decoder = Decoder::instance();

	std::wstring input = L"JIODالجملة لا معنى ل.";
	std::wstring output = decoder.decodeToUTF(encoder.encode(input));
	assert(input == output);

	std::cout << "Fourth test has been succesfully passed" << std::endl;
}


void test5() {
	std::setlocale(LC_ALL, "ja_JP.UTF - 8");
	Encoder& encoder = Encoder::instance();
	Decoder& decoder = Decoder::instance();

	std::wstring input = L"XSSこの文は意味をなさない。";
	std::wstring output = decoder.decodeToUTF(encoder.encode(input));
	assert(input == output);
	
	std::cout << "Fifth test has been succesfully passed" << std::endl;
}


int main() {
	test1();
	test2();
	test3();
	test4();
	test5();
	return 0;
}