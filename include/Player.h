#pragma once

#include <string>
#include "TicTacToeType.h"

// Forward Declarations
class Player;

class Player
{
public:
  // custom constructor
  // fills _pattrn with pattern, fills name with _name, fills _win_msg with win_msg
  Player(Pattern pa, std::string name, std::string win_msg)
    : _pattern(pa), _name(name), _win_msg(win_msg)
  {
  }

  const Pattern pattern() const { return _pattern; }
  const std::string name() const { return _name; }

  void win()
  {
    std::cout << "WINNER: " << *this << std::endl;
    std::string temp(_win_msg.length() + 12, '#');
    std::cout << temp << std::endl;
    std::cout << "#     " << _win_msg << "     #" << std::endl;
    std::cout << temp << std::endl;
  }

  friend std::ostream & operator<<(std::ostream & os, const Player & p);

protected:
private:
  const Pattern _pattern;
  const std::string _name;
  const std::string _win_msg;
};

inline std::ostream &
operator<<(std::ostream & os, const Player & p)
{
  os << p.name() << "(" << p.pattern() << " )";
  return os;
}
