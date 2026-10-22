#pragma once

#include <cstddef>
#include <iosfwd>

namespace lab2 {

class String {
private:
    std::size_t size_;
    std::size_t capacity_;
    char* data_;
    void UpdateCapacity();

public:
    String();
    explicit String(const char* mes);
    String(const String& other);
    String(String&& other) noexcept;
    String& operator=(String other);

    ~String();

    void swap(String& other) noexcept;

    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] std::size_t capacity() const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] const char* c_str() const;

    void push_back(char c);
    void append(char c);
    void append(const char* text);
    void append(const String& other);

    static constexpr std::size_t npos{static_cast<std::size_t>(-1)};
    std::size_t find(const char* text) const;
    void print(std::ostream& out) const;
    String wrap(std::size_t width) const;
};

}
