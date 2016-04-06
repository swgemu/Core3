/*
 * IntegerParam.h
 *
 *  Created on: 22-feb-2009
 *      Author: TheAnswer
 */

#ifndef INTEGERPARAM_H_
#define INTEGERPARAM_H_

#include "templates/params/TemplateBase.h"

class IntegerParam : public TemplateBase<int> {

public:
	IntegerParam() : TemplateBase<int>(0) {
		setType(INTEGER);
	}

	IntegerParam(const IntegerParam& p) : TemplateBase<int>(p) {
		setType(INTEGER);
	}

	IntegerParam& operator= (int val) {
		create(val);

		return *this;
	}

	String toString() {
		return String::valueOf(get());
	}

	virtual bool parse(engine::util::Chunk* source) {
		uint8 readCase = source->readByte();
		uint8 byte2 = source->readByte();

		if (readCase == 1 && byte2 == 0x20) {
			create(source->readInt());

			return true;
		} else if (readCase == 2 && byte2 == 0x20) {
			/*int size = source->getUnsignedInt();

			QVector<IntegerParam> params;

			for (int i = 0; i < size; ++i) {
				int unknown = source->getUnsignedInt();

				IntegerParam param;

				if (param.parse(source))
					params.push_back(param);
			}*/

			IffStream* iffStream = source->getIffStream();

			StringBuffer msg;
			msg << "unhandled IntegerParam type! in " << iffStream->getFileName();

			Logger::console.info(msg.toString());

		}/* else {
			create(0);
		}*/

		return false;
	}

};


#endif /* INTEGERPARAM_H_ */
