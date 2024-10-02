#include <iostream>
#include <vector>

struct Grid {
    std::vector<Point>* points;

    Grid()
    {
        points = new std::vector<Point>();
    }

    ~Grid()
    {
        delete points;
        points = nullptr;
    }

    void Emplace(Point p)
    {
        points->emplace_back(std::move(p));
    }
};

struct Point {
    int x;
    int y;

    Point()
    {
        this->x = 0;
        this->y = 0;
    }

    ~Point()
    {
        std::cout << "Point destroyed!" << std::endl;
    }

};

void print(Point &p)
{
    std::cout << "x: " << p.x << ", y: " << p.y << std::endl;
}

int main()
{
    Grid *g = new Grid();

    for(int i = 0; i < 1000; i++)
    {

        Point p = Point();
        g->Emplace(std::move(p));
    }

    delete g;
    g = nullptr;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
