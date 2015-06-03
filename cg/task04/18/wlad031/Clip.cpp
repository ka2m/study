#pragma once
#include "stdafx.h"
#include <algorithm>

#include "Transform.h"

using namespace std;

void Clip1Left(float& x1, float& y1, 
			   float dx, float dy, float dxL) {

	y1 = y1 + dxL * (dy / dx);
	x1 = x1 + dxL;
}

void Clip1Top(float& x1, float& y1,
			  float dx, float dy, float dyT) {
	
	x1 = x1 + dyT * (dx / dy);
	y1 = y1 + dyT;
}

void Clip1Bottom(float& x1, float& y1,
				 float dx, float dy, float dyB) {

	x1 = x1 + dyB * (dx / dy);
	y1 = y1 + dyB;
}

void Clip2Right(float x1, float y1, float& x2, float& y2, 
				float dx, float dy, float dxR) {

	y2 = y1 + dxR * (dy / dx);
	x2 = x1 + dxR;
}

void Clip2Top(float x1, float y1, float& x2, float& y2, 
			  float dx, float dy, float dyT) {

	x2 = x1 + dyT * (dx / dy);
	y2 = y1 + dyT;
}

void Clip2Bottom(float x1, float y1, float& x2, float& y2, 
				 float dx, float dy, float dyB) {

	x2 = x1 + dyB * (dx / dy);
	y2 = y1 + dyB;
}

