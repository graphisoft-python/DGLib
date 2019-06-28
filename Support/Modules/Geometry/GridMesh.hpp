// *****************************************************************************
// 3D mesh, with four sided polygons
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          VT, DBE
//
// [SG compatible]
// *****************************************************************************

#if !defined (GridMesh_HPP)
#define GridMesh_HPP

#pragma once

#include "Coord.h"
#include "Box3DData.h"
#include "TM.h"
#include "HashTable.hpp"
#include "HashSet.hpp"
#include "SharedObject.hpp"
#include <set>

namespace GS {
	class IChannel;
	class OChannel;
	class XMLOChannel;
}


typedef unsigned short	GridLineID;
typedef UInt64			GridElemID;	


// *****************************************************************************
template <typename Elem>	//Elem can be vertex, edge, line, poly only!
class GridElemIDToElem
{
private:
	typedef GS::SharedPtr<Elem>						HTEntry;
	typedef GS::HashTable<GridElemID, HTEntry>		TableType;
public:
	class Iterator : private TableType::ValueIterator
	{
	public:
		Iterator () {}
		Iterator (typename TableType::ValueIterator i) : TableType::ValueIterator (i) {} 
		Iterator (const Iterator& src) : TableType::ValueIterator (src) {}
		Iterator operator= (const Iterator& src) { TableType::ValueIterator::operator = (src); return *this; }
		Iterator operator++ () { typename TableType::ValueIterator& ths = *this; ++ths; return *this;}
		bool operator== (const Iterator& src) { return TableType::ValueIterator::operator== (src); }
		bool operator!= (const Iterator& src) { return TableType::ValueIterator::operator!= (src); }
		Elem* operator-> () const { const typename TableType::ValueIterator* ths = this; return (*ths)->operator-> (); }
		Elem& operator* () const { const typename TableType::ValueIterator* ths = this; return (*ths)->operator* (); }

		operator GS::SharedPtr<Elem> () const 
		{
			const typename TableType::ValueIterator* ths = this;
			return GS::SharedPtr<Elem> ((*ths)->operator-> ());
		}
		operator GS::ConstSharedPtr<Elem> () const 
		{
			const typename TableType::ValueIterator* ths = this; 
			return GS::ConstSharedPtr<Elem> ((*ths)->operator-> ());
		}
	};


	class ConstIterator : private TableType::ConstValueIterator
	{
	public:
		ConstIterator () {}
		ConstIterator (typename TableType::ConstValueIterator i) : TableType::ConstValueIterator (i) {} 
		ConstIterator (const ConstIterator& src) : TableType::ConstValueIterator (src) {}
		ConstIterator operator= (const ConstIterator& src) { TableType::ConstValueIterator::operator = (src); return *this;}
		ConstIterator operator++ () { typename TableType::ConstValueIterator& ths = *this; ++ths; return *this;}
		bool operator== (const ConstIterator& src) { return TableType::ConstValueIterator::operator== (src); }
		bool operator!= (const ConstIterator& src) { return TableType::ConstValueIterator::operator!= (src); }
		const Elem* operator-> () const { const typename TableType::ConstValueIterator* ths = this; return (*ths)->operator-> (); }
		const Elem& operator* () const { const typename TableType::ConstValueIterator* ths = this; return (*ths)->operator* (); }

		operator GS::ConstSharedPtr<Elem> () const
		{
			const typename TableType::ConstValueIterator* ths = this; 
			return GS::ConstSharedPtr<Elem>((*ths)->operator-> ()); 
		}
	};


	GridElemIDToElem (); 
	virtual ~GridElemIDToElem (); 

	//query:
	USize			GetSize () const; 
	bool			IsEmpty () const;
	bool			ContainsKey (GridElemID id) const;

	//modify:
	bool			Add (GridElemID id, const Elem& src, GS::SharedPtr<Elem>& inTableEntry);
	void			Add (GridElemID id, const Elem& src);
	GS::SharedPtr<Elem>
					Add (GridElemID id);	//adds a new or gets an old Elem
	void			Delete (GridElemID id); 
	void			Clear ();

	//element access:
	GS::SharedPtr<Elem>
					Get (GridElemID id); 

	GS::ConstSharedPtr<Elem>
					Get (GridElemID id) const; 

	Iterator		Begin ();
	Iterator		End ();

	ConstIterator	Begin () const;
	ConstIterator	End () const;

private:
	GridElemIDToElem (const GridElemIDToElem&) {} //no copy! 
	GridElemIDToElem& operator= (const GridElemIDToElem&) {} //no copy!
	TableType		myTable;
}; 


