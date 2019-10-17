#pragma once
#include <numeric>
#include <iomanip>

#include <fstream>
#include <sstream>
#include <iostream>

#include <string>
#include <vector>
#include <map>

#include <chrono>
#include <algorithm>
#include <random>

using std::string;


class Hash {
	typedef uint64_t ull;
private:
	std::vector<ull> CONSTANTS = {
		0xac5722731741b35f, 0xd15ae0dfe36be708, 0xb4716cfb00ef9fa5,
		0xad5721362153a25f, 0xedf51b1025ab4b73, 0xac681f0491e880ae,
		0xb33700731453f351, 0xa3d99386e02723d0, 0xee98570b0a2c86c1,
		0x3e8e98647806517a, 0x00de19b96669720c, 0xd3cf86d079714b44,
		0x3ab798f9f1248a49, 0x933d578a3bac2ffb, 0x49e0b7855b927202,
		0x67fef9cc29c74204, 0x702e6b5e574d655a, 0x2f47c232b8b86784,
		0x089dac586322c74c, 0x86a95888f3f014e4, 0x3b327d4a23aaa8b7,
		0xbf6e921d49a7ae7b, 0xd556deeb73579541, 0x4cb9ee52b2a63d8e,
		0xe9ed6b33d3b9710a, 0xf29580796f345395, 0x7a4505c8a197ab49,
		0xc97e20ebf8d6cb42, 0x5fe3b5eff5d30abd, 0x9f62bc4f16ab5245,
		0x7cd5dbb76e848312, 0xa07daf6f9c2505ca, 0xc4822ae329ca9cd1,
		0xc5d01f43153f2d20, 0xc54531f0354aa018, 0xc9f0b39ac908fd11,
		0x3a51d989537e0489, 0x901a62631a6df60b, 0xe95801897323be5b,
		0x261d0e4b99c152c1, 0xcbc72eccad45232f, 0x39535756c9c9794c,
		0x14c29096b03575e2, 0xc17c4df0a7555d15, 0xe86220710cf46ea9,
		0xe34f865658ef035b, 0xa145c5743dcbf493, 0x8d62f19ed1a06fc8,
		0xfd3f4beecf659bdc, 0x851cb13212500dd1, 0x401e35f75dd1a08c,
		0x34eb30cdc56980f2, 0xff70672fc75af943, 0x7c75fbfe96c08c18,
		0x729838281c6e4304, 0x41a6f782a4fa9d87, 0x657793c6f1f74e3b,
		0xcc3904fc2dcb9191, 0x502e1701e64f61f2, 0xe215194ae13c5ba8,
		0x43a85daaf4a2464a, 0xfe2f11d19727f9ed, 0x3d740254c8093218,
		0xceddca83d62d784d

	};
	std::vector<std::string> input_;
	std::vector<ull> hashedInput_;

	int __getTotal(std::string input) {
		return std::accumulate(input.begin(), input.end(), 0);
	}

	ull _mixA(ull input, ull state) {
		return ((input * state) + (state << 5)) ^ (input >> 3);
	}

	ull _mixB(ull input, ull state) {
		return ((input * state) + (state >> 7)) ^ (input >> 4) + 199873;
	}

public:
	Hash(std::string input) : input_({ input }) {}
	Hash(std::vector<std::string> input_arr) : input_(std::move(input_arr)) {}

	std::vector<ull> getHash() const {
		return hashedInput_;
	}

	void hashInput();
	std::string hash128();


};



void Hash::hashInput() {
	ull A;
	unsigned int j = 0;
	for (const auto& line : input_) {
		A = CONSTANTS[j % 64];
		ull cons = 1;
		for (unsigned int i = 0; i < line.size(); ++i) {
			A = (A * __getTotal(line)) ^ (cons * ull(line[i]) * 76963);
			cons = cons * int(line[i]) % int(1e5 + 1);
		}
		hashedInput_.push_back(_mixA(A, 0xFEEDFACECAFEBEEF));
		++j;
	}
}



template <typename T> std::string n2hexstr(T w, size_t hex_len = sizeof(T) << 1) {
	static const char* digits = "0123456789ABDCEF";
	std::string rc(hex_len, '0');
	for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
	return rc;
}





std::string Hash::hash128() {
	ull A;
	ull B;
	std::stringstream stream;
	string answer;
	unsigned int j = 0;
	for (const auto& line : input_) {
		A = CONSTANTS[j % 64];
		B = CONSTANTS[(j + 2) % 64];
		ull consA = 1;
		ull consB = 2;
		for (unsigned int i = 0; i < line.size(); ++i) {
			A = (A * __getTotal(line)) ^ (consA * ull(line[i]) * 514093);
			consA = consA * int(line[i]) % int(1e5 + 1);

			B = (B * __getTotal(line)) ^ (consB * ull(line[i]) * 321571);
			consB = consB * int(line[i]) % int(1e5 + 1);
		}
		ull block_1 = _mixA(A, 0xFEEDFACECAFEBEEF);
		ull block_2 = _mixB(B, 0xBADC0FFEE0DDF00D);

		//answer = n2hexstr(block_1, block_2, 20);
		
		stream << std::setfill('0') << std::setw(sizeof(uint64_t) * 2) <<
			std::hex << (block_1 | 0);

		stream << std::setfill('0') << std::setw(sizeof(uint64_t) * 2) <<
			std::hex << (block_2 | 0);
		++j;
	}

	return stream.str();
}




std::string hash128(std::string input)  {
	Hash hash{ input };
	return hash.hash128();
}




