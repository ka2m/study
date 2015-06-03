#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <math.h>
#include <cstdlib>
int extCode(point a, point Pmin, point Pmax);
point angle(point Pmin, point Pmax, int C);
int corr(int C);

polygon^ Pclip (polygon^ P, point Pmin, point Pmax)
{
	polygon^ P1 = gcnew polygon(0);
	point start = P[P->Count-1];
	int Cstart = extCode(start, Pmin, Pmax);
	int Cend = 0;
	point test = angle(Pmin, Pmax, 17);
	for(int k = 0; k < P->Count; k++)
	{
		
		point end = P[k];
		Cend = extCode(end, Pmin, Pmax);
		//C S
		int C1 = Cstart, C2 = Cend;
		//printf("%x %x\n", C1, C2);
		point p1 = start, p2 = end;
		bool clip = false, flip = false, segm = false;
		while(true)
		{
			if( ((C1 | C2) & 15) == 0) //fully
			{
				segm = true;
				if(flip)
				{
					point t = p1;
					p1 = p2;
					p2 = t;
					int tc = C1;
					C1 = C2;
					C2 = tc;
					flip = !flip;
				}
				break;
			}
			else
			{
				if (((C1 & C2) & 15) == 0)	//partly
				{
					if((C1 & 15) == 0)
					{
						point t = p1;
						p1 = p2;
						p2 = t;
						int tc = C1;
						C1 = C2;
						C2 = tc;
						flip = !flip;
					}
					//b
					if((C1 & 1) != 0)
					{
						float top = p2.y - p1.y;
						float bottom = p2.x - p1.x;
						
						if(p1.x != p2.x && p1.y != p2.y)
							p1.y = p2.y - (p2.x - Pmin.x)*top/bottom;
						p1.x = Pmin.x;
					} else 
						//c
						if((C1 & 2) != 0)
						{
							float top = p2.y - p1.y;
							float bottom = p2.x - p1.x;
							
							if(p1.x != p2.x && p1.y != p2.y)
								p1.y = p2.y - (p2.x - Pmax.x)*top/bottom;
							p1.x = Pmax.x;
						}
						else
							//d
							if((C1 & 4) != 0)
							{
								float top = p2.x - p1.x;
								float bottom = p2.y - p1.y;
								
								if(p1.x != p2.x && p1.y != p2.y)
									p1.x = p2.x - (p2.y - Pmin.y)*top/bottom;
								p1.y = Pmin.y;
							}
							else
								//e
								if((C1 & 8) != 0)
								{
									float top = p2.x - p1.x;
									float bottom = p2.y - p1.y;
									
									if(p1.x != p2.x && p1.y != p2.y)
										p1.x = p2.x - (p2.y - Pmax.y)*top/bottom;
									p1.y = Pmax.y;
								}
					if((C1 & 15) != 0 && !flip)
						clip = true;
					C1 = extCode(p1, Pmin, Pmax);
					//segm = true;
					
					
				}
				else	//invis
				{
					segm = false;
					break;
				}
			}
		}

		
		//end C S
		
		C2 = Cend;
		if(segm)
		{
			if(clip)
				P1->Add(p1);
			P1->Add(p2);
		}
		
		else
		{
			
			//a
			if((Cend & 16) != 0)
			{
				if((Cstart & Cend & 15) == 0)
				{
					if((Cstart & 16) == 0)
					{
						C1 = Cend + corr(Cstart);
					}
					else
					{
						p1 = start;
						p2 = end;
						int C11 = Cstart, C12 = Cend;
						point mid = p1;
						C1 = Cstart;
						while(true)
						{
							mid.x = (p1.x + p2.x)/2;
							mid.y = (p1.y + p2.y)/2;
							C1 = extCode(mid, Pmin, Pmax);
							if ((C1&16)!=0)
							{
								if (C1==C12) 
								{
									p2=mid;
									C12=C1;
								}
								else if (C1==C11)
								{
									p1=mid;
									C11=C1;
								}
								else  
									break;
							}
							else
							{
								if((C1 & C12) != 0)
									C1 = C11 + corr(C1);
								else
									C1 = C12 + corr(C1);
								break;
							}
						}
					}
					//ii
					P1->Add(angle(Pmin, Pmax, C1));
				}
			}
			else
			{
				if((Cstart & Cend & 15) == 0)
				{
					if((Cstart & 16) != 0)
						C2 = Cstart + corr(Cend);
					else
						C2 = Cstart + Cend + 16;
				}
			}
			
		}
		
		if((C2 & 16) != 0)
			P1->Add(angle(Pmin, Pmax, C2));
		Cstart = Cend;
		start = end;
	}

	return P1;
}

