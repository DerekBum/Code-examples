#include "Scheme.hpp"

Scheme::Scheme(int capacity) : capacity(capacity), size_(0), figures_(new Figure*[capacity]) {}

Scheme::~Scheme() {
    for (int i = 0; i < size_; i++)
        delete figures_[i];
    delete [] figures_;
}

void Scheme::push_back_figure(Figure *fg) {
    figures_[size_] = fg;
    size_++;
}

int Scheme::find_by_id(int id) const {
    for (int i = 0; i < size_; i++)
        if (figures_[i]->get_id() == id)
            return i;
    assert("No such figure");
    return -1;
}

void Scheme::remove_figure(int id) {
    int index = find_by_id(id);
    delete figures_[index];
    for (int i = index + 1; i < size_; i++)
        figures_[i - 1] = figures_[i];
    size_--;
}

void Scheme::print_all_figures() const {
    for (int i = 0; i < size_; i++)
        figures_[i]->print();
}

Figure * Scheme::is_inside_figure(int x, int y) const {
    for (int i = 0; i < size_; i++)
        if (figures_[i]->is_inside(x, y))
            return figures_[i];
    return nullptr;
}

void Scheme::zoom_figure(int id, int factor) {
    int index = find_by_id(id);
    figures_[index]->zoom(factor);
}

void Scheme::move(int id, int new_x, int new_y) {
    int index = find_by_id(id);
    figures_[index]->move(new_x, new_y);
}