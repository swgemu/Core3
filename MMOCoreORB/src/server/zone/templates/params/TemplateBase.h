/*
 * TemplateBase.h
 *
 *  Created on: 22-feb-2009
 *      Author: TheAnswer
 */

#ifndef TEMPLATEBASE_H_
#define TEMPLATEBASE_H_

#include "engine/engine.h"

#include "Param.h"

template <class V> class TemplateBase : public Param {
protected:
	V value;
	//T unknown;

public:
	TemplateBase(const V& defaultValue) : Param() {
		create(defaultValue);
	}

	TemplateBase(const TemplateBase& t) : Param() {
		create(t.value);
	}

	virtual ~TemplateBase() {

	}

	void create(const V& val) {
		value = val;
	}

	virtual int compareTo(const V& val) const {
		if (value < val)
			return 1;
		else if (value > val)
			return -1;
		else return 0;
	}

	/*TemplateBase& operator= (const V& val) {
		create(val);

		return *this;
	}*/

	/*V& operator= (const V& val) {
		create(val);

		return value;
	}*/

	virtual bool operator== (const V& val) const {
		return compareTo(val) == 0;
	}

	virtual bool operator< (const V& val) const {
		return compareTo(val) < 0;
	}

	virtual bool operator> (const V& val) const {
		return compareTo(val) > 0;
	}

	virtual bool operator!= (const V& val) const {
		return compareTo(val) != 0;
	}

	/*virtual V& operator+= (const V& val) {
		return value += val;
	}

	virtual V& operator-= (const V& val) {
		return value -= val;
	}*/

	operator V() const {
		return value;
	}

	virtual V getValue() const {
		return value;
	}

	virtual V get() const {
		return value;
	}

	virtual void setValue(const V& val/*, const T& unk*/) {
		value = val;
		//unknown = unk;
	}
};

#endif /* TEMPLATEBASE_H_ */
