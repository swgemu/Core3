/*
 * PaletteData.h
 *
 *  Created on: 29/03/2012
 *      Author: victor
 */

#ifndef PALETTEDATA_H_
#define PALETTEDATA_H_

#include "engine/engine.h"
#include "server/zone/templates/datatables/DataTableRow.h"

class PaletteData : public Object {
protected:
	String name;
	int creationColumns;
	int creationIndexes;
	int idNoviceColumns;
	int idNoviceIndexes;
	int idLevel1Columns;
	int idLevel1Indexes;
	int idLevel2Columns;
	int idLevel2Indexes;
	int idLevel3Columns;
	int idLevel3Indexes;
	int idLevel4Columns;
	int idLevel4Indexes;
	int idMasterColumns;
	int idMasterIndexes;

public:
	PaletteData() {
		creationColumns = creationIndexes
				= idNoviceColumns = idNoviceIndexes
				= idLevel1Columns = idLevel1Indexes
				= idLevel2Columns = idLevel2Indexes
				= idLevel3Columns = idLevel3Indexes
				= idLevel4Columns = idLevel4Indexes
				= idMasterColumns = idMasterIndexes = 0;
	}

	void readObject(DataTableRow* row) {
		row->getValue(0, name);
		row->getValue(1, creationColumns);
		row->getValue(2, creationIndexes);
		row->getValue(3, idNoviceColumns);
		row->getValue(4, idNoviceIndexes);
		row->getValue(5, idLevel1Columns);
		row->getValue(6, idLevel1Indexes);
		row->getValue(7, idLevel2Columns);
		row->getValue(8, idLevel2Indexes);
		row->getValue(9, idLevel3Columns);
		row->getValue(10, idLevel3Indexes);
		row->getValue(11, idLevel4Columns);
		row->getValue(12, idLevel4Indexes);
		row->getValue(13, idMasterColumns);
		row->getValue(14, idMasterIndexes);
	}

	int getCreationColumns() const {
		return creationColumns;
	}

	int getCreationIndexes() const {
		return creationIndexes;
	}

	int getIdLevel1Columns() const {
		return idLevel1Columns;
	}

	int getIdLevel1Indexes() const {
		return idLevel1Indexes;
	}

	int getIdLevel2Columns() const {
		return idLevel2Columns;
	}

	int getIdLevel2Indexes() const {
		return idLevel2Indexes;
	}

	int getIdLevel3Columns() const {
		return idLevel3Columns;
	}

	int getIdLevel3Indexes() const {
		return idLevel3Indexes;
	}

	int getIdLevel4Columns() const {
		return idLevel4Columns;
	}

	int getIdLevel4Indexes() const {
		return idLevel4Indexes;
	}

	int getIdMasterColumns() const {
		return idMasterColumns;
	}

	int getIdMasterIndexes() const {
		return idMasterIndexes;
	}

	void setIdMasterIndexes(int idMasterIndexes) {
		this->idMasterIndexes = idMasterIndexes;
	}

	int getIdNoviceColumns() const {
		return idNoviceColumns;
	}

	int getIdNoviceIndexes() const {
		return idNoviceIndexes;
	}

	String getName() {
		return name;
	}
};

#endif /* PALETTEDATA_H_ */
