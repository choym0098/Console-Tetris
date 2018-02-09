#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <vector>

class Observer;

class Subject{
  // protected:
 public:
  std::vector<Observer*> observers;
  std::vector<Observer*> getObservers();

 public:
  void attach(Observer *ob);
  void detach(Observer *ob);
  void notifyObservers(); 
  virtual ~Subject()=0;
};

#endif