//impl for GridElemIDToElem: 
template <typename Elem>
GridElemIDToElem<Elem>::GridElemIDToElem ()
{
}

template <typename Elem>
/*virtual*/
GridElemIDToElem<Elem>::~GridElemIDToElem ()
{
}

template <typename Elem>
USize			GridElemIDToElem<Elem>::GetSize () const
{
	return myTable.GetSize (); 
}

template <typename Elem>
bool			GridElemIDToElem<Elem>::IsEmpty () const
{
	return myTable.IsEmpty (); 
}

template <typename Elem>
bool			GridElemIDToElem<Elem>::ContainsKey (GridElemID id) const
{
	return myTable.ContainsKey (id); 
}

template <typename Elem>
void			GridElemIDToElem<Elem>::Delete (GridElemID id)
{
	HTEntry* e = nullptr; 
	if (DBVERIFY (myTable.Get (id, &e))) {
		DBASSERT (e != nullptr); 
		myTable.Delete (id); 
	}
}

template <typename Elem>
void			GridElemIDToElem<Elem>::Clear ()
{
	for (Iterator it = myTable.BeginValues (); it != myTable.EndValues (); ++it) {
		it->Clear ();
	}
	myTable.Clear ();
}

 template <typename Elem>
 bool			GridElemIDToElem<Elem>::Add (GridElemID id, const Elem& src, GS::SharedPtr<Elem>& inTableEntry)
 {
 	bool didAdd = false;
 	HTEntry* e = nullptr;
 	if (!myTable.Get (id, &e)) {
 		didAdd = myTable.Add (id, new /*(allocator.Allocate ())*/ Elem (src), &e); 
		if (didAdd) {
			(*e)->SetID (id); 
		}
 	}
 	DBASSERT (e != nullptr);
 
 	inTableEntry = *e;
 
 	return didAdd;
 }

 template <typename Elem>
 void			GridElemIDToElem<Elem>::Add (GridElemID id, const Elem& src)
 {
 	HTEntry* e = nullptr;
 	if (!myTable.Get (id, &e)) {
 		bool didAdd = myTable.Add (id, new /*(allocator.Allocate ())*/ Elem (src), &e); 
		if (didAdd) {
			(*e)->SetID (id); 
		}
		else {
		throw GS::GSException ();
	}
 }
 	DBASSERT (e != nullptr);
 }

template <typename Elem>
GS::SharedPtr<Elem>	GridElemIDToElem<Elem>::Add (GridElemID id)	//adds a new or gets an old Elem
{
	HTEntry* e = nullptr; 
	if (!myTable.Get (id, &e)) {
		if (myTable.Add (id, new /*(allocator.Allocate ())*/ Elem (), &e)) {
			(*e)->SetID (id); 
		}
	}
	if (DBERROR (e == nullptr)) 
		throw GS::IllegalReferenceException ();

	return *e; 
}

template <typename Elem>
GS::SharedPtr<Elem>	GridElemIDToElem<Elem>::Get (GridElemID id)
{
	HTEntry* e = nullptr;
	if (myTable.Get (id, &e)) {
		return *e;
	}
	return GS::SharedPtr<Elem> (nullptr);
}

template <typename Elem>
GS::ConstSharedPtr<Elem>	GridElemIDToElem<Elem>::Get (GridElemID id) const
{
	const HTEntry* e = nullptr;
	if (myTable.Get (id, &e)) {
		return *e;
	}
	return GS::ConstSharedPtr<Elem> (nullptr);
}


template <typename Elem>
typename GridElemIDToElem<Elem>::Iterator
				GridElemIDToElem<Elem>::Begin ()
{
	return myTable.BeginValues (); 
}

template <typename Elem>
typename GridElemIDToElem<Elem>::Iterator
				GridElemIDToElem<Elem>::End ()
{
	return myTable.EndValues ();
}

template <typename Elem>
typename GridElemIDToElem<Elem>::ConstIterator
				GridElemIDToElem<Elem>::Begin () const
{
	return myTable.BeginValues ();
}

template <typename Elem>
typename GridElemIDToElem<Elem>::ConstIterator
				GridElemIDToElem<Elem>::End () const
{
	return myTable.EndValues ();
}

// *****************************************************************************


const GridLineID InvalidMeshLineID = 0xFFFF;
const GridElemID InvalidMeshElemID = 0xFFFFFFFF;

inline GridElemID MergeGridIDs (GridLineID mainID, GridLineID secID)
{
	if (mainID < InvalidMeshLineID && secID < InvalidMeshLineID) {
		return (GridElemID (mainID) << 16) | GridElemID (secID);
	}

	return InvalidMeshElemID; 
}

