#include <fstream>
#include <iostream>

void copy(size_t size, int * old_arr, int * new_arr)
{
  for (const int * i = old_arr; i != size + old_arr; i++) {
    *new_arr = *i;
    new_arr++;
  }
}

int * extendArr(size_t n, size_t m, size_t size, int * arr)
{
  int * new_arr = new int[size + n * m+ 2];
  copy(size, arr, new_arr);
  delete [] arr;
  return new_arr;
}

void outputArr(int * arr, size_t size, std::ofstream & output)
{
  size_t p = 0;
  while (p < size) {
    output << ' ' << arr[p++];
  }
  output << '\n';
}

void lft_bot_cnt(int * arr, const long long n, const long long m, const size_t orig_m, size_t p, size_t k)
{
  if (n <= 0 || m <= 0) {
    return;
  }
  for (long long i = 0; i < m; i++) {
    arr[p] += k;
    k++;
    p++;
  }
  p--;
  for (long long i = 0; i < n - 1; i++) {
    p -= orig_m;
    arr[p] += k;
    k++;
  }
  for (long long i = 0; i < m - 1; i++) {
    p--;
    arr[p] += k;
    k++;
  }
  for (long long i = 0; i < n - 2; i++) {
    p += orig_m;
    arr[p] += k;
    k++;
  }
  lft_bot_cnt(arr, n - 2, m - 2, orig_m, ++p, k);
}

void fll_inc_wav(int * arr, const long long n, const long long m, const size_t orig_m, size_t p, size_t k)
{
  if (n <= 0 || m <= 0) {
    return;
  }
  for (long long i = 0; i < m; i++) {
    arr[p] += k;
    p++;
  }
  p--;
  for (long long i = 0; i < n - 1; i++) {
    p += orig_m;
    arr[p] += k;
  }
  for (long long i = 0; i < m - 1; i++) {
    p--;
    arr[p] += k;
  }
  for (long long i = 0; i < n - 2; i++) {
    p -= orig_m;
    arr[p] += k;
  }
  fll_inc_wav(arr, n - 2, m - 2, orig_m, ++p, ++k);
}

int main(int argc, char ** argv)
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

  if (argv[1][0] == '1' && argv[1][1] == '\0') {
    int arr[10000] = {0};
    size_t n = 0, m = 0, p = 0, cnt = 0;

    while (input >> n >> m) {
      arr[p++] = n;
      arr[p++] = m;
      for (size_t i = 0; i < n * m; i++) {
        if (!(input >> arr[p++])) {
          std::cerr << "Bad input" << '\n';
          return 2;
        }
      }
      cnt++;
    }

    if (!input.eof()) {
      std::cerr << "Bad input" << '\n';
      return 2;
    }

    int matrix[10000] = {0};
    p = 0;
    for (size_t i = 0; i < cnt; i++) {
      n = arr[p++];
      m = arr[p++];
      copy(n * m, arr + p, matrix);
      p += n * m;

      lft_bot_cnt(matrix, static_cast<long long>(n), static_cast<long long>(m), m, (n-1)*m, 1);

      output << n << ' ' << m;
      outputArr(matrix, n * m, output);
    }
    p = 0;
    for (size_t i = 0; i < cnt; i++) {
      n = arr[p++];
      m = arr[p++];
      copy(n * m, arr + p, matrix);
      p += n * m;

      fll_inc_wav(matrix, static_cast<long long>(n), static_cast<long long>(m), m, 0, 1);

      output << n << ' ' << m;
      outputArr(matrix, n*m, output);
    }
  } else if (argv[1][0] == '2' && argv[1][1] == '\0') {
    int * arr = nullptr;
    size_t n = 0, m = 0, p = 0, cnt = 0;

    while (input >> n >> m) {
      try {
        arr = extendArr(n, m, p, arr);
      } catch (std::bad_alloc &) {
        std::cerr << "Bad alloc" << '\n';
        delete [] arr;
        return 2;
      }

      arr[p++] = n;
      arr[p++] = m;

      for (size_t i = 0; i < n * m; i++) {
        if (!(input >> arr[p++])) {
          std::cerr << "Bad input" << '\n';
          delete [] arr;
          return 2;
        }
      }
      cnt++;
    }

    if (!input.eof()) {
      std::cerr << "Bad input" << '\n';
      delete [] arr;
      return 2;
    }

    int * matrix = nullptr;
    p = 0;
    for (size_t i = 0; i < cnt; i++) {
      n = arr[p++];
      m = arr[p++];
      try {
        matrix = new int[n*m];
      } catch (const std::bad_alloc &) {
        std::cerr << "Bad alloc" << '\n';
        delete [] arr;
        return 2;
      }
      copy(n*m, arr+p, matrix);
      p += n*m;

      lft_bot_cnt(matrix, static_cast<long long>(n), static_cast<long long>(m), m, (n-1)*m, 1);

      output << n << ' ' << m;
      outputArr(matrix, n*m, output);
      delete [] matrix;
    }

    p = 0;
    for (size_t i = 0; i < cnt; i++) {
      n = arr[p++];
      m = arr[p++];
      try {
        matrix = new int[n*m];
      } catch (const std::bad_alloc &) {
        std::cerr << "Bad alloc" << '\n';
        delete [] arr;
        return 2;
      }
      copy(n*m, arr+p, matrix);
      p += n*m;

      fll_inc_wav(matrix, static_cast<long long>(n), static_cast<long long>(m), m, 0, 1);

      output << n << ' ' << m;
      outputArr(matrix, n*m, output);
      delete [] matrix;
    }

    delete [] arr;
  }
  else {
    if (argv[1][0] >= '0' && argv[1][0] <= '9') {
      std::cerr << "First parameter is out of range" << '\n';
    } else {
      std::cerr << "First parameter is not a number" << '\n';
    }
    return 1;
  }

  return 0;
}
