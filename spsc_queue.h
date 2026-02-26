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
    bool full()
    {
        return _push_cursor - _pop_cursor == _capacity;
    }
    bool empty()
    {
        return _push_cursor == _pop_cursor;
    }
    SizeType size()
    {
        return _push_cursor - _pop_cursor;
    }
    bool push(const N& val)
    {
        if (full()) return false;
        _arr[_push_cursor % _capacity] = val;
        _push_cursor++;
        return true;
    }
    bool pop(N& val)
    {
        if (empty()) return false;
        val = _arr[_pop_cursor % _capacity];
        _arr[_pop_cursor % _capacity].~N();
        _pop_cursor++;
        return true;
    }
private:
    N* _arr;

    SizeType _capacity;
    SizeType _push_cursor;
    SizeType _pop_cursor;
};