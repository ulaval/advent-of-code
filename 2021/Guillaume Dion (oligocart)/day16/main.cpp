// AoC_2021_16

#include <iostream>
#include <vector>
#include <limits>

using std::size_t, std::cout, std::string, std::vector, std::string_view;

string hex2bin(char hex_char) {
	switch (hex_char) {
		case '0': return "0000";
		case '1': return "0001";
		case '2': return "0010";
		case '3': return "0011";
		case '4': return "0100";
		case '5': return "0101";
		case '6': return "0110";
		case '7': return "0111";
		case '8': return "1000";
		case '9': return "1001";
		case 'A': return "1010";
		case 'B': return "1011";
		case 'C': return "1100";
		case 'D': return "1101";
		case 'E': return "1110";
		case 'F': return "1111";
	}
	throw std::logic_error{"Duh?"};
}

using value_t = unsigned long;
struct packet {
	value_t version;
	value_t type_id;
	vector<packet> subpacket;
	value_t literal;
};

value_t value(const string_view bits) {
	auto result = value_t{0};
	const auto size = static_cast<int>(bits.size());
	for (int i=size-1, b=0; i>=0; i--, b++)
		result += static_cast<value_t>(bits[i]-'0') << b;
	return result;
}

value_t parse_literal(packet& p, const string_view bits) {
	int i = 0;
	string value_bits{bits.substr(1, 4)};
	while (bits[i] == '1') {
		i += 5;
		value_bits.append(bits.substr(i+1, 4));
	}
	p.literal = value(value_bits);
	return value_bits.size()/4*5;	// bits processed
}

value_t parse_packet(packet& p, const string_view bits);

value_t parse_operator(packet& p, const string_view bits) {
	auto bits_processed = value_t{0};
	if (bits[0] == '0') {
		// length type ID 0 : 15-bits representing the total length in bits of the sub-packets contained.
		const auto sp_length = value(bits.substr(1, 15));
		while (bits_processed < sp_length) {
			p.subpacket.emplace_back();
			bits_processed += parse_packet(p.subpacket.back(), bits.substr(16+bits_processed));
		}
		return bits_processed + 16;
	}
	else {
		// length type ID 1 : 11-bit representing the number of sub-packets immediately contained.
		const auto sp_count = value(bits.substr(1, 11));
		auto sp_processed = value_t{0};
		while (sp_processed++ < sp_count) {
			p.subpacket.emplace_back();
			bits_processed += parse_packet(p.subpacket.back(), bits.substr(12+bits_processed));
		}
		return bits_processed + 12;
	}
}

value_t parse_packet(packet& p, const string_view bits) {
	p.version = value(bits.substr(0, 3));
	p.type_id = value(bits.substr(3, 3));
	const auto payload = bits.substr(6);
	if (p.type_id == 4)
		return 6 + parse_literal(p, payload);
	else
		return 6 + parse_operator(p, payload);
}

value_t sum_versions(const packet& p) {
	auto sum = p.version;
	for (const auto& s : p.subpacket)
		sum += sum_versions(s);
	return sum;
}

value_t eval_packet(const packet& p) {
	auto v = value_t{0};
	const auto& sub = p.subpacket;
	switch (p.type_id) {
	case 0:	// +
		std::for_each(sub.cbegin(), sub.cend(), [&v](const auto& s){ v += eval_packet(s); });
		break;
	case 1:	// *
		v++;
		std::for_each(sub.cbegin(), sub.cend(), [&v](const auto& s){ v *= eval_packet(s); });
		break;
	case 2:	// min()
		v = std::numeric_limits<value_t>::max();
		std::for_each(sub.cbegin(), sub.cend(), [&v](const auto& s){ v = std::min(v, eval_packet(s)); });
		break;
	case 3:	// max()
		v = std::numeric_limits<value_t>::min();
		std::for_each(sub.cbegin(), sub.cend(), [&v](const auto& s){ v = std::max(v, eval_packet(s)); });
		break;
	case 4:	// literal
		v = p.literal;
		break;
	case 5:	// >
		v = (eval_packet(sub[0]) > eval_packet(sub[1])) ? 1 : 0;
		break;
	case 6:	// <
		v = (eval_packet(sub[0]) < eval_packet(sub[1])) ? 1 : 0;
		break;
	case 7:	// ==
		v = (eval_packet(sub[0]) == eval_packet(sub[1])) ? 1 : 0;
		break;
	}
	return v;
}

int main() {
	string hex_val;
	std::getline(std::cin, hex_val);
	string bits;
	for (const auto c : hex_val)
		bits.append(hex2bin(c));

	packet p{};
	parse_packet(p, bits);
	cout << "Part 1 answer = " << sum_versions(p) << '\n';
	cout << "Part 2 answer = " << eval_packet(p) << '\n';
}
