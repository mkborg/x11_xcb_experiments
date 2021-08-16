#pragma once

/// @brief 'unique_ptr<T>' with automatic conversion to 'T*'

#include "template/deleter.h"

#include <memory>		// std::unique_ptr<>

namespace Template {

// Automatic conversion makes possible to pass 'unique_ptr<T>' as
// argument to functions expecting 'T*'

template <typename T, void(*deleter)(T*)>
struct unique_ptr
  : public std::unique_ptr<T, ::Template::Deleter<T, deleter> >
{
  using base_unique_ptr = std::unique_ptr<T, ::Template::Deleter<T, deleter> >;

  inline operator const T*() const { return base_unique_ptr::get(); }
  inline operator T*() { return base_unique_ptr::get(); }

  inline explicit unique_ptr(T* p)
    : base_unique_ptr(p)
  {
  }

  unique_ptr(unique_ptr&& other) = default;
  unique_ptr& operator =(unique_ptr&& other) = default;
};

} // namespace Template
