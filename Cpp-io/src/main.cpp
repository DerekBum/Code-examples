#include "employees.h"

int main() {
    EmployeesArray employees;

    std::string type;
    std::cin >> type;
    while (type != "exit") {
        if (type == "list")
            employees.print_all();
        else if (type == "add")
            employees.add(employees.read_employee(std::cin));
        else if (type == "load") {
            std::string file_name;
            std::cin >> file_name;
            std::ifstream file(file_name, std::ios_base::binary);
            employees.add_all(file);
            file.close();
        }
        else if (type == "save") {
            std::string file_name;
            std::cin >> file_name;
            std::ofstream file(file_name, std::ios_base::binary);
            employees.print_bin(file);
            file.close();
        }
        std::cin >> type;
    }
    return 0;
}
