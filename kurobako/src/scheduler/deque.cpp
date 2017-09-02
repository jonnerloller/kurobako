#include "deque.h"

namespace sandcastle::concurrency
{
	deque::deque()
	{

	}

	deque::deque(const deque & rhs)
		: m_queue(rhs.m_queue)
	{

	}

	bool deque::empty() const
	{
		std::lock_guard<std::mutex> lock(m_lock);

		return m_queue.empty();
	}

	void deque::push(job* task)
	{
		if (task == nullptr)
			return;

		std::lock_guard<std::mutex> lock(m_lock);

		m_queue.push_back(task);
	}

	job* deque::pop()
	{
		std::lock_guard<std::mutex> lock(m_lock);

		if (m_queue.empty() == true)
			return nullptr;

		job* task = m_queue.front();
		m_queue.pop_front();

		return task;
	}

	job* deque::steal()
	{
		std::lock_guard<std::mutex> lock(m_lock);

		if (m_queue.empty() == true)
			return nullptr;

		job* task = m_queue.back();
		m_queue.pop_back();

		return task;
	}
}