#pragma once

#include <iostream>

// Define a custom enum called Pattern
// members are O, X, and EMPTY.
typedef enum pattern
{
  O,
  X,
  EMPTY
} Pattern;

inline std::ostream &
operator<<(std::ostream & os, const Pattern & p)
{
  if (p == Pattern::O)
    os << "\u25CB";
  // os << "\u23FA";
  if (p == Pattern::X)
    os << "x";
  if (p == Pattern::EMPTY)
    os << " ";
  return os;
}
