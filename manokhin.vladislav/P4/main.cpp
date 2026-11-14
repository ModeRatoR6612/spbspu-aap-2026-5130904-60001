#include <iostream>

namespace manokhin {
  constexpr size_t INITIAL_SIZE = 1;
  constexpr int COEFFICIENT = 10;
  constexpr size_t SIZE2 = 6;
  constexpr char STR2[6] = {'a', 'b', 'c', '_', 'e', 'f'};

  char *extendStr(const char *str, size_t &size, const int k = COEFFICIENT)
  {
    char *const new_str = static_cast< char * >(malloc((size + k) * sizeof(char)));
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

  int seqSym(const char *str, const size_t size) noexcept
  {
    for (size_t i = 1; i < size; ++i) {
      if (str[i] == str[i - 1]) {
        return 1;
      }
    }
    return 0;
  }

  char *uncSym(
      const char *str, const size_t &size, const char *str2, const size_t &size2, char *res, size_t &p) noexcept
  {
    bool is_found = false;
    for (size_t i = 0; i < size; ++i) {
      is_found = false;
      for (size_t j = 0; j < size2; ++j) {
        if (str[i] == str2[j]) {
          is_found = true;
          break;
        }
      }
      if (!is_found) {
        res[p++] = str[i];
      }
    }
    for (size_t i = 0; i < size2; ++i) {
      is_found = false;
      for (size_t j = 0; j < size; ++j) {
        if (str2[i] == str[j]) {
          is_found = true;
          break;
        }
      }
      if (!is_found) {
        res[p++] = str2[i];
      }
    }
    return res;
  }
}

using namespace manokhin;

int main()
{
  size_t size = INITIAL_SIZE, p = 0, cap = INITIAL_SIZE;
  char *str = static_cast< char * >(malloc(size * sizeof(char)));

  if (str == nullptr) {
    std::cerr << "Bad alloc";
    return 1;
  }

  char ch = ' ';
  std::cin >> std::noskipws;

  while (std::cin >> ch && ch != '\n') {
    if (p >= cap) {
      try {
        char *const new_str = extendStr(str, cap);
        free(str);
        str = new_str;
      } catch (const std::bad_alloc &) {
        std::cerr << "Bad alloc";
        return 1;
      }
    }

    str[p++] = ch;
  }

  if (!std::cin) {
    std::cerr << "Bad input";
    free(str);
    return 1;
  }
  size = p;

  std::cout << seqSym(str, size) << '\n';

  if (char *buf = static_cast< char * >(malloc((size + SIZE2) * sizeof(char)))) {
    p = 0;
    buf = uncSym(str, size, STR2, SIZE2, buf, p);

    for (size_t i = 0; i < p; i++) {
      std::cout << buf[i];
    }

    free(buf);
  } else {
    std::cerr << "Bad alloc";
    free(str);
    return 1;
  }

  free(str);
  std::cout << '\n';
  return 0;
}
