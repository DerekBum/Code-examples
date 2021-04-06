#include "Circle.hpp"

Circle::Circle(int id, int x, int y, int radius, const char *label) : Figure(id, x, y), radius(radius) {
    this->label = new char[strlen(label) + 1];
    strcpy(this->label, label);
}

Circle::~Circle() {
    delete [] label;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = ",
           id, x, y, radius);
    for (int i = 0; label[i] != '\0'; i++)
        printf("%c", label[i]);
    printf("\n");
}

void Circle::zoom(int factor) {
    radius *= factor;
}

bool Circle::is_inside(int x, int y) const {
    int distance = (this->x - x) * (this->x - x) + (this->y - y) * (this->y - y);
    return (distance <= radius * radius);
}