inline GridElemID MergeGridElemIDs (GridElemID ID1, GridElemID ID2)
{
	if (ID1 > InvalidMeshElemID && ID2 > InvalidMeshElemID) {
		DBASSERT ((ID1 & InvalidMeshElemID) == 0);
		DBASSERT ((ID2 & InvalidMeshElemID) == 0);

		DBASSERT (ID1 < (((GridElemID)InvalidMeshLineID) << 32));
		DBASSERT (ID2 < (((GridElemID)InvalidMeshLineID) << 32));
	}
	else {
		DBASSERT (ID1 < InvalidMeshLineID);
		DBASSERT (ID2 < InvalidMeshLineID);
	}

	return (ID1 << 16) | ID2;
}


inline GridLineID GetGridMainID (GridElemID elemID)
{
	if (elemID < InvalidMeshElemID) {
		return GridLineID (elemID >> 16);
	}
	return InvalidMeshLineID; 
}

inline GridLineID GetGridSecID (GridElemID elemID)
{
	if (elemID < InvalidMeshElemID) {
		return GridLineID (elemID & InvalidMeshLineID);
	}
	return InvalidMeshLineID; 
}

namespace Geometry {

// direction of neighbour, used for edges and polygons (order is imporant!)
enum	Direction { LEFT = 0, RIGHT, LOWER_RIGHT, LOWER, LOWER_LEFT, UPPER_RIGHT, UPPER, UPPER_LEFT, INVALID_DIR = 0x5000 -1 };			// for main axis dir

inline bool IsValidPolyDirection (Direction dir)
{
	switch (dir) {
		case LEFT:
		case RIGHT:
		case LOWER_RIGHT:
		case LOWER:
		case LOWER_LEFT:
		case UPPER_RIGHT:
		case UPPER:
		case UPPER_LEFT:
			return true;

		default:
			return false;
	}
}

class GridMeshVertex;
class GridMesh;

// *****************************************************************************
// Base class for Lines, Vertices, Edges, Polygons
// *****************************************************************************
template <class IDType>
class GridMeshElement : public GS::SharedObject
{
	protected:
		GridMesh*				m_pGridMesh;		// pointer for GridMesh the element belongs to
		IDType					m_ID;				// 16 bit for lines, 16 + 16 = 32 bit for Vertexes, Edges, Polygons

	public:
		GridMeshElement (void)										: m_pGridMesh (nullptr), m_ID ((IDType) -1)	{}
		GridMeshElement (GridMesh* pGridMesh, IDType ID)			: m_pGridMesh (pGridMesh), m_ID (ID)		{}

		bool				operator== (const GridMeshElement& rightOp) const
		{
			return m_pGridMesh == rightOp.m_pGridMesh && m_ID == rightOp.m_ID;
		}


		const GridMesh*		GetGridMesh (void) const			{ return m_pGridMesh; }
		void				SetGridMesh (GridMesh* pGridMesh)   { m_pGridMesh = pGridMesh; }

		IDType				GetID (void) const					{ /*DBASSERT (m_ID != (IDType) (-1));*/ return m_ID; }
		void				SetID (GridElemID inID)				{ m_ID = (IDType) inID; }
		GridLineID			GetMainLineID (void) const
		{
#if defined (DEBUVERS)
			size_t sizeofIDType = sizeof (IDType);
			DBASSERT (sizeofIDType == sizeof (GridElemID));				// do not use on lines
#endif
			return GetGridMainID (m_ID);
		}

		GridLineID			GetSecondaryLineID (void) const
		{
#if defined (DEBUVERS)
			size_t sizeofIDType = sizeof (IDType);
			DBASSERT (sizeofIDType == sizeof (GridElemID));				// do not use on lines
#endif
			return GetGridSecID (m_ID);
		}
		virtual	void		Clear () = 0; 
};


// *****************************************************************************
// A 3D mesh line class with orientation and staring parameter on surface
// *****************************************************************************
class GEOMETRY_DLL_EXPORT GridMeshLine : public GridMeshElement<GridLineID>
{
	private:
		bool										m_mainDir;		// if false then secondary dir
		GS::SharedPtr<GridMeshVertex>				m_begC;			//endpoint vertices
		GS::SharedPtr<GridMeshVertex>				m_endC;
		UInt32										m_userData;
		Int32										patternInd;

	public:
		GridMeshLine ();
		GridMeshLine (GridMesh* pGridMesh, GridLineID ID, bool mainDir, UInt32 inUserData, Int32 patternInd);
		virtual ~GridMeshLine ();

