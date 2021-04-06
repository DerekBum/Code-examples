#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

class Employee {
public:
    Employee(int32_t TYPE, std::string name, int32_t base_salary);
    explicit Employee(int32_t TYPE);
    virtual ~Employee() = default;

    std::string get_name() const;

    virtual int32_t salary() const;
    virtual std::ostream& print(std::ostream& out) const;
    virtual std::ofstream& bin_print(std::ofstream& out) const;
    virtual std::istream& read(std::istream& in);
    virtual std::ifstream& bin_read(std::ifstream& in);

protected:
    const int TYPE;

private:
    std::string name_;
    int32_t _base_salary;
};

class Developer : public Employee {
public:
    Developer(std::string name, int32_t base_salary, bool has_bonus);
    Developer();

    int32_t salary() const override;
    std::istream& read(std::istream& in) override;
    std::ostream& print(std::ostream& out) const override;
    std::ofstream& bin_print(std::ofstream& out) const override;
    std::ifstream& bin_read(std::ifstream& in) override;

    bool get_bonus() const;
private:
    const int bonus_salary = 1000;
    bool _has_bonus;
};

std::ostream& operator<< (std::ostream&, const Employee&);
std::istream& operator>> (std::istream&, Employee&);
std::ofstream& operator<< (std::ofstream&, const Employee&);
std::ifstream& operator>> (std::ifstream&, Employee&);


class SalesManager : public Employee {
public:
    SalesManager(std::string name, int32_t base_salary, int32_t sold_nm, int32_t price);
    SalesManager();

    int32_t salary() const override;
    std::istream& read(std::istream& in) override;
    std::ostream& print(std::ostream& out) const override;
    std::ofstream& bin_print(std::ofstream& out) const override;
    std::ifstream& bin_read(std::ifstream& in) override;

    int32_t get_sold_nm() const;
    int32_t get_price() const;
private:
    const double price_multiplier = 0.01;
    int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
    ~EmployeesArray();

    void add(Employee *e);
    int32_t total_salary() const;
    void print_all() const;
    void print_bin(std::ofstream& out) const;
    void add_all(std::ifstream& in);

    static Employee * fabric_method(int32_t);
    Employee * read_employee(std::istream& in);
    Employee * read_bin_employee(std::ifstream& in);
    
private:
    int _sz = 0;
    int _total_salary = 0;
    std::vector <Employee*> _employees;
};