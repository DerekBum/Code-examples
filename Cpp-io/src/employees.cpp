#include "employees.h"

Employee::Employee(int32_t TYPE, std::string name, int32_t base_salary)
        : TYPE(TYPE), name_(std::move(name)), _base_salary(base_salary) {}

Employee::Employee(int32_t TYPE) : TYPE(TYPE) {}

Developer::Developer(std::string name, int32_t base_salary, bool has_bonus)
        : Employee(1, std::move(name), base_salary), _has_bonus(has_bonus) {}

Developer::Developer() : Employee(1) {}

SalesManager::SalesManager(std::string name, int32_t base_salary, int32_t sold_nm, int32_t price)
        : Employee(2, std::move(name), base_salary), _sold_nm(sold_nm), _price(price) {}

SalesManager::SalesManager() : Employee(2) {}

std::string Employee::get_name() const {
    return name_;
}

int Employee::salary() const {
    return _base_salary;
}

Employee * EmployeesArray::fabric_method(int32_t type) {
    switch (type) {
        case 1:
            return new Developer;
        case 2:
            return new SalesManager;
        default:
            assert("Wrong type of employee");
            return new Employee(0);
    }
}

Employee * EmployeesArray::read_employee(std::istream& in) {
    int32_t type;
    Employee* emp;
    in >> type;
    emp = EmployeesArray::fabric_method(type);
    in >> *emp;
    return emp;
}

std::istream & Employee::read(std::istream &in) {
    return in >> name_ >> _base_salary;
}

std::istream & Developer::read(std::istream &in) {
    return Employee::read(in) >> _has_bonus;
}

std::istream & SalesManager::read(std::istream &in) {
    return Employee::read(in) >> _sold_nm >> _price;
}

std::istream& operator>> (std::istream& in, Employee& emp) {
    return emp.read(in);
}

static void write_bin_var(std::ofstream& out, const int32_t *ptr, size_t sz) {
    out.write(reinterpret_cast<const char*>(ptr), sz);
}

std::ofstream & Employee::bin_print(std::ofstream &out) const {
    out << name_ << '\0';
    write_bin_var(out, &_base_salary, sizeof(int32_t));
    return out;
}

std::ofstream & Developer::bin_print(std::ofstream &out) const {
    write_bin_var(out, &TYPE, sizeof(int32_t));
    Employee::bin_print(out);
    write_bin_var(out, (int32_t *)&_has_bonus, sizeof(bool));
    return out;
}

std::ofstream & SalesManager::bin_print(std::ofstream &out) const {
    write_bin_var(out, &TYPE, sizeof(int32_t));
    Employee::bin_print(out);
    write_bin_var(out, &_sold_nm, sizeof(int32_t));
    write_bin_var(out, &_price, sizeof(int32_t));
    return out;
}

static void read_bin_var(std::ifstream& in, int32_t *ptr, size_t sz) {
    in.read(reinterpret_cast<char *>(ptr), sz);
}

std::ifstream& operator>> (std::ifstream& in, Employee& emp) {
    return emp.bin_read(in);
}

std::ifstream & Employee::bin_read(std::ifstream &in) {
    char symbol;
    in >> symbol;
    while (symbol != '\0') {
        name_ += symbol;
        in >> symbol;
    }
    read_bin_var(in, &_base_salary, sizeof(int32_t));
    return in;
}

std::ifstream & Developer::bin_read(std::ifstream &in) {
    Employee::bin_read(in);
    read_bin_var(in, (int32_t*)&_has_bonus, sizeof(bool));
    return in;
}

std::ifstream & SalesManager::bin_read(std::ifstream &in) {
    Employee::bin_read(in);
    read_bin_var(in, &_sold_nm, sizeof(int32_t));
    read_bin_var(in, &_price, sizeof(int32_t));
    return in;
}

Employee * EmployeesArray::read_bin_employee(std::ifstream& in) {
    int32_t type;
    Employee* emp;
    read_bin_var(in, &type, sizeof(int32_t));
    emp = EmployeesArray::fabric_method(type);
    in >> *emp;
    return emp;
}

std::ofstream& operator<< (std::ofstream& out, Employee& emp) {
    return emp.bin_print(out);
}

std::ostream & Employee::print(std::ostream &out) const {
    out << "Name: " << name_ << std::endl;
    return out << "Base Salary: " << _base_salary << std::endl;
}

std::ostream & Developer::print(std::ostream &out) const {
    out << "Developer" << std::endl;
    Employee::print(out);
    return out << "Has bonus: " << (_has_bonus ? "+" : "-") << std::endl;
}

std::ostream & SalesManager::print(std::ostream &out) const {
    out << "Sales Manager" << std::endl;
    Employee::print(out);
    out << "Sold items: " << _sold_nm << std::endl;
    return out << "Item price: " << _price << std::endl;
}

std::ostream& operator<< (std::ostream& out, const Employee& emp) {
    return emp.print(out);
}

bool Developer::get_bonus() const {
    return _has_bonus;
}

int Developer::salary() const {
    return Employee::salary() + bonus_salary * _has_bonus;
}

int SalesManager::get_sold_nm() const {
    return _sold_nm;
}

int SalesManager::get_price() const {
    return _price;
}

int SalesManager::salary() const {
    return Employee::salary() + _sold_nm * _price * price_multiplier;
}

EmployeesArray::~EmployeesArray() {
    while (!_employees.empty()) {
        delete _employees.back();
        _employees.pop_back();
    }
}

void EmployeesArray::add(Employee *e) {
    _employees.push_back(e);
    _sz++;
    _total_salary += e->salary();
}

int EmployeesArray::total_salary() const {
    return _total_salary;
}

void EmployeesArray::print_all() const {
    for (int i = 0; i < _sz; i++)
        std::cout << i + 1 << ". " << *_employees[i];
    std::cout << "== Total salary: " << total_salary() << std::endl << std::endl;
}

void EmployeesArray::print_bin(std::ofstream& out) const {
    write_bin_var(out, &_sz, sizeof(int32_t));
    for (int i = 0; i < _sz; i++)
        out << *_employees[i];
}

void EmployeesArray::add_all(std::ifstream &in) {
    int32_t file_size;
    read_bin_var(in, &file_size, sizeof(int32_t));
    for (int i = 0; i < file_size; i++)
        add(read_bin_employee(in));
}