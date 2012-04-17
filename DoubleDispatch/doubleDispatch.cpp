#include <iostream>

// 2 way. Double dispatch
class Rectangle;
class Triangle;
class Shape {
public:
    virtual bool intersects(Triangle const*)  const = 0;
    virtual bool intersects(Rectangle const*) const = 0;
    virtual bool intersects(Shape const*)     const = 0;
    virtual ~Shape() {};
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
    s1->intersects(s2);
    return true;
}

class Triangle : public Shape {
public:
    bool intersects(Triangle const* s) const {
        return intersect(this, s);
    }
    bool intersects(Rectangle const* s) const {
        return intersect(this, s);
    }
    bool intersects(Shape const* s) const {
        return s->intersects(this);
    }
    ~Triangle() {}
};

class Rectangle : public Shape {
public:
    bool intersects(Triangle const* s) const {
        return intersect(s, this);
    }
    bool intersects(Rectangle const* s) const {
        return intersect(this, s);
    }
    bool intersects(Shape const* s) const {
        return s->intersects(this);
    }
    ~Rectangle() {}
};

int main() {
    Shape* s1 = new Rectangle;
    Shape* s2 = new Triangle;

    intersect(s1, s2);

    delete s1;
    delete s2;
    return 0;
}