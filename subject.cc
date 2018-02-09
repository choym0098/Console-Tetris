#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

#include "subject.h"
#include "observer.h"
#include "cell.h"
using namespace std;

vector<Observer*> Subject::getObservers() {
  return observers;
}

void Subject::attach(Observer *ob) {
  observers.emplace_back(ob);
}
    
void Subject::detach(Observer *ob) {
}

void Subject::notifyObservers() {
  for (unsigned int i = 0; i < observers.size(); ++i) {
    observers[i]->notify();
  }
}

Subject::~Subject() {}

