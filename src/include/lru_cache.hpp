#pragma once

#include <list>
#include <unordered_map>

namespace experimental
{
	template <typename K, typename V>
	class lru_cache
	{
		std::size_t maximum_size;
		std::list<std::pair<const K, V>> list_items;
		std::unordered_map<K, typename decltype(list_items)::iterator> map_items;

		void discard()
		{
			if (map_items.size() == maximum_size) {
				auto it = --std::end(list_items);
				map_items.erase(it->first);
				list_items.pop_back();
			}
		}
	public:
		explicit lru_cache(std::size_t maximum)
			: maximum_size(maximum)
		{
			map_items.reserve(maximum);
		}

		void set(const K& key, const V& value)
		{
			auto it = map_items.find(key);
			if (it != std::end(map_items)) {
				list_items.erase(it->second);
				map_items.erase(it);
			}
			discard();
			list_items.push_front(std::make_pair(key, value));
			map_items.insert(std::make_pair(key, std::begin(list_items)));
		}
		bool get(const K& key, V& value)
		{
			auto it = map_items.find(key);
			if (it == std::end(map_items))
				return false;
			list_items.splice(std::begin(list_items), list_items, it->second);
			value = list_items.front().second;
			return true;
		}
	};
}
