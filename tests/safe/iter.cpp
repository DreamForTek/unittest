#include <unittest/safe.hpp>

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <csignal>

auto v1 () -> void {
  auto begin = unittest::v1::vault.begin();
  auto end = unittest::v1::vault.end();
  if (begin != end) {
    std::clog << "vault has returned improper iterators" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  for (auto x : { 1, 2, 3, 4 }) {
    auto future = std::async(std::launch::deferred, [x]{
      return std::error_condition { x, std::generic_category() };
    });
    std::stringstream str1;
    std::stringstream str2;
    str1 << x;
    str2 << x + 1;

    unittest::v1::vault.add(str1.str(), str2.str(), std::move(future));
  }

  auto value = 4;
  for (auto&& entry : unittest::v1::vault) {
    std::stringstream str1;
    std::stringstream str2;
    str1 << value;
    str2 << value + 1;

    if (std::get<0>(entry) != str1.str()) {
      std::clog << "vault added entry<0> in an incorrect order" << std::endl;
      std::exit(EXIT_FAILURE);
    }

    if (std::get<1>(entry) != str2.str()) {
      std::clog << "vault added entry<1> in an incorrect order" << std::endl;
      std::exit(EXIT_FAILURE);
    }

    if (std::get<2>(entry).get().value() != value) {
      std::clog << "vault ran incorrect future" << std::endl;
      std::exit(EXIT_FAILURE);
    }
    value -= 1;
  }
}

auto sigsegv (int) -> void {
  std::clog << "SIGSEGV signal triggered" << std::endl;
  std::exit(EXIT_FAILURE);
}

auto main () -> int {
  std::signal(SIGSEGV, sigsegv);
  v1();
  return EXIT_SUCCESS;
}
