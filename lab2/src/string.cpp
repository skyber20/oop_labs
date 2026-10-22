#include "lab2/string.hpp"

#include <cctype>
#include <cstring>
#include <ostream>
#include <stdexcept>
#include <utility>

namespace lab2 {
String::String(const char* mes)
    : size_(mes == nullptr ? 0 : std::strlen(mes)), capacity_(size_ > 0 ? size_ : 1), data_(new char[capacity_ + 1]) {
    for (std::size_t i{0}; i < size_; ++i) {
        data_[i] = mes[i];
    }

    data_[size_] = '\0';
}

String::String() : String("") {}

String::String(const String& other)
    : size_(other.size_), capacity_(other.data_ == nullptr ? 1 : other.capacity_), data_(new char[capacity_ + 1]) {
    if (other.data_ != nullptr) {
        for (std::size_t i{0}; i < other.size_ + 1; ++i) {
            data_[i] = other.data_[i];
        }
    } else {
        data_[0] = '\0';
    }
}

String::String(String&& other) noexcept
    : size_(std::exchange(other.size_, 0)),
      capacity_(std::exchange(other.capacity_, 0)),
      data_(std::exchange(other.data_, nullptr)) {}

String& String::operator=(String other) {
    swap(other);
    return *this;
}

String::~String() {
    delete[] data_;
}

void String::UpdateCapacity() {
    if (capacity_ > (npos - 1) / 2) {
        throw std::length_error("Слишком длинная строка");
    }
    const std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    char* new_data = new char[new_capacity + 1];

    for (std::size_t i{0}; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    new_data[size_] = '\0';

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

void String::swap(String& other) noexcept {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
}

void String::push_back(char c) {
    if (capacity_ == size_) {
        UpdateCapacity();
    }
    data_[size_] = c;
    data_[++size_] = '\0';
}

void String::append(char c) {
    push_back(c);
}

void String::append(const String& other) {
    const std::size_t length = other.size_;
    for (std::size_t i{0}; i < length; ++i) {
        push_back(other.data_[i]);
    }
}

void String::append(const char* text) {
    append(String(text));
}

std::size_t String::size() const {
    return size_;
}

std::size_t String::capacity() const {
    return capacity_;
}

bool String::empty() const {
    return size_ == 0;
}

const char* String::c_str() const {
    return data_ == nullptr ? "" : data_;
}

std::size_t String::find(const char* text) const {
    const std::size_t length = text == nullptr ? 0 : std::strlen(text);
    if (length == 0) {
        return 0;
    }
    if (length > size_) {
        return npos;
    }

    for (std::size_t i{0}; i <= size_ - length; ++i) {
        std::size_t j{0};
        while (j < length && data_[i + j] == text[j]) {
            ++j;
        }
        if (j == length) {
            return i;
        }
    }
    return npos;
}

void String::print(std::ostream& out) const {
    for (std::size_t i{0}; i < size_; ++i) {
        out << data_[i];
    }
}

String String::wrap(std::size_t width) const {
    if (width == 0) {
        throw std::invalid_argument("Ширина должна быть больше нуля");
    }

    String result;
    std::size_t line_size{0};
    std::size_t i{0};

    while (i < size_) {
        if (data_[i] == '\n') {
            result.push_back('\n');
            line_size = 0;
            ++i;
            continue;
        }
        if (std::isspace(static_cast<unsigned char>(data_[i]))) {
            ++i;
            continue;
        }

        const std::size_t start = i;
        while (i < size_ && !std::isspace(static_cast<unsigned char>(data_[i]))) {
            ++i;
        }
        const std::size_t word_size = i - start;
        if (word_size > width) {
            throw std::invalid_argument("Слово длиннее заданной ширины");
        }

        if (line_size > 0) {
            if (line_size == width || word_size > width - line_size - 1) {
                result.push_back('\n');
                line_size = 0;
            } else {
                result.push_back(' ');
                ++line_size;
            }
        }

        for (std::size_t j{start}; j < i; ++j) {
            result.push_back(data_[j]);
        }
        line_size += word_size;
    }
    return result;
}

}