		bool							IsInMainDir (void) const { return m_mainDir; }
		void							SetMainDir (const bool val) { m_mainDir = val; }
		bool							operator== (const GridMeshLine& other) const;
		bool							operator< (const GridMeshLine& other) const;

		const GS::SharedPtr<GridMeshVertex>&
										GetBegC (void);
		const GS::ConstSharedPtr<GridMeshVertex>&
										GetBegC (void) const;

		const GS::SharedPtr<GridMeshVertex>&
										GetEndC (void);
		const GS::ConstSharedPtr<GridMeshVertex>&
										GetEndC (void) const;

		GridElemID						GetBegCID	(void) const;
		GridElemID						GetEndCID	(void) const;

		void							SetBegC (GridElemID inID);
		void							SetEndC (GridElemID inID);

		UInt32							GetUserData (void) const;
		void							SetUserData (UInt32 inUserData);

		Int32							GetPatternInd () const;
		void							SetPatternInd (Int32 inPatternInd);
		virtual	void					Clear () override { m_begC = m_endC = GS::SharedPtr<GridMeshVertex> ();} 
};

// *****************************************************************************
class GEOMETRY_DLL_EXPORT GridMeshLineStore
{
public:
	GridMeshLineStore (); 

	struct less_SPtrGLine {
		bool operator() (const GS::ConstSharedPtr<GridMeshLine>& lft, const GS::ConstSharedPtr<GridMeshLine>& rght) const
		{
			if (DBVERIFY (lft != nullptr) && DBVERIFY (rght != nullptr)) {
				return (*lft) < (*rght);
			}

			return false;
		}
	};
	typedef std::set<GS::ConstSharedPtr<GridMeshLine>,less_SPtrGLine> SortedGridMeshLines;

	bool													Add (GridElemID id, const GridMeshLine& src, GS::SharedPtr<GridMeshLine>& inTableEntry);
	void													Delete (GridElemID id); 
	void													Clear ();
	bool													ContainsKey (GridElemID id) const;

	GridElemIDToElem<GridMeshLine>::ConstIterator			Begin () const { return id_lines.Begin (); }
	GridElemIDToElem<GridMeshLine>::ConstIterator			End () const { return id_lines.End (); }

	const GridElemIDToElem<GridMeshLine>&					GetLines () const { return id_lines; }
	GridElemIDToElem<GridMeshLine>&							GetLines () { return id_lines; }
	const SortedGridMeshLines&								GetSortedLines () const;
private:
	mutable bool											sortedLinesUpToDate; 
	mutable SortedGridMeshLines								sort_lines;

	GridElemIDToElem<GridMeshLine>							id_lines;
};





// *****************************************************************************
// A 3D mesh vertex class with orientation and staring parameter on surface
// *****************************************************************************
class GEOMETRY_DLL_EXPORT GridMeshVertex : public GridMeshElement<GridElemID> {

	private:
		Coord		m_surfaceParams;
		Coord3D		m_coords;

		friend class GridMesh;
		GridMeshVertex (GridMesh* pGridMesh, GridElemID id, const Coord3D& coords);
		GridMeshVertex (GridMesh* pGridMesh, GridLineID mainLineID, GridLineID secondaryLineID, const Coord& surfaceParams, const Coord3D& coords);

	public:
		GridMeshVertex ();
		virtual ~GridMeshVertex ();

		bool			operator== (const GridMeshVertex& other) const;

		const Coord3D&	GetCoord3D (void) const	{ return m_coords; }
		const Coord&	GetParam (void) const { return m_surfaceParams; }
		Coord&			GetParam (void)	{ return m_surfaceParams; }

