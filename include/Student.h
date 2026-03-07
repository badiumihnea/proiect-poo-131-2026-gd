//
// Created on 3/4/2026.
//
//
// #ifndef OOP_STUDENT_H
// #define OOP_STUDENT_H
// #include <iostream>
// #include <string>
// #include <vector>
//
//
// class Student {
//     int nr_matricol;
//     std::string nume;
//     std::vector<std::string> preferinte;
//
// public:
//     Student(int nr_matricol, const std::string &nume, const std::vector<std::string> &preferinte);
//
//     ~Student();
//
//     Student(const Student &other)
//         : nr_matricol(other.nr_matricol),
//           nume(other.nume),
//           preferinte(other.preferinte) {
//     }
//
//     Student(Student &&other) noexcept
//         : nr_matricol(other.nr_matricol),
//           nume(std::move(other.nume)),
//           preferinte(std::move(other.preferinte)) {
//     }
//
//     Student & operator=(const Student &other) {
//         if (this == &other)
//             return *this;
//         nr_matricol = other.nr_matricol;
//         nume = other.nume;
//         preferinte = other.preferinte;
//         return *this;
//     }
//
//     Student & operator=(Student &&other) noexcept {
//         if (this == &other)
//             return *this;
//         nr_matricol = other.nr_matricol;
//         nume = std::move(other.nume);
//         preferinte = std::move(other.preferinte);
//         return *this;
//     }
//
//     friend std::ostream & operator<<(std::ostream &os, const Student &student) {
//         return os
//                << "nr_matricol: " << student.nr_matricol
//                << " nume: " << student.nume
//                << " preferinte: " << student.preferinte;
//     }
// };
//
//
// #endif //OOP_STUDENT_H