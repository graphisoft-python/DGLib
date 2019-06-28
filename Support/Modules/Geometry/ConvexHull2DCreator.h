#if !defined CONVEX_HULL2D_CREATOR
#define CONVEX_HULL2D_CREATOR

#include "Point2DData.h"
#include "Point3DData.h"
#include "PagedArray.hpp"
#include "HashSet.hpp"
#include "HashCommon.hpp"

class GEOMETRY_DLL_EXPORT ConvexHull2DCreator {
	public:
		ConvexHull2DCreator();

		void AddPoint		(double x, double y);
		void AddPoint		(double x, double y, double z); //the 3rd coord won't be used by the algorithm
		void AddPoint		(const Coord& c);
		void AddPoint		(const Coord3D& c);
		void ClearPoints	(void);

		GS::PagedArray<Coord3D> CalcConvexHull ();

	private:
		class HashableCoord3D {
		private:
			Coord3D p;
		public:
			HashableCoord3D (const Coord3D& p);
			operator const Coord3D& () const;

			HashableCoord3D ();
			operator GS::HashValue () const;
			bool operator==(const HashableCoord3D& other) const;
		};

		GS::HashSet<HashableCoord3D> originalPoints;

		class AngleComparator { //local functor for comparing angles during the sort
			public:
				AngleComparator (const Coord3D& p);
				bool operator () (const Coord3D& first, const Coord3D& second);
			private:
				Coord3D referencePoint;

				AngleComparator(); //disabled
		};
};

#endif
