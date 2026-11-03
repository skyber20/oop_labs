#pragma once

#include <ostream>

namespace lab3 {

    class Student {
    private:
        char* name_;
        int id_;

    public:
        Student();
        Student(const char* name, int id);
        Student(const Student& other);
        Student(Student&& other) noexcept;
        Student& operator=(const Student& other);
        Student& operator=(Student&& other) noexcept;
        ~Student();

        [[nodiscard]] const char* name() const noexcept;
        [[nodiscard]]  int id() const noexcept;

        bool operator==(const Student& other) const;
        friend std::ostream& operator<<(std::ostream& out, const Student& student);

        void swap(Student& other) noexcept;
    };

}