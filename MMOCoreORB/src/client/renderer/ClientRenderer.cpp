/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ClientRenderer.h"

#include "zone/Zone.h"
#include "zone/managers/object/ObjectManager.h"

#include "ClientCore.h"

#include "login/LoginSession.h"
#include "zone/templates/SharedObjectTemplate.h"
#include "zone/managers/templates/TemplateManager.h"
#include "zone/managers/templates/DataArchiveStore.h"
#include "zone/templates/snapshot/WorldSnapshotIff.h"
#include "zone/templates/tangible/SharedBuildingObjectTemplate.h"
#include "zone/templates/appearance/MeshAppearanceTemplate.h"
#include "zone/templates/appearance/DetailAppearanceTemplate.h"
#include "conf/ConfigManager.h"

#include "zone/templates/appearance/PortalLayout.h"
#include "zone/templates/appearance/FloorMesh.h"
#include "zone/templates/appearance/PathGraph.h"
#include "tre3/TreeDirectory.h"
#include "tre3/TreeArchive.h"
#include "pterrain/ptat/TerrainGenerator.h"
#include "pterrain/ptat/ProceduralTerrainAppearance.h"
#include "pterrain/ptat/layer/boundaries/BoundaryRectangle.h"
#include "pterrain/ptat/layer/boundaries/BoundaryPolygon.h"
#include <osgGA/TerrainManipulator>

#include <osgTerrain/Terrain>
#include <osgTerrain/TerrainTile>
#include <osgTerrain/GeometryTechnique>
#include <osgTerrain/DisplacementMappingTechnique>
#include <osgTerrain/Layer>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osgGA/StateSetManipulator>

ClientRenderer::ClientRenderer(ClientCore *core, Zone* zone) : Core("log/renderer.log"), Logger("ClientRenderer") {
	setInfoLogLevel();
	floorMeshGroup = NULL;
	terrainAppearance = NULL;
}

void ClientRenderer::initialize() {
	info("starting up renderer..");
}

