/*
 * ClientPoiDataTable.h
 *
 *  Created on: 02/04/2012
 *      Author: victor
 */

#ifndef CLIENTPOIDATATABLE_H_
#define CLIENTPOIDATATABLE_H_

#include "engine/engine.h"
#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableRow.h"

class PoiData : public Object {
protected:
	String name;
	String description;
	String planet;
	float x, y, z;

public:
	PoiData() : x(0), y(0), z(0) {

	}

	void readObject(DataTableRow* row) {
		row->getValue(0, name);
		row->getValue(1, description);
		row->getValue(2, planet);
		row->getValue(4, x);
		row->getValue(5, z);
		row->getValue(6, y);
	}

	Vector3 getPosition() {
		return Vector3(x, y, z);
	}

	String getDescription() const {
		return description;
	}

	String getName() const {
		return name;
	}

	String getPlanet() const {
		return planet;
	}

	float getX() const {
		return x;
	}
};

class ClientPoiDataTable : public Object {
	VectorMap<String, Vector<Reference<PoiData*> > > pois;
public:
	ClientPoiDataTable() {
		pois.setAllowOverwriteInsertPlan();
	}

	void readObject(DataTableIff* dataTable) {
		for (int i = 0; i < dataTable->getTotalRows(); ++i) {
			PoiData* data = new PoiData();
			data->readObject(dataTable->getRow(i));

			Vector<Reference<PoiData*> > vector = pois.get(data->getPlanet());
			vector.add(data);

			pois.put(data->getPlanet(), vector);
		}
	}

	bool containsPlanet(const String& name) {
		return pois.contains(name);
	}

	Vector<Reference<PoiData*> > getPois(const String& planetName) {
		return pois.get(planetName);
	}

	int size() {
		int count = 0;

		for (int i = 0; i < pois.size(); ++i)
			count += pois.get(i).size();

		return count;
	}
};


#endif /* CLIENTPOIDATATABLE_H_ */
