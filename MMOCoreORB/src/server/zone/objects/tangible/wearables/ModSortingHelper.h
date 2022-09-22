/*
 * ModSortingHelper.h
 */

#ifndef MODSORTINGHELPER_H_
#define MODSORTINGHELPER_H_

/**
 * Rename for clarity/convenience
 */
using Mod = VectorMapEntry<String,int>;

/**
 * @inf
 * The ModSortingHelper class inherits from VectorMap<String, int> and is used
 * to provide the correct sorting for a SEA stat mod in a SortedVector.
 * Specifically, it keeps the relative order of same-value mods so that when a
 * mod is applied to a wearable, ties are broke in the order they appear on the
 * SEA.
 * @imp
 * Overwrites the VectorMapEntry<k,v>::compareTo method to get custom sort
 * behavior in sorted containers.
 */
class ModSortingHelper : public Mod {
public:
	ModSortingHelper(): Mod( "", 0) {}
	ModSortingHelper(String name, int value) : Mod(name, value) {}

	/**
	 * @inf
	 * Overwrite the compareTo method of VectorMapEntry in order to provide
	 * custom sorting logic.
	 * @imp
	 * Using the default compare method where equality values return 0 will
	 * not maintain the relative order of same-value objects being 'put()'
	 * into a SortedVector. This pastebin (http://pastebin.com/AazeG0Lq)
	 * shows how inserting 4 equal elements, A,B,C,D, into a SortedVector
	 * will result in a vector of {A, C, D, B}. This overload results in a
	 * vector of {A, B, C, D }.
	 */
	int compareTo(const Mod& e) const  {
		// Make copies of this and e to get around getValue not being const
		if(  Mod(*this).getValue() >= Mod(e).getValue() ) {
			return 1;
		} else {
			return -1;
		}
	}
};

#endif /* MODSORTINGHELPER_H_ */