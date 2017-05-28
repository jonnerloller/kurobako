#include "counter.h"

namespace sandcastle::concurrency
{
	counter::counter(int i)
		: m_ctr(i)
	{

	}

	counter::counter(const counter & rhs)
		: m_ctr(rhs.m_ctr.load())
	{

	}

	counter & counter::operator=(const counter & rhs)
	{
		m_ctr.store(rhs.m_ctr.load());
		
		return *this;
	}

	counter & counter::operator=(int i)
	{
		m_ctr.store(i);

		return *this;
	}

	counter & counter::operator++()
	{
		++m_ctr;

		return *this;
	}

	counter & counter::operator--()
	{
		--m_ctr;

		return *this;
	}

	counter::operator int() const
	{
		return m_ctr.load();
	}

	bool counter::operator==(const counter & rhs) const
	{
		return rhs.m_ctr.load() == m_ctr.load();
	}

	bool counter::operator!=(const counter & rhs) const
	{
		return rhs.m_ctr.load() != m_ctr.load();
	}
}