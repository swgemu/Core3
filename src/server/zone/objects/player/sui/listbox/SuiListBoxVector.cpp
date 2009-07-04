#include "SuiListBoxVector.h"

#include "SuiListBoxVectorImplementation.h"

/*
 *	SuiListBoxVectorStub
 */

SuiListBoxVector::SuiListBoxVector() {
	_impl = new SuiListBoxVectorImplementation();
	_impl->_setStub(this);
}

SuiListBoxVector::SuiListBoxVector(DummyConstructorParameter* param) {
	_impl = NULL;
}

SuiListBoxVector::~SuiListBoxVector() {
}

unsigned int SuiListBoxVector::size() {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 6);

		return method.executeWithUnsignedIntReturn();
	} else
		return ((SuiListBoxVectorImplementation*) _impl)->size();
}

void SuiListBoxVector::add(String& item) {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 7);
		method.addAsciiParameter(item);

		method.executeWithVoidReturn();
	} else
		((SuiListBoxVectorImplementation*) _impl)->add(item);
}

String& SuiListBoxVector::get(unsigned int index) {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 8);
		method.addUnsignedIntParameter(index);

		method.executeWithAsciiReturn(_return_get);
		return _return_get;
	} else
		return ((SuiListBoxVectorImplementation*) _impl)->get(index);
}

void SuiListBoxVector::removeAll(){
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 9);

		method.executeWithVoidReturn();
	} else
		((SuiListBoxVectorImplementation*) _impl)->removeAll();
}

void SuiListBoxVector::removeLastElement(){
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 10);

		method.executeWithVoidReturn();
	} else
		((SuiListBoxVectorImplementation*) _impl)->removeLastElement();
}

/*
 *	SuiListBoxVectorAdapter
 */

SuiListBoxVectorAdapter::SuiListBoxVectorAdapter(SuiListBoxVectorImplementation* obj) : DistributedObjectAdapter((DistributedObjectServant*) obj) {
}

Packet* SuiListBoxVectorAdapter::invokeMethod(uint32 methid, DistributedMethod* inv) {
	Packet* resp = new MethodReturnMessage(0);

	switch (methid) {
	case 6:
		resp->insertInt(size());
		break;
	case 7:
		add(inv->getAsciiParameter(_param0_add__String_));
		break;
	case 8:
		resp->insertAscii(get(inv->getUnsignedIntParameter()));
		break;
	case 9:
		removeAll();
		break;
	case 10:
		removeLastElement();
		break;
	default:
		return NULL;
	}

	return resp;
}

unsigned int SuiListBoxVectorAdapter::size() {
	return ((SuiListBoxVectorImplementation*) impl)->size();
}

void SuiListBoxVectorAdapter::add(String& item) {
	return ((SuiListBoxVectorImplementation*) impl)->add(item);
}

String& SuiListBoxVectorAdapter::get(unsigned int index) {
	return ((SuiListBoxVectorImplementation*) impl)->get(index);
}

void SuiListBoxVectorAdapter::removeAll() {
	return ((SuiListBoxVectorImplementation*) impl)->removeAll();
}

void SuiListBoxVectorAdapter::removeLastElement() {
	return ((SuiListBoxVectorImplementation*) impl)->removeLastElement();
}

/*
 *	SuiListBoxVectorHelper
 */

SuiListBoxVectorHelper* SuiListBoxVectorHelper::staticInitializer = SuiListBoxVectorHelper::instance();

SuiListBoxVectorHelper::SuiListBoxVectorHelper() {
	className = "SuiListBoxVector";

	DistributedObjectBroker::instance()->registerClass(className, this);
}

void SuiListBoxVectorHelper::finalizeHelper() {
	SuiListBoxVectorHelper::finalize();
}

DistributedObject* SuiListBoxVectorHelper::instantiateObject() {
	return new SuiListBoxVector(DummyConstructorParameter::instance());
}

DistributedObjectAdapter* SuiListBoxVectorHelper::createAdapter(DistributedObjectStub* obj) {
	DistributedObjectAdapter* adapter = new SuiListBoxVectorAdapter((SuiListBoxVectorImplementation*) obj->_getImplementation());

	obj->_setClassName(className);
	obj->_setClassHelper(this);

	adapter->setStub(obj);

	return adapter;
}

/*
 *	SuiListBoxVectorServant
 */

SuiListBoxVectorServant::SuiListBoxVectorServant() {
	_classHelper = SuiListBoxVectorHelper::instance();
}

SuiListBoxVectorServant::~SuiListBoxVectorServant() {
}

void SuiListBoxVectorServant::_setStub(DistributedObjectStub* stub) {
	_this = (SuiListBoxVector*) stub;
}

DistributedObjectStub* SuiListBoxVectorServant::_getStub() {
	return _this;
}

