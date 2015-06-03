#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <math.h>

std::vector<mat> matrices(0);

mat resizeMat;
mat3D T;

void times(mat a, mat b, mat& c) {
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < M; j++) {
			float skalaar = 0;
			for(int k = 0; k < M; k++)
				skalaar += a[i][k] * b[k][j];
			c[i][j] = skalaar;
		}
	}
}

void timesMatVec(mat a, vec b, vec& c) {
	for(int i = 0; i < M; i++) {
		float skalaar = 0;
		for(int j = 0; j < M; j++)
			skalaar += a[i][j] * b[j];
		c[i] = skalaar;
	}
}

void set(mat a, mat& b) {
	for(int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			b[i][j] = a[i][j];
}

void point2vec(point a, vec& b) {
	b[0] = a.x; 
	b[1] = a.y; 
	b[2] = 1;
}

void vec2point(vec a, point& b) {
	b.x = ((float) a[0]) / a[2];
	b.y = ((float) a[1]) / a[2];
}

void makeHomogenVec(float x, float y, vec& c){
	c[0] = x; 
	c[1] = y; 
	c[2] = 1;
}

void unit(mat& a) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (i == j) a[i][j] = 1;
			else a[i][j] = 0;
		}
	}
}

void move(float Tx, float Ty, mat& c) {
	unit(c);
	c[0][M - 1] = Tx;
	c[1][M - 1] = Ty;
}

void rotate(float phi, float x, float y, mat& c) {
	unit(c);
	c[0][0] = cos(phi); c[0][1] = -sin(phi);
	c[1][0] = sin(phi); c[1][1] =  cos(phi);

	c[0][M - 1] = -x * (cos(phi) - 1) + y * sin(phi);
	c[1][M - 1] = -y * (cos(phi) - 1) - x * sin(phi);
}

void scale(float Sx, float Sy, mat& c) {
	unit(c);
	c[0][0] = Sx; 
	c[1][1] = Sy;
}

void reflect(bool xAxis, bool yAxis, mat& c) {
	unit(c);
	if (xAxis) {
		c[1][1] = -1;
	} 
	if (yAxis) {
		c[0][0] = -1;	
	}
}

void frame(float Vx, float Vy, float Vcx, float Vcy,
		   float Wx, float Wy, float Wcx, float Wcy,
		   mat& c) {

	unit(c);
	mat R, c1;

	move(-Vcx, -Vcy, R);
	times(R, c, c1);

	scale(Wx / Vx, Wy / Vy, R);
	times(R, c1, c);

	reflect(1, 0, R);
	times(R, c, c1);

	move(Wcx, Wcy, R);
	times(R, c1, c);
}

void times(mat3D a, mat3D b, mat3D &c) {
	unit(c);
	for(int i = 0; i < M3D; i++) {
		for(int j = 0; j < M3D; j++) {
			float skalaar = 0;
			for(int k = 0; k < M3D; k++)
				skalaar += a[i][k] * b[k][j];
			c[i][j] = skalaar;
		}
	}
}

void timesMatVec(mat3D a, vec3D b, vec3D &c) {
	for(int i = 0; i < M3D; i++) {
		float skalaar = 0;
		for(int j = 0; j < M3D; j++)
			skalaar += a[i][j] * b[j];
		c[i] = skalaar;
	}
}

void set(mat3D a, mat3D &b) {
	for(int i = 0; i < M3D; i++)
		for (int j = 0; j < M3D; j++)
			b[i][j] = a[i][j];
}

