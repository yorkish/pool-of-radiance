#pragma once

#include "Observer.h"
#include <list>

// The Abstract Subject
class Observable {

  public:
	Observable();
	void registerOb(Observer* ob);
	void removeOb(Observer* ob);
	~Observable();

  protected:
	std::list<Observer*> lstObserver;

	void notifyOb();
};
