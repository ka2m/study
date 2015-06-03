#define M 3
typedef float vec[M];
typedef float mat[M][M];

extern mat T;

value struct point {
	float x, y;

	point(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

value struct line {
	point start, end;
	System::String^ name;

	line(point start, point end) {
		this->start = start;
		this->end = end;
		this->name = "";
	}

	line(point start, point end, System::String^ name) {
		this->start = start;
		this->end = end;
		this->name = name;
	}
};

typedef System::Collections::Generic::List<point> polygon;

void times(mat a, mat b, mat c);
void timesMatVec(mat a, vec b, vec c);
void set(mat a, mat b);
void point2vec(point a, vec b);
void vec2point(vec a, point &b);
void makeHomogenVec(float x, float y, vec c);
void unit(mat a);
void move(float Tx, float Ty, mat c);
void rotate(float phi, float x, float y, mat c);
void scale(float Sx, float Sy, mat c);
void reflect(bool xAxis, bool yAxis, mat c);
void frame (float Vx, float Vy, float Vcx, float Vcy,
			float Wx, float Wy, float Wcx, float Wcy,
			mat c);

void normalize(vec& v);
void normal(point s, point e, vec& n);
void normal(vec s, vec& n);
float multSkalar(vec v1, vec v2);
void sum(point p1, point p2, point& r);
void mult(point p, float k, point& r);
void sum(vec v1, vec v2, vec& r);
void mult(vec v1, float k, vec& r);
void sub(point p1, point p2, point& r);
void sub(vec v1, vec v2, vec& r);
float vecLength(vec v);