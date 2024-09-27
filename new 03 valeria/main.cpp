//
//  main.cpp
//  new 03 valeria
//
//  Created by Valeria  Bukova on 27.09.2024.
//

#include <iostream>

class Reservoir {
private:
    char name[100];
    double length;
    double maxDepth;
    char type[50];

    
    void copyString(char* dest, const char* src, int maxLength) {
        int i = 0;
        while (i < maxLength - 1 && src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

    
    bool compareString(const char* str1, const char* str2) const {
        int i = 0;
        while (str1[i] != '\0' && str2[i] != '\0') {
            if (str1[i] != str2[i]) {
                return false;
            }
            i++;
        }
        return str1[i] == str2[i];
    }

public:
    Reservoir() : width(0), length(0), maxDepth(0) {
        name[0] = '\0';
        copyString(type, "неизвестно", sizeof(type));
    }

    Reservoir(const char* n, double w, double l, double d, const char* t)
        : width(w), length(l), maxDepth(d) {
        copyString(name, n, sizeof(name));
        copyString(type, t, sizeof(type));
    }

    Reservoir(const Reservoir& other)
        : width(other.width), length(other.length), maxDepth(other.maxDepth) {
        copyString(name, other.name, sizeof(name));
        copyString(type, other.type, sizeof(type));
    }

    double volume() const {
        return width * length * maxDepth;
    }

    
    double surfaceArea() const {
        return width * length;
    }

   
    bool isSameType(const Reservoir& other) const {
        return compareString(type, other.type);
    }

   
    bool compareSurfaceArea(const Reservoir& other) const {
        if (isSameType(other)) {
            return surfaceArea() == other.surfaceArea();
        }
        return false;
    }

    void setName(const char* n) {
        copyString(name, n, sizeof(name));
    }

    const char* getName() const {
        return name;
    }

    void setWidth(double w) {
        width = w;
    }

    double getWidth() const {
        return width;
    }

    void setLength(double l) {
        length = l;
    }

    double getLength() const {
        return length;
    }

    void setMaxDepth(double d) {
        maxDepth = d;
    }

    double getMaxDepth() const {
        return maxDepth;
    }

    void setType(const char* t) {
        copyString(type, t, sizeof(type));
    }

    const char* getType() const {
        return type;
    }

    Reservoir& operator=(const Reservoir& other) {
        if (this == &other) return *this;

        copyString(name, other.name, sizeof(name));
        copyString(type, other.type, sizeof(type));

        width = other.width;
        length = other.length;
        maxDepth = other.maxDepth;

        return *this;
    }

    void display() const {
        std::cout << "Название: " << name << "\n"
                  << "Тип: " << type << "\n"
                  << "Ширина: " << width << " м\n"
                  << "Длина: " << length << " м\n"
                  << "Максимальная глубина: " << maxDepth << " м\n"
                  << "Объем: " << volume() << " м^3\n"
                  << "Площадь водной поверхности: " << surfaceArea() << " м^2\n";
    }
};

class ReservoirArray {
private:
    Reservoir* reservoirs;
    int size;

public:
    ReservoirArray() : reservoirs(nullptr), size(0) {}

    void add(const Reservoir& res) {
        Reservoir* new_reservoirs = new Reservoir[size + 1];
        for (int i = 0; i < size; ++i) {
            new_reservoirs[i] = reservoirs[i];
        }
        new_reservoirs[size] = res;
        delete[] reservoirs;
        reservoirs = new_reservoirs;
        ++size;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Неверный индекс!\n";
            return;
        }

        Reservoir* new_reservoirs = new Reservoir[size - 1];
        for (int i = 0, j = 0; i < size; ++i) {
            if (i != index) {
                new_reservoirs[j++] = reservoirs[i];
            }
        }
        delete[] reservoirs;
        reservoirs = new_reservoirs;
        --size;
    }

    void displayAll() const {
        for (int i = 0; i < size; ++i) {
            reservoirs[i].display();
            std::cout << "----------------------\n";
        }
    }

    ~ReservoirArray() {
        delete[] reservoirs;
    }
};

int main() {
    Reservoir res1("Озеро Байкал", 80, 600, 1642, "озеро");
    Reservoir res2("Средиземное море", 2500, 3800, 5000, "море");
    Reservoir res3("Пруд на даче", 10, 15, 3, "пруд");

    ReservoirArray reservoirArray;
    reservoirArray.add(res1);
    reservoirArray.add(res2);
    reservoirArray.add(res3);

    std::cout << "Информация о водоемах:\n";
    reservoirArray.displayAll();

    return 0;
}
