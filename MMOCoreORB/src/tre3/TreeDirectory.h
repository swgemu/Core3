/*
 * TreeDirectory.h
 *
 *  Created on: Apr 8, 2011
 *      Author: crush
 */

#ifndef TREEDIRECTORY_H_
#define TREEDIRECTORY_H_

#include "engine/engine.h"
#include "TreeFileRecord.h"

class TreeDirectory : public SortedVector<Reference<TreeFileRecord*> > {
public:
	TreeDirectory() : SortedVector<Reference<TreeFileRecord*> >() {
		setNoDuplicateInsertPlan();
	}

	TreeDirectory(const TreeDirectory& d) : SortedVector<Reference<TreeFileRecord*> >(d) {
		setNoDuplicateInsertPlan();
	}

	TreeDirectory& operator=(const TreeDirectory& d) {
		if (this == &d)
			return *this;

		SortedVector<Reference<TreeFileRecord*> >::operator=(d);

		return *this;
	}

	int compare(Reference<TreeFileRecord*>& o1, const Reference<TreeFileRecord*>& o2) const {
		return o1->compareTo(*o2.get());
	}

	int compare(Reference<TreeFileRecord*>& o1, const String& fileName) const {
		return o1->compareTo(fileName);
	}

	int find(const String& fileName) const {
	    int l = 0, r = Vector<Reference<TreeFileRecord*> >::elementCount - 1;
	    int m = 0, cmp = 0;

	    while (l <= r) {
        	m = (l + r) / 2;

        	Reference<TreeFileRecord*>& obj = Vector<Reference<TreeFileRecord*> >::elementData[m];
        	cmp = compare(obj, fileName);

        	if (cmp == 0)
            	return m;
        	else if (cmp > 0)
	            l = m + 1;
        	else
	            r = m - 1;
	    }

    	return -1;
	}
};


#endif /* TREEDIRECTORY_H_ */
