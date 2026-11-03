#pragma once

#include "lab3/student.hpp"

#include <cstddef>

namespace lab3 {

    class StudentSet {
    private:
        std::size_t size_;
        std::size_t capacity_;
        Student* data_;

    public:
        StudentSet();
        StudentSet(const StudentSet& other);
        StudentSet(StudentSet&& other) noexcept;
        StudentSet& operator=(const StudentSet& other);
        StudentSet& operator=(StudentSet&& other) noexcept;
        ~StudentSet();

        [[nodiscard]] std::size_t size() const noexcept;

        void swap(StudentSet& other) noexcept;

        [[nodiscard]] bool empty() const noexcept;
        [[nodiscard]] bool contains(const Student& student) const;
        bool add(const Student& student);
        bool remove(const Student& student);

        StudentSet& operator+=(const Student& other);
        StudentSet& operator-=(const Student& other);
        bool operator==(const StudentSet& other) const;
        bool operator!=(const StudentSet& other) const;
        bool operator()(const Student& student) const;
        friend std::ostream& operator<<(std::ostream& out, const StudentSet& set);

        StudentSet operator|(const StudentSet& other) const;
        StudentSet operator&(const StudentSet& other) const;
        StudentSet operator-(const StudentSet& other) const;
    };

}