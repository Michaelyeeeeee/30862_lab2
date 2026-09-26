#include "hash_map.h"

hash_map::hash_map(size_t capacity)
{
    _size = 0;
    _capacity = capacity;
    _head = new hash_list[_capacity];
}

hash_map::hash_map(const hash_map &other)
{
    _size = other._size;
    _capacity = other._capacity;

    _head = new hash_list[_capacity];

    for (size_t i = 0; i < _capacity; i++)
    {
        _head[i] = other._head[i];
    }
}

hash_map &hash_map::operator=(const hash_map &other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] _head;

    _size = other._size;
    _capacity = other._capacity;

    _head = new hash_list[_capacity];

    for (size_t i = 0; i < _capacity; i++)
    {
        _head[i] = other._head[i];
    }

    return *this;
}

void hash_map::insert(int key, float value)
{
    size_t index = std::abs(key) % _capacity;

    if (!_head[index].get_value(key).has_value())
    {
        _size++;
    }

    _head[index].insert(key, value);
}

std::optional<float> hash_map::get_value(int key) const
{
    return _head[std::abs(key) % _capacity].get_value(key);
}

bool hash_map::remove(int key)
{
    size_t index = std::abs(key) % _capacity;

    if (_head[index].remove(key))
    {
        _size--;
        return true;
    }

    return false;
}

size_t hash_map::get_capacity() const
{
    return _capacity;
}

void hash_map::get_all_keys(int *keys)
{
    size_t index = 0;
    for (size_t i = 0; i < _capacity; i++)
    {
        _head[i].reset_iter();
        while (!_head[i].iter_at_end())
        {
            std::optional<std::pair<const int *, float *>> p = _head[i].get_iter_value();

            if (p.has_value())
                keys[index++] = *p->first;
            _head[i].increment_iter();
        }
    }
}

void hash_map::get_bucket_sizes(size_t *buckets)
{
    for (size_t i = 0; i < _capacity; i++)
    {
        buckets[i] = _head[i].get_size();
    }
}

hash_map::~hash_map()
{
    delete[] _head;
}