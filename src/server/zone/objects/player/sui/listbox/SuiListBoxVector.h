#ifndef SUILISTBOXVECTOR_H_
#define SUILISTBOXVECTOR_H_

#include "engine/orb/DistributedObjectBroker.h"

class SuiListBoxVector : public DistributedObjectStub {
public:
	SuiListBoxVector();
	virtual ~SuiListBoxVector();

	unsigned int size();

	void add(String& item);

	String& get(unsigned int index);

	void removeAll();

	void removeLastElement();

protected:
	SuiListBoxVector(DummyConstructorParameter* param);

	String _return_get;

	friend class SuiListBoxVectorHelper;
};

class SuiListBoxVectorImplementation;

class SuiListBoxVectorAdapter : public DistributedObjectAdapter {
public:
	SuiListBoxVectorAdapter(SuiListBoxVectorImplementation* impl);

	Packet* invokeMethod(sys::uint32 methid, DistributedMethod* method);

	unsigned int size();

	void add(String& item);

	String& get(unsigned int index);

	void removeAll();

	void removeLastElement();
protected:
	String _param0_add__String_;
};

class SuiListBoxVectorHelper : public DistributedObjectClassHelper, public Singleton<SuiListBoxVectorHelper> {
	static SuiListBoxVectorHelper* staticInitializer;

public:
	SuiListBoxVectorHelper();

	void finalizeHelper();

	DistributedObject* instantiateObject();

	DistributedObjectAdapter* createAdapter(DistributedObjectStub* obj);

	friend class SingletonWrapper<SuiListBoxVectorHelper>;
};

class SuiListBoxVectorServant : public DistributedObjectServant {
public:
	SuiListBoxVector* _this;

public:
	SuiListBoxVectorServant();
	virtual ~SuiListBoxVectorServant();

	void _setStub(DistributedObjectStub* stub);
	DistributedObjectStub* _getStub();

};

#endif /*SUILISTBOXVECTOR_H_*/
