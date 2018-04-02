#ifndef COMMON_RAIICAP_H_
#define COMMON_RAIICAP_H_

#include "../Main_loop.h"

template<typename T>
class raiicap {
public:
	friend uint8_t Main_loop::start();
private:
	raiicap() {
	}
};

#endif /* COMMON_RAIICAP_H_ */
