#pragma once
#include <algorithm>
#include <vector>
#include <map>
#include <list>
#include <share.h>
#include <string>
#include "boost/shared_ptr.hpp"
#include <mutex>
#include <cmath>

using namespace std;

#define RELARGE_MAX (1000) 

template <typename T>
class ObjPool
{
public:
	ObjPool(std::string pool_name):m_str_pool_name(pool_name) { resize_reset(); }
	~ObjPool() { resize_reset(); }
	typedef boost::shared_ptr<T> _element_ptr;
	#define LOCK std::lock_guard<std::mutex> lock(m_mutex);
public:
	_element_ptr alloc()
	{
		LOCK;
		if (m_unused_elem_pool.size() <= 0)
		{
			resize_relarge();
		}
		_element_ptr ptr = m_unused_elem_pool.back();
		m_unused_elem_pool.pop_back();
		m_used_elem_pool.push_back(ptr);
		return ptr;
	}
	bool free(_element_ptr ptr)
	{
		LOCK;
		if (!ptr)
		{
			return false;
		}
		auto itF = std::find(m_used_elem_pool.begin(), m_used_elem_pool.end(), ptr);
		if (itF != m_used_elem_pool.end())
		{
			m_used_elem_pool.erase(itF);
			m_unused_elem_pool.push_back(ptr);
			return true;
		}

		return false;
	}
private:
	void resize_relarge()
	{
		int32_t elesize = m_size;
		int32_t nadd_size = min(m_size, 1000);
		if (nadd_size <= 0)
		{
			nadd_size = 100;
		}
		for (int32_t idx = 0; idx < nadd_size; ++idx)
		{
			_element_ptr ptr = boost::make_shared<T>();
			m_unused_elem_pool.push_back(ptr);
			m_size++;
		}
	}
	void resize_reset()
	{
		m_unused_elem_pool.clear();
		m_used_elem_pool.clear();
		m_size = 0;
	}
private:
	vector<_element_ptr> m_used_elem_pool;
	vector<_element_ptr> m_unused_elem_pool;
	std::mutex m_mutex;
	int32_t m_size;
	std::string m_str_pool_name;
};

#define POOL_INST(pool_name) \
	g##pool_name##Pool

#define POOL_DEF(pool_name) \
	extern ObjPool<pool_name> POOL_INST(pool_name)	

#define POOL_IMPL(pool_name) \
	ObjPool<pool_name> POOL_INST(pool_name)(#pool_name);

#define POOL_ALLOC(pool_name) \
	POOL_INST(pool_name).alloc();	

#define POOL_FREE(pool_name, ptr) \
	POOL_INST(pool_name).free(ptr);	

	
	




