#include <iostream>
#include "lru_cache.hpp"

int main()
{
	experimental::lru_cache<int, std::string> cache(2);
	std::string s;

	cache.set(1, "one");
	cache.set(2, "two");
	cache.set(3, "three");

	cache.get(2, s);
	std::cout << "key: " << 2 << ", value: " << s << '\n';
	return 0;
}