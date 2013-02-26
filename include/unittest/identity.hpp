#ifndef UNITTEST_IDENTITY_HPP
#define UNITTEST_IDENTITY_HPP
#pragma once

#include <unittest/utility.hpp>
#include <unittest/export.hpp>
#include <unittest/traits.hpp>
#include <unittest/error.hpp>

#include <typeinfo>
#include <sstream>
#include <utility>
#include <memory>

#include <cstdint>

namespace unittest {
inline namespace v1 {

class UNITTEST_EXPORT_API identity final {
  std::int64_t statement;

  identity () noexcept;

  auto assert_is_not (intptr_t, intptr_t, const char*) -> void;
  auto assert_is_not (intptr_t, intptr_t) -> void;

  auto assert_is (intptr_t, intptr_t, const char*) -> void;
  auto assert_is (intptr_t, intptr_t) -> void;

  auto assert_is_not_null(void*, const char*) -> void;
  auto assert_is_not_null(void*) -> void;

  auto assert_is_null (void*, const char*) -> void;
  auto assert_is_null (void*) -> void;

public:

  auto operator = (identity const&) noexcept -> identity& = delete;
  auto operator = (identity&&) noexcept -> identity& = delete;
  identity (identity&&) noexcept = delete;

  ~identity () noexcept;

  static auto instance () noexcept -> identity&;
  auto reset () noexcept -> void;

  /* assert_equal */
  template <typename T, typename U>
  auto assert_equal (T const& lhs, U const& rhs, const char* msg) ->
  typename enable_if<trait::eq<T, U>>::type {
    this->statement += 1;
    if (lhs == rhs) { return; }
    throw exception { "assert_equal", msg, this->statement };
  }

  template <typename T, typename U>
  auto assert_equal (T const& lhs, U const& rhs) -> typename enable_if<
    trait::eq<T, U>,
    trait::is_printable<T>,
    trait::is_printable<U>
  >::type {
    this->statement += 1;
    if (lhs == rhs) { return; }
    std::ostringstream stream;
    stream << lhs << " is not equal to " << rhs;
    throw exception { "assert_equal", stream.str(), this->statement };
  }

  /* assert_is_not */
  template <typename T>
  auto assert_is_not (T const& lhs, T const& rhs, const char* msg) -> void {
    auto one = std::addressof(lhs);
    auto two = std::addressof(rhs);
    this->assert_is_not(one, two, msg);
  }

  template <typename T>
  auto assert_is_not (T const& lhs, T const& rhs) -> void {
    this->assert_is_not(std::addressof(lhs), std::addressof(rhs));
  }

  template <typename T>
  auto assert_is_not (T* lhs, T* rhs, const char* msg) -> void {
    auto lhs_ = reinterpret_cast<intptr_t>(lhs);
    auto rhs_ = reinterpret_cast<intptr_t>(rhs);
    this->assert_is_not(lhs_, rhs_, msg);
  }


  template <typename T>
  auto assert_is_not (T* lhs, T* rhs) -> void {
    auto lhs_ = reinterpret_cast<intptr_t>(lhs);
    auto rhs_ = reinterpret_cast<intptr_t>(rhs);
    this->assert_is_not(lhs_, rhs_);
  }

  /* assert_is */
  template <typename T>
  auto assert_is (T const& lhs, T const& rhs, const char* msg) -> void {
    this->assert_is(std::addressof(lhs), std::addressof(rhs), msg);
  }

  template <typename T>
  auto assert_is (T const& lhs, T const& rhs) -> void {
    this->assert_is(std::addressof(lhs), std::addressof(rhs));
  }

  template <typename T>
  auto assert_is (T* lhs, T* rhs, const char* msg) -> void {
    auto lhs_ = reinterpret_cast<intptr_t>(lhs);
    auto rhs_ = reinterpret_cast<intptr_t>(rhs);
    this->assert_is(lhs_, rhs_, msg);
  }

  template <typename T>
  auto assert_is (T* rhs, T* lhs) -> void {
    auto lhs_ = reinterpret_cast<intptr_t>(lhs);
    auto rhs_ = reinterpret_cast<intptr_t>(rhs);
    this->assert_is(lhs_, rhs_);
  }

  /* assert_is_not_null */
  template <typename T>
  auto assert_is_not_null (T* ptr, const char* msg) -> void {
    this->assert_is_not_null(static_cast<void*>(ptr), msg);
  }

  template <typename T>
  auto assert_is_not_null (T* ptr) -> void {
    this->assert_is_null(static_cast<void*>(ptr));
  }

  /* assert_is_null */
  template <typename T>
  auto assert_is_null (T* ptr, const char* msg) -> void {
    this->assert_is_null(static_cast<void*>(ptr), msg);
  }

  template <typename T>
  auto assert_is_null (T* ptr) -> void {
    this->assert_is_null(static_cast<void*>(ptr));
  }

  /* assert_false */
  auto assert_false (bool, const char*) -> void;
  auto assert_false (bool) -> void;

  /* assert_true */
  auto assert_true (bool, const char*) -> void;
  auto assert_true (bool) -> void;

  /* fail */
  auto fail (const char*) -> void;
  auto fail () -> void;
};

extern UNITTEST_EXPORT_API identity& self;

}} /* namespace unittest::v1 */

#endif /* UNITTEST_IDENTITY_HPP */
