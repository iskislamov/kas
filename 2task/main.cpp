#include "CString.h"
#include <cassert>


void test() {
	CString s("as");
	CString s1 = "as";
	s += 'a';
	assert(s == "asa");
	assert(s1 <= s);
	assert(s1 < s);
	assert(s == (s1 + "a"));
	CString s2(CString("nasdb"));
	CString s3;
	CString s4 = "nasdb";
	assert(s2.length() == 5);
	assert(s2.empty() == false);
	assert(s2 == s4);
	assert(s3.length() == 0);
	assert(s3.empty() == true);
	assert(s2 > s3);
	assert(s2 > s1);
	assert(s2 >= s1);
	assert(s1 != s);

	s3 += s1 + s2;
	assert(s3 == "asnasdb");

	CString s5 = std::move(CString("ax"));

	swap(s4, s1);
	assert(s4 == "as");
	assert(s1.length() == 5);
	assert(s1 == "nasdb");

	std::cout << "Write some string, please" << std::endl;
	std::cin >> s5;
	std::cout << "Input string:" << std::endl;
	std::cout << s5 << std::endl;
	size_t length = s5.length();
	char str1[] = "sdihdfpauhfdpifsduhfpdsiuhdfspdfhpfdhadsfpiafsduhdsf";
	char str2[] = "1231231sajoidjsa";
	s5 += str1;
	assert(s5.length() == length + 52);
	s5 = str2 + s5;
	assert(length + 68 == s5.length());
	s3 = s2;
	s3 = str1 + s3;
	s3 += str2;

	assert(str1 + s2 + str2 == s3);

	s1[3] = '%';
	assert(s1 == "nas%b");
	assert(s5[4] == '2');
	s1[6] = '1';
	assert(s1 == "nas%b");
	assert(str1 < s3);


}


int main() {
	test();
	system("pause");
	return 0;
}