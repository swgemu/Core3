/*
 * PerlinNoise.h
 *
 *  Created on: 17/12/2010
 *      Author: victor
 */

#ifndef PERLINNOISE_H_
#define PERLINNOISE_H_

/* coherent noise function over 1, 2 or 3 dimensions */
/* (copyright Ken Perlin) */

#define B 0x100
#define BM 0xff

#define N 0x1000
#define NP 12   /* 2^N */
#define NM 0xfff

#include "Random.h"
#include <cmath>

class PerlinNoise {
	int p[B + B + 2];
	//float g3[B + B + 2][3];
	float g2[B + B + 2][2];
	float g1[B + B + 2];

	int start;

	trn::ptat::Random* rand;

#define s_curve(t) ( t * t * (3. - 2. * t) )

#define lerp(t, a, b) ( a + t * (b - a) )

#define setup(i,b0,b1,r0,r1, n)\
                t = (double)vec[i] + (double)N;\
                n = t < 0.0 && t != (double)(int32_t)t;\
                b0 = ((int)t - n) & BM;\
                b1 = (b0+1) & BM;\
                r0 = t - ((int)t - n);\
                r1 = r0 - 1.;
/*
#define setup(i,b0,b1,r0,r1)\
		t = (double)vec[i] + (double)N;\
		b0 = ((int)t) & BM;\
		b1 = (b0+1) & BM;\
		r0 = t - (int)t;\
		r1 = r0 - 1.;
*/

public:
	PerlinNoise(trn::ptat::Random* r) {
		p[0] = 0;
		g2[0][0] = 0;
		g1[0] = 0;

		start = 1;
		rand = r;
	}

	float noise1(double arg)
	{
		int bx0, bx1, b00, b10, b01, b11, negx;
		double rx0, rx1;
		float *q;
		double t, sx, u, v, vec[1];

		vec[0] = arg;
		if (start) {
			start = 0;
			init();
		}

		setup(0, bx0,bx1, rx0,rx1,negx);

		sx = s_curve(rx0);

		u = rx0 * g1[ p[ bx0 ] ];
		v = rx1 * g1[ p[ bx1 ] ];

		return lerp(sx, u, v);
	}


	float noise2(double vec[2]) {
		int bx0, bx1, by0, by1, b00, b10, b01, b11, negx, negy;
		double rx0, rx1, ry0, ry1;
		float *q;
		double t, sx, sy, a, b, u, v;
		int i, j;

		if (start) {
			start = 0;
			init();
		}

		setup(0, bx0,bx1, rx0,rx1,negx);

		setup(1, by0,by1, ry0,ry1,negy);

		i = p[ bx0 ];
		j = p[ bx1 ];

		b00 = p[ i + by0 ];
		b10 = p[ j + by0 ];
		b01 = p[ i + by1 ];
		b11 = p[ j + by1 ];

		sx = s_curve(rx0);

		sy = s_curve(ry0);


#define at2(rx,ry) ( rx * q[0] + ry * q[1] )

		q = g2[ b00 ] ;
		u = at2(rx0,ry0);


		q = g2[ b10 ] ;
		v = at2(rx1,ry0);


		a = lerp(sx, u, v);

		q = g2[ b01 ] ;
		u = at2(rx0,ry1);

		q = g2[ b11 ] ;
		v = at2(rx1,ry1);

		b = lerp(sx, u, v);

		return lerp(sy, a, b);
	}

	static void normalize2(float v[2]) {
		double s;

		s = sqrt(v[0] * v[0] + v[1] * v[1]);
		v[0] = v[0] / s;
		v[1] = v[1] / s;
	}

	static void normalize3(float v[3]) {
		double s;

		s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
		v[0] = v[0] / s;
		v[1] = v[1] / s;
		v[2] = v[2] / s;
	}

	void init() {
		int i, j, k;

		for (i = 0 ; i < B ; i++) {
			p[i] = i;

			g1[i] = (double)((rand->next() % (B + B)) - B) / B;

			for (j = 0 ; j < 2 ; j++) {
				g2[i][j] = (double)((rand->next() % (B + B)) - B) / B;
			}

			normalize2(g2[i]);

			/*for (j = 0 ; j < 3 ; j++)
				g3[i][j] = (double)((rand->generateTable() % (B + B)) - B) / B;

			normalize3(g3[i]);*/
		}

		while (--i) {
			k = p[i];
			p[i] = p[j = rand->next() % B];
			p[j] = k;
		}

		for (i = 0 ; i < B + 2 ; i++) {
			p[B + i] = p[i];
			g1[B + i] = g1[i];

			for (j = 0 ; j < 2 ; j++)
				g2[B + i][j] = g2[i][j];

			/*for (j = 0 ; j < 3 ; j++)
				g3[B + i][j] = g3[i][j];*/
		}
	}

};

#endif /* PERLINNOISE_H_ */
