/*
 * CloseObjectsVector.h
 *
 *  Created on: 11/06/2012
 *      Author: victor
 */

#ifndef ZONECLOSEOBJECTSVECTOR_H_
#define ZONECLOSEOBJECTSVECTOR_H_

#include <algorithm>

#include "system/lang/Object.h"
#include "system/lang/ref/Reference.h"
#include "system/platform.h"
#include "system/thread/ReadWriteLock.h"
#include "system/util/SortedVector.h"
#include "system/util/VectorMap.h"

namespace engine {
namespace core {
template <class O> class ManagedReference;
}  // namespace core
}  // namespace engine
namespace sys {
namespace util {
template <class E> class Vector;
}  // namespace util
}  // namespace sys

namespace server {
 namespace zone {
   class QuadTreeEntry;

class CloseObjectsVector : public Object {
	mutable ReadWriteLock mutex;
	SortedVector<Reference<server::zone::QuadTreeEntry*> > objects;

	VectorMap<uint32, SortedVector<server::zone::QuadTreeEntry*> > messageReceivers;

#ifdef CXX11_COMPILER
	static_assert(sizeof(server::zone::QuadTreeEntry*) == sizeof(Reference<server::zone::QuadTreeEntry*>), "Reference<> size is not the size of a pointer");
#endif

protected:
	void dropReceiver(server::zone::QuadTreeEntry* entry);
	void putReceiver(server::zone::QuadTreeEntry* entry, uint32 receiverTypes);

public:
	CloseObjectsVector();

	Reference<server::zone::QuadTreeEntry*> remove(int index);

	bool contains(const Reference<server::zone::QuadTreeEntry*>& o) const;

	void removeAll(int newSize = 10, int newIncrement = 5);

	bool drop(const Reference<server::zone::QuadTreeEntry*>& o);

	void safeCopyTo(Vector<server::zone::QuadTreeEntry*>& vec) const;

	void safeCopyReceiversTo(Vector<server::zone::QuadTreeEntry*>& vec, uint32 receiverType) const;
	void safeCopyReceiversTo(Vector<engine::core::ManagedReference<server::zone::QuadTreeEntry*> >& vec, uint32 receiverType) const;

	void safeCopyTo(Vector<engine::core::ManagedReference<server::zone::QuadTreeEntry*> >& vec) const;

	SortedVector<engine::core::ManagedReference<server::zone::QuadTreeEntry*> > getSafeCopy() const;

	Reference<server::zone::QuadTreeEntry*> get(int idx) const;

	int put(const Reference<server::zone::QuadTreeEntry*>& o);
	int put(Reference<server::zone::QuadTreeEntry*>&& o);

	inline int size() const {
		return objects.size();
	}

	void setNoDuplicateInsertPlan() {
		objects.setNoDuplicateInsertPlan();
	}
};

 }
}

using namespace server::zone;

#endif /* ZONECLOSEOBJECTSVECTOR_H_ */