bool clip(float& x1, float& y1, float& x2, float& y2, point Pmin, point Pmax) {

	float xmin = Pmin.x, ymin = Pmin.y;
	float xmax = Pmax.x, ymax = Pmax.y;

	if (x1 > x2) {
		swap(x1, x2);
		swap(y1, y2);
	}

	int C1 = 0, C2 = 0;
	if (x1 < xmin) C1 += 1;		if (x2 < xmin) C2 += 1;
	if (x1 > xmax) C1 += 2;		if (x2 > xmax) C2 += 2;
	if (y1 < ymin) C1 += 4;		if (y2 < ymin) C2 += 4;
	if (y1 > ymax) C1 += 8;		if (y2 > ymax) C2 += 8;
	
	if (C1 & C2) return 0;

	if (C1 == 0) {
		if (C2 == 0) return 1;

		float dx = x2 - x1, dy = y2 - y1;

		if (dy >= 0) {
			float dxR = xmax - x1, dyT = ymax - y1;

			if (dy * dxR < dx * dyT) Clip2Right(x1, y1, x2, y2, dx, dy, dxR);
			else Clip2Top(x1, y1, x2, y2, dx, dy, dyT);
			return 1;
		}

		if (dy < 0) {
			float dxR = xmax - x1, dyB = ymin - y1;

			if (dy * dxR < dx * dyB) Clip2Bottom(x1, y1, x2, y2, dx, dy, dyB);
			else Clip2Right(x1, y1, x2, y2, dx, dy, dxR);
			return 1;
		}
	}

	if (C1 == 1) {
		float dx = x2 - x1, dy = y2- y1;
		float dxL = xmin - x1, dyT = ymax - y1;
		float x1t = x1, y1t = y1;

		if (C2 == 0) { 
			Clip1Left(x1, y1, dx, dy, dxL); 
			return 1; 
		}

		if (dy >= 0) {
			if (dy * dxL > dx * dyT) return 0;
			float dxR = xmax - x1; dyT = ymax - y1;

			if (dy * dxR < dx * dyT) Clip2Right(x1t, y1t, x2, y2, dx, dy, dxR);
			else Clip2Top(x1t, y1t, x2, y2, dx, dy, dyT);

			Clip1Left(x1, y1, dx, dy, dxL);
			return 1;
		}

		if (dy < 0) {
			dxL = xmin - x1; float dyB = ymin - y1;

			if (dy * dxL < dx * dyB) return 0;
			float dxR = xmax - x1; dyB = ymin - y1;

			if (dy * dxR < dx * dyB) Clip2Bottom(x1, y1, x2, y2, dx, dy, dyB);
			else Clip2Right(x1, y1, x2, y2, dx, dy, dxR);

			Clip1Left(x1, y1, dx, dy, dxL);
			return 1;
		}
	}

	if (C1 == 4) {
		float dx = x2 - x1, dy = y2 - y1;
		float dxR = xmax - x1, dyB = ymin - y1;
		float x1t = x1, y1t = y1;

		if (C2 == 0) {
			Clip1Bottom(x1, y1, dx, dy, dyB);
			return 1;
		}

		if (dy > 0) {
			if (dy * dxR < dx * dyB) return 0;
			float dyT = ymax - y1;

			if (dy * dxR < dx * dyT) Clip2Right(x1t, y1t, x2, y2, dx, dy, dxR);
			else Clip2Top(x1t, y1t, x2, y2, dx, dy, dyT);

			Clip1Bottom(x1, y1, dx, dy, dyB);
			return 1;
		}

		if (dy <= 0) return 0;
	}

	if (C1 == 5) {
		float dx = x2 - x1, dy = y2 - y1;
		float x1t = x1, y1t = y1;
		
		if (dy > 0) {
			float dxL = xmin - x1, dyT = ymax - y1;
			if (dy * dxL > dx * dyT) return 0;

			float dxR = xmax - x1, dyB = ymin - y1;
			if (dy * dxR < dx * dyB) return 0;
			
			if (dyB * dxR < dxL * dyT) {
				if (dy * dxL < dx * dyB) {
					Clip1Bottom(x1, y1, dx, dy, dyB);

					if (x2 > xmax) Clip2Right(x1t, y1t, x2, y2, dx, dy, dxR);
					return 1;
				}

				Clip1Left(x1, y1, dx, dy, dxL);
				if (C2 == 0) return 1;

				if (dy * dxR < dx * dyT && C2 != 0) {
					Clip2Right(x1t, y1t, x2, y2, dx, dy, dxR);
					return 1;
				}

				Clip2Top(x1t, y1t, x2, y2, dx, dy, dyT);
				return 1;

			} else {
				if (dy * dxR < dx * dyT) {
					Clip1Bottom(x1, y1, dx, dy, dyB);

					if (x2 > xmax) Clip2Right(x1t, y1t, x2, y2, dx, dy, dxR);
					return 1;
				}

				if (dy * dxL < dx * dyB) {
					Clip1Bottom(x1, y1, dx, dy, dyB);

					if (C2 != 0) Clip2Top(x1t, y1t, x2, y2, dx, dy, dyT);
					return 1;
				}

				Clip1Left(x1, y1, dx, dy, dxL);
				if (C2 == 0) return 1;

				Clip2Top(x1t, y1t, x2, y2, dx, dy, dyT);
				return 1;
			}
		}

		if (dy <= 0) return 0;
	}

	if (C1 == 8) {
		float dx = x2 - x1, dy = y2 - y1;
		float dxR = xmax - x1, dyT = ymax - y1;
		float x1t = x1, y1t = y1;

		if (C2 == 0) {
			Clip1Top(x1, y1, dx, dy, dyT);
			return 1;
		}

		if (dy < 0) {
			if (dy * dxR > dx * dyT) return 0;
			float dyB = ymin - y1;

			if (dy * dxR > dx * dyB) Clip2Right(x1t, y1t, x2, y2, dx, dy, dxR);
			else Clip2Bottom(x1t, y1t, x2, y2, dx, dy, dyB);

			Clip1Top(x1, y1, dx, dy, dyT);
			return 1;
		} 

		if (dy >= 0) return 0;
	}

	if (C1 == 9) {
		float dx = x2 - x1, dy = y2 - y1;
		float x1t = x1, y1t = y1;

		if (dy < 0) {
			float dxR = xmax - x1, dyT = ymax - y1;
			if (dy * dxR > dx * dyT) return 0;

			float dxL = xmin - x1, dyB = ymin - y1;
			if (dy * dxL < dx * dyB) return 0;

			if (dyT * dxR > dxL * dyB) {
				if (dy * dxL > dx * dyT) {
					Clip1Top(x1, y1, dx, dy, dyT);
					if (x2 > xmax) Clip2Right(x1t, y1t, x2, y2, dx, dy, dxR);
					return 1;
				}

				Clip1Left(x1, y1, dx, dy, dxL);
				if (C2 == 0) return 1;

				if (dy * dxR > dx * dyB) {
					Clip2Right(x1t, y1t, x2, y2, dx, dy, dxR);
					return 1;
				}

				Clip2Bottom(x1t, y1t, x2, y2, dx, dy, dyB);
				return 1;

			} else {
				if (dy * dxR > dx * dyB) {
					Clip1Top(x1, y1, dx, dy, dyT);
					if (x2 > xmax) Clip2Right(x1t, y1t, x2, y2, dx, dy, dxR);
					return 1;
				}

				if (dy * dxL > dx * dyT) {
					Clip1Top(x1, y1, dx, dy, dyT);
					if (C2 != 0) Clip2Bottom(x1t, y1t, x2, y2, dx, dy, dyB);
					return 1;
				}

				Clip1Left(x1, y1, dx, dy, dxL);

				if (C2 != 0) Clip2Bottom(x1t, y1t, x2, y2, dx, dy, dyB);
					
				return 1;
			}
		} 
		
		if (dy >= 0) return 0;
	}
}