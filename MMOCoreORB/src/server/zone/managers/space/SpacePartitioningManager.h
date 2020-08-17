/*
 * SpacePartitioningManager.h
 *
 *  Created on: 14/08/2020
 *      Author: daniel
 */

#ifndef SPACE_PARTITIONING_MANAGER_H_
#define SPACE_PARTITIONING_MANAGER_H_

#include "server/zone/objects/scene/SceneObject.h"

/*
    Space partitioning uses a 3D cell based partitioning system where the world is divided into evenly sized cells.

    concepts:

    cell - represents a 3d cube that can contain observables and observers and can be represented by a 3d vector location by dividing the coordinates with cellsize

    observer - object that has a set radius that represents how far the observer can see in standard coordinates (represents players)

    observable - object that can be seen by observers (non player objects)

    pros:
        Moving objects is extremely fast compared to most other partitioning systems 
        The partitioning method is extremely easy to understand and implement
    cons:
        Because all cells are evenly distributed we can't control the fidelity of the partioning near areas with many objects(in space I somewhat doubt that this will be a problem)
        We allocate all the cells even if no objects are there(memory problem)


    Implentation thoughts:
        The underlying concept for the this implementation is that all objects are always in movement. This means in my first iteration I decided not to store the objects visible
        by the observer in their class, because every update that would have to be recalculated, and therefore it makes more sense just to go through the cells at query time.

        There is no difference between that and update if they move every frame. Actually storing the visible objects has overhead by maintaining it.

        I have added optimization for querying close objects where we only check the outermost cells, since anything closer will by definition always be closer than the radius.

    
    Todo: 
        need more tests

        need benchmark(no point in trying to optimize without measurements) 

*/

namespace server {
namespace zone {
namespace managers {
namespace space {

class SpacePartitioningManager {
public:
    SpacePartitioningManager(const unsigned int& cellSize, const float& boundCoordinates);
    ~SpacePartitioningManager();
    SpacePartitioningManager(const SpacePartitioningManager& o) = delete;
    SpacePartitioningManager(SpacePartitioningManager&&) = delete;
    SpacePartitioningManager& operator=(const SpacePartitioningManager& rhs) = delete;
    SpacePartitioningManager& operator=(const SpacePartitioningManager&& rhs) = delete;


    void addObject(SceneObject* object);
    void moveObject(SceneObject* object);
    void removeObject(SceneObject* object);
    
    void addObserver(SceneObject* observer, const float& radius);
    void moveObserver(SceneObject* observer);
    void removeObserver(SceneObject* observer); 

    Vector<SceneObject*> getCloseObjects(SceneObject* observer);   
    Vector<SceneObject*> getCloseObjects(SceneObject* observer, const float& radius);   

    Vector<SceneObject*> getCloseObservers(SceneObject* observer);
    Vector<SceneObject*> getCloseObservers(SceneObject* observer, const float& radius);   

    Vector<SceneObject*> getCloseObserversByLocation(const float& x, const float& y, const float& z, const float& radius);  
private:
    class Observer;
    class Observable;
    class Location;

    void internalAddObservable(Observable& observable);
    void internalRemoveObservable(Observable& observable);
    void internalAddObserver(Observer& observer);
    void internalRemoveObserver(Observer& observer);
    
    Vector<SceneObject*> internalGetCloseObjects(const Observer& observer, const float& radius);

    void fillCloseObjects(Vector<SceneObject*>& v, const Observer& observer, const float& radius, const unsigned int& x0, const unsigned int& x1, 
                    const unsigned int& y0, const unsigned int& y1,
                    const unsigned int& z0, const unsigned int& z1);


    Vector<SceneObject*> internalGetCloseObservers(const Observer& observer, const float& radius);

    void fillCloseObservers(Vector<SceneObject*>& v, const Observer& observer, const float& radius, const unsigned int& x0, const unsigned int& x1, 
                    const unsigned int& y0, const unsigned int& y1,
                    const unsigned int& z0, const unsigned int& z1);
private:

    struct Location {
        bool parseFromBinaryStream(ObjectInputStream* stream);
        bool toBinaryStream(ObjectOutputStream* stream);
        bool operator==(const Location& rhs);
        unsigned int x, y, z; 
    };

    class Cell {
    public:
        void addObservable(Observable* observable);
        void removeObservable(Observable* observable);
        void addObserver(Observer* observer);
        void removeObserver(Observer* observer);

        bool parseFromBinaryStream(ObjectInputStream* stream);
        bool toBinaryStream(ObjectOutputStream* stream);
 
        HashTable<SceneObject*, Observer*> observers;
        HashTable<SceneObject*, Observable*> observables;
    };

    class Observer {
    public:
        Observer();
        Observer(const float& x, const float& y, const float& z, const float& radius, const unsigned int& radiusCellUnit, const Location& location, SceneObject* object);
        Observer(const Observer& o);
        Observer(Observer&&);
        Observer& operator=(const Observer& rhs);

        bool parseFromBinaryStream(ObjectInputStream* stream);
        bool toBinaryStream(ObjectOutputStream* stream);
    
        float x, y, z; //the last coordinates of the observer since move
        float radius;
        unsigned int radiusCellUnit; 
        Location location;
        SceneObject* object;
    };

    class Observable {
    public:
        Observable();
        Observable(const float& x, const float& y, const float& z, const Location& location, SceneObject* object);
        Observable(Observable&& o);
        Observable(const Observable&);
        Observable& operator=(const Observable& rhs);

        bool parseFromBinaryStream(ObjectInputStream* stream);
        bool toBinaryStream(ObjectOutputStream* stream);
 
        float x, y, z; //the last coordinates of the observable since move
        Location location;
        SceneObject* object;
    };

private:
    Location convert3DToLocation(const float& x, const float& y, const float& z);
    unsigned int convertLocationtoIndex(const Location& location);
    float clampCoordinate(const float& v);
    unsigned int clampLocationElement(const unsigned int& v);
    unsigned int convertRadiusToCellUnit(const float& v);
private:
    unsigned int cellLength;
    unsigned int cellSize; //has to be power of two
    float boundCoordinates; //has to be power of two. maximum coordinates for x y z
    unsigned int bitshiftLength; //instead of dividing with cellsize use bitshifting.
    Vector<Cell> cells;
    HashTable<SceneObject*, Observer> observers;
    HashTable<SceneObject*, Observable> observables;
};


}
}
}
}

#endif