void ClientRenderer::loadSnapshotNode(WorldSnapshotNode *node, WorldSnapshotIff *wsiff, HashTable<uint32, String> &crcTable) {
	
	uint64 objectID = node->getObjectID();
	String templateName = wsiff->getObjectTemplateName(node->getNameID());
	
	info(templateName + " updateRange: " + String::valueOf(node->getGameObjectType()), true);
	if(templateName.contains("arch")) {
		objectID = 12;
	}
//	if(node->getUnknown2()) {
//		SharedObjectTemplate *shot = manager->getTemplate(node->getUnknown2());
//		info("PortalLayout ", true);
//	}
//	if (ConfigManager::instance()->isProgressMonitorActivated())
//		printf("\r\tLoading snapshot objects: [%d] / [?]\t", totalObjects);
	
	String serverTemplate = templateName.replaceFirst("shared_", "");
	Vector3 position = node->getPosition();
	
	SharedObjectTemplate *shot = manager->getTemplate(serverTemplate.hashCode());
	
	//osg::MatrixTransform * rotation  = new osg::MatrixTransform( );
	osg::MatrixTransform * transform  = new osg::MatrixTransform( );
	
	Quaternion quat = node->getDirection();
	
	// value_type x, value_type y, value_type z, value_type w )
	
	osg::Quat nodeQuat(quat.getX(), quat.getY(), quat.getZ(), quat.getW() );
	
	//rotation->setMatrix(  );
	//
	transform->setMatrix(osg::Matrix::scale(1, -1, 1) *  osg::Matrix::rotate(nodeQuat) * osg::Matrix::translate( osg::Vec3f(position.getX(), position.getZ(), position.getY()) ));
	
	//rotation->addChild(transform);
	
	root->addChild(transform);
	
	if ( shot == NULL ) {
		error("Null SharedObjectTemplate " + serverTemplate);
	}
	
	if(serverTemplate.contains("palace"))
		position = position;
	
	if(node->getUnknown2() != 0) {
		String name = TemplateManager::instance()->getTemplateFile(node->getUnknown2());
		PortalLayout *layout = TemplateManager::instance()->getPortalLayout(name);
		if(layout != NULL) {
			transform->addChild(layout->draw());
		}
	} else if (shot != NULL) {
		PortalLayout *layout = shot->getPortalLayout();
		AppearanceTemplate *tmpl = shot->getAppearanceTemplate();
		if(layout) {
			transform->addChild(layout->draw());
		} else if(tmpl) {
			transform->addChild(tmpl->draw());
		} else if (templateName.contains("cell") == false && templateName.contains("soundobject") == false){
			info("Null apperance template for " + templateName, true);
		}
	} else {
		info("Null portal and appearance for: " + serverTemplate, true);
	}
 
	
	
//		PortalLayout *layout = shot->getPortalLayout();
//		if(layout != NULL) {
//			transform->addChild(layout->draw());
//		}

	

	//Load child nodes
	for (int i = 0; i < node->getNodeCount(); ++i) {
		WorldSnapshotNode* childNode = node->getNode(i);
		
		if (childNode == NULL) {
			info("Null childNode", true);
			continue;
		}
		
		loadSnapshotNode(childNode, wsiff, crcTable);
	}

	
}
void ClientRenderer::run() {
	
	root = new osg::Group();
	
	osg::Light* pLight = new osg::Light();
	pLight->setLightNum (0);
	pLight->setAmbient (osg::Vec4d (0.2, 0.2, 0.2, 1.0));
	pLight->setDiffuse (osg::Vec4d (0.5, 0.5, 0.5, 1.0));
	pLight->setSpecular (osg::Vec4d (0.0, 0.0, 0.0, 1.0));
	osg::LightSource* pLightsource = new osg::LightSource();
	pLightsource->setLight (pLight);
	pLightsource->setStateSetModes (*root->getOrCreateStateSet(), osg::StateAttribute::ON);
	root->addChild (pLightsource);
	
	
	ConfigManager::instance()->loadConfigData();
	DataArchiveStore::instance()->loadTres(ConfigManager::instance()->getTrePath(), ConfigManager::instance()->getTreFiles());
	
	root->addChild(createTerrain());
	
	HashTable<uint32, String> crcTable;
	
	manager = TemplateManager::instance();//new TemplateManager();
	
	manager->loadLuaTemplates();
	
	TreeDirectory *directory = DataArchiveStore::instance()->getTreeArchive()->getTreeDirectory("appearance");
	for(int i=0; i<directory->size(); i++) {
		Reference<TreeFileRecord*> record = directory->get(i);
		String recordName = "appearance/" + record->getRecordName();
		if(recordName.contains(".pob") == false)
			continue;
		IffStream *stream = DataArchiveStore::instance()->openIffFile(recordName);
		if(stream == NULL)
			continue;
		
		uint32 crc = PortalLayout::loadCRC(stream);
		TemplateManager::instance()->addTemplate(crc, recordName);
	}

	
	IffStream *snapshotStream = DataArchiveStore::instance()->openIffFile("snapshot/naboo.ws");
	
	WorldSnapshotIff snapshot;
	snapshot.readObject(snapshotStream);
	
	for (int i = 0; i < snapshot.getNodeCount(); ++i) {
		WorldSnapshotNode* node = snapshot.getNode(i);
		loadSnapshotNode(snapshot.getNode(i), &snapshot, crcTable);
	}
	
	osgViewer::Viewer viewer;
	osg::DisplaySettings::instance()->setNumMultiSamples( 8 );

	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	root->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::ON );
	//root->getOrCreateStateSet()->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
	viewer.setSceneData(root);
	
	viewer.run();
}