		void			SetCoord3D (const Coord3D& coord);
		void			SetParam (const Coord& p);
		virtual	void	Clear () override	{/*Nothing to clear!*/}
};


// *****************************************************************************
// A 3D mesh edge class with two vertices
// *****************************************************************************
class GEOMETRY_DLL_EXPORT GridMeshEdge : public GridMeshElement<GridElemID>,
										 public GS::Hashable
{
	private:
		GS::SharedPtr<GridMeshVertex>					m_begC;				// ID of begC
		GS::SharedPtr<GridMeshVertex>					m_endC;				// ID of endC
		UInt32						m_userData;

	private:
		friend class GridMesh;
		GridMeshEdge (GridMesh* pGridMesh, GridElemID begC, GridElemID endC);
		GridMeshEdge (GridMesh* pGridMesh, GridElemID ID, GridElemID begC, GridElemID endC, UInt32 userData);	// can only be constructed from GridMesh because of begC, endC indices
		void					SetBegCID	(GridElemID v);
		void					SetEndCID	(GridElemID v);


	public:
		GridMeshEdge (void);
		GS::ConstSharedPtr<GridMeshVertex>	GetBegC (void) const;
		GS::SharedPtr<GridMeshVertex>		GetBegC	(void);
		GS::ConstSharedPtr<GridMeshVertex>	GetEndC (void) const;
		GS::SharedPtr<GridMeshVertex>		GetEndC	(void);
		GridElemID							GetBegCID	(void) const;
		GridElemID							GetEndCID	(void) const;
		


		bool								operator== (const GridMeshEdge& rightOp) const;
		UInt32								GetUserData (void)			const	{ return m_userData; }
		void								SetUserData (UInt32 inData)			{ m_userData = inData; }
		UInt32								GenerateHashValue (void)	const override;
		virtual	void						Clear () override { m_begC = m_endC = GS::SharedPtr<GridMeshVertex> ();} 


};

// *****************************************************************************
// A 3D mesh polygon class with four edge indices
// *****************************************************************************
class GEOMETRY_DLL_EXPORT GridMeshPolygon : public GridMeshElement<GridElemID> {
	public:
 		struct GridEdgeInfo {
 			GridElemID	id;
 			bool		mainAxis;

			GridEdgeInfo () : id (0), mainAxis (false) {}
 		};

		GridMeshPolygon ();


	private:
		GS::PagedArray<GS::SharedPtr<GridMeshPolygon>>	m_neighbours[8];		// up to 8 are used at once, there can be more neighbours at a given direction
		GS::SharedPtr<GridMeshEdge>						m_edges[4];				// edges in polygon: 1 and 3 are main edges, 0 and 2 are secondary edges 

	private:
		friend class GridMesh;
		GridMeshPolygon (GridMesh* pGridMesh, GridElemID bottomEdgeID, GridElemID rightEdgeID, GridElemID topEdgeID, GridElemID leftEdgeID);	// can only be constructed from GridMesh
		GridMeshPolygon (GridMesh* pGridMesh, GridElemID id, GridElemID bottomEdgeID, GridElemID rightEdgeID, GridElemID topEdgeID, GridElemID leftEdgeID);	// can only be constructed from GridMesh
		GridMeshPolygon (GridMesh* pGridMesh, GridLineID mainLineID, GridLineID secLineID, GridElemID bottomEdgeID, GridElemID rightEdgeID, GridElemID topEdgeID, GridElemID leftEdgeID);	// can only be constructed from GridMesh
		void	SetNeighbour (Direction dir, GridElemID inID);

	public:
		bool	operator== (const GridMeshPolygon& rightOp) const;

		GS::ConstSharedPtr<GridMeshEdge>	GetEdge (unsigned char inIndex) const;
		GS::SharedPtr<GridMeshEdge>	GetEdge (unsigned char inIndex);
		void			SetEdge (unsigned char inIndex, GridElemID edgeID);

		// get the points
		void	GetVertices (Coord3D (&outVertices) [4]) const;
		void	GetParamVertices (Coord (&paramVertices) [4]) const;

		// get/set neighbours
		GS::ConstSharedPtr<GridMeshPolygon>	GetNeighbour (Direction dir) const;
		GS::SharedPtr<GridMeshPolygon>		GetNeighbourForModify (Direction dir) const;
		void	GetNeighbours (Direction dir, GS::PagedArray<GS::SharedPtr<GridMeshPolygon>>& neighbours) const;
		void	GetNeighbours (Direction dir, GS::PagedArray<GS::ConstSharedPtr<GridMeshPolygon>>& neighbours) const;
		void	SetNeighbour (Direction dir, GS::SharedPtr<GridMeshPolygon> neig);
		void	ConnectNeighbour (Direction dir, GS::SharedPtr<GridMeshPolygon> neig);
		void	ClearNeighbours (Direction dir);
		void	AddNeighbour (Direction dir, GridElemID inID);
		void	GetAllNeighbours (GS::PagedArray<GS::SharedPtr<GridMeshPolygon>>& outArray) const;
		const GS::PagedArray<GS::SharedPtr<GridMeshPolygon>>&	GetNeighbours (Direction dir) const 
		{
			if (DBVERIFY (IsValidPolyDirection(dir)))
				return m_neighbours[dir];
			throw GS::IllegalReferenceException ();
		}

#ifdef DEBUVERS
		bool	CheckNeighbours () const;
#endif

		Vector3D GetNormal (void) const;

		void	CellCoordToParam (const Coord& coord, Coord* paramCoord) const;
		void	CellCoordToCoord3D (const Coord& coord, Coord3D* coord3D) const;
		bool	Coord3DToCellCoord (const Coord3D& c, Coord* cellRelative) const;

