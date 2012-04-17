#include <iostream>
#include <typeinfo.h>
#include <map>
#include <functional>

// 3 way with RTTI and typeid
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

typedef std::pair<type_info const*, type_info const*> types;
struct TypeInfoLess : std::binary_function <types,types,bool> {
    bool operator()(types const& type1, types const& type2) {
        return type1.first->before(*type2.first) 
            || type1.first == type2.first
            && (type1.second)->before(*type2.second);
    }
};

std::map<types, bool (*)(Shape const*, Shape const*), TypeInfoLess> matcher;

bool intersectTT(Shape const* s1, Shape const* s2) {
    std::cout << "Triangle vs Triangle" << std::endl;
    return true;
}

bool intersectRR(Shape const* s1, Shape const* s2) {
    std::cout << "Rectangle vs Rectangle" << std::endl;
    return true;
}

bool intersectTR(Shape const* s1, Shape const* s2) {
    std::cout << "Triangle vs Rectangle" << std::endl;
    return true;
}

bool intersectRT(Shape const* s1, Shape const* s2) {
    std::cout << "Rectangle vs Triangle" << std::endl;
    return true;
}

bool intersect(Shape const* s1, Shape const* s2) {
    if (matcher.size() == 0) {
        matcher.insert(std::make_pair(
            std::make_pair(&typeid(Triangle),  &typeid(Triangle)),  
            intersectTT));
        matcher.insert(std::make_pair(
            std::make_pair(&typeid(Rectangle), &typeid(Rectangle)),
            intersectRR));
        matcher.insert(std::make_pair(
            std::make_pair(&typeid(Triangle),  &typeid(Rectangle)), 
            intersectTR));
        matcher.insert(std::make_pair(
            std::make_pair(&typeid(Rectangle), &typeid(Triangle)),  
            intersectRT));
    }

    return matcher[std::make_pair(&typeid(*s1), &typeid(*s2))](s1, s2);
}

int main() {
    Shape* s1 = new Rectangle;
    Shape* s2 = new Triangle;

    intersect(s1, s2);

    delete s1;
    delete s2;
    return 0;
}