osg::ref_ptr<osg::Node> ClientRenderer::createTerrain() {
	//    return NULL;
	
	
	
	IffStream* iffStream = DataArchiveStore::instance()->openIffFile( "terrain/naboo.trn" );
	
	if (terrainAppearance != NULL)
		delete terrainAppearance;
	int minTerrainX = -8000;
	int minTerrainY = -8000;
	int maxTerrainX = 8000;
	int maxTerrainY = 8000;
	
	terrainAppearance = new ProceduralTerrainAppearance(NULL);
	
	terrainAppearance->load(iffStream);
	
	delete iffStream;
	
	/* float centerX = -3011;
	 float centerY = 2218;*/
	
	String centerString;
	StringBuffer stream;
	stream << "minX:" << minTerrainX << " maxX:" << maxTerrainX << " minY:" << minTerrainY << " maxY:" << maxTerrainY;
	
	info(stream.toString(), true);
	
	float centerX = minTerrainX + ((maxTerrainX - minTerrainX) / 2);
	float centerY = minTerrainY + ((maxTerrainY - minTerrainY) / 2);
	
	float terrainSize = 512;//appearance.getSize();
	
	float originX = centerX + (-terrainSize / 2);//-2797;
	float originY = centerY + (-terrainSize / 2);// 2218; //-terrainSize / 2;
	
	float chunkSize = 8;
	float distanceBetweenHeights = 2;
	
	unsigned int numRows = static_cast<unsigned int>( terrainSize / chunkSize );
	unsigned int numColumns = numRows;
	
	float oneChunkRows = chunkSize / distanceBetweenHeights + 1 ;
	float oneChunkColumns = chunkSize / distanceBetweenHeights + 1;
	
	
	osg::ref_ptr<osgTerrain::Terrain> trnMesh( new osgTerrain::Terrain) ;
	trnMesh->setSampleRatio( 1.0 / distanceBetweenHeights );
	
	//osg::ref_ptr<osgTerrain::ImageLayer> lastImageLayer;
	
	Vector<TerrainChunk*>* chunks = terrainAppearance->generateTerrainChunks(originX, originY, terrainSize, distanceBetweenHeights, oneChunkRows, oneChunkColumns, chunkSize);
	
	info("generated chunks:" + String::valueOf(chunks->size()), true);
	
	// int rowCount = 0, columnCount = 0;
	int currentImageLayer = 0;
	
	for (int c = 0; c < chunks->size(); ++c) {
		
		TerrainChunk* chunk = chunks->get(c);
		
		osg::ref_ptr<osgTerrain::TerrainTile> terrainTile = new osgTerrain::TerrainTile;
		
		osg::HeightField* tileGrid = new osg::HeightField;
		tileGrid->allocate(oneChunkRows, oneChunkColumns);
		tileGrid->setName("HeightField grid");
		
		tileGrid->setXInterval(distanceBetweenHeights);
		tileGrid->setYInterval(distanceBetweenHeights);
		
		Vector<ShaderFamily*> insertedFamilies;
		//insertedFamilies.setNoDuplicateInsertPlan();
		
		//float* heightData = chunk->getHeightData();
		
		currentImageLayer = 0;
		
		osg::ref_ptr<osg::Image> colorMap = new osg::Image();
		
		colorMap->setImage(oneChunkRows, oneChunkColumns, 1, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)chunk->takeColorData(), osg::Image::USE_MALLOC_FREE);
		
		osg::ref_ptr<osgTerrain::ImageLayer> imageLayer = new osgTerrain::ImageLayer(colorMap);
		
		terrainTile->setColorLayer(currentImageLayer++, imageLayer);
		
		for(int i = 0; i < oneChunkRows; ++i) {
			for (int j = 0; j < oneChunkColumns; ++j) {
				float height = chunk->getHeight(i, j);
				tileGrid->setHeight(i, j, height);
				
				int shaderId = chunk->getShader(j, i);
				
				ShaderFamily* fam = terrainAppearance->getShaderFamily(shaderId);
				
				if (fam != NULL) {
					if (!insertedFamilies.contains(fam)) {
						
						insertedFamilies.add(fam);
						
						String shaderFileName = "shader/" + String(fam->getFamilyName().toCharArray()) + ".sht";
						shaderFileName = shaderFileName.toLowerCase();
						
						Vector<ShaderVar*>* shaderVars = fam->getShaderVars();
						
						//int size = shaderVars->size();
						
						float totalWeight = 0;
						
						for (int k = 0; k < shaderVars->size(); ++k) {
							totalWeight += shaderVars->get(k)->weight;
						}
						
						
						int random = System::random((int)(totalWeight * 1000));
						
						float currentWeight = 0;
						for (int k = 0; k < shaderVars->size(); ++k) {
							currentWeight += shaderVars->get(k)->weight;
							
							if (random <= (currentWeight * 1000)) {
								shaderFileName = shaderVars->get(k)->name.toCharArray();
								shaderFileName = "shader/" + shaderFileName + ".sht";
								
								break;
							}
						}
						
						/*    if (rect.containsPoint(-4777, 4066)) {
						 MainWindow::instance->outputToConsole(shaderFileName);
						 }*/
						
						// MainWindow::instance->outputToConsole(shaderFileName);
						
						osg::ref_ptr<osg::StateSet> shader = NULL;//repo->loadShader(shaderFileName.toStdString());
						
						if (shader == NULL) {
							//MainWindow::instance->outputToConsole("could not open shader:" + shaderFileName);
						}
						
						sys::byte red = 255, green = 255, blue = 255;
						
						if (fam != NULL) {
							fam->getColor(red, green, blue);
							
							//  MainWindow::instance->outputToConsole("red " + QString::number(red) + " green " + QString::number(green) + " blue " + QString::number(blue));
						}
						
						osg::StateAttribute* texture = NULL;// (shader->getTextureAttribute(0, osg::StateAttribute::TEXTURE));
						
						if (texture == NULL) {
							//MainWindow::instance->outputToConsole("texture NULL");
						} else {
							
							osg::Texture2D* tex = dynamic_cast<osg::Texture2D*>(texture);
							
							//tex->get
							osg::ref_ptr<osgTerrain::ImageLayer> imageLayer = new osgTerrain::ImageLayer;//(tex->getImage());
							imageLayer->setImage(tex->getImage());
							imageLayer->setMagFilter(osg::Texture::LINEAR);
							imageLayer->setMinFilter(osg::Texture::LINEAR_MIPMAP_LINEAR);
							//imageLayer->setW
							terrainTile->setColorLayer(currentImageLayer++, imageLayer);
							
							
						}
						
						
						//   int random = System::random((int)(totalWeight * 1000));
						
						
					}
				}/* else
				  MainWindow::instance->outputToConsole("shader fam null for id: " + QString::number(shaderId));*/
			}
		}
		
		osg::ref_ptr<osgTerrain::Locator> tileLocator = new osgTerrain::Locator;
		tileLocator->setCoordinateSystemType( osgTerrain::Locator::PROJECTED );
		
		
		tileLocator->setTransformAsExtents( chunk->getOriginX(), chunk->getOriginY() , chunk->getOriginX() + chunkSize, chunk->getOriginY() + chunkSize);
		
		
		
		osg::ref_ptr<osgTerrain::HeightFieldLayer> heightFieldLayerTile = new osgTerrain::HeightFieldLayer( tileGrid );
		heightFieldLayerTile->setLocator( tileLocator.get() );
		
		
		
		terrainTile->setElevationLayer( heightFieldLayerTile.get() );
		terrainTile->setName("haha");
		//   terrainTile->setBlendingPolicy(osgTerrain::TerrainTile::ENABLE_BLENDING_WHEN_ALPHA_PRESENT);
		// terrainTile->setBlendingPolicy(osgTerrain::TerrainTile::ENABLE_BLENDING);
		//   terrainTile->setRequiresNormals(true);
		
		
		//   terrainTile->setRequiresNormals(true);
		
		//terrainTile->getOrCreateStateSet()->setMode(GL_LIGHTING, false);
		
		trnMesh->addChild(terrainTile);
		
		delete chunk;
		
		//  for (int i = 0; i )
		
	}
	
	delete chunks;
	
	
	Vector<Boundary*>* waterBoundaries =  terrainAppearance->getWaterBoundaries();
	
	BoundaryRectangle* rect = NULL;
	BoundaryPolygon* poly = NULL;
	
	osg::Geode* waterGeode = new osg::Geode;
	
	/*
	 for (int i = 0; i < waterBoundaries->size(); ++i) {
	 Boundary* boundary = waterBoundaries->get(i);
	 
	 rect = dynamic_cast<BoundaryRectangle*>(boundary);
	 
	 QString shaderFileName;
	 
	 if (rect != NULL) {
	 //rect->get
	 shaderFileName = rect->getWaterShader().toCharArray();
	 
	 float height = rect->getLocalWaterTableHeight();
	 
	 osg::ref_ptr<osg::StateSet> shader = repo->loadShader("shader/" + shaderFileName.toStdString() + ".sht");
	 
	 if (shader == NULL)
	 MainWindow::instance->outputToConsole("could not open shader " + shaderFileName);
	 
	 osg::Geometry* geometry( new osg::Geometry() );
	 osg::Vec3Array* vertices( new osg::Vec3Array() );
	 
	 vertices->push_back(osg::Vec3(rect->getX0(), rect->getY0(), height));
	 vertices->push_back(osg::Vec3(rect->getX0(), rect->getY1(), height));
	 vertices->push_back(osg::Vec3(rect->getX1(), rect->getY0(), height));
	 vertices->push_back(osg::Vec3(rect->getX1(), rect->getY1(), height));
	 
	 geometry->setVertexArray(vertices);
	 
	 
	 geometry->addPrimitiveSet(
	 new osg::DrawArrays(
	 osg::PrimitiveSet::TRIANGLE_STRIP,
	 0, vertices->size())
	 );
	 
	 if (shader != NULL) {
	 geometry->setStateSet(shader);
	 //geometry->set
	 } else {
	 MainWindow::instance->outputToConsole("could not open global water shader");
	 }
	 
	 
	 waterGeode->addDrawable( geometry );
	 
	 } else if ((poly = dynamic_cast<BoundaryPolygon*>(boundary)) != NULL){
	 shaderFileName = poly->getWaterShader().toCharArray();
	 
	 //MainWindow::instance->outputToConsole("poly water table");
	 
	 shaderFileName = poly->getWaterShader().toCharArray();
	 
	 float height = poly->getLocalWaterTableHeight();
	 
	 osg::ref_ptr<osg::StateSet> shader = repo->loadShader("shader/" + shaderFileName.toStdString() + ".sht");
	 
	 if (shader == NULL)
	 MainWindow::instance->outputToConsole("could not open shader " + shaderFileName);
	 
	 osg::Geometry* geometry( new osg::Geometry() );
	 osg::Vec3Array* vertices( new osg::Vec3Array() );
	 
	 Vector<Point2D*>* polyVertices = poly->getVertices();
	 
	 for (int i = 0; i < polyVertices->size(); ++i) {
	 Point2D* point = polyVertices->get(i);
	 
	 vertices->push_back(osg::Vec3(point->getX(), point->getY(), height));
	 }
	 
	 
	 geometry->setVertexArray(vertices);
	 
	 
	 geometry->addPrimitiveSet(
	 new osg::DrawArrays(
	 osg::PrimitiveSet::POLYGON,
	 0, vertices->size())
	 );
	 
	 if (shader != NULL) {
	 geometry->setStateSet(shader);
	 //geometry->set
	 } else {
	 MainWindow::instance->outputToConsole("could not open water shader");
	 }
	 
	 
	 waterGeode->addDrawable( geometry );
	 }
	 
	 }
	 */
	
	// GLOBAL WATER
	
	if (terrainAppearance->hasGlobalWaterTableOption()) {
		//MainWindow::instance->outputToConsole("creating global water table");
		osg::Geometry* geometry( new osg::Geometry() );
		osg::Vec3Array* vertices( new osg::Vec3Array() );
		
		
		
		float terrainHalfSize = terrainSize / 2;
		float height = terrainAppearance->getGlobalWaterTableHeight();
		
		vertices->push_back(osg::Vec3(-terrainHalfSize, -terrainHalfSize, height));
		vertices->push_back(osg::Vec3(-terrainHalfSize, terrainHalfSize, height));
		vertices->push_back(osg::Vec3(terrainHalfSize, -terrainHalfSize, height));
		vertices->push_back(osg::Vec3(terrainHalfSize, terrainHalfSize, height));
		
		//        osg::Vec4Array* colors( new osg::Vec4Array() );
		//       colors->push_back( osg::Vec4( 0.0f, 0.0f, 1.0f, 0.3f ) );
		
//		QString shaderFileName = terrainAppearance->getGlobalWaterShader().toCharArray();
//		
//		osg::ref_ptr<osg::StateSet> shader = repo->loadShader("shader/" + shaderFileName.toStdString() + ".sht");
//		
//		if (shader != NULL) {
//			geometry->setStateSet(shader);
//			//geometry->set
//		} else {
//			//MainWindow::instance->outputToConsole("could not open global water shader");
//		}
		
		//  geometry->setColorArray( colors );
		//  geometry->setColorBinding( osg::Geometry::BIND_OVERALL );
		geometry->setVertexArray(vertices);
		geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP,0, vertices->size()));
		//geometry->getOrCreateStateSet()->setMode();
		
		
		
		waterGeode->addDrawable( geometry );
	}
	
	waterGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, false);
	
	//osg::Node* node = new osg::Node;
	//node->addCh
	
	trnMesh->setName("TerrainMesh");
	
	osg::MatrixTransform* master = new osg::MatrixTransform;
	master->addChild(trnMesh);
	master->addChild(waterGeode);
	master->setName("master terrain transform");
	
