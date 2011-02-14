/*
 * DataTableIff.h
 *
 *  Created on: Feb 11, 2011
 *      Author: crush
 */

#ifndef DATATABLEIFF_H_
#define DATATABLEIFF_H_

#include "engine/engine.h"
#include "../IffTemplate.h"

class DataTableCell;

class DataTableIff : public IffTemplate {
	Vector<String> columns;
	Vector<byte> columnTypes;
	Vector<DataTableCell*> cells;

public:
	DataTableIff();
	~DataTableIff();

	void readObject(IffStream* iffStream);
};


#endif /* DATATABLEIFF_H_ */
