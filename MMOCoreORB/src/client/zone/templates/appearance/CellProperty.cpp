#include "CellProperty.h"
#include "zone/managers/templates/TemplateManager.h"
#include "zone/managers/templates/DataArchiveStore.h"
#include "AppearanceTemplate.h"
#include "PathNode.h"
#include "FloorMesh.h"
#include "engine/util/u3d/AStarAlgorithm.h"

CellProperty::CellProperty() : Object(), Logger("CellProperty"), canSeeParentCell(false), numberOfPortals(0),
	floorMesh(NULL), appearanceTemplate(NULL), cellID(0) {
		volume = NULL;
}

CellProperty::CellProperty(int cellID) : Logger("CellProperty"), canSeeParentCell(false), numberOfPortals(0),
	floorMesh(NULL), appearanceTemplate(NULL), cellID(cellID) {
				volume = NULL;
}

CellProperty::CellProperty(const CellProperty& c) : Object(), Logger("CellProperty"),
		name(c.name), canSeeParentCell(c.canSeeParentCell), numberOfPortals(c.numberOfPortals),
			floorMesh(c.floorMesh), appearanceTemplate(c.appearanceTemplate), cellID(c.cellID) {
				volume = c.volume;

}
Vector<MeshData*> CellProperty::getTransformedMeshData(Matrix4 transform) {

	Vector<MeshData*> dummy;
	return dummy;
}

osg::ref_ptr<osg::Node> CellProperty::draw() {
	//info("Drawing ComponentAppearanceTemplate " + TemplateManager::instance()->getAppearanceTemplateString(this), true);
	osg::Group* group = new osg::Group();
	
//	if(volume)
//		group->addChild(volume->draw());
	
	if(floorMesh)
		group->addChild(floorMesh->draw());
	
	if(appearanceTemplate)
		group->addChild(appearanceTemplate->draw());
	
	return group;
	
}

CellProperty& CellProperty::operator=(const CellProperty& c) {
	if (this == &c)
		return *this;

	name = c.name;
	numberOfPortals = c.numberOfPortals;
	canSeeParentCell = c.canSeeParentCell;
	floorMesh = c.floorMesh;
	appearanceTemplate = c.appearanceTemplate;
	cellID = c.cellID;

	return *this;
}

void CellProperty::load_0005(IffStream* iffStream) {
	iffStream->openForm('0005');
	
	Chunk* dataChunk = iffStream->openChunk('DATA');
	
	numberOfPortals = iffStream->getInt();
	
	canSeeParentCell = iffStream->getByte();
	
	iffStream->getString(name);
	
	String meshFile;
	iffStream->getString(meshFile);
	
	if (meshFile.length() > 1) {
		AppearanceTemplate* app = TemplateManager::instance()->getAppearanceTemplate(meshFile);
		//IffStream *stream = DataArchiveStore::instance()->openIffFile(meshFile);
		//app->readObject(stream);
		if (app != NULL) {
			appearanceTemplate = app;
		} else {
			info("Error reading mesh " + meshFile, true);
		}
	}
	
	int readCase2 = iffStream->getByte();
	
	if (dataChunk->hasData()) {
		String floorFile;
		iffStream->getString(floorFile);
		
		if (floorFile.length() > 1) {
			floorMesh = TemplateManager::instance()->getFloorMesh(floorFile);
			//IffStream *stream = DataArchiveStore::instance()->openIffFile(floorFile);
			//floorMesh->readObject(stream);
			floorMesh->setCellID(cellID);
		}
	}
	
	iffStream->closeChunk();
	
	// get bounding volume, usually CMSH
	volume = BoundingVolumeList::getVolume(iffStream);
	
	iffStream->closeForm('0005');
}


void CellProperty::load_0004(IffStream* iffStream) {
	iffStream->openForm('0004');
	
	Chunk* dataChunk = iffStream->openChunk('DATA');
	
	numberOfPortals = iffStream->getInt();
	
	canSeeParentCell = iffStream->getByte();
	
	iffStream->getString(name);
	
	String meshFile;
	iffStream->getString(meshFile);
	
	if (meshFile.length() > 1) {
		AppearanceTemplate* app = TemplateManager::instance()->getAppearanceTemplate(meshFile);
		//IffStream *stream = DataArchiveStore::instance()->openIffFile(meshFile);
		//app->readObject(stream);
		if (app != NULL) {
			appearanceTemplate = app;
		} else {
			info("Error reading mesh " + meshFile, true);
		}
	}
	
	int readCase2 = iffStream->getByte();
	
	if (dataChunk->hasData()) {
		String floorFile;
		iffStream->getString(floorFile);
		
		if (floorFile.length() > 1) {
			floorMesh = TemplateManager::instance()->getFloorMesh(floorFile);
			//IffStream *stream = DataArchiveStore::instance()->openIffFile(floorFile);
			//floorMesh->readObject(stream);
//			if(floorMesh != NULL)
//			floorMesh->setCellID(cellID);
		}
	}
	
	iffStream->closeChunk();
	
	iffStream->closeForm('0005');
}

void CellProperty::readObject(IffStream* iffStream) {
	iffStream->openForm('CELL');

	try {
		uint32 nextForm = iffStream->getNextFormType();

		if(nextForm == '0004') {
			load_0004(iffStream);
		} else if(nextForm == '0005') {
			load_0005(iffStream);
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