		void	CellCoordToSurfaceCoord (const Coord& coord, Coord* surfaceCoord) const;
		virtual	void					Clear () override; 

	public:
		GridEdgeInfo			operator () (unsigned char inIndex) const;

};

// *****************************************************************************
// A 3D mesh class
// *****************************************************************************
class GEOMETRY_DLL_EXPORT GridMesh
{
	public:
		class ConstIterator;

		typedef GridElemIDToElem<GridMeshLine>::Iterator LineIterator;
		typedef GridElemIDToElem<GridMeshLine>::ConstIterator ConstLineIterator;

		typedef GridElemIDToElem<GridMeshEdge>::ConstIterator ConstEdgeIterator;

		typedef GridElemIDToElem<GridMeshVertex>::ConstIterator ConstVertIterator;
		typedef GridElemIDToElem<GridMeshVertex>::Iterator VertIterator;

		typedef GridElemIDToElem<GridMeshPolygon>::ConstIterator ConstPolyIterator;
		typedef GridElemIDToElem<GridMeshPolygon>::Iterator PolyIterator;

		//Support for visitation of the mesh elements: 
		ConstLineIterator BeginLine (const bool isMainAxis) const;
		ConstLineIterator EndLine (const bool isMainAxis) const; 

		LineIterator BeginLine (const bool isMainAxis);
		LineIterator EndLine (const bool isMainAxis); 

		ConstEdgeIterator BeginEdge (const bool isMainAxis) const;
		ConstEdgeIterator EndEdge (const bool isMainAxis) const; 

		ConstVertIterator BeginVert () const;
		ConstVertIterator EndVert () const; 

		VertIterator BeginVert ();
		VertIterator EndVert (); 

		ConstPolyIterator BeginPoly () const;
		ConstPolyIterator EndPoly () const; 

		PolyIterator BeginPoly ();
		PolyIterator EndPoly (); 


	private:
		friend class GridMeshLine;
		friend class GridMeshEdge;
		friend class GridMeshPolygon;
		friend class ConstIterator;

		class Coord3DWrapper :  public GS::Hashable {

			protected :
				double x, y, z;

			public :
				Coord3DWrapper ();
				Coord3DWrapper (const Coord3D&);
				Coord3DWrapper&  operator= (const Coord3D& rightOp);
				bool operator== (const Coord3DWrapper& rightOp) const;
				operator Coord3D () const;
				UInt32 GenerateHashValue (void) const override;
		};

		bool									m_useIDs;

		GridLineID								m_nextMainLineID;			// current maximal main line ID in main direction
		GridLineID								m_nextSecondaryLineID;		// current maximal main line ID in secondary direction

		GS::ConstSharedPtr<GridMeshPolygon>
												m_lowerLeftPoly;
		GS::ConstSharedPtr<GridMeshPolygon>
												m_lowerRightPoly;

		GridMeshLineStore						m_meshLinesMainAxis;		// lines in main axis
		GridMeshLineStore						m_meshLinesSecondaryAxis;	// lines in secondary axis
		GridElemIDToElem<GridMeshVertex>		m_meshVertices;				// 3D points
		GridElemIDToElem<GridMeshPolygon>		m_meshPolygons;				// polygons
		GridElemIDToElem<GridMeshEdge>			m_meshEdgesMainAxis;
		GridElemIDToElem<GridMeshEdge>			m_meshEdgesSecondaryAxis;


		GS::HashTable<GridMeshEdge, GridElemID>		m_mainEdgeToID;
		GS::HashTable<GridMeshEdge, GridElemID>		m_secondaryEdgeToID;
		GS::HashTable<Coord3DWrapper, GridElemID>	m_coord3DToID;				// used only if not using IDs (offseted mesh)
		GridElemID									m_coordVertNextId;

		GS::SharedPtr<GridMeshVertex>	m_cornerPoints[4];			// lower left, lower right, upper right and upper left points
	public:
	// flags of the grid lines
		enum GridLineFlags {
				MainAxisGridLine		= 0x00000001,				// this grid line is grid in the main direction
				SecondaryAxisGridLine	= 0x00000002,				// this grid line is grid in the secondary direction
				CustomGridLine			= 0x00000004,				// ... is a custom grid line
				AutomaticGridLine		= 0x00000008				// ... is not a custom grid line
			};

		// -------- constructors, destructor-------------------------------------
		GridMesh	(bool useIDs = true);		// set useIDs=false for offseted mesh
		GridMesh	(const GridMesh& source);
		~GridMesh	(void);
		void					Clear (); 

