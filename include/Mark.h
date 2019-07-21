#pragma once

#include "TicTacToeType.h"
#include "Position.h"

// Forward Declarations
class Mark;

class Mark
{
public:
  // default constructor
  // calls default construct _position, fills _pattern with EMPTY
  Mark()
  {
    _pattern = Pattern::EMPTY;
    _position = Position();
  }

  // FUXME: custom constructor
  // fills _position with position, fills _pattern with EMPTY
  Mark(Position p)
  {
    _pattern = Pattern::EMPTY;
    _position = Position(p.x(), p.y());
  }

  // FUXME: custom constructor
  // fills _position with position, fills _pattern with pattern
  Mark(Position p, Pattern pa)
  {
    set(pa);
    _position = Position(p.x(), p.y());
  }

  Pattern & pattern() { return _pattern; }
  Position & position() { return _position; }

  const Pattern pattern() const { return _pattern; }
  const Position position() const { return _position; }

  // method set() takes in a Pattern p and fills _pattern with p
  void set(Pattern p)
  {
    if (p == Pattern::O)
    {
      _pattern = Pattern::O;
    }
    else if (p == Pattern::X)
    {
      _pattern = Pattern::X;
    }
    else if (p == Pattern::EMPTY)
    {
      _pattern = Pattern::EMPTY;
    }
  }

  friend std::ostream & operator<<(std::ostream & os, const Position & p);

protected:
private:
  Pattern _pattern;
  Position _position;
};

inline std::ostream &
operator<<(std::ostream & os, const Mark & m)
{
  os << m.position() << ": " << m.pattern();

  return os;
}
