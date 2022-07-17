#include "lru_cache.hpp"

int main()
{
	experimental::lru_cache<int, std::string> cache {
		std::make_pair(1, "one"),
		std::make_pair(2, "two"),
		std::make_pair(3, "three"),
		std::make_pair(3, "three"),
	};

	cache.set(2, "two");
	cache.set(5, "five");
	cache.set(6, "six");
	return 0;
}
