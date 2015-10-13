class VectorShuffle {
public:
	VectorShuffle(uint32 size, uint32 seed) 
		: size(size), seed(seed), idx(0), nBits(0) {
		// to illustrate, let's use size = 5 = 0b0101
		uint32 mask = size;

		// it will take 3 iterations, so nBits == 3
		while (mask) {
			mask = mask >> 1;
			++nBits;
		}

		// force the number of bits to be even to ensure 
		// we can split the size equally.
		// since nBits == 3 == 0b0011, we had one so 
		// nBits = 4 == 0b0100 (notice this is a case that
		// makes this step necessary)
		if (nBits & 1)
			++nBits;

		// Now we actually only need the half size of nBits
		// so nBits = 2 == 0b0010
		nBits = nBits >> 1;
		// and the rMask = (1 << 2 == 0b0100) - 1 == 0b0011
		rMask = (1 << nBits) - 1;
		// which makes lMask = 0b0011 << 2 == 0b1100
		lMask = rMask << nBits;

		// and the maximum number available (+1) is 0b10000 == 16
		nMax = rMask + lMask + 1;
	}

	bool next(uint32& idx) {
		while (index < nMax) {
			idx = encrypt(index);
			++index;

			if (idx < size)
				return true;
		}

		return false;
	}

	bool prev(uint32& idx) {
		while (index > 1) {
			idx = encrypt(index - 2);
			--index;

			if (idx < size)
				return true;
		}

		return false;
	}

private:
	uint32 size;
	uint32 seed;
	uint32 idx;
	uint32 rMask;
	uint32 lMask;
	uint32 nMax;
	uint8 nBits;

	uint32 encrypt(uint32 i) {
		uint32 left = (i & lMask) >> nBits;
		uint32 right = i & rMask;

		// HERE'S TEH MAGIC (4-round Feistel encryption)
		for (int j = 0; j < 4; ++j) {
			uint32 nLeft = right;
			uint32 nRight = left ^ (HASH(right, seed) & rMask);
			left = nLeft;
			right = nRight;
		}

		return (left << nBits) | right;
	}
}