		// -------------------- general member functions --------------------

		GridMesh&				operator= (const GridMesh& source);

		void					Reset (void);
		bool					UsesIDs (void) const { return m_useIDs; };

		bool					IsValidLineID (bool mainDir, GridLineID inID) const;
		bool					IsValidEdgeID (bool mainDir, GridElemID inID) const;
		bool					IsValidPolygonID (GridElemID inID) const;

		Vector3D				GetNormal (void) const;					//normal of the first polygon!

		GS::ConstSharedPtr<GridMeshVertex>
								GetVertex (GridElemID inID)			const;
		GS::SharedPtr<GridMeshVertex>
								GetVertex (GridElemID inID);
		void					DeleteVertex (GridElemID inID);

		UInt32					GetVertexCount (void)				const;
		UInt32					GetPolygonCount (void)				const;
		UInt32					GetEdgeCount (bool mainDir)			const;
		GS::SharedPtr<GridMeshEdge>
								GetEdge (bool mainDir, GridElemID inID);
		GS::ConstSharedPtr<GridMeshEdge>
								GetEdge (bool mainDir, GridElemID inID)		const;
		void					DeleteEdge (bool mainDir, GridElemID inID);

		GS::SharedPtr<GridMeshPolygon>
								GetPolygon (GridElemID inID);
		GS::ConstSharedPtr<GridMeshPolygon>
								GetPolygon (GridElemID inID)	const;

		GS::SharedPtr<GridMeshPolygon>
								FindPolygon (GridElemID inID);
		GS::ConstSharedPtr<GridMeshPolygon>
								FindPolygon (GridElemID inID)	const;

		void					DeletePolygon (GridElemID inID);

		GridElemID				GetLowerLeftPolygonID (void)	 const;
		GridElemID				GetLowerRightPolygonID (void) const;
		void					SetLowerLeftPolygonID (GridElemID id);
		void					SetLowerRightPolygonID (GridElemID id);

		UInt32					GetLineCount (bool mainDir)				const;

		GS::SharedPtr<GridMeshLine>
								GetLine (bool mainDir, GridLineID inID);
		GS::ConstSharedPtr<GridMeshLine>		
								GetLine (bool mainDir, GridLineID inID)	const;
		GridLineID				GetNextLineID (bool mainDir) const;
		void					DeleteLine (bool mainDir, GridLineID inID);

		void					LineIDsChanged (bool mainDir);			// can throw

		void					UpdateCornerInfos ();
		GS::ConstSharedPtr<GridMeshVertex>
								GetCornerVertex (unsigned char inIndex) const;

		void					AddVertex (GridLineID mainID, GridLineID secID, const Coord& param, const Coord3D& coord);
		bool					AddLine (UInt32 userData, Int32 patternInd, GridLineID* newId);
		GridElemID				GetDelGridElemID (const GridLineID lineID, const bool mainDir) const;
		bool					IsLineLastPoly (const GridLineID lineID, const bool mainDir) const;
		bool					GetLineAtParam (bool mainDir, double inParam, GridMeshLine* outLn) const;
		bool					GetNeighbourLines (bool mainDir, double inParam, GS::SharedPtr<Geometry::GridMeshLine>& outLn1, GS::SharedPtr<Geometry::GridMeshLine>& outLn2);
		bool					GetNeighbourLines (bool mainDir, double inParam, GS::ConstSharedPtr<Geometry::GridMeshLine>& outLn1, GS::ConstSharedPtr<Geometry::GridMeshLine>& outLn2) const;
		UInt32					CreatePolygon  (GridLineID mainLineID, GridLineID secLineID, GS::PagedArray<Coord>& params, GS::PagedArray<Coord3D>& coords);
		void					GetSortedLines (GS::PagedArray<GridMeshLine>& mainLines, GS::PagedArray<GridMeshLine>& secLines) const;
		void					CreatePolygonsAndEdges ();			// can throw
		GridElemID				CreatePolygonFromPoints  (const Coord3D& lowerLeft, const Coord3D& lowerRight, const Coord3D& upperRight, const Coord3D& upperLeft);
		bool					MakePolygon (GridElemID leftPolyID, GridElemID newPolyID, GridElemID rightPolyID,
											GridElemID lowerLeftPolyID, GridElemID lowerPolyID, GridElemID lowerRightPolyID,
											GridElemID upperLeftPolyID, GridElemID upperPolyID, GridElemID upperRightPolyID);
		bool					ResizePolygon (GridElemID polyID, GridElemID newLowerRightID, GridElemID newUpperRightID, GridElemID newUpperLeftID);

