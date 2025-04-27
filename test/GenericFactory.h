#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <functional>

// ��������ģ����
template<typename BaseType>
class GenericFactory {
public:
    using Creator = std::function<std::unique_ptr<BaseType>()>;

    // ע��������
    template<typename DerivedType>
    void registerType(const std::string& typeName) {
        creators[typeName] = []() -> std::unique_ptr<BaseType> {
            return std::make_unique<DerivedType>();
            };
    }

    // ��������
    std::unique_ptr<BaseType> create(const std::string& typeName) {
        auto it = creators.find(typeName);
        if (it != creators.end()) {
            return it->second();
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, Creator> creators;
};

// ʾ��ʹ��
class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void draw() override { std::cout << "Drawing Circle" << std::endl; }
};

class Rectangle : public Shape {
public:
    void draw() override { std::cout << "Drawing Rectangle" << std::endl; }
};

//int main() {
//    GenericFactory<Shape> shapeFactory;
//
//    // ע������
//    shapeFactory.registerType<Circle>("circle");
//    shapeFactory.registerType<Rectangle>("rectangle");
//
//    // ��������
//    auto circle = shapeFactory.create("circle");
//    auto rect = shapeFactory.create("rectangle");
//
//    if (circle) circle->draw();
//    if (rect) rect->draw();
//
//    return 0;
//}