int extCode(point a, point Pmin, point Pmax)
{
	int C = 0;
	if(a.x < Pmin.x)
	{
		if(a.y < Pmin.y) return 0x15;
		if(a.y > Pmax.y) return 0x19;
		return 0x1;
	}
	if(a.x > Pmax.x)
	{
		if(a.y < Pmin.y) return 0x16;
		if(a.y > Pmax.y) return 0x1A;
		return 0x2;
	}
	if(a.y < Pmin.y) return 0x4;
	if(a.y > Pmax.y) return 0x8;
	return 0x0;
}

point angle(point Pmin, point Pmax, int C)
{
	point a;
	if((C&1))
		a.x = Pmin.x;
	if((C&2))
		a.x = Pmax.x;
	if((C&4))
		a.y = Pmin.y;
	if((C&8))
		a.y = Pmax.y;
	return a;
}

int corr(int C)
{
	int f = 0;
	if((C&1))
		f = -1;
	if((C&2))
		f = 1;
	if((C&4))
		f = -4;
	if((C&8))
		f = 4;
	return f;
}

int comp(line x, line y)
{	
	if(x.start.y < y.start.y)
		return -1;
	if(x.start.y > y.start.y)
		return 1;
	return 0;
}

int compAEL(int x, int y)
{
	line *xl = (line *)x;
	line *yl = (line *)y;
	
	if(xl->start.x < yl->start.x)
		return -1;
	if(xl->start.x > yl->start.x)
		return 1;

	if(xl->end.x < yl->end.x)
		return -1;
	if(xl->end.x > yl->end.x)
		return 1;
	return 0;
}


void Pfill (polygon^ P, System::Drawing::Bitmap^ image, System::Drawing::Color C)
{
	if(!P->Count)
		return;
	System::Drawing::Graphics^ g = System::Drawing::Graphics::FromImage(image);
	System::Drawing::Pen^ pen = gcnew System::Drawing::Pen(C);
	
	System::Collections::Generic::List<line> S;
	point a, b;
	a = P[P->Count - 1];
	for (int j = 0; j < P->Count; j++)
	{
		b = P[j];
		line l;
		if(a.y <= b.y)
		{
			l.start = a;
			l.end = b;
		}
		else
		{
			l.start = b;
			l.end = a;
		}
		S.Add(l);
		//g ->DrawLine(pen, l.start.x, l.start.y, l.end.x, l.end.y);
		a = b;
	}
	S.Sort(gcnew System::Comparison<line>(comp));
	point Pmin = S[0].start, Pmax = S[0].start;
	for(int i =0; i<S.Count; i++)
	{
		if(S[i].start.y < Pmin.y)
			Pmin = S[i].start;
		if(S[i].end.y < Pmin.y)
			Pmin = S[i].end;

		if(S[i].start.y > Pmax.y)
			Pmax = S[i].start;
		if(S[i].end.y > Pmax.y)
			Pmax = S[i].end;
	}
	//3
	int yt = Pmin.y;
	System::Collections::Generic::List<int> AEL;

	//4
	while(true)
	{
		for(int i = 0; i<S.Count; i++)
		{
			if((int)S[i].start.y == yt && ((int)S[i].start.y != (int)S[i].end.y))
			{
				line* h = (line*) malloc(sizeof(line));
				h->start.x = S[i].start.x;
				h->start.y = S[i].end.y;
				h->end.x = (S[i].end.x - S[i].start.x)/(S[i].end.y - S[i].start.y);
				AEL.Add((int)h);
			}
			if((int)S[i].start.y == yt && (int)S[i].start.y == (int)S[i].end.y)
				g ->DrawLine(pen, (int)S[i].start.x, (int)S[i].start.y, (int)S[i].end.x, (int)S[i].end.y);
		}

		for(int i = 0; i<S.Count; i++)
		{
			if((int)S[i].start.y == yt)
			{
				S.Remove(S[i]);
				i--;
			}
		}

		//7
		int ysnext = INT_MAX;
		for(int i =0; i<S.Count; i++)
		{
			if((int)S[i].start.y < ysnext)
				ysnext = (int)S[i].start.y;
		}
		//8
		float yaelnext = INT_MAX;
		AEL.Sort(gcnew System::Comparison<int>(compAEL));
		for(int i =0; i<AEL.Count; i++)
		{
			if(((line*)(AEL[i]))->start.y < yaelnext && (int)(((line*)(AEL[i]))->start.y) != yt)
				yaelnext = (int)((line*)AEL[i])->start.y;
		}
		//9?
		
		while(yt != ysnext)
		{
			//10
			for(int i = 0; i < AEL.Count-1; i+=2)
			{
				float x1 = (int)((line*)AEL[i])->start.x;
				float x2 = (int)((line*)AEL[i+1])->start.x;
				g ->DrawLine(pen, (int)((line*)AEL[i])->start.x, yt, (int)((line*)AEL[i+1])->start.x, yt);
			}
			//14
			
			for(int i =0; i < AEL.Count; i++)
			{
				//printf("%f  + %f = ", AEL[i]->start.x, AEL[i]->end.x);
				float end = ((line*)AEL[i])->end.x;
				((line*)AEL[i])->start.x += ((line*)AEL[i])->end.x;
				//printf("%f\n", AEL[i]->start.x);
			}
			yt+=1;
			if( yt >= yaelnext)
			{
				for(int i =0; i < AEL.Count; i++)
				{
					if((int)((line*)AEL[i])->start.y <= yt)
					{
						line* l = (line*)AEL[i];
						free(l);
						AEL.Remove(AEL[i]);
						i--;
					}
				}
				int size = AEL.Count;
				yaelnext = INT_MAX;
				for(int i =0; i<AEL.Count; i++)
				{
					if((int)((line*)AEL[i])->start.y < yaelnext && (int)((line*)AEL[i])->start.y != yt)
						yaelnext = (int)((line*)AEL[i])->start.y;
				}
			}
			if(yt > Pmax.y)
				return;
		}
	}
	return;
}