//	rootNode->addChild(createHUD(updateText, objectText));
//	rootNode->addChild(pointerTransform);
	// rootNode->addChild(waterGeode);
	
	return master;
}


osg::ref_ptr< osg::StateSet > ClientRenderer::loadShader( const String shaderFilename )
{
	return NULL;
//	if( shaderFilename.isEmpty() )
//	{
//		std::cout << "loadShader called with null filename!" << std::endl;
//		return NULL;
//	}
//	
//	std::map< std::string, osg::ref_ptr< osg::StateSet > >::iterator
////	currentState = stateMap.find( shaderFilename );
//	
////	if( stateMap.end() != currentState )
////	{
////		// Shader has already been loaded.
////		std::cout << "Shader already loaded: " << shaderFilename << std::endl;
////		return currentState->second;
////	}
//	
//	// Otherwise we need to read the shader from the archive.
////	std::cout << "Reading shader from archive: " << shaderFilename << std::endl;
//	
//	// Read file data into a stream
//	
//	istream shaderFile( archive.getFileStream( shaderFilename ) );
//	
//	if (shaderFile == NULL)
//		return NULL;
//	
//	// Figure out what type this generic .iff actually is.
//	std::string type =  ml::base::getType( *shaderFile );
//	
//	if( "SSHT" != type
//	   && "CSHD" != type
//	   && "SWTS" != type
//	   )
//	{
////		std::cout << "Not a shader. File is type: " << type << std::endl;
//		return NULL;
//	}
//	
//	osg::ref_ptr< osg::StateSet > stateSet( new osg::StateSet );
//	osg::ref_ptr< osg::Material > mat( new osg::Material );
//	mat->setName( shaderFilename );
//	stateSet->setAttributeAndModes( mat.get() );
//	
//	if( NULL != shaderFile.get() )
//	{
//		float ar, ag, ab, aa;
//		float dr, dg, db, da;
//		float sr, sg, sb, sa;
//		float er, eg, eb, ea;
//		float shiny;
//		
//		std::string normalTextureName;
//		
//		ml::swts animatedShader;
//		ml::sht shader;
//		ml::cshd cshader;
//		
//		//stateSet->setMode(GL_BLEND,osg::StateAttribute::ON);
//		
//		if( animatedShader.isRightType( *shaderFile ) )
//		{
//			animatedShader.readSWTS( *shaderFile );
//			
//			std::string texName;
//			std::string texTag;
//#if 0
//			delete shaderFile;
//			std::string newShaderName = animatedShader.getShaderFilename();
//			loadShader( newShaderName, newShaderName );
//			csRef<iTextureWrapper> texWrapper;
//			unsigned int numTextures = animatedShader.getNumTextures();
//			for( unsigned int i = 0; i < numTextures; ++i )
//			{
//				animatedShader.getTextureInfo( i, texName, texTag );
//				texWrapper = loadOrGetTexture( texName );
//			}
//			mat =
//			engine->GetMaterialList()->FindByName( newShaderName.c_str() );
//#endif
//			
//			animatedShader.getTextureInfo( 0, texName, texTag );
//			
//			std::string diffuseTextureName = texName;
//		}
//		else if( shader.isRightType( *shaderFile ) )
//		{
//			shader.readSHT( *shaderFile );
//			shader.getAmbient( aa, ab, ag, ar );
//	  mat->setAmbient( osg::Material::FRONT, osg::Vec4( ar, ag, ab, aa ) );
//			shader.getDiffuse( da, db, dg, dr );
//	  mat->setDiffuse( osg::Material::FRONT, osg::Vec4( dr, dg, db, da ) );
//			shader.getSpecular( sa, sb, sg, sr );
//	  mat->setSpecular( osg::Material::FRONT, osg::Vec4( sr, sg, sb, sa ) );
//			shader.getEmissive( ea, eb, eg, er );
//	  mat->setEmission( osg::Material::FRONT, osg::Vec4( er, eg, eb, ea ) );
//			shader.getShininess( shiny );
//	  mat->setShininess( osg::Material::FRONT, shiny );
//			
//			std::string diffuseTextureName = shader.getMainTextureName();
//	  unsigned int diffuseTextureUnit = shader.getMainTextureUnit();
//			
//	  osg::ref_ptr< osg::Texture2D > diffuseTexture =
//			loadTextureFile( diffuseTextureName );
//			
//	  if( NULL != diffuseTexture )
//	  {
//		  diffuseTexture->setWrap( osg::Texture::WRAP_S,
//								  osg::Texture::REPEAT );
//		  diffuseTexture->setWrap( osg::Texture::WRAP_T,
//								  osg::Texture::REPEAT );
//		  stateSet->setTextureAttributeAndModes( diffuseTextureUnit,
//												diffuseTexture.get(),
//												osg::StateAttribute::ON );
//	  }
//			
//			normalTextureName = shader.getNormalTextureName();
//		}
//		else if( cshader.isRightType( *shaderFile ) )
//		{
//			cshader.readCSHD( *shaderFile );
//			cshader.getAmbient( aa, ab, ag, ar );
//	  mat->setAmbient( osg::Material::FRONT, osg::Vec4( ar, ag, ab, aa ) );
//			cshader.getDiffuse( da, db, dg, dr );
//	  mat->setDiffuse( osg::Material::FRONT, osg::Vec4( dr, dg, db, da ) );
//			cshader.getSpecular( sa, sb, sg, sr );
//	  mat->setSpecular( osg::Material::FRONT, osg::Vec4( sr, sg, sb, sa ) );
//			cshader.getEmissive( ea, eb, eg, er );
//	  mat->setEmission( osg::Material::FRONT, osg::Vec4( er, eg, eb, ea ) );
//			cshader.getShininess( shiny );
//	  mat->setShininess( osg::Material::FRONT, shiny );
//			
//			std::string diffuseTextureName = cshader.getMainTextureName();
//	  unsigned int diffuseTextureUnit = shader.getMainTextureUnit();
//			normalTextureName = shader.getNormalTextureName();
//			
//	  osg::ref_ptr< osg::Texture2D > diffuseTexture =
//			loadTextureFile( diffuseTextureName );
//			
////	  std::cout << __FILE__ << ": " << __LINE__ << ": " << diffuseTextureUnit<< std::endl;
//			
//	  if( NULL != diffuseTexture )
//	  {
//		  diffuseTexture->setWrap( osg::Texture::WRAP_S,
//								  osg::Texture::REPEAT );
//		  diffuseTexture->setWrap( osg::Texture::WRAP_T,
//								  osg::Texture::REPEAT );
//		  stateSet->setTextureAttributeAndModes( diffuseTextureUnit,
//												diffuseTexture.get(),
//												osg::StateAttribute::ON );
//	  }
////	  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//			
//		}
//		else
//		{
////			std::cout << "File not .SHT or .CSHD" << std::endl;
//		}
//		
////		std::cout << "Creating material: " << shaderFilename
//		<< std::endl;
//		
//		
//		if( NULL == mat )
//		{
////			std::cout << "Material creation failed" << std::endl;
//		}
//		else
//		{
////			std::cout << "Material created: "
//			<< mat->getName()
//			<< std::endl;
//		}
//		
//#if 0
//		if( !commonShader->getNormalTextureName().empty() )
//		{
////			std::cout << "Creating normal shader variable" << std::endl;
//			csRef<csShaderVariable> normalSV =
//			mat->GetMaterial()->GetVariableAdd(strings->Request("tex normal"));
////			std::cout << "Loading/Getting normal texture: "
//			<< normalTextureName
//			<< std::endl;
//			csRef<iTextureWrapper> texNorm =
//			loadOrGetTexture( normalTextureName );
//			texNorm->SetTextureClass ("normalmap");
//			normalSV->SetValue( texNorm );
//		}
//#endif
//		
//	} //if NULL != shaderFile
//	
//	//stateMap[ shaderFilename ] = stateSet;
//	
//	return stateSet;
}
