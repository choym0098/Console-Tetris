#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <string>

class Subject;
class Board;
class Observer{
 public:
  virtual void notify()=0; // Passes on multiple types of notifications
  virtual ~Observer() = default;
  virtual void notify(Board*)=0;
};

#endif
