
#pragma once

#include <stdexcept>
#include <string>

class BufferReader
{
private:
    const uint8_t* _p = NULL;
    const uint8_t* _begin;
    const uint8_t* _end;

public:
    BufferReader(const uint8_t* begin, size_t size)
    {
        _p = begin;
        _begin = begin;
        _end = begin + size;
    }

    template<typename T>
    bool read_next(T* out)
    {
        if ((_end - _p) < sizeof(T))
            return false;

        T x =*reinterpret_cast<const T*>(_p);
        *out = *reinterpret_cast<const T*>(_p);
        _p += sizeof(T);

        return true;
    }

    bool read_next(std::string& out, int len)
    {
        if ((_end - _p) < len)
            return false;

        out.assign(reinterpret_cast<const char*>(_p), len);
        _p += len;

        return true;
    }

    template<typename T>
    bool read_next_or_throw(T* out)
    {
        if (!read_next(out))
            throw std::runtime_error("read_next_or_throw() failed.");

        return true;
    }

    bool read_next_or_throw(std::string& out, int len)
    {
        if (!read_next(out, len))
            throw std::runtime_error("read_next_or_throw() failed.");

        return true;
    }
};
