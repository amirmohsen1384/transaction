#ifndef DATALIST_H
#define DATALIST_H

#include <memory>
#include <cassert>
#include <stdexcept>
#include <iostream>

template<typename T>
class DataList
{
private:
    struct DataContainer
    {
        T _data;
        std::weak_ptr<DataContainer> _prev;
        std::shared_ptr<DataContainer> _next;
        DataContainer(const T& data) : _data(data), _next(nullptr), _prev() {}
    };

public:
    DataList() : _first(nullptr), _last(nullptr), _size(0) {}

    DataList(const std::initializer_list<T>& list) : DataList()
    {
        for (const auto& item : list)
            append(item);
    }

    DataList(const DataList& other) : DataList()
    {
        auto current = other._first;
        if (current)
        {
            do
            {
                append(current->_data);
                current = current->_next;
            } 
            while (current != other._first);
        }
    }

    DataList(DataList&& other) noexcept
        : _first(std::move(other._first)), _last(std::move(other._last)), _size(other._size)
    {
        other._first = nullptr;
        other._last = nullptr;
        other._size = 0;
    }

    DataList& operator=(const DataList& other)
    {
        if (this != &other)
        {
            clear();
            auto current = other._first;
            if (current)
            {
                do
                {
                    append(current->_data);
                    current = current->_next;
                }
                while (current != other._first);
            }
        }
        return *this;
    }

    DataList& operator=(DataList&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            _first = std::move(other._first);
            _last = std::move(other._last);
            _size = other._size;
            other._first = nullptr;
            other._last = nullptr;
            other._size = 0;
        }
        return *this;
    }

    void append(const T& value)
    {
        auto node = std::make_shared<DataContainer>(value);
        if (isEmpty())
        {
            _first = _last = node;
            node->_next = node;
            node->_prev = node;
        }
        else
        {
            node->_prev = _last;
            node->_next = _first;
            _last->_next = node;
            _first->_prev = node;
            _last = node;
        }
        ++_size;
    }

    void prepend(const T& value)
    {
        auto node = std::make_shared<DataContainer>(value);
        if (isEmpty())
        {
            _first = _last = node;
            node->_next = node;
            node->_prev = node;
        }
        else
        {
            node->_next = _first;
            node->_prev = _last;
            _first->_prev = node;
            _last->_next = node;
            _first = node;
        }
        ++_size;
    }

    bool remove(const T& value)
    {
        if (isEmpty())
        {
            return false;
        }

        auto current = _first;
        do
        {
            if (current->_data == value)
            {
                if (_size == 1)
                {
                    _first.reset();
                    _last.reset();
                    _size = 0;
                    return true;
                }

                auto prev = current->_prev.lock();
                auto next = current->_next;

                if (current == _first)
                {
                    _first = next;
                }

                if (current == _last)
                {
                    _last = prev;
                }

                if (prev)
                {
                    prev->_next = next;
                }

                if (next)
                {
                    next->_prev = prev;
                }

                --_size;
                return true;
            }
            current = current->_next;
        }
        while (current != _first);

        return false;
    }

    bool contains(const T& value) const
    {
        if (isEmpty())
            return false;

        auto current = _first;
        do
        {
            if (current->_data == value)
                return true;

            current = current->_next;
        }
        while (current != _first);
        return false;
    }

    void clear()
    {
        if (isEmpty())
            return;

        auto current = _first;
        do
        {
            auto next = current->_next;
            current->_next.reset();
            current->_prev.reset();
            current = next;
        }
        while (current != _first);

        _first.reset();
        _last.reset();
        _size = 0;
    }

    void insert(int index, const T& value)
    {
        if (index <= 0)
        {
            prepend(value);
        }
        else if (index >= size())
        {
            append(value);
        }
        else
        {
            auto current = _first;
            for (int i = 0; i < index; ++i)
                current = current->_next;

            auto prev = current->_prev.lock();
            auto node = std::make_shared<DataContainer>(value);
            node->_prev = prev;
            node->_next = current;

            if (prev)
                prev->_next = node;
            current->_prev = node;

            ++_size;
        }
    }

    bool isEmpty() const { return _size == 0; }

    std::size_t size() const { return _size; }

    T& value(int index)
    {
        if (index < 0 || index >= size())
        {
            throw std::invalid_argument("Index out of bounds");
        }
        auto current = _first;
        for (int i = 0; i < index; ++i)
        {
            current = current->_next;
        }
        return current->_data;
    }

    const T& value(int index) const
    {
        if (index < 0 || index >= size())
            throw std::invalid_argument("Index out of bounds");

        auto current = _first;
        for (int i = 0; i < index; ++i)
        {
            current = current->_next;
        }
        return current->_data;
    }

    T& operator[](int index) { return value(index); }

    const T& operator[](int index) const { return value(index); }

    void reverse()
    {
        if (isEmpty())
        {
            return;
        }
        int begin = 0, end = size() - 1;
        while (begin < end)
        {
            std::swap(value(begin++), value(end--));
        }
    }

    ~DataList()
    { 
        clear();
    }

    template<typename X>
    friend std::ostream& operator<<(std::ostream& stream, const DataList<X>& container);

private:
    std::shared_ptr<DataContainer> _first;
    std::shared_ptr<DataContainer> _last;
    std::size_t _size;
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const DataList<T>& container)
{
    if (container.isEmpty())
    {
        return stream;
    }
    
    auto current = container._first;
    do
    {
        stream << current->_data << '\n';
        current = current->_next;
    }
    while (current != container._first);

    return stream;
}

#endif // DATALIST_H