/* 460. LFU Cache
 * Design and implement a data structure for Least Frequently Used (LFU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item. For the purpose of this problem, when there is a tie (i.e., two or more keys that have the same frequency), the least recently used key would be evicted.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LFUCache cache = new LFUCache( 2 ); // 2 is capacity

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.get(3);       // returns 3.
cache.put(4, 4);    // evicts key 1.
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4

*/

#include<list>
#include<vector>
#include<unordered_map>

using namespace std;

class LFUCache {
private:
    struct CacheEntry {
        int key;
        int value;
        CacheEntry() {}
        CacheEntry(int k, int v): key(k), value(v) {}
    };
    struct LFUEntry {
        int freq;
            list<CacheEntry> lru;
    };
    struct LFUIterator {
        list<LFUEntry>::iterator qit;
        list<CacheEntry>::iterator lit;
        LFUIterator() {}
        LFUIterator(list<LFUEntry>::iterator q, list<CacheEntry>::iterator l): qit(q), lit(l) {}
    };
    int cap, size;
    list<LFUEntry> queue; // list by frequency desc, int: freq, list<CacheEntry>: by used less -> more recently
    unordered_map<int, LFUIterator> hash;

    // this call only takes qit != queue.end()
    void addInternal(list<LFUEntry>::iterator qit, int key, int value) {
        if (qit == queue.end()) {
            printf("unsupported functionality by addInternal\n");
            return;
        }
        list<CacheEntry>::iterator lit = qit->lru.insert(qit->lru.end(), {key, value});
        hash[key] = {qit, lit};
    }

    list<LFUEntry>::iterator removeInternal(LFUIterator its, bool addNext=false) {
        auto qit = its.qit;
        auto lit = its.lit;
        int freq = qit->freq + 1, key = lit->key;
        qit->lru.erase(lit);
        hash.erase(key);
        if (qit->freq != 0 && qit->lru.size() == 0) {
            qit = queue.erase(qit);
        } else {
            ++qit;
        }
        if (!addNext) {
            return qit;
        }
        // need to add the current freq + 1
        if (qit == queue.end() || qit->freq > freq) {
            qit = queue.insert(qit, {freq, list<CacheEntry>()});
        }
        return qit;
    }

    // return the iterator pointing to the next frequency (current + 1)
    // because we immediately use it to add the new frequency
    // @return qit cannot be end()
    // also update the unordered_map hash
    list<LFUEntry>::iterator removeExisting(LFUIterator its) {
        return removeInternal(its, true);
    }

    // remove the least frequently used if it exits
    // note that freq 0 always exists,
    void removeLeastFrequent() {
        auto qit = queue.begin();
        if ((qit->lru.size() == 0) && ((++qit) == queue.end())) {
            return;
        }
        removeInternal(LFUIterator(qit, qit->lru.begin()), false);
    }

    void printQueue() {
        for (auto q : queue) {
            printf("freq == %d\n", q.freq);
            if (q.lru.size() == 0) {
                printf("list empty\n");
            }
            for (auto l : q.lru) {
                printf("%d -> %d\n", l.key, l.value);
            }
        }
    }
public:
    LFUCache(int capacity) {
        if (capacity == 0) {
            return;
        }
        cap = capacity;
        size = 0;
        // freq 0 list always exits
        queue.push_back({0, list<CacheEntry>()});
        // how to handle case for cap == 0
    }

    int get(int key) {
        auto it = hash.find(key);
        if (it == hash.end()) {
            return -1;
        }
        // update the entry

        int value = it->second.lit->value;
        // now qit is the iterator position we're inserting into
        auto qit = removeExisting(it->second);
        addInternal(qit, key, value);
        return value;
    }

    void put(int key, int value) {
        if (cap == 0) {
            return;
        }
        auto it = hash.find(key);
        auto qit = queue.end();
        if (it == hash.end()) {
            ++size;
            qit = queue.begin();
        } else {
            qit = removeExisting(it->second);
        }
        if (size > cap) {
            removeLeastFrequent();
            --size;
        }
        addInternal(qit, key, value);
    }
};

struct TestData {
    int capacity;
    vector<vector<int>> data; // size == 2: put, size == 1: get
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
int main() {
    vector<TestData> tests = {{2, {{1, 1}, {2, 2}, {1}, {3, 3}, {2}, {3}, {1},
        {4, 4}, {1}, {3}, {4}}},
        {0, {{0, 0}, {0}}}};
    LFUCache *obj;
    for (auto t : tests) {
        obj = new LFUCache(t.capacity);
        printf("Create LFU cache of capacity %d\n", t.capacity);
        for(auto d : t.data) {
            if (d.size() == 1) {
                // cache get
                printf("Get value for key %d: ", d[0]);
                int res = obj->get(d[0]);
                printf("%d\n", res);
            } else if (d.size() == 2) {
                // cache put
                printf("Put %d -> %d in cache\n", d[0], d[1]);
                obj->put(d[0], d[1]);
            } else {
                printf("invalid input\n");
            }
        }
        printf("\n");
    }
    return 0;
}
