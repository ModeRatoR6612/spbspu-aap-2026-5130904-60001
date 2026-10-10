#include <iostream>

int main()
{
  int prev = 0;
  std::cin >> prev;

  if (!std::cin) {
    std::cerr << "Unexpected input" << '\n';
    return 1;
  }

  if (prev == 0) {
    std::cerr << "No sequence" << '\n';
    return 2;
  }

  int a = 0;
  std::cin >> a;

  if (!std::cin) {
    std::cerr << "Unexpected input" << '\n';
    return 1;
  }

  if (a == 0) {
    std::cout << 0 << '\n' << 0 << '\n';
    return 0;
  }
  int fath = 0;
  std::cin >> fath;

  if (!std::cin) {
    std::cerr << "Unexpected input" << '\n';
    return 1;
  }

  int mn = 0;
  int grt = 0;
  while (fath != 0) {
    if (a < prev && a < fath) {
      mn++;
    }
    if (a < prev && a > fath) {
      grt++;
    }

    prev = a;
    a = fath;
    std::cin >> fath;

    if (!std::cin) {
      std::cerr << "Unexpected input" << '\n';
      return 1;
    }
  }
  std::cout << mn << '\n';
  std::cout << grt << '\n';
  return 0;
}
