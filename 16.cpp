#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <tuple>
#include <vector>
#include <limits>

using namespace std;

const char *hex_char_to_bin(char c) {
  switch (toupper(c)) {
  case '0':
    return "0000";
  case '1':
    return "0001";
  case '2':
    return "0010";
  case '3':
    return "0011";
  case '4':
    return "0100";
  case '5':
    return "0101";
  case '6':
    return "0110";
  case '7':
    return "0111";
  case '8':
    return "1000";
  case '9':
    return "1001";
  case 'A':
    return "1010";
  case 'B':
    return "1011";
  case 'C':
    return "1100";
  case 'D':
    return "1101";
  case 'E':
    return "1110";
  case 'F':
    return "1111";
  default:
    throw invalid_argument("Unrecognized char");
  }
}

std::string hex_str_to_bin_str(const std::string &hex) {
  std::string bin;
  for (auto c : hex) {
    bin += hex_char_to_bin(c);
  }
  return bin;
}

// Returns the final number, count of consumed bits, and the version sum
tuple<unsigned long long, int, int> interpret_bit_str(const string &bit_str) {
  const auto version = std::stoi(bit_str.substr(0, 3), 0, 2);
  const auto type_id = std::stoi(bit_str.substr(3, 3), 0, 2);
  int consumed = 6;
  if (type_id == 4) {
    unsigned i = 6;
    string num_string;
    while (true) {
      consumed += 5;
      num_string += bit_str.substr(i + 1, 4);
      if (bit_str[i] == '0') {
        break;
      }
      i += 5;
    }
    const auto num = std::stoull(num_string, 0, 2);
    return {num, consumed, version};
  } else {
    const auto length_type_id = bit_str[6];
    int version_sum = version;
    vector<unsigned long long> values;
    if (length_type_id == '0') {
      auto bits_to_consume = std::stoi(bit_str.substr(7, 15), 0, 2);
      consumed += 16 + bits_to_consume;
      int i = 22;
      while (bits_to_consume > 0) {
        const auto[n, c, vs] = interpret_bit_str(bit_str.substr(i));
        i += c;
        bits_to_consume -= c;
        version_sum += vs;
        values.push_back(n);
      }
      if (bits_to_consume < 0) {
        throw runtime_error("Can't consume too many bits");
      }
    } else {
      auto packets_to_consume = std::stoi(bit_str.substr(7, 11), 0, 2);
      consumed += 12;
      int i = 18;
      while (packets_to_consume > 0) {
        const auto[n, c, vs] = interpret_bit_str(bit_str.substr(i));
        i += c;
        consumed += c;
        packets_to_consume--;
        version_sum += vs;
        values.push_back(n);
      }
    }
    unsigned long long num;
    if (type_id == 0) {
      num = 0;
      for (const auto &v : values) {
        num += v;
      }
    } else if (type_id == 1) {
      num = 1;
      for (const auto &v : values) {
        num *= v;
      }
    } else if (type_id == 2) {
      num = std::numeric_limits<unsigned long long>::max();
      for (const auto &v : values) {
        if (v < num) {
          num = v;
        }
      }
    } else if (type_id == 3) {
      num = 0;
      for (const auto &v : values) {
        if (v > num) {
          num = v;
        }
      }
    } else if (type_id == 5) {
      if (values.size() != 2) {
        throw runtime_error("Unexpected values size");
      }
      if (values[0] > values[1]) {
        num = 1;
      } else {
        num = 0;
      }
    } else if (type_id == 6) {
      if (values.size() != 2) {
        throw runtime_error("Unexpected values size");
      }
      if (values[0] < values[1]) {
        num = 1;
      } else {
        num = 0;
      }
    } else if (type_id == 7) {
      if (values.size() != 2) {
        throw runtime_error("Unexpected values size");
      }
      if (values[0] == values[1]) {
        num = 1;
      } else {
        num = 0;
      }
    } else {
      throw runtime_error("Unexpected type_id");
    }
    return {num, consumed, version_sum};
  }
}

int main() {
  ifstream ifs("input/16.txt");
  string hex_str;
  ifs >> hex_str;
  const auto bit_str = hex_str_to_bin_str(hex_str);
  const auto [n, _, vs] = interpret_bit_str(bit_str);
  cout << vs << endl;
  cout << n << endl;
}