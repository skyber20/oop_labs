#include "lab3/student.hpp"

#include <cstring>
#include <utility>
#include <ostream>
#include <cstddef>

namespace lab3 {

    Student::Student(const char *name, int id) : name_(nullptr), id_(id) {
        const std::size_t size = name == nullptr ? 0 : std::strlen(name);

        name_ = new char[size + 1];

        for (std::size_t i{0}; i < size; ++i) {
            name_[i] = name[i];
        }

        name_[size] = '\0';
    }

    Student::Student() : Student("", 0) {}

    Student::Student(const Student& other) : Student(other.name_, other.id_) {}

    Student::Student(Student&& other) noexcept
        : name_(other.name_), id_(other.id_) {
        other.name_ = nullptr;
        other.id_ = 0;
    }

    Student& Student::operator=(const Student& other) {
        if (this != &other) {
            Student tmp(other);
            swap(tmp);
        }

        return *this;
    }

    Student& Student::operator=(Student&& other) noexcept {
        if (this != &other) {
            Student tmp(std::move(other));
            swap(tmp);
        }

        return *this;
    }

    Student::~Student() {
        delete[] name_;
    }

    const char* Student::name() const noexcept {
        return name_ == nullptr ? "" : name_;
    }

    int Student::id() const noexcept {
        return id_;
    }

    void Student::swap(Student &other) noexcept {
        std::swap(name_, other.name_);
        std::swap(id_, other.id_);
    }

    bool Student::operator==(const Student &other) const {
        return id_ == other.id_;
    }

    std::ostream& operator<<(std::ostream& out, const Student& student) {
        out << "Student(name=" << student.name() << ", id=" << student.id() << ")";
        return out;
    }

}
