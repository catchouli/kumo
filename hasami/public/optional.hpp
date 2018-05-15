#pragma once
// If this is conflicting with the built in header in a future version of a compiler
// see sdk.cmake and remove the "${SDKDIR}/include/c++11" include folder for that compiler
#include "c++11/optional.hpp"
namespace std {
  using experimental::optional;
  using experimental::make_optional;
}