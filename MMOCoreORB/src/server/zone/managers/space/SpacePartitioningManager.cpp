
#include "SpacePartitioningManager.h"
#include <algorithm>


namespace server {
namespace zone {
namespace managers {
namespace space {

bool SpacePartitioningManager::Location::parseFromBinaryStream(ObjectInputStream* stream)
{
    x = stream->readShort();
    y = stream->readShort();
    z = stream->readShort();
    return true;
}

bool SpacePartitioningManager::Location::toBinaryStream(ObjectOutputStream* stream)
{
    stream->writeShort(x);
    stream->writeShort(y);
    stream->writeShort(z);
    return true;
}

bool SpacePartitioningManager::Location::operator==(const Location& rhs)
{
    return x == rhs.x && y == rhs.y && z == rhs.z;
}

bool SpacePartitioningManager::Cell::parseFromBinaryStream(ObjectInputStream* stream) 
{
    observers.parseFromBinaryStream(stream);
    observables.parseFromBinaryStream(stream);
	return true;
}

bool SpacePartitioningManager::Cell::toBinaryStream(ObjectOutputStream* stream) 
{
    observers.toBinaryStream(stream);
    observables.toBinaryStream(stream);
	return true;
}

void SpacePartitioningManager::Cell::addObservable(Observable* observable)
{
    observables.put(observable->object, observable);
}

void SpacePartitioningManager::Cell::removeObservable(Observable* observable)
{
    observables.remove(observable->object);
}

void SpacePartitioningManager::Cell::addObserver(Observer* observer)
{
    observers.put(observer->object, observer);
}

void SpacePartitioningManager::Cell::removeObserver(Observer* observer)
{
    observers.remove(observer->object);
}

SpacePartitioningManager::Observer::Observer() {}

SpacePartitioningManager::Observer::Observer(const float& x, const float& y, const float& z, const float& radius, const unsigned int& radiusCellUnit, const Location& location, SceneObject* object)
    : x(x), y(y), z(z), radius(radius), radiusCellUnit(radiusCellUnit), location(location), object(object)
{

}

SpacePartitioningManager::Observer::Observer(const Observer& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    radius = rhs.radius;
    radiusCellUnit = rhs.radiusCellUnit;
    location = rhs.location;
    object = rhs.object;
}


SpacePartitioningManager::Observer::Observer(Observer&& o)
{
    x = o.x;
    y = o.y;
    z = o.z;
    radius = o.radius;
    radiusCellUnit = o.radiusCellUnit;
    location = o.location;
    object = o.object;
}

SpacePartitioningManager::Observer& SpacePartitioningManager::Observer::operator=(const Observer& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    radius = rhs.radius;
    radiusCellUnit = rhs.radiusCellUnit;
    location = rhs.location;
    object = rhs.object;
    return *this;
}

bool SpacePartitioningManager::Observer::parseFromBinaryStream(ObjectInputStream* stream) 
{
    x = stream->readFloat();
    y = stream->readFloat();
    z = stream->readFloat();
    radius = stream->readFloat();
    radiusCellUnit = stream->readInt();
    location = stream->readPrimitive<Location>();
    object = stream->readPrimitive<SceneObject*>();
	return true;
}

bool SpacePartitioningManager::Observer::toBinaryStream(ObjectOutputStream* stream) 
{
    stream->writeFloat(x);
    stream->writeFloat(y);
    stream->writeFloat(z);
    stream->writeFloat(radius);
    stream->writeInt(radiusCellUnit);
    stream->writePrimitive(location);
    stream->writePrimitive(object);
	return true;
}

SpacePartitioningManager::Observable::Observable() {}

SpacePartitioningManager::Observable::Observable(const float& x, const float& y, const float& z, const SpacePartitioningManager::Location& location, SceneObject* object)
    : x(x), y(y), z(z), location(location), object(object) {}

SpacePartitioningManager::Observable::Observable(Observable&& o)
{
    x = o.x;
    y = o.y;
    z = o.z;
    location = o.location;
    object = o.object;
}

SpacePartitioningManager::Observable::Observable(const Observable& o)
{
    x = o.x;
    y = o.y;
    z = o.z;
    location = o.location;
    object = o.object;
}

SpacePartitioningManager::Observable& SpacePartitioningManager::Observable::operator=(const Observable& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    location = rhs.location;
    object = rhs.object;
    return *this;
}

bool SpacePartitioningManager::Observable::parseFromBinaryStream(ObjectInputStream* stream) 
{
    x = stream->readFloat();
    y = stream->readFloat();
    z = stream->readFloat();
    location = stream->readPrimitive<Location>();
    object = stream->readPrimitive<SceneObject*>();
	return true;
}

bool SpacePartitioningManager::Observable::toBinaryStream(ObjectOutputStream* stream) 
{
    stream->writeFloat(x);
    stream->writeFloat(y);
    stream->writeFloat(z);
    stream->writePrimitive(location);
    stream->writePrimitive(object);
	return true;
}

SpacePartitioningManager::SpacePartitioningManager(const unsigned int& cellSize, const float& boundCoordinates)
: cellSize(cellSize), boundCoordinates(boundCoordinates), cells(pow((2 * boundCoordinates) / cellSize, 3), 100)
{
    bitshiftLength = log2(cellSize);
    cellLength = (unsigned int)(boundCoordinates * 2) >> bitshiftLength;

    //have to add all the cells one by one... need to look into bulk adding this if possible
    for(unsigned int i = 0; i < pow((2 * boundCoordinates) / cellSize, 3); ++i) {
        Cell cell;
        cells.add(cell);
    }
    
}

SpacePartitioningManager::~SpacePartitioningManager()
{
}

float SpacePartitioningManager::clampCoordinate(const float& v) 
{
    return std::max(-boundCoordinates, std::min(boundCoordinates, v));
}

unsigned int SpacePartitioningManager::clampLocationElement(const unsigned int& v)
{
    return std::max(0u, std::min(cellLength, v));
}

unsigned int SpacePartitioningManager::convertRadiusToCellUnit(const float& v)
{
    return (unsigned int)(v + cellSize - 1) / cellSize - 1;
}

SpacePartitioningManager::Location SpacePartitioningManager::convert3DToLocation(const float& x, const float& y, const float& z)
{
    unsigned int nx = (unsigned int)(clampCoordinate(x) + boundCoordinates);
    unsigned int ny = (unsigned int)(clampCoordinate(y) + boundCoordinates);
    unsigned int nz = (unsigned int)(clampCoordinate(z) + boundCoordinates);

    Location location;
    
    location.x = nx >> bitshiftLength;
    location.y = ny >> bitshiftLength;
    location.z = nz >> bitshiftLength;

    return location;
}

unsigned int SpacePartitioningManager::convertLocationtoIndex(const SpacePartitioningManager::Location& location)
{
    unsigned int max = cellLength;
    return location.x + max * (location.y + max * location.z);
}

void SpacePartitioningManager::internalAddObservable(SpacePartitioningManager::Observable& observable)
{
    Cell& cell = cells.elementAtUnsafe(convertLocationtoIndex(observable.location));
    cell.addObservable(&observable);
}

void SpacePartitioningManager::internalRemoveObservable(SpacePartitioningManager::Observable& observable)
{
    unsigned int index = convertLocationtoIndex(observable.location);
    cells.elementAtUnsafe(index).removeObservable(&observable);
}

void SpacePartitioningManager::internalAddObserver(SpacePartitioningManager::Observer& observer)
{
    Cell& cell = cells.elementAtUnsafe(convertLocationtoIndex(observer.location));
    cell.addObserver(&observer);
}

void SpacePartitioningManager::internalRemoveObserver(SpacePartitioningManager::Observer& observer)
{
    unsigned int index = convertLocationtoIndex(observer.location);
    cells.elementAtUnsafe(index).removeObserver(&observer);
}

Vector<SceneObject*> SpacePartitioningManager::internalGetCloseObjects(const Observer& observer, const float& radius)
{

    Vector<SceneObject*> close;

    unsigned int cellRadius = convertRadiusToCellUnit(radius);

    
    if(cellRadius >= 1) {

        //get the cells that are guaranteed to be in the cells without checking radius distance for individual objects

        unsigned int in_x0 = clampLocationElement(observer.location.x - (cellRadius-1));
        unsigned int in_y0 = clampLocationElement(observer.location.y - (cellRadius-1));
        unsigned int in_z0 = clampLocationElement(observer.location.z - (cellRadius-1));

        unsigned int in_x1 = clampLocationElement(observer.location.x + (cellRadius-1));
        unsigned int in_y1 = clampLocationElement(observer.location.y + (cellRadius-1));
        unsigned int in_z1 = clampLocationElement(observer.location.z + (cellRadius-1));

        for(unsigned int x = in_x0; x <= in_x1; ++x) {

            for(unsigned int y = in_y0; y <= in_y1; ++y) {

                for(unsigned int z = in_z0; z <= in_z1; ++z) {

                    Location location;
                    location.x = x;
                    location.y = y;
                    location.z = z;

                    Cell& cell = cells.elementAtUnsafe(convertLocationtoIndex(location));

                    auto obsIteration = cell.observables.iterator();

                    while(obsIteration.hasNext()) {    
                        close.add(obsIteration.next()->object);
                    }

                }

            }
        }


        //we now have to go through all the 6 faces of the outer cells that needs individually checking of objects
        //doing these seperate to reduce branching
        //you could probably check the clamp on both edges once instead of all faces

        //all faces going from topleft

        unsigned int f1_x0 = clampLocationElement(observer.location.x - cellRadius);
        unsigned int f1_y0 = clampLocationElement(observer.location.y - cellRadius);
        unsigned int f1_z0 = clampLocationElement(observer.location.z - cellRadius);
    
        unsigned int f1_x1 = clampLocationElement(observer.location.x + cellRadius);
        unsigned int f1_y1 = clampLocationElement(observer.location.y + cellRadius);
        unsigned int f1_z1 = clampLocationElement(observer.location.z - cellRadius);

        unsigned int f2_x1 = clampLocationElement(observer.location.x - cellRadius);
        unsigned int f2_y1 = clampLocationElement(observer.location.y + cellRadius);
        unsigned int f2_z1 = clampLocationElement(observer.location.z + cellRadius);

        unsigned int f3_x1 = clampLocationElement(observer.location.x + cellRadius);
        unsigned int f3_y1 = clampLocationElement(observer.location.y - cellRadius);
        unsigned int f3_z1 = clampLocationElement(observer.location.z + cellRadius);

        //all faces going from bottomright

        unsigned int f4_x1 = clampLocationElement(observer.location.x + cellRadius);
        unsigned int f4_y1 = clampLocationElement(observer.location.y + cellRadius);
        unsigned int f4_z1 = clampLocationElement(observer.location.z + cellRadius);

        unsigned int f4_x0 = clampLocationElement(observer.location.x - cellRadius);
        unsigned int f4_y0 = clampLocationElement(observer.location.y - cellRadius);
        unsigned int f4_z0 = clampLocationElement(observer.location.z + cellRadius);

        unsigned int f5_x0 = clampLocationElement(observer.location.x - cellRadius);
        unsigned int f5_y0 = clampLocationElement(observer.location.y + cellRadius);
        unsigned int f5_z0 = clampLocationElement(observer.location.z - cellRadius);

        unsigned int f6_x0 = clampLocationElement(observer.location.x + cellRadius);
        unsigned int f6_y0 = clampLocationElement(observer.location.y - cellRadius);
        unsigned int f6_z0 = clampLocationElement(observer.location.z - cellRadius);

        fillCloseObjects(close, observer, radius, f1_x0, f1_x1, f1_y0, f1_y1, f1_z0, f1_z1);
        fillCloseObjects(close, observer, radius, f1_x0, f2_x1, f1_y0, f2_y1, f1_z0, f2_z1);
        fillCloseObjects(close, observer, radius, f1_x0, f3_x1, f1_y0, f3_y1, f1_z0, f3_z1);

        fillCloseObjects(close, observer, radius, f4_x0, f4_x1, f4_y0, f4_y1, f4_z0, f4_z1);
        fillCloseObjects(close, observer, radius, f5_x0, f4_x1, f5_y0, f4_y1, f5_z0, f4_z1);
        fillCloseObjects(close, observer, radius, f6_x0, f4_x1, f6_y0, f4_y1, f6_z0, f4_z1);
    }

    else {
        unsigned int x0 = clampLocationElement(observer.location.x - cellRadius);
        unsigned int y0 = clampLocationElement(observer.location.y - cellRadius);
        unsigned int z0 = clampLocationElement(observer.location.z - cellRadius);

        unsigned int x1 = clampLocationElement(observer.location.x + cellRadius);
        unsigned int y1 = clampLocationElement(observer.location.y + cellRadius);
        unsigned int z1 = clampLocationElement(observer.location.z + cellRadius);

        fillCloseObjects(close, observer, radius, x0, x1, y0, y1, z0, z1);
    }


    return std::move(close);
}


void SpacePartitioningManager::fillCloseObjects(Vector<SceneObject*>& v, const Observer& observer, const float& radius, const unsigned int& x0, const unsigned int& x1, 
                    const unsigned int& y0, const unsigned int& y1,
                    const unsigned int& z0, const unsigned int& z1)
{
    
    for(unsigned int x = x0; x <= x1; ++x) {

        for(unsigned int y = y0; y <= y1; ++y) {

            for(unsigned int z = z0; z <= z1; ++z) {

                Location location;
                location.x = x;
                location.y = y;
                location.z = z;

                Cell& cell = cells.elementAtUnsafe(convertLocationtoIndex(location));

                auto obsIteration = cell.observables.iterator();

                while(obsIteration.hasNext()) {   
                    
                    Observable* obs = obsIteration.next();

                    Vector3 a(obs->x, obs->y, obs->z);
                    Vector3 b(observer.x, observer.y, observer.z);

                    if(a.distanceTo(b) <= radius) {
                         v.add(obs->object);
                    }
                }

            }
        }
    }
}


//disgusting! find a way not have copy pasted code with mininal difference

Vector<SceneObject*> SpacePartitioningManager::internalGetCloseObservers(const Observer& observer, const float& radius)
{

    Vector<SceneObject*> close;

    unsigned int cellRadius = convertRadiusToCellUnit(radius);

    
    if(cellRadius >= 1) {

        //get the cells that are guaranteed to be in the cells without checking radius distance for individual objects

        unsigned int in_x0 = clampLocationElement(observer.location.x - (cellRadius-1));
        unsigned int in_y0 = clampLocationElement(observer.location.y - (cellRadius-1));
        unsigned int in_z0 = clampLocationElement(observer.location.z - (cellRadius-1));

        unsigned int in_x1 = clampLocationElement(observer.location.x + (cellRadius-1));
        unsigned int in_y1 = clampLocationElement(observer.location.y + (cellRadius-1));
        unsigned int in_z1 = clampLocationElement(observer.location.z + (cellRadius-1));

        for(unsigned int x = in_x0; x <= in_x1; ++x) {

            for(unsigned int y = in_y0; y <= in_y1; ++y) {

                for(unsigned int z = in_z0; z <= in_z1; ++z) {

                    Location location;
                    location.x = x;
                    location.y = y;
                    location.z = z;

                    Cell& cell = cells.elementAtUnsafe(convertLocationtoIndex(location));

                    auto obsIteration = cell.observers.iterator();

                    while(obsIteration.hasNext()) {    
                        close.add(obsIteration.next()->object);
                    }

                }

            }
        }


        //we now have to go through all the 6 faces of the outer cells that needs individually checking of objects
        //doing these seperate to reduce branching
        //you could probably check the clamp on both edges once instead of all faces

        //all faces going from topleft

        unsigned int f1_x0 = clampLocationElement(observer.location.x - cellRadius);
        unsigned int f1_y0 = clampLocationElement(observer.location.y - cellRadius);
        unsigned int f1_z0 = clampLocationElement(observer.location.z - cellRadius);
    
        unsigned int f1_x1 = clampLocationElement(observer.location.x + cellRadius);
        unsigned int f1_y1 = clampLocationElement(observer.location.y + cellRadius);
        unsigned int f1_z1 = clampLocationElement(observer.location.z - cellRadius);

        unsigned int f2_x1 = clampLocationElement(observer.location.x - cellRadius);
        unsigned int f2_y1 = clampLocationElement(observer.location.y + cellRadius);
        unsigned int f2_z1 = clampLocationElement(observer.location.z + cellRadius);

        unsigned int f3_x1 = clampLocationElement(observer.location.x + cellRadius);
        unsigned int f3_y1 = clampLocationElement(observer.location.y - cellRadius);
        unsigned int f3_z1 = clampLocationElement(observer.location.z + cellRadius);

        //all faces going from bottomright

        unsigned int f4_x1 = clampLocationElement(observer.location.x + cellRadius);
        unsigned int f4_y1 = clampLocationElement(observer.location.y + cellRadius);
        unsigned int f4_z1 = clampLocationElement(observer.location.z + cellRadius);

        unsigned int f4_x0 = clampLocationElement(observer.location.x - cellRadius);
        unsigned int f4_y0 = clampLocationElement(observer.location.y - cellRadius);
        unsigned int f4_z0 = clampLocationElement(observer.location.z + cellRadius);

        unsigned int f5_x0 = clampLocationElement(observer.location.x - cellRadius);
        unsigned int f5_y0 = clampLocationElement(observer.location.y + cellRadius);
        unsigned int f5_z0 = clampLocationElement(observer.location.z - cellRadius);

        unsigned int f6_x0 = clampLocationElement(observer.location.x + cellRadius);
        unsigned int f6_y0 = clampLocationElement(observer.location.y - cellRadius);
        unsigned int f6_z0 = clampLocationElement(observer.location.z - cellRadius);

        fillCloseObservers(close, observer, radius, f1_x0, f1_x1, f1_y0, f1_y1, f1_z0, f1_z1);
        fillCloseObservers(close, observer, radius, f1_x0, f2_x1, f1_y0, f2_y1, f1_z0, f2_z1);
        fillCloseObservers(close, observer, radius, f1_x0, f3_x1, f1_y0, f3_y1, f1_z0, f3_z1);

        fillCloseObservers(close, observer, radius, f4_x0, f4_x1, f4_y0, f4_y1, f4_z0, f4_z1);
        fillCloseObservers(close, observer, radius, f5_x0, f4_x1, f5_y0, f4_y1, f5_z0, f4_z1);
        fillCloseObservers(close, observer, radius, f6_x0, f4_x1, f6_y0, f4_y1, f6_z0, f4_z1);
    }

    else {
        unsigned int x0 = clampLocationElement(observer.location.x - cellRadius);
        unsigned int y0 = clampLocationElement(observer.location.y - cellRadius);
        unsigned int z0 = clampLocationElement(observer.location.z - cellRadius);

        unsigned int x1 = clampLocationElement(observer.location.x + cellRadius);
        unsigned int y1 = clampLocationElement(observer.location.y + cellRadius);
        unsigned int z1 = clampLocationElement(observer.location.z + cellRadius);

        fillCloseObservers(close, observer, radius, x0, x1, y0, y1, z0, z1);
    }


    return std::move(close);
}


void SpacePartitioningManager::fillCloseObservers(Vector<SceneObject*>& v, const Observer& observer, const float& radius, const unsigned int& x0, const unsigned int& x1, 
                    const unsigned int& y0, const unsigned int& y1,
                    const unsigned int& z0, const unsigned int& z1)
{
    
    for(unsigned int x = x0; x <= x1; ++x) {

        for(unsigned int y = y0; y <= y1; ++y) {

            for(unsigned int z = z0; z <= z1; ++z) {

                Location location;
                location.x = x;
                location.y = y;
                location.z = z;

                Cell& cell = cells.elementAtUnsafe(convertLocationtoIndex(location));

                auto obsIteration = cell.observers.iterator();

                while(obsIteration.hasNext()) {   
                    
                    Observer* obs = obsIteration.next();

                    Vector3 a(obs->x, obs->y, obs->z);
                    Vector3 b(observer.x, observer.y, observer.z);

                    if(a.distanceTo(b) <= radius) {
                         v.add(obs->object);
                    }
                }

            }
        }
    }
}

void SpacePartitioningManager::addObject(SceneObject* object)
{
    Location location = convert3DToLocation(object->getPositionX(), object->getPositionY(), object->getPositionZ());

    Observable observable(object->getPositionX(), object->getPositionY(), object->getPositionZ(), location, object);

    observables.put(object, std::move(observable));

    internalAddObservable(observables.get(object));
}

void SpacePartitioningManager::removeObject(SceneObject* object)
{
    Observable& observable = observables.get(object);

    internalRemoveObservable(observable);

    observables.remove(object);
}

void SpacePartitioningManager::moveObject(SceneObject* object)
{
    Observable& observable = observables.get(object);

    Location location = convert3DToLocation(object->getPositionX(), object->getPositionY(), object->getPositionZ());

    observable.x = object->getPositionX();
    observable.y = object->getPositionX();
    observable.z = object->getPositionX();

    //same location nothing to do
    if(location == observable.location) {
        return;
    }

    internalRemoveObservable(observable);

    observable.location = location;

    internalAddObservable(observable);
}


void SpacePartitioningManager::addObserver(SceneObject* object, const float& radius)
{
    Location location = convert3DToLocation(object->getPositionX(), object->getPositionY(), object->getPositionZ());

    Observer obs(object->getPositionX(), object->getPositionY(), object->getPositionZ(), radius, convertRadiusToCellUnit(radius), location, object);

    observers.put(object, std::move(obs));

    Observer& observer = observers.get(object);

    internalAddObserver(observer);
}

void SpacePartitioningManager::moveObserver(SceneObject* object)
{

    Observer& observer = observers.get(object);

    Location location = convert3DToLocation(object->getPositionX(), object->getPositionY(), object->getPositionZ());

    observer.x = object->getPositionX();
    observer.y = object->getPositionX();
    observer.z = object->getPositionX();

    //same location nothing to do
    if(location == observer.location) {
        return;
    }

    internalRemoveObserver(observer);

    observer.location = location;

    internalAddObserver(observer);

}

void SpacePartitioningManager::removeObserver(SceneObject* object)
{
    Observer& observer = observers.get(object);

    internalRemoveObserver(observer);

    observers.remove(object);
}


Vector<SceneObject*> SpacePartitioningManager::getCloseObjects(SceneObject* object)
{
    Observer& observer = observers.get(object);

    Vector<SceneObject*> close = internalGetCloseObjects(observer, observer.radius);

    return std::move(close);
}

Vector<SceneObject*> SpacePartitioningManager::getCloseObjects(SceneObject* object, const float& radius)
{
    
    Observer& observer = observers.get(object);

    Vector<SceneObject*> close = internalGetCloseObjects(observer, std::min(radius, observer.radius));

    return std::move(close);
}

Vector<SceneObject*> SpacePartitioningManager::getCloseObservers(SceneObject* object)
{
    Observer& observer = observers.get(object);

    Vector<SceneObject*> close = internalGetCloseObservers(observer, observer.radius);

    return std::move(close);
}

Vector<SceneObject*> SpacePartitioningManager::getCloseObservers(SceneObject* object, const float& radius)
{
    Observer& observer = observers.get(object);

    Vector<SceneObject*> close = internalGetCloseObservers(observer, std::min(radius, observer.radius));

    return std::move(close);
}

}
}
}
}

