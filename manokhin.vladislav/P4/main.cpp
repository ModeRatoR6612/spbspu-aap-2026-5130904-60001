#include <iostream>

namespace manokhin {
  constexpr size_t INITIAL_SIZE = 1;
  constexpr int COEFFICIENT = 10;

  char * extendStr(const char * str, size_t &size, const int k = COEFFICIENT) {
    char * new_str = static_cast<char *>(malloc((size + k) * sizeof(char)));
    if (new_str == nullptr) {
      std::cerr << "Bad alloc";
      throw std::bad_alloc();
    }

    for (size_t i = 0; i < size; ++i) {
      new_str[i] = str[i];
    }

    size += k;
    return new_str;
  }

  int seq_sym(const char * str, const size_t size) {
    for (size_t i = 1; i < size; ++i) {
      if (str[i] == str[i-1]) {
        return 1;
      }
    }
    return 0;
  }
}


using namespace manokhin;

int main() {
  size_t size = INITIAL_SIZE, p = 0, cap = INITIAL_SIZE;
  char * str = static_cast<char *>(malloc(size * sizeof(char)));

  if (str == nullptr) {
    std::cerr << "Bad alloc";
    return 2;
  }

  char ch = ' ';
  std::cin >> std::noskipws;

  while (std::cin >> ch && ch != '\n') {
    if (size < cap+1) {
      try {
        char * new_str = extendStr(str, cap);
        free(str);
        str = new_str;
      } catch (const std::bad_alloc &) {
        std::cerr << "Bad alloc";
        return 1;
      }
    }

    str[p++] = ch;
    size++;
  }

  if (!std::cin) {
    std::cerr << "Bad input";
    return 1;
  }

  std::cout << seq_sym(str, size);

  // for (size_t i = 0; i < size; i++) {
  //   std::cout << str[i];
  // }

  free(str);
  std::cout << '\n';
  return 0;
}
