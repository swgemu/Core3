/*
 * Layer.cpp
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#include "affectors/AffectorProceduralRule.h"
#include "filters/FilterProceduralRule.h"
#include "boundaries/Boundary.h"

#include "Layer.h"

#include "affectors.h"
#include "boundaries.h"
#include "filters.h"

Layer::~Layer() {
	while (children.size() > 0) {
		delete children.remove(0);
	}

	while (boundaries.size() > 0) {
		delete boundaries.remove(0);
	}

	while (affectors.size() > 0) {
		delete affectors.remove(0);
	}

	while (filters.size() > 0) {
		delete filters.remove(0);
	}
}

void Layer::parseFromIffStream(engine::util::IffStream* iffStream) {
	uint32 version = iffStream->getNextFormType();

	iffStream->openForm(version);

	switch (version) {
	case '0003':
		parseFromIffStream(iffStream, Version<'0003'>());
		break;
	default:
		System::out << "unknown Layer version 0x" << hex << version << endl;
		break;
	}

	iffStream->closeForm(version);
}

void Layer::parseFromIffStream(engine::util::IffStream* iffStream, Version<'0003'>) {
	infoHeader.readObject(iffStream);

	iffStream->openChunk('ADTA');

	boundariesFlag = iffStream->getUnsignedInt();
	filterFlag = iffStream->getUnsignedInt();
	uint32 var3 = iffStream->getUnsignedInt();

	String var4;
	iffStream->getString(var4);

	iffStream->closeChunk('ADTA');

	int number = iffStream->getRemainingSubChunksNumber();

	for (int i = 0; i < number; ++i) {
		bool result = false;

		auto boundary = parseBoundary(iffStream);

		if (boundary == nullptr) {
			auto filter = parseFilter(iffStream);

			if (filter == nullptr) {
				auto rule = parseAffector(iffStream);

				if (rule == nullptr) {
					uint32 type = iffStream->getNextFormType();

					if (type != 'LAYR') {
						System::out << "Unknown Type:[" << hex << type << "] in Layer parsing detected!!!\n";
						iffStream->skipChunks();
					} else {
						Layer* layer = new Layer(this);
						layer->readObject(iffStream);
						children.add(layer);
					}
				} else {
					AffectorProceduralRule* affector = dynamic_cast<AffectorProceduralRule*>(rule);

					if (affector != nullptr) {
						affectors.add(affector);

						/*if (affector->isEnabled()) {

						  if (affector->isHeightTypeAffector())
						  heightAffectors.add(affector);
						  else if (affector->is)
						  }*/
					}
				}

			} else {
				filters.add(filter);
			}
		} else {
			boundaries.add(boundary);
		}
	}
}

IffTemplateVariable* Layer::parseAffector(IffStream* iffStream) {
	IffTemplateVariable* res = nullptr;
	uint32 type = iffStream->getNextFormType();

	switch (type) {
	case ('ACBM'):
		iffStream->skipChunks();
		break;
	case ('ACCN'): {
		res = new AffectorColorConstant();
		break;
	}
	case ('ACRF'): {
		res = new AffectorColorRampFractal();
		break;
	}
	case ('ACRH'): {
		res = new AffectorColorRampHeight();
		break;
	}
	case ('AENV'):  {
		res = new AffectorEnvironment();
		break;
	}
	case ('AEXC'): {
		res = new AffectorExclude();
		break;
	}
	case ('AFBM'):
		iffStream->skipChunks();
		break;
	case ('AFDN'): {
		res = new AffectorRadialConstant();
		break;
	}
	case ('AFCN'): {
		res = new AffectorFCN();
		break;
	}
	case ('AFDF'): {
		res = new AffectorRadialFarConstant();
		break;
	}
	case ('AFSC'): {
		res = new AffectorNoncollideFloraConstant();
		break;
	}
	case ('AFSN'): {
		res = new AffectorFloraNonCollidableConstant();
		break;
	}
	case ('AHBM'):
		iffStream->skipChunks();
		break;
	case ('AHSM'):
		iffStream->skipChunks();
		break;
	case ('AHCN'): {
		res = new AffectorHeightConstant();
		break;
	}
	case ('AHFR'): {
		res = new AffectorHeightFractal();
		break;
	}
	case ('AHTR'): {
		res = new AffectorHeightTerrace();
		break;
	}
	case ('APAS'): {
		res = new AffectorPassable();
		break;
	}
	case ('ARCN'): { // same as afdn
		res = new AffectorRCN();
		break;
	}
	case ('ASBM'):
		iffStream->skipChunks();
		break;
	case ('ARIV'): {
		res = new AffectorRiver();
		break;
	}
	case ('AROA'): {
		res = new AffectorRoad();
		break;
	}
	case ('ASCN'): {
		res = new AffectorShaderConstant();
		break;
	}
	case ('ASRP'): {
		res = new AffectorShaderReplace();
		break;
	}
	default:
		res = nullptr;
		break;
	}

	if (res != nullptr)
		res->readObject(iffStream);

	return res;
}

Boundary* Layer::parseBoundary(IffStream* iffStream) {
	Boundary* res = nullptr;
	uint32 type = iffStream->getNextFormType();

	switch (type) {
	case ('BPOL'): {
		res = new BoundaryPolygon();
		break;
	}
	case ('BREC'): {
		res = new BoundaryRectangle();
		break;
	}
	case ('BALL'): // empty in client
		iffStream->skipChunks();
		break;
	case ('BCIR'): {
		res = new BoundaryCircle();
		break;
	}
	case ('BPLN'): {
		res = new BoundaryPolyline();
		break;
	}
	case ('BSPL'): // empty in client
		iffStream->skipChunks();
		break;
	default:
		res = nullptr;
		break;
	}

	if (res != nullptr)
		res->readObject(iffStream);

	return res;
}

FilterProceduralRule* Layer::parseFilter(IffStream* iffStream) {
	FilterProceduralRule* res = nullptr;
	uint32 type = iffStream->getNextFormType();

	switch (type) {
	case ('FHGT'): {
		res = new FilterHeight();
		break;
	}
	case ('FBIT'): {
		res = new FilterBitmap();
		break;
	}
	case ('FDIR'): {
		res = new FilterDirection();
		break;
	}
	case ('FFRA'): {
		res = new FilterFractal();
		break;
	}
	case ('FSHD'): {
		res = new FilterShader();
		break;
	}
	case ('FSLP'): {
		res = new FilterSlope();
		break;
	}
	default:
		res = nullptr;
		break;
	}

	if (res != nullptr)
		res->readObject(iffStream);

	return res;
}
