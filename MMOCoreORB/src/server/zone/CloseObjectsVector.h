/*
 * CloseObjectsVector.h
 *
 *  Created on: 11/06/2012
 *      Author: victor
 */

#ifndef ZONECLOSEOBJECTSVECTOR_H_
#define ZONECLOSEOBJECTSVECTOR_H_

#include "system/util/SortedVector.h"
#include "system/lang/ref/Reference.h"
#include "system/thread/ReadWriteLock.h"

#include "engine/core/ManagedReference.h"
namespace server {
 namespace zone {
class TreeEntry;

class CloseObjectsVector : public Object {
	mutable ReadWriteLock mutex;
	SortedVector<Reference<server::zone::TreeEntry*> > objects;

	VectorMap<uint32, SortedVector<server::zone::TreeEntry*> > messageReceivers;

	uint32 count;

#if defined(CXX11_COMPILER) && !defined(TRACE_REFERENCES)
	static_assert(sizeof(server::zone::TreeEntry*) == sizeof(Reference<server::zone::TreeEntry*>), "Reference<> size is not the size of a pointer");
#endif

protected:
	void dropReceiver(server::zone::TreeEntry* entry);
	void putReceiver(server::zone::TreeEntry* entry, uint32 receiverTypes);
public:
	enum {
		PLAYERTYPE = 1 << 0,
		CREOTYPE = 1 << 1,
		COLLIDABLETYPE = 1 << 2,
		INSTALLATIONTYPE = 1 << 3,
		STRUCTURETYPE = 1 << 4,
		SHIPTYPE = 1 << 5,
		PLAYERSHIPTYPE = 1 << 6,
		MAXTYPES = PLAYERSHIPTYPE
	};

	CloseObjectsVector();

	Reference<server::zone::TreeEntry*> remove(int index);

	bool contains(const Reference<server::zone::TreeEntry*>& o) const;

	void removeAll(int newSize = 10, int newIncrement = 5);

	bool drop(const Reference<server::zone::TreeEntry*>& o);

	void safeCopyTo(Vector<server::zone::TreeEntry*>& vec) const;
	void safeCopyTo(Vector<ManagedReference<server::zone::TreeEntry*> >& vec) const;

	void safeCopyReceiversTo(Vector<server::zone::TreeEntry*>& vec, uint32 receiverType) const;
	void safeCopyReceiversTo(Vector<ManagedReference<server::zone::TreeEntry*> >& vec, uint32 receiverType) const;
	void safeAppendReceiversTo(Vector<server::zone::TreeEntry*>& vec, uint32 receiverType) const;
	void safeAppendReceiversTo(Vector<ManagedReference<server::zone::TreeEntry*> >& vec, uint32 receiverType) const;

	SortedVector<ManagedReference<server::zone::TreeEntry*> > getSafeCopy() const;

	const Reference<server::zone::TreeEntry*>& get(int idx) const;

	int put(const Reference<server::zone::TreeEntry*>& o);
	int put(Reference<server::zone::TreeEntry*>&& o);

	void safeRunForEach(const Function<void(TreeEntry* const&)>& lambda, uint32 receiverType) const;

	int size() const NO_THREAD_SAFETY_ANALYSIS {
		return count;
	}

	void setNoDuplicateInsertPlan() {
		objects.setNoDuplicateInsertPlan();
	}

	static String receiverFlagsToString(int flags) {
		StringBuffer buf;
		String sep = "";

		if (flags & PLAYERTYPE) {
			flags = flags & ~PLAYERTYPE;
			buf << sep << "PLAYER";
			sep = ", ";
		}

		if (flags & CREOTYPE) {
			flags = flags & ~CREOTYPE;
			buf << sep << "CREO";
			sep = ", ";
		}

		if (flags & COLLIDABLETYPE) {
			flags = flags & ~COLLIDABLETYPE;
			buf << sep << "COLLIDABLE";
			sep = ", ";
		}

		if (flags & STRUCTURETYPE) {
			flags = flags & ~STRUCTURETYPE;
			buf << sep << "STRUCTURE";
			sep = ", ";
		}

		if (flags & SHIPTYPE) {
			flags = flags & ~SHIPTYPE;
			buf << sep << "SHIP";
			sep = ", ";
		}

		if (flags & PLAYERSHIPTYPE) {
			flags = flags & ~PLAYERSHIPTYPE;
			buf << sep << "PLAYERSHIP";
			sep = ", ";
		}

		if (flags)
			buf << sep << "<unexpected flags: " << flags << ">";

		if (buf.length() == 0)
			buf << "<no flags>";

		return buf.toString();
	}
};

 }
}

using namespace server::zone;

#endif /* ZONECLOSEOBJECTSVECTOR_H_ */
