#ifndef _ZEUS_TIME_UTILS_H_
#define _ZEUS_TIME_UTILS_H_

#include <time.h>
#include <stdint.h>

namespace utils {

	uint64_t get_ticks();
	double get_time();
	void sleep(double sec);

	class StopWatch {
	private:

		double _start = 0;

	public:

		inline StopWatch(): _start(get_time()) {}

		inline void start() {_start = get_time();}

		inline double get_start_time() const {return _start;}

		inline double getCurrentTime() const {return get_time();}

		inline double get() const {return get_time() - _start;}
	};
}

#endif
