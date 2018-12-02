#pragma once


#include <string>
#include <vector>


class Exception {
public:
	Exception(const std::string& msg);
	std::string what() const;
private:
	std::string message_;
};


using byte = unsigned char;


class Encoder {
public:
	static Encoder& instance();

	std::string encode(const std::string&);
	std::string encode(const std::wstring&);
	std::string encode(const std::vector<byte>&);
	std::string encode(const byte*, size_t);

	Encoder(const Encoder&) = delete;
	Encoder& operator=(const Encoder&) = delete;
private:
	Encoder();
};


class Decoder {
public:
	static Decoder& instance();

	std::string decodeToASCII(const std::string&);
	std::wstring decodeToUTF(const std::string&);

	Decoder(const Decoder&) = delete;
	Decoder& operator=(const Decoder&) = delete;
private:
	Decoder();
};