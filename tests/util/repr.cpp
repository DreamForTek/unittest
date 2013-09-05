#include <unittest/utility.hpp>

#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <vector>

#include <cstdlib>

int main () {
  using namespace unittest;

  std::vector<int> x { 1, 2, 3 };
  int y = 4;

  std::ostringstream stream1;
  stream1 << y;
  if (stream1.str() != "4") {
    std::clog << "stream::operator << returned unexpected value: " << y
              << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::ostringstream stream;
  std::ostringstream stream2;
  stream << "<unknown-type @ " << std::addressof(x) << ">";
  stream2 << x;
  if (stream2.str() != stream.str()) {
    std::clog << "stream::operator << returned unexpected value: "
              << x
              << " instead of " << stream.str()
              << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::ostringstream null_stream;
  std::ostringstream null_stream2;
  stream2 << "nullptr";
  stream << nullptr;

  if (null_stream.str() != null_stream2.str()) {
    std::clog << "nullptr_stream::operator << returned: " << null_stream.str()
              << " instead of " << null_stream2.str()
              << std::endl;
  }


  return EXIT_SUCCESS;
}
