#include "NavMeshJob.h"
#include "NavMeshManager.h"
#include "pathfinding/RecastNavMeshBuilder.h"
#include "terrain/manager/TerrainManager.h"
#include "terrain/ProceduralTerrainAppearance.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "templates/building/InteriorLayoutTemplate.h"


void NavMeshJob::addArea(const AABB& area) {
    float size = area.extents().getX() * area.extents().getZ();

    Locker locker(getMutex());

    if(areas.size() > 0) {
        for (int i = areas.size() - 1; i >= 0; i--) {
            const AABB& existing = areas.get(i);
            float existingSize = existing.extents().getX() * existing.extents().getZ();

            if (existingSize > size) {
                // check to see if an existing AABB completely encompasses the one we are adding
                if(NavMeshManager::AABBEncompasessAABB(existing, area))
                    return;
            } else if(NavMeshManager::AABBEncompasessAABB(area, existing)) {
                // Check to see if the AABB we are adding encompasses one already in the list
                areas.remove(i);
                continue;
            }
        }
    }

    areas.add(area);
}


bool NavMeshJob::startJob() {
    ManagedReference<NavArea*> area = getNavArea();

    if (area == NULL) {
        return false;
    }

    Reference<Zone*> zone = area->getZone();

    if (zone == NULL) {
        return false;
    }

    Locker areaLocker(getMutex());
    //copy and clear this vector otherwise our scene data may not be correct if a zone was added during the build process
    Vector <AABB> dirtyZones = Vector<AABB>(getAreas());
    getAreas().removeAll();
    areaLocker.release();

    const AABB& bBox = area->getBoundingBox();

    float range = bBox.extents()[bBox.longestAxis()];
    const Vector3& center = bBox.center();

    String name = area->getMeshName();

    area->info("Starting building navmesh for area: " + name + " on planet: " + zone->getZoneName() + " at: " + area->getPosition().toString(), true);

    SortedVector <ManagedReference<QuadTreeEntry *>> closeObjects;
    zone->getInRangeSolidObjects(center.getX(), center.getZ(), range, &closeObjects, true);

    Vector <Reference<MeshData *>> meshData;

    for (int i = 0; i < closeObjects.size(); i++) {
        SceneObject *sceno = closeObjects.get(i).castTo<SceneObject *>();
        if (sceno) {
            // TODO: Figure out why we need this
            // Example: v 1393.67 3.09307e+06 -3217
            // mos entha pristine wall
            const float height = sceno->getPosition().getZ();
            if (height > 10000 || height < -10000)
                continue;

            static const Matrix4 identity;

            meshData.addAll(sceno->getTransformedMeshData(&identity));
        }
    }

    Reference<RecastNavMeshBuilder*> builder = NULL;

    const AtomicBoolean* running = getJobStatus();
    builder = new RecastNavMeshBuilder(zone, name, running);

    builder->setRecastConfig(getRecastConfig());

    float poleDist = getRecastConfig().distanceBetweenPoles;

    if (poleDist < 1.0f) {
        poleDist = zone->getPlanetManager()->getTerrainManager()->getProceduralTerrainAppearance()->getDistanceBetweenPoles();
    }

    builder->initialize(meshData, bBox, poleDist);
    meshData.removeAll();

    // This will take a very long time to complete
    bool initialBuild = (!area->isNavMeshLoaded());
    if (initialBuild) {
#ifdef NAVMESH_DEBUG
        info("Rebuilding Base Mesh", true);
#endif
        builder->build();
    } else if (dirtyZones.size() > 0) {
#ifdef NAVMESH_DEBUG
        info("Rebuilding area", true);
#endif
        builder->rebuildAreas(dirtyZones, area);
    }

#ifdef NAVMESH_DEBUG
    info("NavArea->name: " + name);
#endif

    if (!running->get()) {
        return false;
    }

    Core::getTaskManager()->executeTask([area, name, builder, initialBuild, this] {
        if (NavMeshManager::instance()->isStopped())
            return false;

        Locker locker(area);
        RecastNavMesh* navmesh = area->getNavMesh();

        if (initialBuild) {
            navmesh->setName(name);
            navmesh->setDetourNavMeshHeader(builder->getNavMeshHeader());
        } else {
            dtNavMesh* oldMesh = navmesh->getNavMesh();

            if (oldMesh)
                dtFreeNavMesh(oldMesh);
        }

        navmesh->setDetourNavMesh(builder->getNavMesh());
        navmesh->setupDetourNavMeshHeader();
        area->_setUpdated(true);
        area->info("Done building and setting navmesh for area: " + name + " on planet: " + area->getZone()->getZoneName() + " at: " + area->getPosition().toString(), true);
        return true;
    }, "setNavMeshLambda");
    return true;
}

bool BuildingMeshJob::startJob() {
    PortalLayout* layout = templ->getPortalLayout();

    if (layout == NULL)
        return false;

    float maxExtent = 0.0f;

    Vector<Reference<MeshData*> > data;

//    if (layout->getCellTotalNumber() == 1)
//        return false;

    for (int i=1; i<layout->getCellTotalNumber()+1; i++) {
        FloorMesh* mesh = layout->getFloorMesh(i);
        if (mesh == NULL)
            continue;

        const AABB& box = mesh->getAABBTree()->getBoundingBox();

        Vector3 extents = box.extents();
        float x = fabs(extents.getX());
        float y = fabs(extents.getY());
        float z = fabs(extents.getZ());
        float max = Math::max(x, Math::max(y, z));
        if (max > maxExtent)
            maxExtent = max;

        data.addAll(mesh->getLocalMeshData());
    }

    String interiorLayout = templ->getInteriorLayoutFileName();
    InteriorLayoutTemplate *ilf = TemplateManager::instance()->getInteriorLayout(interiorLayout);
    static Logger logger;
    logger.info("ILF FileName: " + interiorLayout, true);
    if (ilf != NULL) {
        const auto& children = ilf->getChildren();
        for (const auto& child : children) {
            Matrix4 transform = child->getTransform();
            transform.swapLtoR();

            String obj = child->getTemplateFile();
            obj = obj.replaceFirst("shared_", "");
            SharedObjectTemplate *childTemplate = TemplateManager::instance()->getTemplate(obj.hashCode());
            if (childTemplate == NULL) {
                logger.info("No SHOT for : " + obj, true);
                continue;
            }
            AppearanceTemplate *appr = childTemplate->getAppearanceTemplate();
            if (appr != NULL) {
                data.addAll(appr->getTransformedMeshData(transform));
            } else {
                logger.info("No Appearance Template " + obj, true);
            }
        }
    } else {
        logger.info("No ILF File", true);
    }

    AABB box(Vector3(-maxExtent, -maxExtent, -maxExtent), Vector3(maxExtent, maxExtent, maxExtent));

    AtomicBoolean jobStatus(true);
    Reference<RecastNavMeshBuilder*> builder = new RecastNavMeshBuilder(NULL, getMeshName(), &jobStatus);

    builder->initialize(data, box, -1);
    builder->build();

    Locker locker(navmesh->getMutex());
    navmesh->setDetourNavMeshHeader(builder->getNavMeshHeader());
    navmesh->setDetourNavMesh(builder->getNavMesh());
    navmesh->setupDetourNavMeshHeader();
    navmesh->saveToFile();

    Core::getTaskManager()->executeTask([=] {
        if (NavMeshManager::instance()->isStopped())
            return;


    }, "setNavMeshLambda");

    return true;
}
