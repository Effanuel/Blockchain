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


class Hash {
	typedef uint64_t ull;
private:
	std::vector<ull> CONSTANTS = {
		0xac5722731741b35f, 0xd15ae0dfe36be708, 0xb4716cfb00ef9fa5,
		0xad5721362153a25f, 0xedf51b1025ab4b73, 0xac681f0491e880ae,
		0xb33700731453f351, 0xa3d99386e02723d0, 0xee98570b0a2c86c1
	};
	std::vector<std::string> input_;
	std::vector<ull> hashedInput_;

	int __getTotal(std::string input) {
		return std::accumulate(input.begin(), input.end(), 0);
	}

	ull _mix(ull input, ull state) {
		return ((input * state) + (state << 5)) ^ (input >> 3);
	}

public:
	Hash(std::string input) : input_({ input }) {}
	Hash(std::vector<std::string> input_arr) : input_(std::move(input_arr)) {}

	std::vector<ull> getHash() const {
		return hashedInput_;
	}
	ull stringToHex(std::string input) {
		return std::stoll(input, 0, 0);
	}


	void hashInput() {
		ull A;
		unsigned int j = 0;
		for (const auto& line : input_) {
			A = CONSTANTS[j % 8];
			ull cons = 1;
			for (unsigned int i = 0; i < line.size(); ++i) {
				A = (A * __getTotal(line)) ^ (cons * ull(line[i]) * 76963);
				cons = cons * int(line[i]) % int(1e5 + 1);
			}
			hashedInput_.push_back(_mix(A, 0xFEEDFACECAFEBEEF));
			++j;
		}
	}
};

std::string hash64(std::string input) {
	Hash hash{ input };
	hash.hashInput();

	std::stringstream stream;
	stream <<
		std::setfill('0') << std::setw(sizeof(uint64_t) * 2) <<
		std::hex << hash.getHash()[0];
	return stream.str();
}




