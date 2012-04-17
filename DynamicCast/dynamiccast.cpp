#include <iostream>

// 1 way with dynamic casts
class Shape {
    public:
    virtual ~Shape() {}

};

class Triangle : public Shape {
    public:
    ~Triangle() {}
};

class Rectangle : public Shape {
    public:
    ~Rectangle() {}
};

bool intersect(Triangle const* s1, Triangle const* s2) {
    std::cout << "Triangle vs Triangle" << std::endl;
    return true;
}

bool intersect(Rectangle const* s1, Rectangle const* s2) {
    std::cout << "Rectangle vs Rectangle" << std::endl;
    return true;
}

bool intersect(Triangle const* s1, Rectangle const* s2) {
    std::cout << "Triangle vs Rectangle" << std::endl;
    return true;
}

bool intersect(Shape const* s1, Shape const* s2) {
    if (Triangle const* t1 = dynamic_cast<Triangle const*>(s1)) {
        if (Triangle const* t2 = dynamic_cast<Triangle const*>(s2)) {
            return intersect(t1, t2);
        } else if (Rectangle const* r2 = dynamic_cast<Rectangle const*>(s2)) {
            return intersect(t1, r2);
        }
    } else if (Rectangle const* r1 = dynamic_cast<Rectangle const*>(s1)) {
        if (Rectangle const* r2 = dynamic_cast<Rectangle const*>(s2)) {
            return intersect(r1, r2);
        } else if (Triangle const* t2 = dynamic_cast<Triangle const*>(s2)) {
            return intersect(t2, r1);
        }
    }

    return false;
}

int main() {
    Shape* s1 = new Rectangle;
    Shape* s2 = new Triangle;

    intersect(s1, s2);

    delete s1;
    delete s2;
    return 0;
}