		void					OffsetSurfaceParams (double horizontalOffset);

		void					Transform (const TRANMAT& tran);
		void					Scale (double scaleFactor);
		void					CellCoordToParam (GridElemID polyID, const Coord& coord, Coord* paramCoord) const;
		void					CellCoordToCoord3D (GridElemID polyID, const Coord& coord, Coord3D* coord3D) const;
		bool					Coord3DToCellCoord (GridElemID polyID, const Coord3D& c, Coord* cellRelative) const;
		GridLineID				IsOnLine (const Coord& surfaceCoord, bool main) const;
		GridElemID				GetPolygonID (const Coord& surfaceCoord) const;

		GS::ConstSharedPtr<GridMeshVertex>
								GetCornerPoint (UInt32 idx) const;

		ConstIterator			Begin (UInt32 flags) const;					// can throw
		ConstIterator			Enumerate (UInt32 flags) const;				// can throw
		ConstIterator			End (UInt32 flags) const;					// can throw

		GSErrCode				Read (GS::IChannel& ic);
		GSErrCode				Write (GS::OChannel& oc, ULong version) const;
		GSErrCode				WriteXML (GS::XMLOChannel& oc) const;

#ifdef DEBUVERS
		bool					Check () const;
#endif
	private:
		void					ConstructFrom (const GridMesh& source);
		void					UpdateCornerInfos (GS::PagedArray<GridMeshLine>& sortedMainLines, GS::PagedArray<GridMeshLine>& sortedSecLines);

		GridElemID				AddMainEdge (GridElemID newID, GridElemID begC, GridElemID endC, UInt32 userData);
		GridElemID				AddMainEdge (GridLineID mainID, GridLineID secID, GridElemID begC, GridElemID endC, UInt32 userData);
		GridElemID				AddSecondaryEdge (GridElemID newID, GridElemID begC, GridElemID endC,  UInt32 userData);
		GridElemID				AddSecondaryEdge (GridLineID mainID, GridLineID secID, GridElemID begC, GridElemID endC,  UInt32 userData);

		void					ReadVersion1 (GS::IChannel& ic);			// can throw
		void					WriteVersion1 (GS::OChannel& oc) const;		// can throw
};


// *****************************************************************************
// Iterator class for GridmeshLines
// *****************************************************************************

class GEOMETRY_DLL_EXPORT GridMesh::ConstIterator
{
	private:
		Int32											current;
		GS::PagedArray<const GridMeshLine*, 16>				filteredData;

	public:
		class X {};

		ConstIterator	(const GridMesh& gridMesh, Int32 idx, UInt32 flags);			// can throw

		Int32 GetCurrent () const											{ return current; }
		ULong GetElemNum () const											{ return filteredData.GetSize (); }

		const GridMeshLine&		operator*  () const									{ return *filteredData[current]; }
		const GridMeshLine*		operator-> () const									{ return filteredData[current]; }
		const GridMeshLine&		operator[] (Int32 offset) const						{ return *filteredData[current + offset]; }

		ConstIterator&	operator++ ();
		ConstIterator&	operator-- ();

		ConstIterator	operator+  (Int32 offset) const;					// can throw
		ConstIterator	operator-  (Int32 offset) const;					// can throw
		Int32			operator-  (const ConstIterator& rightOp) const		{ return current - rightOp.current; }

		const ConstIterator&	operator+= (Int32 offset);
		const ConstIterator&	operator-= (Int32 offset);

		ConstIterator&	ToFirst ()									{ current = 0; return *this; }
		ConstIterator&	ToLast ()									{ current = filteredData.GetSize () - 1; return *this; }

		bool		operator== (const ConstIterator& rightOp) const;
		bool		operator!= (const ConstIterator& rightOp) const;
		bool		operator<  (const ConstIterator& rightOp) const;
		bool		operator<= (const ConstIterator& rightOp) const;
		bool		operator>  (const ConstIterator& rightOp) const;
		bool		operator>= (const ConstIterator& rightOp) const;

		bool		operator== (const X*) const								{ return current < 0 || current >= Int32 (filteredData.GetSize ()); }
		bool		operator!= (const X*) const								{ return current >= 0 && current < Int32 (filteredData.GetSize ()); }
};

inline GridMesh::ConstIterator& GridMesh::ConstIterator::operator++ ()
{
	PRECOND (current < Int32 (filteredData.GetSize ()));

	current++;
	return *this;
}


inline GridMesh::ConstIterator& GridMesh::ConstIterator::operator-- ()
{
	PRECOND (current >= 0);

	current--;
	return *this;
}


}

#endif
