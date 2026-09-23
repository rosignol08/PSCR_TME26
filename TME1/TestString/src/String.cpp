#include "String.h"

namespace pr
{

    // TODO: Implement constructor e.g. using initialization list
    String::String(const char *s)
    {
        std::cout << "String constructor called for: " << s << std::endl;
        data = s; // shallow copy
    }

    String::~String()
    {
        std::cout << "String destructor called for: " << (data ? data : "(null)")
                  << std::endl;
        delete[] this;
    }

    String::String(const String &other)
    {
        this->data = new char[length(other.data)];
    }

    String::String(String &&other) noexcept
    {
        this->data = new char[length(other.data)];
        other = nullptr;
    }

    String &String::operator=(const String &other)
    {
        String s = String(other);
        return s;
    }

    String &String::operator=(String &&other) noexcept
    {
        *this = other;
    }

    bool String::operator<(const String &other) const
    {
        if (compare(this->data, other.data) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    std::ostream &operator<<(std::ostream &os, const String &str)
    {
        return os << str.data;
    }

    bool operator==(const String &a, const String &b)
    {
        if (compare(a.data, b.data) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    String operator+(const String &a, const String &b)
    {
        size_t la = length(a.data);
        size_t lb = length(b.data);
        char *buf = new char[la + lb + 1];
        //a
        for (size_t i = 0; i < la; ++i)
            buf[i] = a.data[i];
        //b
        for (size_t j = 0; j < lb; ++j)
            buf[la + j] = b.data[j];
        buf[la + lb] = '\0';

        String s(buf);
        return s;
    }

} // namespace pr
