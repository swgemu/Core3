/*
 * Sgmt.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef SGMT_H_
#define SGMT_H_

#include "engine/util/u3d/Vector3.h"

#include "../TemplateVariable.h"

#include <vector>

#define DEBUG_FATAL(x, y) assert(!(x) && (y))
//#define DEBUG_FATAL(x, y) ;

class Point3D : public Object {
public:
	Point3D() : x(0), z(0), y(0) {

	}

	Point3D(const Point3D& p) = default;

	Point3D& operator=(const Point3D& p) = default;

	Point3D(float x, float y, float z) : x(x), z(z), y(y) {

	}

	float x, z, y;
};

class Segment : public TemplateVariable<'SGMT'> {
	Vector<Point3D> positions;

public:
	~Segment() {
		/*for (int i = 0; i < positions.size(); ++i)
			delete positions.get(i);*/
	}

	template<class T>
	static T linearInterpolate(const T& start, const T& end, float t) {
		return ((end - start) * t) + start;
	}


	template<class T>
	static const T clamp(const T &minT, const T &t, const T &maxT)
	{
		DEBUG_FATAL(maxT < minT, ("clamp error: max value is less than min value"));
		return (t < minT) ? minT : ((t > maxT) ? maxT : t);
	}

	void createRoadData() {
		return;

		Logger::console.info("createRoadData on the segment", true);

		if (positions.size () > 3)  {
			Logger::console.info("positions.size() > 3", true);

			Vector<Point3D> newPointList;
			newPointList.add (positions.get(0));

			unsigned int i;
			for (i = 1; i < positions.size () - 1; ++i)  {
				const float y = (positions.get(i - 1).y + positions.get(i).y + positions.get(i + 1).y) / 3.f;

				newPointList.add (Point3D (positions.get(i).x, y, positions.get(i).z));
			}

			newPointList.add (positions.get(i));

			positions = newPointList;
		}
	}

	int getNumberOfPoints() {
		return positions.size();
	}

	void setPoint(int index, const Point3D& point) {
		positions.set(index, point);
	}

	const Point3D& getPoint(int index) {
		return positions.get(index);
	}

	bool find(Vector3 worldPosition, float& result)  {
		//Logger::console.info("positions.size():" + String::valueOf(positions.size()), true);

		if (positions.size() == 0)
			return false;

		typedef std::vector<Point3D> PointList;

		PointList m_pointList;

		for (int i=0; i<positions.size(); i++) {
			m_pointList.push_back(positions.get(i));
		}

//		Vector2d position = oposition;

		Point3D position(worldPosition.getX(), worldPosition.getY(), worldPosition.getZ());

#if 1
		{
			const float x0 = std::min (m_pointList.begin ()->x, m_pointList.back ().x);
			const float z0 = std::min (m_pointList.begin ()->z, m_pointList.back ().z);
			const float x1 = std::max (m_pointList.begin ()->x, m_pointList.back ().x);
			const float z1 = std::max (m_pointList.begin ()->z, m_pointList.back ().z);
//		DEBUG_FATAL (position.x < x0 || position.x > x1 || position.y < z0 || position.y > z1, ("position out of range"));
			position.x = clamp (x0, position.x, x1);
			position.y = clamp (z0, position.y, z1);
		}
#endif

		const float width  = m_pointList.back ().x - m_pointList.begin ()->x;
		const float height = m_pointList.back ().z - m_pointList.begin ()->z;

		if (fabsf (width) >= fabsf (height))
		{
			if (width >= 0)
			{
				DEBUG_FATAL (width == 0, ("this can't happen"));

				//-- go from -x to +x
				PointList::const_iterator current  = m_pointList.begin ();
				PointList::const_iterator previous = current;

				for (; current != m_pointList.end () && current->x < position.x; previous = current, ++current)
					;

				DEBUG_FATAL (current == m_pointList.begin (), ("couldn't straddle begin"));
				DEBUG_FATAL (current == m_pointList.end (), ("couldn't straddle end"));

				const float t = (position.x - previous->x) / (current->x - previous->x);
				result = linearInterpolate (previous->y, current->y, t);
			}
			else
			{
				//-- go from +x to -x
				PointList::const_reverse_iterator current  = m_pointList.rbegin ();
				PointList::const_reverse_iterator previous = current;

				for (; current != m_pointList.rend () && current->x < position.x; previous = current, ++current)
					;

				DEBUG_FATAL (current == m_pointList.rbegin (), ("couldn't straddle rbegin"));
				DEBUG_FATAL (current == m_pointList.rend (), ("couldn't straddle rend"));

				const float t = (position.x - previous->x) / (current->x - previous->x);
				result = linearInterpolate (previous->y, current->y, t);
			}
		}
		else
		{
			if (height >= 0)
			{
				DEBUG_FATAL (height == 0, ("this can't happen"));

				//-- go from -z to +z
				PointList::const_iterator current  = m_pointList.begin ();
				PointList::const_iterator previous = current;

				for (; current != m_pointList.end () && current->z < position.y; previous = current, ++current)
					;

				DEBUG_FATAL (current == m_pointList.begin (), ("couldn't straddle begin"));
				DEBUG_FATAL (current == m_pointList.end (), ("couldn't straddle end"));

				const float t = (position.y - previous->z) / (current->z - previous->z);
				result = linearInterpolate (previous->y, current->y, t);
			}
			else
			{
				//-- go from +z to -z
				PointList::const_reverse_iterator current  = m_pointList.rbegin ();
				PointList::const_reverse_iterator previous = current;

				for (; current != m_pointList.rend () && current->z < position.y; previous = current, ++current)
					;

				DEBUG_FATAL (current == m_pointList.rbegin (), ("couldn't straddle rbegin"));
				DEBUG_FATAL (current == m_pointList.rend (), ("couldn't straddle rend"));

				const float t = (position.y - previous->z) / (current->z - previous->z);
				result = linearInterpolate (previous->y, current->y, t);
			}
		}

		return true;
	}

	void readObject(engine::util::IffStream* iffStream) {
		iffStream->openChunk('SGMT');

		int count = iffStream->getDataSize() / 12;

		for (int i = 0; i < count; i++) {
			Point3D position;
			position.x = iffStream->getFloat();
			position.y = iffStream->getFloat();
			position.z = iffStream->getFloat();

			positions.add(position);
		}

		iffStream->closeChunk('SGMT');
	}


};


#endif /* SGMT_H_ */
