#include <atomic>
#include <cstddef>

template <typename N>
class Queue
{
public:
    using SizeType = std::size_t;
    explicit Queue(SizeType capacity) : _capacity(capacity)
    {
        _push_cursor = 0;
        _pop_cursor = 0;
        _arr = new N[_capacity];
    }
    ~Queue()
    {
        delete[] _arr;
    }
    SizeType size()
    {
        return (_push_cursor - _pop_cursor);
    }
    bool push(const N& val)
    {
        SizeType push = _push_cursor.load(std::memory_order_relaxed);
        SizeType pop = _pop_cursor.load(std::memory_order_relaxed);
        if (full(push, pop)) return false;
        _arr[push % _capacity] = val;
        _push_cursor.fetch_add(1, std::memory_order_relaxed);

        return true;
    }
    bool pop(N& val)
    {
        SizeType pop =  _pop_cursor.load(std::memory_order_relaxed);
        SizeType push =  _push_cursor.load(std::memory_order_relaxed);
        if (empty(push, pop)) return false;
        val = _arr[pop % _capacity];
        _pop_cursor.fetch_add(1, std::memory_order_relaxed);
        return true;
    }
private:

    bool full(SizeType push, SizeType pop)
    {
        return push - pop == _capacity;
    }
    bool empty(SizeType push, SizeType pop)
    {
        return push == pop;
    }
    SizeType size(SizeType push, SizeType pop)
    {
        return push - pop;
    }

    N* _arr;
    SizeType _capacity;
    std::atomic<SizeType> _push_cursor;
    std::atomic<SizeType> _pop_cursor;
};