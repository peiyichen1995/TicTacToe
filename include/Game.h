#pragma once

#include <sstream>
#include <limits>
#include <regex>
#include "Board.h"
#include "Player.h"

// Forward Declarations
class Game;

class Game
{
public:
  Game() : _board(NULL), _p1(NULL), _p2(NULL)
  {
    std::cout << "###############################################\n";
    std::cout << "##             Game Board Setup              ##\n";
    std::cout << "###############################################\n";
    // allocate memory for _board by calling getRow() and getCol()
    _board = new Board(getNumber("Number of rows: "), getNumber("Number of columns: "));

    std::cout << std::endl;
    std::cout << "###############################################\n";
    std::cout << "##                  Player 1                 ##\n";
    std::cout << "###############################################\n";
    // allocate memory for _p1 by calling getPattern(), getName(), and getWinMsg()
    _p1 = new Player(getPattern(), getName(), getWinMsg());

    std::cout << std::endl;
    std::cout << "###############################################\n";
    std::cout << "##                  Player 2                 ##\n";
    std::cout << "###############################################\n";
    // allocate memory for _p2 by calling getPattern(), getName(), and getWinMsg()
    _p2 = new Player(getPattern(), getName(), getWinMsg());

    std::cout << std::endl;
    std::cout << "###############################################\n";
    std::cout << "##               Win Condition               ##\n";
    std::cout << "###############################################\n";
    _T = std::min(_board->M(), _board->N());
    _i = 0;
    _j = 0;
    _win = 0;
    std::cout << "The first player to place " << _T
              << " consecutive pieces, \neither in a row, in a column, or on a diagonal.\n";
  }

  // desctructor frees allocated memory
  ~Game()
  {
    delete _board;
    delete _p1;
    delete _p2;
  }

  std::string getMatchedRegex(std::regex to_match)
  {
    std::string input;
    std::getline(std::cin, input);
    while (!std::regex_match(input, to_match))
    {
      std::cout << "ERROR: Invalid input, please try again: ";
      std::getline(std::cin, input);
    }
    return input;
  }

  //   unsigned int getRow()
  //   {
  //     std::cout << "Number of rows: ";
  //     std::regex e("^[[:blank:]]*[0-9]+[[:blank:]]*$");
  //     std::stringstream ss(getMatchedRegex(e));
  //     int M;
  //     ss >> M;
  //     return M;
  //   }

  //   unsigned int getCol()
  //   {
  //     std::cout << "Number of columns: ";
  //     //
  //     std::regex e("^[[:blank:]]*[0-9]+[[:blank:]]*$");
  //     std::stringstream ss(getMatchedRegex(e));
  //     int N;
  //     ss >> N;
  //     return N;
  //   }

  unsigned int getNumber(std::string message)
  {
    std::cout << message;
    std::regex e("^[[:blank:]]*\\d+[[:blank:]]*$");
    std::stringstream ss(getMatchedRegex(e));
    int N;
    ss >> N;
    return N;
  }

  Pattern getPattern()
  {
    if (_p1)
    {
      if (_p1->pattern() == Pattern::O)
        return Pattern::X;
      if (_p1->pattern() == Pattern::X)
        return Pattern::O;
    }

    std::cout << "Choose your mark:\n";
    std::cout << "-----enter o for " << Pattern::O << std::endl;
    std::cout << "-----enter x for " << Pattern::X << std::endl;
    std::cout << "Your choice: ";
    std::regex e("[[:blank:]]*[OXox]+[[:blank:]]*$");
    std::stringstream ss(getMatchedRegex(e));
    char mark;
    ss >> mark;

    Pattern p = Pattern::EMPTY;
    if (mark == 'o' || mark == 'O')
      p = Pattern::O;
    else if (mark == 'x' || mark == 'X')
      p = Pattern::X;
    return p;
  }

  std::string getName()
  {
    std::string name;
    std::cout << "Your name: ";
    std::getline(std::cin, name);
    return name;
  }

  std::string getWinMsg()
  {
    std::string msg;
    std::cout << "Win message: ";
    std::getline(std::cin, msg);
    return msg;
  }

  void start()
  {
    pregame();
    while (!terminate())
    {
      nextTurn();
      prePlay();
      play();
      postPlay();
    }
    if (_win == 1)
    {
      _turn->win();
    }
    else
    {
      std::cout << "No winner." << std::endl;
    }
  }

