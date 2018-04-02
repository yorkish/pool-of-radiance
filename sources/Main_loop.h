#ifndef POR_MAIN_LOOP_H
#define POR_MAIN_LOOP_H

#include <cstdint>

class Main_loop {
public:
	Main_loop();
	uint8_t start();
	~Main_loop();
};

#endif // POR_MAIN_LOOP_H
