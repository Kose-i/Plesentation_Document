#include <iostream>
#include <vector>
#include <cmath>

constexpr double p_error {0.01};
constexpr double p_find {1/3.0};

std::vector<std::vector<double>> dataset(int n_count) {
  std::vector<std::vector<double>> table(2,std::vector<double>(2));
  table[0][0] = p_error*std::pow(p_find, n_count);
  table[0][1] = (1-p_error)*std::pow(p_find, n_count);
  table[1][0] = p_error*(1 - std::pow(p_find, n_count));
  table[1][1] = (1-p_error)*(1-std::pow(p_find, n_count));
  return table;
}

int main(int argc, char** argv) {
  auto t = dataset(1);
  for (const auto e : t) {
    for (const auto& f : e) {
      std::cout << f << '\n';
    }
  }
}
