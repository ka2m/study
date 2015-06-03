#define M 3
typedef float vec[M];
typedef float mat[M][M];

extern mat T;

value struct point {
	float x, y;
};

value struct line {
	point start, end;
	System::String^ name;
};

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