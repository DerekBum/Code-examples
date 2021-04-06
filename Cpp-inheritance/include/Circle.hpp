#include "Figure.hpp"
#include <cstring>

class Circle : public Figure {
public:
    Circle(int id, int x, int y, int radius, const char* label);
    ~Circle();
    void print() const override;
    void zoom(int factor) override;
    bool is_inside(int x, int y) const override;

private:
    int radius;
    char* label;
};