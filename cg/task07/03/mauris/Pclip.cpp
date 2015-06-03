#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <math.h>
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