#pragma once

#include <iostream>


class CString {
public:
	CString();
	CString(const char*);

	CString(const CString&);
	CString& operator=(const CString&);
	
	CString(CString&&);
	CString& operator=(CString&&);

	~CString();


	friend bool operator==(const CString&, const CString&);
	friend bool operator!=(const CString&, const CString&);
	friend bool operator<(const CString&, const CString&);
	friend bool operator<=(const CString&, const CString&);
	friend bool operator>(const CString&, const CString&);
	friend bool operator>=(const CString&, const CString&);


	friend CString operator+(const CString&, const CString&);
	CString& operator+=(const CString&);
	
	friend CString operator+(const CString&, const char&);
	CString& operator+=(const char&);
	

	size_t length() const;
	bool empty() const;
	const char& operator[](size_t) const;
	char& operator[](size_t);

	friend std::istream& operator>>(std::istream&, CString&);
	friend std::ostream& operator<<(std::ostream& , const CString&);

	friend void swap(CString&, CString&);
private:
	static const int growth_factor_ = 2;
	//static const int buf_size_ = 16;
	size_t size_ = 0;
	size_t allocated_size_ = 0;
	//char buf_[buf_size_];
	char* str_ = nullptr;
};