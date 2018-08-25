//
// Created by Victor Popovici on 7/2/17.
//

#include "engine/core/ManagedReference.h"

#include "CloseObjectsVector.h"

#include "server/zone/QuadTreeEntry.h"

CloseObjectsVector::CloseObjectsVector() : messageReceivers() {
	objects.setNoDuplicateInsertPlan();

	messageReceivers.setNoDuplicateInsertPlan();
}

void CloseObjectsVector::safeCopyTo(Vector<ManagedReference<QuadTreeEntry*> >& vec) const {
	vec.removeAll(size(), size() / 2);

	ReadLocker locker(&mutex);

	//vec.addAll(*this);
	for (int i = 0; i < objects.size(); ++i) {
		const auto& obj = objects.getUnsafe(i);

		vec.emplace(obj);
	}
}

SortedVector<ManagedReference<QuadTreeEntry*> > CloseObjectsVector::getSafeCopy() const {
	ReadLocker locker(&mutex);

	SortedVector<ManagedReference<QuadTreeEntry*> > copy;

	for (int i = 0; i < objects.size(); ++i) {
		const auto& obj = objects.getUnsafe(i);

		copy.emplace(obj.get());
	}

	return copy;
}

void CloseObjectsVector::safeCopyTo(Vector<QuadTreeEntry*>& vec) const {
	vec.removeAll(size(), size() / 2);

	ReadLocker locker(&mutex);

	for (int i = 0; i < objects.size(); ++i) {
		vec.add(objects.getUnsafe(i).get());
	}
}

bool CloseObjectsVector::contains(const Reference<QuadTreeEntry*>& o) const {
	ReadLocker locker(&mutex);

	bool ret = objects.find(o) != -1;

	return ret;
}

void CloseObjectsVector::removeAll(int newSize, int newIncrement) {
	Locker locker(&mutex);

	objects.removeAll(newSize, newIncrement);

	messageReceivers.removeAll(newSize, newIncrement);
}

void CloseObjectsVector::dropReceiver(QuadTreeEntry* entry) {
	uint32 receiverTypes = entry->registerToCloseObjectsReceivers();

	if (receiverTypes && messageReceivers.size()) {
		for (int i = 0; i < CloseObjectsVector::MAXTYPES; ++i) {
			uint32 type = 1 << i;

			if (receiverTypes & type) {
				int idx = messageReceivers.find(type);

				if (idx != -1) {
					auto& receivers = messageReceivers.elementAt(idx).getValue();

					receivers.drop(entry);
				}
			}
		}
	}
}

Reference<QuadTreeEntry*> CloseObjectsVector::remove(int index) {
	Locker locker(&mutex);

	const auto& ref = objects.get(index);

	dropReceiver(ref);

	return objects.remove(index);
}

bool CloseObjectsVector::drop(const Reference<QuadTreeEntry*>& o) {
	Locker locker(&mutex);

	dropReceiver(o);

	return objects.drop(o);
}

void CloseObjectsVector::safeCopyReceiversTo(Vector<QuadTreeEntry*>& vec, uint32 receiverType) const {
	ReadLocker locker(&mutex);

	int i = messageReceivers.find(receiverType);

	if (i != -1) {
		const auto& receivers = messageReceivers.elementAt(i).getValue();

		vec.removeAll(receivers.size(), receivers.size() / 2);

		vec.addAll(receivers);
	}
}

void CloseObjectsVector::safeCopyReceiversTo(Vector<ManagedReference<QuadTreeEntry*> >& vec, uint32 receiverType) const {
	ReadLocker locker(&mutex);

	int i = messageReceivers.find(receiverType);

	if (i != -1) {
		const auto& receivers = messageReceivers.elementAt(i).getValue();

		vec.removeAll(receivers.size(), receivers.size() / 2);

		for (int i = 0; i < receivers.size(); ++i)
			vec.emplace(receivers.getUnsafe(i));
	}
}

void CloseObjectsVector::safeAppendReceiversTo(Vector<QuadTreeEntry*>& vec, uint32 receiverType) const {
	ReadLocker locker(&mutex);

	int i = messageReceivers.find(receiverType);

	if (i != -1) {
		const auto& receivers = messageReceivers.elementAt(i).getValue();
		vec.addAll(receivers);
	}
}

void CloseObjectsVector::safeAppendReceiversTo(Vector<ManagedReference<QuadTreeEntry*> >& vec, uint32 receiverType) const {
	ReadLocker locker(&mutex);

	int i = messageReceivers.find(receiverType);

	if (i != -1) {
		const auto& receivers = messageReceivers.elementAt(i).getValue();
		for (int i = 0; i < receivers.size(); ++i)
			vec.emplace(receivers.getUnsafe(i));
	}
}

Reference<QuadTreeEntry*> CloseObjectsVector::get(int idx) const {
	return objects.get(idx);
}

void CloseObjectsVector::putReceiver(QuadTreeEntry* entry, uint32 receiverTypes) {
	if (receiverTypes) {
		for (int i = 0; i < CloseObjectsVector::MAXTYPES; ++i) {
			uint32 type = 1 << i;

			if (receiverTypes & type) {
				int idx = messageReceivers.find(type);

				if (idx != -1) {
					auto& receivers = messageReceivers.elementAt(idx).getValue();

					receivers.put(entry);
				} else {
					SortedVector<QuadTreeEntry*> vec;
					vec.setNoDuplicateInsertPlan();

					vec.put(entry);

					messageReceivers.put(std::move(type), std::move(vec));
				}
			}
		}
	}
}

int CloseObjectsVector::put(const Reference<QuadTreeEntry*>& o) {

	uint32 receiverTypes = o->registerToCloseObjectsReceivers();
	Locker locker(&mutex);

	putReceiver(o.get(), receiverTypes);

	return objects.put(o);
}

int CloseObjectsVector::put(Reference<QuadTreeEntry*>&& o) {
	uint32 receiverTypes = o->registerToCloseObjectsReceivers();
	Locker locker(&mutex);
	putReceiver(o.get(), receiverTypes);

	return objects.put(std::move(o));
}