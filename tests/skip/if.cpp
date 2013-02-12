#include <unittest/error.hpp>
#include <unittest/skip.hpp>

#include <iostream>
#include <csignal>

/* Tests the skip_if interface */
auto v1 () -> void {
  auto always = unittest::v1::skip_if(true, "always-skip") = []{};
  auto never = unittest::v1::skip_if(false, "never-skip") = []{ throw 42; };

  try {
    always();
    std::clog << "skip_if always did not throw" << std::endl;
    std::exit(EXIT_FAILURE);
  } catch (unittest::v1::skipping const& e) {
    if (e.what() != std::string { "always-skip" }) {
      std::clog << "skip_if always did not throw proper error" << std::endl;
      std::exit(EXIT_FAILURE);
    }
  } catch (...) {
    std::clog << "unexpected exception thrown by skip_if always" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  try {
    never();
    std::clog << "skip_if never does not contain proper function" << std::endl;
    std::exit(EXIT_FAILURE);
  } catch (int value) {
    if (value != 42) {
      std::clog << "skip_if never function threw incorrect value" << std::endl;
      std::exit(EXIT_FAILURE);
    }
  } catch (...) {
    std::clog << "unexpected exception thrown by skip_if never" << std::endl;
    std::exit(EXIT_FAILURE);
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
