#include "Observable.h"
#include "Global.h"

using std::list;

Observable::Observable() {}

void Observable::registerOb(Observer* ob) {
	lstObserver.push_back(ob);
}

void Observable::removeOb(Observer* ob)   {
	lstObserver.remove(ob);
}

void Observable::notifyOb() {
	list<Observer*>::iterator iter = lstObserver.begin();

	while (iter != lstObserver.end()) {
		((Observer*)(*iter))->update(true);
		iter++;
	}
}

Observable::~Observable() {
	list <Observer*>::iterator iter = lstObserver.begin();

	while (iter != lstObserver.end()) {
		delete *iter ;
		_gblMemory.push_back(InfoAlloc('D',__FILE__, __LINE__));
		iter++;
	}

	lstObserver.clear();
}
