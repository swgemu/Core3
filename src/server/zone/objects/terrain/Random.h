/*
 * Random.h
 *
 *  Created on: 17/12/2010
 *      Author: victor
 */

#ifndef RANDOM_H_
#define RANDOM_H_

class Random {
	int seed;
	int number;

	int table[322];

public:
	Random() {
		number = 0;
		seed = 0;
	}

	void setSeed(int seed) {
		this->seed = seed;
	}

	int next() {
		int v2, v5;
		int v8;

		if (seed <= 0 || number == 0) {
			v2 = -seed;

			if (v2 >= 1)
				seed = v2;
			else
				seed = 1;

			for (int i = 329; i >= 0; --i) {
				int valueTo1 = seed;
				int value2 = 16807 * valueTo1;
				int tempDiv = valueTo1 / 0x1F31D;
				int value3 = (0x7FFFFFFF * tempDiv);
				v5 = value2 - value3;

				seed = v5;

				if (v5 < 0)
					seed = seed + 0x7FFFFFFF;

				if (i < 322) {
					table[i] = seed;
				}
			}

			number = table[0];
		}

		int valueTo1 = seed;
		int value2 = 16807 * valueTo1;
		int tempDiv = valueTo1 / 0x1F31D;
		int value3 = (0x7FFFFFFF * tempDiv);

		v5 = value2 - value3;

		seed = v5;

		if (v5 < 0)
			seed = seed + 0x7FFFFFFF;

		v8 = ((double) number / 6669205.0); // random index?

		number = table[v8];
		table[v8] = seed;

		return number;
	}
};


#endif /* RANDOM_H_ */
