#include <unittest/error.hpp>

using std::string;

namespace unittest {
inline namespace v1 {

exception::exception (const char* type, string&& msg, int64_t val) noexcept :
  message { std::move(msg) },
  name { type },
  value { val }
{ }

exception::exception (exception const& that) noexcept :
  message { that.message },
  name { that.name },
  value { that.value }
{ }

exception::~exception () noexcept { }

auto exception::count  () const noexcept -> int64_t { return this->value; }
auto exception::what () const noexcept -> const char* {
  return this->message.c_str();
}

auto exception::type () const noexcept -> const char* {
  return this->name.c_str();
}

skipping::skipping (string&& msg) : message { std::move(msg) } { }
auto skipping::what () const noexcept -> const char* {
  return this->message.c_str();
}

failure::failure (string&& msg, int64_t val) :
  exception { "failure", std::move(msg), val }
{ }

assert_false::assert_false (string&& msg, int64_t val) :
  exception { "assert_false", std::move(msg), val }
{ }

assert_true::assert_true (string&& msg, int64_t val) :
  exception { "assert_true", std::move(msg), val }
{ }

assert_is_not::assert_is_not (string&& msg, int64_t val) :
  exception { "assert_is_not", std::move(msg), val }
{ }

assert_is::assert_is (string&& msg, int64_t val) :
  exception { "assert_is", std::move(msg), val }
{ }

assert_is_not_null::assert_is_not_null (string&& msg, int64_t val) :
  exception { "assert_is_not_null", std::move(msg), val }
{ }

assert_is_null::assert_is_null (string&& msg, int64_t val) :
  exception { "assert_is_null", std::move(msg), val }
{ }

}} /* namespace unittest::v1 */
