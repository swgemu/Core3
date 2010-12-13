/*
 * PortalLayout.cpp
 *
 *  Created on: 03/12/2010
 *      Author: victor
 */

#include "PortalLayout.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "MeshAppearanceTemplate.h"

void PortalLayout::parse(IffStream* iffStream) {
	try {
		iffStream->openForm('PRTO');

		uint32 type = iffStream->getNextFormType();

		if (type != '0003' && type != '0004') {
			StringBuffer stream;
			stream << "invalid PROTO type 0x" << hex << type;
			error(stream);

			return;
		}


		iffStream->openForm(type);

		Chunk* data = iffStream->openChunk('DATA');

		uint32 var1 = iffStream->getInt();
		uint32 var2 = iffStream->getInt();

		iffStream->closeChunk('DATA');

		iffStream->openForm('PRTS');

		//skipping PRTS
		iffStream->closeForm('PRTS');

		//open CELS form

		parseCELSForm(iffStream);


		iffStream->closeForm(type);

		iffStream->closeForm('PRTO');
	} catch (...) {
		String err = "unable to parse file ";
		err += iffStream->getFileName();
		error(err);
	}
}

void PortalLayout::parseCELSForm(IffStream* iffStream) {
	try {
		iffStream->openForm('CELS');

		uint32 nextType;

		while ((nextType = iffStream->getNextFormType()) == 'CELL') {
			try {
				iffStream->openForm('CELL');

				++cellTotalNumber;
				uint32 nextForm = iffStream->getNextFormType();

				if (nextForm != '0005') {
					//SWGForensics::instance->printToConsole(QString("wrong cell form ") + iffStream->getFileName().c_str());
					error(String("wrong cell form ") + iffStream->getFileName());

					continue;
				}

				iffStream->openForm('0005');

				Chunk* dataChunk = iffStream->openChunk('DATA');

				int sizeunk = iffStream->getInt();

				int readCase = iffStream->getByte();

				String cellName;
				iffStream->getString(cellName);

				String meshFile;
				iffStream->getString(meshFile);

				if (meshFile.length() > 1) {
					AppearanceTemplate* app = TemplateManager::instance()->getAppearanceTemplate(meshFile);

					if (app != NULL)
						appearanceTemplates.add(dynamic_cast<MeshAppearanceTemplate*>(app->getFirstMesh()));
				}

				int readCase2 = iffStream->getByte();

				if (dataChunk->hasData()) {
					String floorFile;
					iffStream->getString(floorFile);

					if (floorFile.length() > 1) {
						FloorMesh* floorMesh = TemplateManager::instance()->getFloorMesh(floorFile);

						floorMeshes.add(floorMesh);
					}
				}

				iffStream->closeChunk();

				iffStream->closeForm('0005');

				iffStream->closeForm('CELS');
			} catch (Exception& e) {
				error(e.getMessage());
				error("parsing CELS for " + iffStream->getFileName());
				e.printStackTrace();
			} catch (...) {
				error("parsing CELS for " + iffStream->getFileName());
			}
		}

	} catch (Exception& e) {
		//error(e.getMessage());
		//error("parsing CELS for " + iffStream->getFileName());
	} catch (...) {
		//error("parsing CELS for " + iffStream->getFileName());
	}

	if (cellTotalNumber > 0)
		--cellTotalNumber;
}
