#include "lab3/student_set.hpp"

#include <utility>
#include <ostream>
#include <cstddef>

namespace lab3 {

    StudentSet::StudentSet() : size_(0), capacity_(0), data_(nullptr) {}

    StudentSet::~StudentSet() {
        delete[] data_;
    }

    StudentSet::StudentSet(const StudentSet& other)
        : size_(other.size_), capacity_(other.capacity_),
          data_(capacity_ == 0 ? nullptr : new Student[capacity_]) {
        try {
            for (std::size_t i{0}; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        catch (...) {
            delete[] data_;
            throw;
        }
    }

    StudentSet::StudentSet(StudentSet&& other) noexcept
        : size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
          other.size_ = 0;
          other.capacity_ = 0;
          other.data_ = nullptr;
    }

    StudentSet& StudentSet::operator=(const StudentSet& other) {
        if (this != &other) {
            StudentSet tmp(other);
            swap(tmp);
        }

        return *this;
    }

    StudentSet& StudentSet::operator=(StudentSet&& other) noexcept {
        if (this != &other) {
            StudentSet tmp(std::move(other));
            swap(tmp);
        }

        return *this;
    }

    void StudentSet::swap(StudentSet& other) noexcept {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(data_, other.data_);
    }

    std::size_t StudentSet::size() const noexcept {
        return size_;
    }

    bool StudentSet::empty() const noexcept {
        return size_ == 0;
    }

    bool StudentSet::contains(const Student& student) const {
        for (std::size_t i{0}; i < size_; ++i) {
            if (data_[i] == student) return true;
        }

        return false;
    }

    bool StudentSet::operator()(const Student& student) const {
        return contains(student);
    }

    bool StudentSet::add(const Student& student) {
        if (contains(student)) return false;

        if (size_ == capacity_) {
            std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;

            Student* new_data = new Student[new_capacity];

            try {
                for (std::size_t i{0}; i < size_; ++i) {
                    new_data[i] = data_[i];
                }

                new_data[size_] = student;
            }
            catch (...) {
                delete[] new_data;
                throw;
            }

            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
        else {
            data_[size_] = student;
        }

        ++size_;
        return true;
    }

    bool StudentSet::remove(const Student& student) {
        for (std::size_t i{0}; i < size_; ++i) {
            if (data_[i] == student) {
                for (std::size_t j{i}; j + 1 < size_; ++j) {
                    data_[j] = std::move(data_[j + 1]);
                }

                --size_;
                return true;
            }
        }

        return false;
    }

    StudentSet& StudentSet::operator+=(const Student& other) {
        add(other);
        return *this;
    }

    StudentSet& StudentSet::operator-=(const Student& other) {
        remove(other);
        return *this;
    }

    bool StudentSet::operator==(const StudentSet& other) const {
        if (size_ != other.size_) return false;

        for (std::size_t i{0}; i < size_; ++i) {
            if (!contains(other.data_[i])) return false;
        }

        return true;
    }

    bool StudentSet::operator!=(const StudentSet& other) const {
        return !(*this == other);
    }

    std::ostream& operator<<(std::ostream& out, const StudentSet& set) {
        out << "{ ";

        for (std::size_t i{0}; i < set.size_; ++i) {
            out << set.data_[i];

            if (i + 1 < set.size_) {
                out << ", ";
            }
        }

        out << " }";
        return out;
    }

    StudentSet StudentSet::operator|(const StudentSet& other) const {
        StudentSet result(*this);

        for (std::size_t i{0}; i < other.size_; ++i) {
            result.add(other.data_[i]);
        }

        return result;
    }

    StudentSet StudentSet::operator&(const StudentSet& other) const {
        StudentSet result;

        for (std::size_t i{0}; i < size_; ++i) {
            if (other.contains(data_[i])) {
                result.add(data_[i]);
            }
        }

        return result;
    }

    StudentSet StudentSet::operator-(const StudentSet& other) const {
        StudentSet result;

        for (std::size_t i{0}; i < size_; ++i) {
            if (!other.contains(data_[i])) {
                result.add(data_[i]);
            }
        }

        return result;
    }

}
