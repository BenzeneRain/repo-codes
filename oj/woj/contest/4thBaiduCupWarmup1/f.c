#include <iostream>
using namespace std;

#define out(x) (cout << #x << ": " << x << endl)
typedef long long int64;
const int maxint = 0x7FFFFFFF;
const int64 maxint64 = 0x7FFFFFFFFFFFFFFFLL;
template <class T> void show(T a, int n) { for (int i = 0; i < n; ++i) cout << a[i] << ' '; cout << endl; }
template <class T> void show(T a, int r, int l) { for (int i = 0; i < r; ++i) show(a[i], l); cout << endl; }

const int maxn = 200;

typedef struct point_t
{
    int x, y;
};

typedef struct polygon_t
{
    int n;
    point_t p[maxn];
};

int operator <(const point_t &a, const point_t &b)
{
    return a.y < b.y || a.y == b.y && a.x < b.x;
}

point_t operator -(const point_t &a, const point_t &b)
{
    point_t ret;
    ret.x = a.x - b.x;
    ret.y = a.y - b.y;
    return ret;
}

double dist(const point_t &a, const point_t &b)
{
    return sqrt(double((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

int cross(const point_t &a, const point_t &b)
{
    return a.x * b.y - a.y * b.x;
}

int turn_left(const point_t &a, const point_t &b, const point_t &c)
{
    return cross(b - a, c - b) > 0;
}

class point_set_c
{
public:
    void init(int _n, point_t _p[]);
    polygon_t convex_hull();
private:
    int n;
    point_t p[maxn];
};

void point_set_c::init(int _n, point_t _p[maxn])
{
    n = _n;
    for (int i = 0; i < n; i++)
        p[i] = _p[i];
}

polygon_t point_set_c::convex_hull()
{
    int stack[maxn];
    int top = 1;
    stack[0] = 0;

    sort(p, p + n);

    for (int i = 1; i < n;)
    {
        if (top == 1 || turn_left(p[stack[top - 2]], p[stack[top - 1]], p[i]))
            stack[top++] = i++;
        else top--;
    }
    int t_top = top;
    for (int i = n - 2; i >= 0;)
    {
        if (top == t_top || turn_left(p[stack[top - 2]], p[stack[top - 1]], p[i]))
            stack[top++] = i--;
        else top--;
    }
    
    polygon_t ret;
    ret.n = 0;
    for (int i = 0; i < top - 1; i++)
        ret.p[ret.n++] = p[stack[i]];
    return ret;
}

int main()
{
	class point_set_c 
}