float sign (point p1, point p2, point p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

int orientation(point p, point q, point r)
{
	int val = sign(r, q, p);	//(q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (val == 0)
		return 0;
	return (val > 0)? 1: 2;
}

void convex(polygon^ P, polygon^ H)
{
	if(P->Count < 3)
		return;

	// Initialize Result
    int *next = new int[P->Count];
    for (int i = 0; i < P->Count; i++)
        next[i] = -1;
 
    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < P->Count; i++)
        if (P[i].x < P[l].x)
            l = i;
 
    // Start from leftmost point, keep moving counterclockwise
    // until reach the start point again
    int p = l, q;
    do
    {
        // Search for a point 'q' such that orientation(p, i, q) is
        // counterclockwise for all points 'i'
        q = (p+1)%P->Count;
        for (int i = 0; i < P->Count; i++)
          if (orientation(P[p], P[i], P[q]) == 2)
             q = i;
 
        next[p] = q;  // Add q to result as a next point of p
        p = q; // Set p as q for next iteration
    } while (p != l);

	for (int i = 0; i < P->Count; i++)
    {
        if (next[i] != -1)
           H->Add(P[i]);
    }
	delete next;

}




bool pit(point p, point a, point b, point c)
{
	bool b1, b2, b3;

    b1 = sign(p, a, b) < 0.0f;
    b2 = sign(p, b, c) < 0.0f;
    b3 = sign(p, c, a) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}

point pip(polygon^ P)	//vnutrtochka
{
	if(P->Count == 0)
		return point();
	if(P->Count < 3)
		return P[0];
	
	polygon^ H = gcnew polygon(0);
	convex(P, H);
	int v = 0, a = 0, b = 0;
	bool vfound = false;
	
	for(int i = 0; i<P->Count; i++)
	{
		for(int j = 0; j<H->Count; j++)
		{
			if(P[i].x == H[j].x && P[i].y == H[j].y)
			{
				v = i;
				vfound = true;
				break;
			}
			if(vfound)
				break;
		}
	}

	a = v - 1;
	if(a < 0)
		a = P->Count + a;
	b = v + 1;
	if(b >= P->Count)
		b -= P->Count;

	point min;
	float mindist = FLT_MAX;
	bool foundqinside = false;
	for(int q =0; q<P->Count; q++)
	{
		if(q != a && q != b && q != v)
		{
			if(pit(P[q], P[v], P[a], P[b]))
			{
				foundqinside = true;
				point qv;
				qv.x = P[q].x - P[v].x;
				qv.y = P[q].y - P[v].y;
				float dist = qv.x * qv.x + qv.y*qv.y;
				if(dist < mindist)
				{
					min = qv;
					mindist = dist;
				}
			}
		}
	}
	point p;
	if(foundqinside)
	{
		
		p.x = P[v].x + min.x/2;
		p.y = P[v].y + min.y/2;
	}
	else
	{
		p.x =  (P[v].x +  P[a].x +  P[b].x)/3;
		p.y =  (P[v].y +  P[a].y +  P[b].y)/3;
	}
	
	return p;

}