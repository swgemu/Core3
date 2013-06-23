/*
 * VectorParam.h
 *
 *  Created on: 22-feb-2009
 *      Author: TheAnswer
 */

#ifndef VECTORPARAM_H_
#define VECTORPARAM_H_

#include "TemplateBase.h"

/*
template <class Type>
class VectorParamData {
public:
	VectorParamData() {

	}
};

template <class Data>
class VectorParam : public TemplateBase<VectorParamData<Type> > {
	int size;
	QVector<Data> data;
public:
	VectorParam() : TemplateBase<VectorParamData<Type>, VectorParamData<Type> >(VectorParamData<Type>()) {

	}
};*/

template <class Data>
class VectorParam : public Param {
	Vector<Data> vectorData;

public:
	VectorParam() : Param() {
	}

	~VectorParam() {
	}

	Vector<Data> get() const {
		return vectorData;
	}

	Data& get(int i) {
		return vectorData.get(i);
	}

	void add(Data data) {
		vectorData.add(data);
	}

	String toString() {
		//String var;
		StringBuffer stream;

		stream << "{";
		for (int i = 0; i < vectorData.size(); ++i) {
			stream << vectorData.get(i).toString();

			if (i + 1 < vectorData.size())
				stream << ",";
		}

		stream << "}";

		return stream.toString();
	}

	bool parse(Chunk* data) {
		int size = data->readInt();

		/*uint8 unk = data->getUnsignedByte();
		uint32 num = data->getUnsignedInt();*/

		Vector<Data> newData;

		for (int i = 0; i < size; ++i) {
			Data param;

			if (param.parse(data))
				newData.add(param);
		}

		if (!newData.isEmpty()) {
			vectorData = newData;
			return true;
		} else {
			return false;
		}
	}
};



#endif /* VECTORPARAM_H_ */
