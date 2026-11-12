#include <fstream>
#include <iostream>

namespace manokhin {
  constexpr size_t MAX_SIZE = 10000;

  void copy(const size_t size, const int *old_arr, int *new_arr)
  {
    for (const int *i = old_arr; i != size + old_arr; i++) {
      *new_arr = *i;
      new_arr++;
    }
  }

  int *extendArr(const size_t n, const size_t m, const size_t size, const int *arr)
  {
    int *const new_arr = new int[size + n * m + 2];
    copy(size, arr, new_arr);
    return new_arr;
  }

  std::ofstream &outputMatrix(std::ofstream &output, const int *arr, const size_t n, const size_t m)
  {
    size_t p = 0;
    output << n << ' ' << m;
    while (p < n * m) {
      output << ' ' << arr[p++];
    }
    return output;
  }

  void lftBotCnt(int *arr, size_t n, size_t m, size_t orig_m, size_t p, size_t k)
  {
    if (n <= 0 || m <= 0) {
      return;
    }
    for (size_t i = 0; i < m; i++) {
      arr[p] += k;
      k++;
      p++;
    }
    if (n == 1) {
      return;
    }
    p--;
    for (size_t i = 0; i < n - 1; i++) {
      p -= orig_m;
      arr[p] += k;
      k++;
    }
    if (m == 1) {
      return;
    }
    for (size_t i = 0; i < m - 1; i++) {
      p--;
      arr[p] += k;
      k++;
    }
    for (size_t i = 0; i < n - 2; i++) {
      p += orig_m;
      arr[p] += k;
      k++;
    }
    if (n <= 2 && m <= 2) {
      return;
    }
    lftBotCnt(arr, n - 2, m - 2, orig_m, ++p, k);
  }

  void fllIncWav(int *arr, size_t n, size_t m, size_t orig_m, size_t p, size_t k)
  {
    if (n == 0 || m == 0) {
      return;
    }
    for (size_t i = 0; i < m; i++) {
      arr[p] += k;
      p++;
    }
    if (n == 1) {
      return;
    }
    p--;
    for (size_t i = 0; i < n - 1; i++) {
      p += orig_m;
      arr[p] += k;
    }
    if (m == 1) {
      return;
    }
    for (size_t i = 0; i < m - 1; i++) {
      p--;
      arr[p] += k;
    }
    for (size_t i = 0; i < n - 2; i++) {
      p -= orig_m;
      arr[p] += k;
    }
    if (n <= 2 && m <= 2) {
      return;
    }
    fllIncWav(arr, n - 2, m - 2, orig_m, ++p, ++k);
  }
}

int main(int argc, char **argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments" << '\n';
    return 1;
  }
  if (argc > 4) {
    std::cerr << "Too many arguments" << '\n';
    return 1;
  }

  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);

  if (!input.is_open()) {
    std::cerr << "Cannot open input file" << '\n';
    return 2;
  }
  if (!output.is_open()) {
    std::cerr << "Cannot open output file" << '\n';
    return 2;
  }

  const char par = argv[1][0];

  if ((par != '1' && par != '2') || argv[1][1] != '\0') {
    if (par >= '0' && par <= '9') {
      std::cerr << "First parameter is out of range" << '\n';
    } else {
      std::cerr << "First parameter is not a number" << '\n';
    }
    return 1;
  }

  size_t p = 0, cnt = 0, n = 0, m = 0;
  int *dyn_arr = nullptr;
  int *arr = dyn_arr;
  int fix_arr[manokhin::MAX_SIZE] = {0};

  if (par == '1') {
    arr = fix_arr;
  }

  bool is_data = false;

  while (input >> n >> m) {
    is_data = true;
    if (par == '2') {
      try {
        int *const new_arr = manokhin::extendArr(n, m, p, arr);
        delete[] dyn_arr;
        dyn_arr = new_arr;
        arr = dyn_arr;
      } catch (std::bad_alloc &) {
        std::cerr << "Bad alloc" << '\n';
        delete[] dyn_arr;
        return 2;
      }
    }

    arr[p++] = n;
    arr[p++] = m;

    for (size_t i = 0; i < n * m; i++) {
      if (!(input >> arr[p++])) {
        std::cerr << "Bad input" << '\n';
        delete[] dyn_arr;
        return 2;
      }
    }
    cnt++;
  }

  if (!input.eof() || !is_data) {
    std::cerr << "Bad input" << '\n';
    delete[] dyn_arr;
    return 2;
  }

  p = 0;
  int *dyn_matrix = nullptr;
  int *matrix = dyn_matrix;
  int static_matrix[manokhin::MAX_SIZE] = {0};
  if (par == '1') {
    matrix = static_matrix;
  }

  for (size_t i = 0; i < cnt; i++) {
    n = arr[p++];
    m = arr[p++];

    if (par == '2') {
      try {
        dyn_matrix = new int[n * m];
        matrix = dyn_matrix;
      } catch (const std::bad_alloc &) {
        std::cerr << "Bad alloc" << '\n';
        delete[] dyn_arr;
        return 2;
      }
    }

    manokhin::copy(n * m, arr + p, matrix);
    p += n * m;

    manokhin::lftBotCnt(matrix, n, m, m, (n - 1) * m, 1);

    manokhin::outputMatrix(output, matrix, n, m);
    output << '\n';

    delete[] dyn_matrix;
  }

  p = 0;

  for (size_t i = 0; i < cnt; i++) {
    n = arr[p++];
    m = arr[p++];

    if (par == '2') {
      try {
        dyn_matrix = new int[n * m];
        matrix = dyn_matrix;
      } catch (const std::bad_alloc &) {
        std::cerr << "Bad alloc" << '\n';
        delete[] dyn_arr;
        return 2;
      }
    }

    manokhin::copy(n * m, arr + p, matrix);
    p += n * m;

    manokhin::fllIncWav(matrix, n, m, m, 0, 1);

    manokhin::outputMatrix(output, matrix, n, m);
    output << '\n';

    delete[] dyn_matrix;
  }

  delete[] dyn_arr;

  return 0;
}
