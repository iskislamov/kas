#include <cstring>
#include "CString.h"


CString::CString() {
	size_ = 0;
	allocated_size_ = 1;
	str_ = new char[1];
	str_[size_] = '\0';
}

CString::CString(const char* str = "") {
	size_ = strlen(str);

	allocated_size_ = size_ + 1;
	str_ = new char[allocated_size_];
	
	for (size_t i = 0; i < size_; ++i) {
		str_[i] = str[i];
	}
	str_[size_] = '\0';
}


CString::CString(const CString& rhs) {
std::cout <<"ASSIGNconstructor\n" << std::flush;
	size_ = rhs.size_;
	allocated_size_ = size_ + 1;
	str_ = new char[allocated_size_];
	
	for (size_t i = 0; i < size_; ++i) {
		str_[i] = rhs.str_[i];
	}
	str_[size_] = '\0';
}

CString& CString::operator=(const CString& rhs) {
std::cout << "ASSIGNoperator=\n" << std::flush;
	if (this != &rhs) {
		delete[] str_;
		size_ = rhs.size_;
		allocated_size_ = size_ + 1;
		str_ = new char[allocated_size_];
		
		for (size_t i = 0; i < size_; ++i) {
			str_[i] = rhs.str_[i];
		}
		str_[size_] = '\0';
	}
	return *this;
}


CString::CString(CString&& rhs) {
std::cout <<"MOVEconstructor\n" << std::flush;
	std::swap(size_, rhs.size_);
	std::swap(allocated_size_, rhs.allocated_size_);
	std::swap(str_, rhs.str_);
}

CString& CString::operator=(CString&& rhs) {
std::cout <<"MOVEoperator=\n" << std::flush;
	if (this != &rhs) {
		delete[] str_;

		size_ = rhs.size_;
		allocated_size_ = rhs.allocated_size_;
		str_ = rhs.str_;

		rhs.size_ = 0;
		rhs.allocated_size_ = 0;
		rhs.str_ = nullptr;
	}
	return *this;
}


CString::~CString() {
	size_ = 0;
	allocated_size_ = 0;
	delete[] str_;
}


bool operator==(const CString& lhs, const CString& rhs) {
	return strcmp(lhs.str_, rhs.str_) == 0;
}

bool operator!=(const CString& lhs, const CString& rhs) {
	return strcmp(lhs.str_, rhs.str_) != 0;
}

bool operator<(const CString& lhs, const CString& rhs) {
	return strcmp(lhs.str_, rhs.str_) < 0;
}

bool operator<=(const CString& lhs, const CString& rhs) {
	return !(rhs < lhs);
}

bool operator>(const CString& lhs, const CString& rhs) {
	return strcmp(lhs.str_, rhs.str_) > 0;
}

bool operator>=(const CString& lhs, const CString& rhs) {
	return !(lhs < rhs);
}


CString operator+(const CString& lhs, const CString& rhs) {
	CString ts = lhs;
std::cout <<"operator+\n" << std::flush;
	return ts += rhs;
}

CString& CString::operator+=(const CString& rhs) {
std::cout <<"operator+=\n" << std::flush;
	size_t new_size = size_ + rhs.size_;

	if (new_size + 1 > allocated_size_) {
		allocated_size_ = (new_size + 1) * growth_factor_;
		char* buffer = new char[allocated_size_];

		for (size_t i = 0; i < size_; ++i) {
			buffer[i] = str_[i];
		}

		delete[] str_;
		str_ = buffer;
	}

	for (size_t i = size_; i < new_size; ++i) {
		str_[i] = rhs.str_[i - size_];
	}
	size_ = new_size;
	str_[size_] = '\0';

	return *this;
}


CString operator+(const CString& lhs, const char& c) {
	CString ts = lhs;
	return ts += c;
}

CString& CString::operator+=(const char& c) {
	if (size_ + 2 > allocated_size_) {
		allocated_size_ = (size_ + 2) * growth_factor_;
		char* buffer = new char[allocated_size_];

		for (size_t i = 0; i < size_; ++i) {
			buffer[i] = str_[i];
		}

		delete[] str_;
		str_ = buffer;
	}
	str_[size_] = c;
	++size_;
	str_[size_] = '\0';

	return *this;
}


size_t CString::length() const {
	return size_;
}

bool CString::empty() const {
	return size_ == 0;
}

const char& CString::operator[](size_t ind) const {
	return ind >= 0 && ind < size_ ? str_[ind] : 0;
}

char& CString::operator[](size_t ind) {
	static char dummy;
	dummy = ' ';
	return ind >= 0 && ind < size_ ? str_[ind] : dummy;
}


std::istream& operator>>(std::istream& istr, CString& lhs) {
	char buffer[1024];

	istr.getline(buffer, sizeof(buffer));
	lhs = buffer;

	return istr;
}

std::ostream& operator<<(std::ostream& ostr, const CString& lhs) {
	return ostr << lhs.str_;
}


void swap(size_t& l, size_t& r) {
	size_t tmp = l;
	l = r;
	r = tmp;
}

void swap(CString& lhs, CString& rhs) {
	swap(lhs.size_, rhs.size_);
	swap(lhs.allocated_size_, rhs.allocated_size_);
	std::swap(lhs.str_, rhs.str_);

}