void sum(mat3D a, mat3D b, mat3D& c) {
	unit(c);
	for (int i = 0; i < M3D; i++) {
		for (int j = 0; j < M3D; j++) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}

void mult(mat3D a, float k, mat3D& c) {
	unit(c);
	for (int i = 0; i < M3D; i++) {
		for (int j = 0; j < M3D; j++) {
			c[i][j] = a[i][j] * k;
		}
	}
}

void point2vec(point3D a, vec3D &b) {
	b[0] = a.x; 
	b[1] = a.y; 
	b[2] = a.z;
	b[3] = 1;
}

void vec2point(vec3D a, point3D &b) {
	b.x = ((float) a[0]) / a[3];
	b.y = ((float) a[1]) / a[3];
	b.z = ((float) a[2]) / a[3];
}

void makeHomogenVec(float x, float y, float z, vec3D &c) {
	c[0] = x; 
	c[1] = y; 
	c[2] = z;
	c[3] = 1;
}

void unit(mat3D &a) {
	for (int i = 0; i < M3D; i++) {
		for (int j = 0; j < M3D; j++) {
			if (i == j) a[i][j] = 1;
			else a[i][j] = 0;
		}
	}
}

void move(float Tx, float Ty, float Tz, mat3D &c) {
	unit(c);
	c[0][M3D - 1] = Tx;
	c[1][M3D - 1] = Ty;
	c[2][M3D - 1] = Tz;
}
void timesMatFloat (mat3D a, float b, mat3D &c) {
	for (int i = 0; i < M3D; i++) {
		for (int j = 0; j < M3D; j++) {
			c[i][j] = a[i][j] * b;
		}
	}
}
void rotate (point3D n, float phi, mat3D &c) {
	unit(c);
	mat3D m1, m2, m3, t;

	unit(m1);
	unit(m2);
	unit(m3);

	m2[0][0] = 0;		m2[0][1] = -n.z;	m2[0][2] = n.y;	
	m2[1][0] = n.z;		m2[1][1] = 0;		m2[1][2] = -n.x;
	m2[2][0] = -n.y;	m2[2][1] = n.x;		m2[2][2] = 0;	

	mult(m2, sin(phi), t);
	sum(m1, t, m2);

	m3[0][0] = n.x * n.x - 1;	m3[0][1] = n.x * n.y;		m3[0][2] = n.x * n.z;
	m3[1][0] = n.x * n.y;		m3[1][1] = n.y * n.y - 1;	m3[1][2] = n.y * n.z;
	m3[2][0] = n.x * n.z;		m3[2][1] = n.y * n.z;		m3[2][2] = n.z * n.z - 1;

	float k = 1 - cos(phi);
	mult(m3, k, t);
	sum(m2, t, m3);

	m3[3][3] = 1;
	set(m3, c);
}

void scale(float Sx, float Sy, float Sz, mat3D &c) {
	unit(c);
	c[0][0] = Sx; 
	c[1][1] = Sy;
	c[1][2] = Sz;
}

void sum(vec3D a, vec3D b, vec3D& c) {
	for (int i = 0; i < M3D - 1; i++) {
		c[i] = a[i] + b[i];
	}
	c[M3D - 1] = 1;
}

void sum(point3D a, point3D b, point3D& c) {
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

void mult(vec3D a, float k, vec3D& c) {
	for (int i = 0; i < M3D - 1; i++) {
		c[i] = a[i] * k;
	}
	c[M3D - 1] = 1;
}

void set(point3D a, point &b) {
	b.x = a.x;
	b.y = a.y;
}

void vecMult(vec3D a, vec3D b, vec3D& c) {
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
	c[3] = 1;
}

void normalize(vec3D& v) {
	float len = vecLength(v);
	for (int i = 0; i < M3D - 1; i++) {
		v[i] = v[i] / len;
	}
	v[M3D - 1] = 1;
}

void sub(vec3D a, vec3D b, vec3D& c) {
	for (int i = 0; i < M3D - 1; i++) {
		c[i] = a[i] - b[i];
	}
	c[M3D - 1] = 1;
}

float vecLength(vec3D v) {
	float s = 0;
	for (int i = 0; i < M3D - 1; i++) {
		s += v[i] * v[i];
	}

	return sqrt(s);
}

void calculateAxes(point3D eye, point3D center, point3D up, vec3D& x, vec3D& y, vec3D& z) {
	vec3D s, p, u;

	point2vec(eye, s);
	point2vec(center, p);
	point2vec(up, u);

	normalize(u);

	vec3D es1, es2, es3, t1;

	mult(p, -1, t1);
	sum(s, t1, es3);
	normalize(es3);

	vecMult(u, es3, es1);
	normalize(es1);

	vecMult(es3, es1, es2);
	normalize(es2);

	x = es1;
	y = es2;
	z = es3;
}

void LookAt(point3D eye, point3D center, point3D up, mat3D &c) {
	unit(c);

	vec3D es1, es2, es3;

	calculateAxes(eye, center, up, es1, es2, es3);

	mat3D R1, R2;
	unit(R1);
	unit(R2);

	move(-eye.x, -eye.y, -eye.z, R1);

	R2[0][0] = es1[0];	R2[0][1] = es1[1];	R2[0][2] = es1[2];
	R2[1][0] = es2[0];	R2[1][1] = es2[1];	R2[1][2] = es2[2];
	R2[2][0] = es3[0];	R2[2][1] = es3[1];	R2[2][2] = es3[2];

	times(R2, R1, c);
}

void Ortho(float Vx, float Vy, float near, float far, mat3D &c) {
	unit(c);

	c[0][0] = 2.0 / Vx;
	c[1][1] = 2.0 / Vy;
	c[2][2] = 2.0 / (far - near);
	c[2][3] = (far + near) / (far - near);
}

void Perspective(float fovy, float aspect, float near, float far, mat3D &c) {
	unit(c);

	c[0][0] = (1.0 / aspect) * (1.0 / tan(fovy / 2.0));
	c[1][1] = 1.0 / tan(fovy / 2.0);
	c[2][2] = (far + near) / (far - near);
	c[2][3] = (2.0 * far * near) / (far - near);
	c[3][2] = -1.0;
	c[3][3] = 0;
}

float round(float x, int n) {
	int k = 1;
	for (int i = 0; i < n; i++) {
		k *= 10;
	}

	return ((float)((int)(x * k))) / k;
}