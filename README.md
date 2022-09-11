<p>This is a sample of a simple lru cache implementation using C++11.</p>
<p>How it works:</p>
<ul>
 <li>as long as the cache size is less than the maximum, it works like a regular <b>unordered map</b>.</li>
 <li>the <b>set()</b> method remembers the new value corresponding to the key.</li>
 <li>the <b>get()</b> method returns <b>false</b> if nothing was put by the key. If the key matches some value, then <b>get()</b> returns <b>true</b> and this value. If before set operation the cache size equals the maximum, then the LRU algorithm is triggered and the cache removes from itself the key that was accessed first.</li>
</ul>
<p>The computational complexity of the <b>get()</b> and <b>set()</b> methods is <b>O(1)</b> on average.</p>
