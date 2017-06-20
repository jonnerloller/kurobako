#ifndef concurrency_counter_h__
#define concurrency_counter_h__

#include <atomic>

namespace sandcastle::concurrency
{
	class counter
	{
	public:

		counter(int = 0);
		counter(const counter& rhs);
		counter& operator=(const counter& rhs);

		counter& operator=(int);
		counter& operator++();
		counter& operator--();

		operator int() const;
		bool operator==(const counter&) const;
		bool operator!=(const counter&) const;

	private:

		std::atomic<int> m_ctr;

	};
}


#endif