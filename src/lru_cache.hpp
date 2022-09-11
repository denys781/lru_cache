#pragma once

#include <list>
#include <unordered_map>

namespace experimental
{
	template <typename _Key, typename _Value>
	class lru_cache
	{
	public:
		using key_type = _Key;
		using value_type = _Value;

		explicit lru_cache(std::size_t size) : m_size(size)
		{
			m_map_items.reserve(size);
		}

		void set(const key_type& key, const value_type& value)
		{
			auto it = m_map_items.find(key);
			if (it != std::end(m_map_items)) {
				m_list_items.erase(it->second);
				m_map_items.erase(it);
			}
			discard();
			m_list_items.push_front(std::make_pair(key, value));
			m_map_items.insert(std::make_pair(key, std::begin(m_list_items)));
		}

		bool get(const key_type& key, value_type& value)
		{
			auto it = m_map_items.find(key);
			if (it == std::end(m_map_items))
				return false;
			m_list_items.splice(std::begin(m_list_items), m_list_items, it->second);
			value = m_list_items.front().second;
			return true;
		}
	private:
		void discard()
		{
			if (m_map_items.size() == m_size) {
				auto it = --std::end(m_list_items);
				m_map_items.erase(it->first);
				m_list_items.pop_back();
			}
		}

		std::size_t m_size;
		std::list<std::pair<const key_type, value_type>> m_list_items;
		std::unordered_map<key_type, typename decltype(m_list_items)::iterator> m_map_items;
	};
}