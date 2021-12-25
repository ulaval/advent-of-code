// AoC_2021_24

#include <array>
#include <cassert>
#include <iostream>
#include <vector>

using std::size_t, std::cout, std::cerr, std::string, std::vector, std::array;

template <typename T, typename... Ts>
bool is_any_of(T&& t, Ts&&... ts)
{
	return ((t == ts) || ...);
}

uint64_t g_model_number = 0;
int g_current_digit = 13;
int g_next_input = 0;		// forces an input value

struct instruction {
	string name;
	char op1;
	char op2;
	int value;
};

using registers = array<int64_t, 4>;

std::ostream& operator<<(std::ostream& out, const registers& r)
{
	out << "[ w=" << r[0] << ", x=" << r[1] << ", y=" << r[2] << ", z=" << r[3] << " ]";
	return out;
}

auto read_input(std::istream& in) {
	instruction i{};
	array<vector<instruction>, 14> code_segments{};
	int current_segment = 14;
    while (in >> i.name) {
		assert(is_any_of(i.name, "inp", "add", "mul", "div", "mod", "eql"));
		i.op2 = '\0';
		i.value = 0;
		in >> i.op1;
		assert(is_any_of(i.op1, 'w', 'x', 'y', 'z'));
		if (i.name != "inp") {
			string s;
			in >> s;
			if (is_any_of(s[0], 'w', 'x', 'y', 'z'))
				i.op2 = s[0];
			else
				i.value = std::stoi(s);
		}
		else current_segment--;
		code_segments[current_segment].push_back(i);
	}
	return code_segments;
}

constexpr uint64_t intpow(int base, int exp) {
	assert(base > 1 && exp >= 0);
	uint64_t pow = 1;
	for (int i=0; i<exp; i++)
		pow *= base;
	return pow;
}

int input() {
	assert(g_current_digit >= 0 && g_current_digit < 14);
	assert(g_model_number >= 11111111111111);
	assert(g_next_input >= 0);
	if (g_next_input > 0)
		return g_next_input;
	int digit = (g_model_number/intpow(10, g_current_digit)) % 10;
	g_current_digit--;
	return digit;
}

void execute(registers& r, const instruction& i) {
	if (i.name == "inp") {
		r[i.op1-'w'] = input();
	}
	else if (i.name == "add") {
		r[i.op1-'w'] += (i.op2 == '\0') ? i.value : r[i.op2-'w'];
	}
	else if (i.name  == "mul") {
		r[i.op1-'w'] *= (i.op2 == '\0') ? i.value : r[i.op2-'w'];
	}
	else if (i.name == "div") {
		assert((i.op2 == '\0' && i.value != 0) || (i.op2 != '\0' && r[i.op2-'w'] != 0));
		r[i.op1-'w'] /= (i.op2 == '\0') ? i.value : r[i.op2-'w'];
	}
	else if (i.name == "mod") {
		assert(r[i.op1-'w'] >= 0);
		assert((i.op2 == '\0' && i.value > 0) || (i.op2 != '\0' && r[i.op2-'w'] > 0));
		r[i.op1-'w'] %= (i.op2 == '\0') ? i.value : r[i.op2-'w'];
	}
	else {
		assert(i.name == "eql");
		if (i.op2 == '\0')
			r[i.op1-'w'] = (r[i.op1-'w'] == i.value) ? 1 : 0;
		else
			r[i.op1-'w'] = (r[i.op1-'w'] == r[i.op2-'w']) ? 1 : 0;
	}
}

void run_code(registers& r, const vector<instruction>& code) {
	for (const auto& instr : code)
		execute(r, instr);
}

int main() {

    const auto code_segments = read_input(std::cin);

    // Part 1
    {
		g_model_number = 99999999999999;
		g_current_digit = 13;
		g_next_input = 0;
		long loops = 0, step = 0;
		while (++loops) {
			registers r{};
			for (int s=13; s>=0; s--)
				run_code(r, code_segments[s]);
			if (r['z'-'w'] == 0) {
				cerr << g_model_number << '\n';
				break;
			}
			if (++step == 100'000'000) {
				cerr << "still looping... " << loops << '\n';
				step = 0;
			}
			g_model_number--;
			g_current_digit = 13;
		}
    }

    // Part 2
    {

    }
}
