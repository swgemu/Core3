/*
 * FloatParam.h
 *
 *  Created on: 22-feb-2009
 *      Author: TheAnswer
 */

#ifndef FLOATPARAM_H_
#define FLOATPARAM_H_

#include "../TemplateBase.h"

class FloatParam : public TemplateBase<float> {
	float min;
	float max;
public:
	FloatParam() : TemplateBase<float>(0.f) {
		setType(FLOAT);
		min = 0;
		max = 0;
	}

	FloatParam(float m) : TemplateBase<float>(m) {
		setType(FLOAT);
		min = 0;
		max = 0;
	}

	FloatParam& operator= (float val) {
		create(val);

		return *this;
	}

	inline void setMin(float m) {
		min = m;
	}

	inline void setMax(float m) {
		max = m;
	}

	String toString() {
		StringBuffer in;

		if (min != 0 || max != 0) {
			in << "{" << min << ", " << max << "}";
		} else {
			in << get();
		}

		return in.toString();
	}

	static bool toBinaryStream(ObjectOutputStream* stream) {
		return false;
	}

	/*static bool parseFromString(T* address, const sys::lang::String& value, int version = 0) {
		return address->parseFromString(value, version);
	}*/

	static bool parseFromBinaryStream(ObjectInputStream* stream) {
		return false;
	}


	virtual bool parse(engine::util::Chunk* source) {
		uint8 readCase = source->readByte();
		uint8 byte2 = source->readByte();

		if (readCase == 1 && byte2 == 0x20) {
			create(source->readFloat());

			return true;
		} else if (readCase == 2 && byte2 == 0x20) {
			IffStream* iffStream = source->getIffStream();


			StringBuffer msg;
			msg << "unhandled FloatParam type! in " <<  iffStream->getFileName();
			Logger::console.error(msg.toString());
			/*stream << iffStream->getFileName().c_str() << "\n";
			SWGForensics::instance->printToConsole(text);*/
		} else if (readCase == 3 && byte2 == 0x20) {
			/*IffStream* iffStream = source->getIffStream();

			QString text;
			QTextStream stream(&text);

			stream << "READ CASE 3 MOTHER FUCKER FloatParam type! in ";
			stream << iffStream->getFileName().c_str() << "\n";
			SWGForensics::instance->printToConsole(text);*/

			min = source->readFloat();
			max = source->readFloat();
		}

			/* else {
			create(0.f);
		}*/

		return false;
	}

	inline float getMin() {
		return min;
	}

	inline float getMax() {
		return max;
	}
};


#endif /* FLOATPARAM_H_ */
