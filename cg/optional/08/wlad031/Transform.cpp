#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <math.h>

mat T;

void times(mat a, mat b, mat c) {
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < M; j++) {
			float skalaar = 0;
			for(int k = 0; k < M; k++)
				skalaar += a[i][k] * b[k][j];
			c[i][j] = skalaar;
		}
	}
}

void timesMatVec(mat a, vec b, vec c) {
	for(int i = 0; i < M; i++) {
		float skalaar = 0;
		for(int j = 0; j < M; j++)
			skalaar += a[i][j] * b[j];
		c[i] = skalaar;
	}
}

void set(mat a, mat b) {
	for(int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			b[i][j] = a[i][j];
}

void point2vec(point a, vec b) {
	b[0] = a.x; 
	b[1] = a.y; 
	b[2] = 1;
}

void vec2point(vec a, point &b) {
	b.x = ((float) a[0]) / a[2];
	b.y = ((float) a[1]) / a[2];
}

void makeHomogenVec(float x, float y, vec c){
	c[0] = x; 
	c[1] = y; 
	c[2] = 1;
}

void unit(mat a) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (i == j) a[i][j] = 1;
			else a[i][j] = 0;
		}
	}
}

void move(float Tx, float Ty, mat c) {
	unit(c);
	c[0][M - 1] = Tx;
	c[1][M - 1] = Ty;
}

void rotate(float phi, float x, float y, mat c) {
	unit(c);
	c[0][0] = cos(phi); c[0][1] = -sin(phi);
	c[1][0] = sin(phi); c[1][1] =  cos(phi);

	c[0][M - 1] = -x * (cos(phi) - 1) + y * sin(phi);
	c[1][M - 1] = -y * (cos(phi) - 1) - x * sin(phi);
}

void scale(float Sx, float Sy, mat c) {
	unit(c);
	c[0][0] = Sx; 
	c[1][1] = Sy;
}

void reflect(bool xAxis, bool yAxis, mat c) {
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
		   mat c) {

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

void normalize(vec& v) {
	float len = vecLength(v);
	for (int i = 0; i < M - 1; i++) {
		v[i] = v[i] / len;
	}

	v[M - 1] = 1;
}

void normal(point s, point e, vec& n) {
	point2vec(point(e.y - s.y, -(e.x - s.x)), n);
	normalize(n);
}

void normal(vec s, vec& n) {
	point2vec(point(s[1], -s[0]), n);
	normalize(n);
}

float multSkalar(vec v1, vec v2) {
	float res = 0;

	for (int i = 0; i < M - 1; i++) {
		res += v1[i] * v2[i];
	}

	return res;
}

void sum(point p1, point p2, point& r) {
	r.x = p1.x + p2.x;
	r.y = p1.y + p2.y;
}

void mult(point p, float k, point& r) {
	r.x = p.x * k;
	r.y = p.y * k;
}

void sum(vec v1, vec v2, vec& r) {
	for (int i = 0; i < M - 1; i++) {
		r[i] = v1[i] + v2[i];
	}
	r[M - 1] = 1;
}

void mult(vec v1, float k, vec& r) {
	for (int i = 0; i < M; i++) {
		r[i] = v1[i] * k;
	}
	r[M - 1] = 1;
}

float vecLength(vec v) {
	float r = 0;

	for (int i = 0; i < M - 1; i++) {
		r += v[i] * v[i];
	}

	return sqrt(r);
}

void sub(point p1, point p2, point& r) {
	r.x = p1.x - p2.x;
	r.y = p1.y - p2.y;
}

void sub(vec v1, vec v2, vec& r) {
	for (int i = 0; i < M - 1; i++) {
		r[i] = v1[i] - v2[i];
	}
	r[M - 1] = 1;
}