#pragma once
#include "stdafx.h"
#include <algorithm>
#include "Transform.h"
#include "Pclip.h"

using namespace std;

int extCode(point a, point min, point max) {
	int C = 0;
	if(a.x < min.x) {
		C++;
		
		if(a.y < min.y) {
			C += 20;
		}

		if(a.y > max.y) {
			C += 24;
		}

		return C;
	}
	
	if(a.x > max.x) {
		C += 2;

		if(a.y < min.y) {
			C += 20;
		}

		if(a.y > max.y) {
			C += 24;
		}

		return C;
	}

	if(a.y < min.y) {
		C += 4;
	}

	if(a.y > max.y) {
		C += 8;
	}

	return C;
}

point Angle(int C, point min, point max) {
	point ans;

	if(C & 1) ans.x = min.x;
	if(C & 2) ans.x = max.x;
	if(C & 4) ans.y = min.y;
	if(C & 8) ans.y = max.y;

	return ans;
}

int Tcc(int C) {
	int corr;

	if(C & 1) corr = -1;
	if(C & 2) corr = 1;
	if(C & 4) corr = -4;
	if(C & 8) corr = 4;

	return corr;
}

polygon^ Pclip (polygon^ P, point min, point max) {
	int n = P->Count;
	point A = P[n - 1];
	int Cstart = extCode(A, min, max);
	polygon^ P1 = gcnew polygon(0);
	
	for(int k = 0; k < n; k++) {
		point B = P[k];
		int Cend = extCode(B, min, max);
		
		int C1 = Cstart;
		int C2 = Cend;

		float x1 = A.x;
		float y1 = A.y;
		float x2 = B.x;
		float y2 = B.y;

		bool clip = false;
		bool flip = false;
		bool segm = false;

		while(true) {
			if(((C1 | C2) & 15) == 0) {
				if(flip) {
					swap(x1, x2);
					swap(y1, y2);
				}
				segm = true;
				break;
			} else {
				if(C1 & C2 & 15) {
					segm = false;
					break;
				} else {
					if((C1 & 15) == 0) {
						swap(x1, x2);
						swap(y1, y2);
						swap(C1, C2);
						flip = !flip;
					}

					if((C1 & 15) != 0 && !flip) {
						clip = true;	
					}

					float dx = x2 - x1;
					float dy = y2 - y1;

					if(C1 & 1) {
						y1 = y2 - (x2 - min.x) * dy / dx;
						x1 = min.x;
					}

					else if(C1 & 2) {
						y1 = y2 - (x2 - max.x) * dy / dx;
						x1 = max.x;
					}

					else if(C1 & 4) {
						x1 = x2 - (y2 - min.y) * dx / dy;
						y1 = min.y;
					}

					else if(C1 & 8) {
						x1 = x2 - (y2 - max.y) * dx / dy;
						y1 = max.y;
					}

					point tmp = {x1, y1};
					C1 = extCode(tmp, min, max);

				}
			}
		}

		C2 = Cend;
		point A1 = {x1, y1};
		point B1 = {x2, y2};

		if(segm) {
			if(clip) {
				P1->Add(A1);
			}
			P1->Add(B1);
		} else {
			if(Cend & 0x10) {
				if((Cstart & Cend & 0x0F) == 0) {
					if((Cstart & 0x10) == 0) {
						C1 = Cend + Tcc(Cstart);
					} else {
						x1 = A.x;
						y1 = A.y;
						x2 = B.x;
						y2 = B.y;

						int C11 = Cstart;
						int C12 = Cend;
						
						step17aib:
						point mid = {(x1 + x2) / 2, (y1 + y2) / 2};
						C1 = extCode(mid, min, max);
						
						if(C1 & 16) {
							if(C1 == C12) {
								x2 = mid.x;
								y2 = mid.y;
								C12 = C1;
								goto step17aib;
							}
							
							if(C1 == C11) {
								x1 = mid.x;
								y1 = mid.y;
								C11 = C1;
								goto step17aib;
							}
						} else {
							if(C1 & C12) {
								C1 = C11 + Tcc(C1);
							} else {
								C1 = C12 + Tcc(C1);
							}
						}
					}

					point tmp = Angle(C1, min, max);
					P1->Add(tmp);
				}
			} else {
				if((Cstart & Cend & 0x0F) == 0) {
					if(Cstart & 0x10) {
						C2 = Cstart + Tcc(Cend);
					} else {
						C2 = Cstart + Cend + 16;
					}
				}
			}
		}

		if(C2 & 0x10) {
			point tmp = Angle(C2, min, max);
			P1->Add(tmp);
		}

		A = B;
		Cstart = Cend;
	}
	
	return P1;
}
