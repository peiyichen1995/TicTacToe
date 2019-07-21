#pragma once

#include <vector>
#include "Mark.h"

// Forward Declarations
class Board;

class Board
{
public:
  // default constructor
  // fills _M with 3, fills _N with 3, allocate memory for _marks, calls initialize() to initialize
  // marks.
  Board() : _M(3), _N(3), _marks(_M * _N) { initialize(); }

  // custom constructor
  // fills _M with m, fills _N with n, allocate memory for _marks, calls initialize() to initialize
  Board(unsigned int m, unsigned int n) : _M(m), _N(n), _marks(_M * _N) { initialize(); }

  // destructor for Board
  ~Board()
  {
    for (auto p : _marks)
      delete p;
  }

  // method initialize() fills _marks with pointers to Mark by allocating memory for each
  // Mark.
  void initialize()
  {
    for (unsigned int i = 0; i < _M; i++)
      for (unsigned int j = 0; j < _N; j++)
        _marks[i * _N + j] = new Mark();
  }

  const unsigned int M() { return _M; }
  const unsigned int N() { return _N; }

  const unsigned int M() const { return _M; }
  const unsigned int N() const { return _N; }

  // access the Mark at row i column j
  Mark & operator()(unsigned int i, unsigned int j) { return *_marks[i * _N + j]; }

  // const access the Mark at row i column j
  const Mark & operator()(unsigned int i, unsigned int j) const { return *_marks[i * _N + j]; }

  // method set() sets the Pattern of the Mark at row i column j to p.
  void set(unsigned int i, unsigned int j, Pattern pa) { _marks[i * _N + j]->set(pa); }

  friend std::ostream & operator<<(std::ostream & os, const Board & p);

protected:
private:
  const unsigned int _M;
  const unsigned int _N;
  std::vector<Mark *> _marks;
};

inline std::ostream &
operator<<(std::ostream & os, const Board & b)
{
  const unsigned int M = b.M();
  const unsigned int N = b.N();

  std::cout << std::endl;

  std::cout << "   ";
  for (unsigned int j = 0; j < N; j++)
    std::cout << "  " << std::setw(3) << j << "  ";

  std::cout << "\n   ";
  for (unsigned int j = 0; j < N; j++)
    std::cout << " ______";
  std::cout << std::endl;
  for (unsigned int i = 0; i < M; i++)
    for (unsigned int temp = 0; temp < 3; temp++)
      for (unsigned int j = 0; j < N; j++)
      {
        if (j == 0)
        {
          if (temp == 1)
            std::cout << std::setw(3) << i;
          else
            std::cout << "   ";
        }

        if (temp == 0)
        {
          std::cout << "|      ";
          if (j == N - 1)
            std::cout << "|\n";
        }
        if (temp == 1)
        {
          std::cout << "|  " << b(i, j).pattern() << "   ";
          if (j == N - 1)
            std::cout << "|\n";
        }
        if (temp == 2)
        {
          std::cout << "|______";
          if (j == N - 1)
            std::cout << "|\n";
        }
      }
  return os;
}
