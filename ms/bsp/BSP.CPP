/* Research Program for Binary Space Partition Tree */

#include <stdio.h>

class Point3f {
  public:
    float x, y, z;
    Point3f();
    Point3f(Point3f& pt);
    Point3f(float _x, float _y, float _z);
    int operator==(const Point3f& pt) const;
    int operator!=(const Point3f& pt) const;
};

Point3f::Point3f() { x = y = z = 0.0f;}

Point3f::Point3f(Point3f& pt) 
{ x = pt.x; y = pt.y; z = pt.z;}

Point3f::Point3f(float _x, float _y, float _z) 
{ x = _x; y = _y; z = _z;}

int Point3f::operator==(const Point3f& pt) const 
{ return (x == pt.x) && (y == pt.y) && (z == pt.z);}

int Point3f::operator!=(const Point3f& pt) const
{ return (x != pt.x) || (y != pt.y) || (z != pt.z);}

class Box3f : public Point3f {
  public:
    Point3f ep;
    Box3f();
    Box3f(Box3f& box);
    Box3f(Point3f& _sp, Point3f& _ep);
};

Box3f::Box3f() {}

Box3f::Box3f(Box3f& box) : Point3f(box), ep(box.ep) {}

Box3f::Box3f(Point3f& _sp, Point3f& _ep) : Point3f(_sp), ep(_ep) {}

class OctTreeNode2f {
  public:
    float min, max;
    Point3f *obj;
    OctTreeNode2f *in, *out;
    OctTreeNode2f();
    OctTreeNode2f(float _min, float _max);
};

OctTreeNode2f::OctTreeNode2f() { min = max = 0.0f;}

OctTreeNode2f::OctTreeNode2f(float _min, float _max)
{ min = _min; max = _max;}


#include <windows.h>
void main() {
  printf("Binary Space Partition Tree Research\n");
  LARGE_INTEGER li, ct;
  if (QueryPerformanceFrequency(&li)) {
    printf("QueryPerformanceFrequency is supported %d:%d\n", li.LowPart, li.HighPart);
    for (int i=0; i<10; i++) {
      QueryPerformanceCounter(&ct);
      printf("QueryPerformanceCounter is %d:%d\n", ct.LowPart, ct.HighPart);
    }
  }
}

