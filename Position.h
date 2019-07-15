#pragma once

#include <iostream>
#include <iomanip>

// Forward Declarations
class Position;

class Position
{
public:
  Position() : _x(0), _y(0) {}

  // fills _x with x, fills _y with y
  Position(int a, int b) {_x = a; _y = b;}

  int & x() { return _x; }
  int & y() { return _y; }

  const int x() const { return _x; }
  const int y() const { return _y; }

  friend std::ostream & operator<<(std::ostream & os, const Position & p);

protected:
private:
  int _x;
  int _y;
};

inline std::ostream &
operator<<(std::ostream & os, const Position & p)
{
  os << '(' << std::setw(3) << p.x() << ", " << std::setw(3) << p.y() << ')';
  return os;
}
