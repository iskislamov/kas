#include "base64.h"
#include "utf8.h"
#include <sstream>


static const int ASCII = 256;

static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


inline void decode_utf8(const std::string& bytes, std::wstring& wstr) {
	utf8::utf8to32(bytes.begin(), bytes.end(), std::back_inserter(wstr));
}

inline void encode_utf8(const std::wstring& wstr, std::string& bytes) {
	utf8::utf32to8(wstr.begin(), wstr.end(), std::back_inserter(bytes));
}


Exception::Exception(const std::string& message) {
	message_ = message;
}

std::string Exception::what() const { 
	return message_;
}


Encoder::Encoder() {}

Encoder& Encoder::instance() {
	static Encoder e;
	return e;
}

std::string Encoder::encode(const std::string& str) {
	if (str.size() == 0) {
		return "";
	}

	std::vector<byte> data(str.size());
	for (int i = 0; i < str.size(); ++i) {
		data[i] = str[i];
	}
	return encode(&data[0], str.size());
}

std::string Encoder::encode(const std::wstring& wstr) {
	std::string str;
	encode_utf8(wstr, str);
	return encode(str);
}

std::string Encoder::encode(const std::vector<byte>& data) {
	return encode(&data[0], data.size());
}

std::string Encoder::encode(const byte* data, size_t size) {
	std::stringstream stream;
	size_t stream_size = 0;
	int value = 0;
	int shift = -6;

	for (size_t i = 0; i < size; ++i) {
		byte curr = *(data + i);
		value = (value << 8) + curr;
		shift += 8;

		while (shift >= 0) {
			stream << base64_chars[(value >> shift) & 0x3F];
			++stream_size;
			shift -= 6;
		}
	}

	if (shift > -6) {
		stream << base64_chars[((value << 8) >> (shift + 8)) & 0x3F];
		++stream_size;
	}

	while (stream_size % 4) {
		stream << '=';
		++stream_size;
	}

	return stream.str();
}


Decoder::Decoder() {}

Decoder& Decoder::instance() {
	static Decoder d;
	return d;
}

std::string Decoder::decodeToASCII(const std::string& encoded_string) {
	std::stringstream stream;
	std::vector<int> alphabet(ASCII, -1);
	int value = 0;
	int shift = -8;

	for (size_t i = 0; i < base64_chars.size(); ++i) {
		alphabet[base64_chars[i]] = i;
	}

	for (size_t i = 0; i < encoded_string.size() && encoded_string[i] != '='; ++i) {
		byte c = encoded_string[i];

		if (alphabet[c] == -1) {
			throw new Exception("Not a BASE64 string");
		}

		value = (value << 6) + alphabet[c];
		shift += 6;

		if (shift >= 0) {
			stream << (char((value >> shift) & 0xFF));
			shift -= 8;
		}
	}
	return stream.str();
}

std::wstring Decoder::decodeToUTF(const std::string& encoded_string) {
	std::wstring wstr;
	decode_utf8(decodeToASCII(encoded_string), wstr);
	return wstr;
}