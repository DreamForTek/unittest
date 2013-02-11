#ifndef UNITTEST_IDENTITY_HPP
#define UNITTEST_IDENTITY_HPP
#pragma once

#include <unittest/export.hpp>

#include <typeinfo>
#include <utility>
#include <cstdint>

namespace unittest {
inline namespace v1 {

class UNITTEST_EXPORT_API identity final {
  std::int64_t statement;
  identity () noexcept;

public:

  auto operator = (identity const&) noexcept -> identity& = delete;
  auto operator = (identity&&) noexcept -> identity& = delete;
  identity (identity&&) noexcept = delete;

  identity (identity const&) noexcept;
  ~identity () noexcept;

  static auto instance () noexcept -> identity&;
  auto assert_false (bool, const char*) -> void;
  auto assert_true (bool, const char*) -> void;

  auto assert_false (bool) -> void;
  auto assert_true (bool) -> void;

  auto assert_is_not (intptr_t, intptr_t, const char*) -> void;
  auto assert_is (intptr_t, intptr_t, const char*) -> void;

  auto assert_is_not (intptr_t, intptr_t) -> void;
  auto assert_is (intptr_t, intptr_t) -> void;

  auto fail (const char*) -> void; /* TODO: [[noreturn]] */
  auto fail () -> void; /* TODO: Mark as [[noreturn]] */
};

extern UNITTEST_EXPORT_API identity& self;

}} /* namespace unittest::v1 */

#endif /* UNITTEST_IDENTITY_HPP */
