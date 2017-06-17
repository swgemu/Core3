#include "CellProperty.h"

#include "templates/manager/TemplateManager.h"

void CellPortal::readObject(IffStream* iff) {
	Chunk* chunk = iff->openChunk();

	uint32 formType = chunk->getChunkID();
	
	if (formType == '0004' || formType == '0005') {

		if (formType == '0005') {
			iff->getByte(); // Unknown flag
		}

		solid = (bool) iff->getByte();
		geometryIndex = iff->getInt();
		winding = (bool) iff->getByte();
		int unk = iff->getInt();
		iff->getString(doorName);
		transformFlag = (bool) iff->getByte();

		doorTransform[0][0] = iff->getFloat();
		doorTransform[1][0] = iff->getFloat();
		doorTransform[2][0] = iff->getFloat();
		doorTransform[3][0] = iff->getFloat();

		doorTransform[0][1] = iff->getFloat();
		doorTransform[1][1] = iff->getFloat();
		doorTransform[2][1] = iff->getFloat();
		doorTransform[3][1] = iff->getFloat();

		doorTransform[0][2] = iff->getFloat();
		doorTransform[1][2] = iff->getFloat();
		doorTransform[2][2] = iff->getFloat();
		doorTransform[3][2] = iff->getFloat();
	} else {
		TemplateManager::instance()->error("Invalid CellPortal type");
	}

	iff->closeChunk();
}

CellProperty::CellProperty() : Object(), Logger("CellProperty"), numberOfPortals(0),
	floorMesh(NULL), appearanceTemplate(NULL), cellID(0), boundingVolume(NULL) {

}

CellProperty::CellProperty(int cellID) : Logger("CellProperty"), numberOfPortals(0), floorMesh(NULL),
	appearanceTemplate(NULL), cellID(cellID), boundingVolume(NULL) {
}

CellProperty::CellProperty(const CellProperty& c) : Object(), Logger("CellProperty"),
	name(c.name), numberOfPortals(c.numberOfPortals), floorMesh(c.floorMesh), appearanceTemplate(c.appearanceTemplate),
	cellID(c.cellID), boundingVolume(c.boundingVolume), portals(c.portals) {

}

CellProperty& CellProperty::operator=(const CellProperty& c) {
	if (this == &c)
		return *this;

	name = c.name;
	numberOfPortals = c.numberOfPortals;
	floorMesh = c.floorMesh;
	appearanceTemplate = c.appearanceTemplate;
	cellID = c.cellID;
	boundingVolume = c.boundingVolume;
	portals = c.portals;

	return *this;
}

void CellProperty::loadVersion5(IffStream* iffStream) {
	iffStream->openForm('0005');

	Chunk* dataChunk = iffStream->openChunk('DATA');

	numberOfPortals = iffStream->getInt();

	Byte unk = iffStream->getByte();

	iffStream->getString(name);

	String meshFile;
	iffStream->getString(meshFile);

	if (meshFile.length() > 1) {
		AppearanceTemplate* app = TemplateManager::instance()->getAppearanceTemplate(meshFile);
		if (app != NULL) {
			appearanceTemplate = app;
		} else {
			info("Error reading mesh " + meshFile, true);
		}
	}

	bool flag = (bool) iffStream->getByte();

	if (flag) {
		String floorFile;
		iffStream->getString(floorFile);
		floorMesh = TemplateManager::instance()->getFloorMesh(floorFile);
		floorMesh->setCellID(cellID);

	}

	iffStream->closeChunk();

	// get bounding volume, usually CMSH
	boundingVolume = BoundingVolumeFactory::getVolume(iffStream);

	for (int i = 0; i < numberOfPortals; i++) {
		iffStream->openForm('PRTL');

		Reference < CellPortal * > portal = new CellPortal();
		portal->readObject(iffStream);

		iffStream->closeForm('PRTL');

		portals.emplace(std::move(portal));

	}

	iffStream->closeForm('0005');
}

void CellProperty::loadVersion4(IffStream* iffStream) {
	iffStream->openForm('0004');

	Chunk* dataChunk = iffStream->openChunk('DATA');

	numberOfPortals = iffStream->getInt();

	Byte unk = iffStream->getByte();

	iffStream->getString(name);

	String meshFile;
	iffStream->getString(meshFile);

	if (meshFile.length() > 1) {
		AppearanceTemplate* app = TemplateManager::instance()->getAppearanceTemplate(meshFile);
		if (app != NULL) {
			appearanceTemplate = app;
		} else {
			info("Error reading mesh " + meshFile, true);
		}
	}

	bool flag = (bool) iffStream->getByte();

	if (flag) {
		String floorFile;
		iffStream->getString(floorFile);
		floorMesh = TemplateManager::instance()->getFloorMesh(floorFile);

	}

	iffStream->closeChunk();

	for (int i = 0; i < numberOfPortals; i++) {
		iffStream->openForm('PRTL');

		Reference < CellPortal * > portal = new CellPortal();
		portal->readObject(iffStream);

		iffStream->closeForm('PRTL');

		portals.emplace(std::move(portal));

	}

	iffStream->closeForm('0004');
}

void CellProperty::readObject(IffStream* iffStream) {
	iffStream->openForm('CELL');

	try {
		uint32 nextForm = iffStream->getNextFormType();

		if (nextForm == '0004') {
			loadVersion4(iffStream);
		} else if (nextForm == '0005') {
			loadVersion5(iffStream);
		} else {
			String message = String("wrong cell form ") + iffStream->getFileName();
			error(message);

			throw Exception(message);
		}


	} catch (Exception& e) {
		error(e.getMessage());
		error("parsing CELL for " + iffStream->getFileName());
		e.printStackTrace();
	} catch (...) {
		error("parsing CELL for " + iffStream->getFileName());
	}

	iffStream->closeForm('CELL');
}
