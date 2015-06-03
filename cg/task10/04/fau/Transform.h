#include <array>
#include <cmath>
#include <vector>

value struct point {
	float x, y;

	point(float ax, float ay) {
		x = ax;
		y = ay;
	}
};

value struct point3D {
	float x, y, z;

	point3D(float ax, float ay, float az) {
		x = ax;
		y = ay;
		z = az;
	}
};


value struct line {
	point start, end;
	System::String^ name;
};

#define M 3
#define M3D 4

typedef std::tr1::array<float, M> vec;
typedef std::tr1::array<vec, M> mat;

typedef std::tr1::array<float, M3D> vec3D;

typedef std::tr1::array<vec3D, M3D> mat3D;

extern mat T;
extern mat3D T3D;



typedef System::Collections::Generic::List<point> polygon;
typedef System::Collections::Generic::List<point3D> polygon3D;

void times(mat a, mat b, mat &c);
void timesMatVec(mat a, vec b, vec &c);
void set(mat a, mat &b);
void point2vec(point a, vec &b);
void vec2point(vec a, point &b);
void makeHomogenVec(float x, float y, vec &c);
void unit(mat &a);
void move(float Tx, float Ty, mat &c);
void rotate(float phi, float x, float y, mat &c);
void scale(float Sx, float Sy, mat &c);


void reflectHorizontal(mat& c);
void reflectVertical(mat& c);

void frame(float Vx, float Vy, float Vcx, float Vcy,
		   float Wx, float Wy, float Wcx, float Wcy,
		   mat &c);


void times (mat3D a, mat3D b, mat3D &c);
void timesMatVec (mat3D a, vec3D b, vec3D &c);

void set (mat3D a, mat3D &b);
void set (point3D a, point &b);


void point2vec (point3D a, vec3D &b);
void vec2point (vec3D a, point3D &b);

void makeHomogenVec (float x, float y, float z, vec3D &c);
void unit (mat3D &a);
void move (float Tx, float Ty, float Tz, mat3D &c);
void rotate (point3D n, float phi, mat3D &c);
void scale (float Sx, float Sy, float Sz, mat3D &c);
void normalize(vec3D &v);

void LookAt (point3D eye, point3D center, point3D up, mat3D &c);
void Ortho (float Vx, float Vy, float near, float far, mat3D &c);
void Frustrum (float Vx, float Vy, float near, float far, mat3D &c);
void Perspective (float fovy, float aspect, float near, float far, mat3D &c);

void add (point3D a, point3D b, point3D &c);
void add (mat3D a, mat3D b, mat3D &c);
void add (vec3D a, vec3D b, vec3D &c);

void sub (vec3D a, vec3D b, vec3D &c);

void mul (mat3D a, float k, mat3D &c);
void mul (vec3D a, float k, vec3D &c);
void mul (vec3D a, vec3D b, vec3D &c);