  void pregame()
  {
    std::cout << *_board << std::endl;
    _turn = _p2;
  }

  void nextTurn()
  {
    _turn = _turn == _p1 ? _p2 : _p1;
    std::cout << "Player " << *_turn << "'s turn. Please place your chess.\n";
  }

  void prePlay() {}

  bool isvalid(unsigned int i, unsigned int j)
  {
    if (i >= _board->M() || j >= _board->N())
    {
      return false;
    }
    if ((*_board)(i, j).pattern() != Pattern::EMPTY)
      return false;
    return true;
  }

  void play()
  {
    unsigned int i, j;

    // request valid i and j
    i = getNumber("X position: ");
    j = getNumber("Y position: ");
    while (isvalid(i, j) == false)
    {
      std::cout << "ERROR: Invalid input, please try again: ";
      i = getNumber("X position: ");
      j = getNumber("Y position: ");
    }

    _i = i;
    _j = j;

    _board->set(i, j, _turn->pattern());
  }

  void postPlay() { std::cout << *_board << std::endl; }

  // method terminate() determines whether we should terminate the game
  // return true if we should terminate, return false if we should not.
  // If there is a winner, print the winner's win message.

  bool hlinewin(unsigned int i, unsigned int j, Pattern pa)
  {
    unsigned int count = 1;
    for (unsigned int a = j + 1; a < _board->N(); a++)
    {
      if ((*_board)(i, a).pattern() != pa)
        break;
      count++;
    }
    for (int b = j - 1; b >= 0; b--)
    {
      if ((*_board)(i, b).pattern() != pa)
        break;
      count++;
    }

    if (count >= _T)
      return true;
    else
      return false;
  }

  bool vlinewin(unsigned int i, unsigned int j, Pattern pa)
  {
    unsigned int count = 1;
    for (unsigned int a = i + 1; a < _board->M(); a++)
    {
      if ((*_board)(a, j).pattern() != pa)
        break;
      count++;
    }
    for (int b = i - 1; b >= 0; b--)
    {
      if ((*_board)(b, j).pattern() != pa)
        break;
      count++;
    }
    if (count >= _T)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  bool dialinewin(unsigned int i, unsigned int j, Pattern pa)
  {
    unsigned int count = 1;
    int a = i - 1;
    int b = j - 1;
    while (a >= 0 && b >= 0)
    {
      if ((*_board)(a, b).pattern() != pa)
        break;
      count++;
      a--;
      b--;
    }
    a = i + 1;
    b = j + 1;
    while (a < int(_board->M()) && b < int(_board->N()))
    {
      if ((*_board)(a, b).pattern() != pa)
        break;
      count++;
      a++;
      b++;
    }
    if (count >= _T)
      return true;

    // Check another diagonal
    count = 1;
    a = i - 1;
    b = j + 1;
    while (a >= 0 && b < int(_board->N()))
    {
      if ((*_board)(a, b).pattern() != pa)
        break;
      count++;
      a--;
      b++;
    }
    a = i + 1;
    b = j - 1;
    while (a < int(_board->M()) && b >= 0)
    {
      if ((*_board)(a, b).pattern() != pa)
        break;
      count++;
      a++;
      b--;
    }
    if (count >= _T)
      return true;
    else
      return false;
  }

  bool isfull()
  {
    unsigned int is = 1;
    for (unsigned int i = 0; i < _board->M(); i++)
      for (unsigned int j = 0; j < _board->N(); j++)
        if ((*_board)(i, j).pattern() == Pattern::EMPTY)
        {
          is = 0;
          break;
        }

    if (is == 0)
      return false;
    else
      return true;
  }

  bool terminate()
  {
    Pattern pa = _turn->pattern();
    unsigned int i = _i;
    unsigned int j = _j;
    if (hlinewin(i, j, pa) == true || vlinewin(i, j, pa) == true || dialinewin(i, j, pa) == true)
    {
      _win = 1;
      return true;
    }
    else if (isfull() == true)
    {
      _win = 0;
      return true;
    }
    else
      return false;
  }

protected:
private:
  Board * _board;
  Player * _p1;
  Player * _p2;
  Player * _turn;
  unsigned int _T;
  unsigned int _i;
  unsigned int _j;
  unsigned int _win;
};
