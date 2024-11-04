#include <iostream>
#include <vector>
using namespace std;

class Geometricshape {
public:
    virtual float area() {
        cout << "Calculating area in Geometricshape (no specific shape chosen).\n";
        return 0;
    }
};

class circle : public Geometricshape {
public:
    int r;
    float area() override {
        cout << "Circle Area: " << 3.14 * r * r << endl;
        return 3.14 * r * r;
    }
};

class triangle : public Geometricshape {
public:
    float b, h;
    float area() override {
        cout << "Triangle Area: " << (0.5 * b) * h << endl;
        return (0.5 * b) * h;
    }
};

class rectangle : public Geometricshape {
public:
    int w, h;
    float area() override {
        cout << "Rectangle Area: " << w * h << endl;
        return w * h;
    }
};

float calcArea(Geometricshape* shape) {
    return shape->area();
}

int main() {
    int choice;
    circle c;
    triangle t;
    rectangle r;

    c.r = 2;
    t.b = 4.0;
    t.h = 9.0;
    r.h = 3;
    r.w = 2;
    

    do {
        cout << "\nChoose a shape to calculate the area (enter 0 to exit):\n";
        cout << "1. Geometric Shape (Default)\n";
        cout << "2. Circle\n";
        cout << "3. Triangle\n";
        cout << "4. Rectangle\n";
        cout << "5. Avrage\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            calcArea(new Geometricshape());
            break;
        case 2:
            calcArea(&c);
            break;
        case 3:
            calcArea(&t);
            break;
        case 4:
            calcArea(&r);
            break;
        case 5:
        {
            vector<Geometricshape*> shap;

            shap.push_back(&c);
            shap.push_back(&t);
            shap.push_back(&r);
            float avarea = 0;
            for (int i = 0; i < shap.size(); i++) {
                avarea += calcArea(shap[i]);
            }
            cout << "Avrage area = " << avarea / shap.size() << endl;
            break;
        }
        case 0:
            cout << "Exiting the program!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
