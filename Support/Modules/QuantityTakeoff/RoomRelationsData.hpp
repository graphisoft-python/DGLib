// *********************************************************************************************************************
// Description:		Ez majd valami szep helyre at lesz rakva!
//
// Module:
// Namespace:
// Contact person:	TaB
//
// SG compatible
// *********************************************************************************************************************

#ifndef ROOMRELATIONSDATA_HPP
#define ROOMRELATIONSDATA_HPP

#include "QuantityTakeoffExport.hpp"
#include "ODBReference.hpp"
#include "Polygon2D.hpp"
#include "GeneralElem.hpp"

namespace EDB {
	typedef ODB::ConstRef<GeneralElem> GeneralElemConstRef;
}

namespace RoomRelations
{
	class QUANTITYTAKEOFF_DLL_EXPORT ElemData
	{
	private:
		EDB::GeneralElemConstRef	elem;
		Int32						roomEdge;	// index of the room polygon edge adjacent to the wall
		double						tBeg;
		double						tEnd;
		UInt32						flag;
	public:
		ElemData () : elem (nullptr), roomEdge (0), tBeg (0.0), tEnd (0.0), flag (0)
		{
		}

		ElemData (EDB::GeneralElemConstRef inElem, Int32 inRoomEdge, double inTBeg, double inTEnd, UInt32 inFlag) : elem (inElem), roomEdge (inRoomEdge), tBeg (inTBeg), tEnd (inTEnd), flag (inFlag)
		{
		}

		EDB::GeneralElemConstRef	GetElem ()		const { return elem; }
		Int32						GetEdgeID ()	const { return roomEdge; }
		double						GetBegT ()		const { return tBeg; }
		double						GetEndT ()		const { return tEnd; }
		UInt32						GetFlag ()		const { return flag; }

		GSErrCode	Read (GS::IChannel& ic)
		{
			GSErrCode err = elem.ReadRef (ic);
			if (err == NoError)
				err = ic.Read (roomEdge);
			if (err == NoError)
				err = ic.Read (tBeg);
			if (err == NoError)
				err = ic.Read (tEnd);
			if (err == NoError)
				err = ic.Read (flag);
			return err;
		}

		GSErrCode Write (GS::OChannel& oc) const
		{
			GSErrCode err = elem.WriteRef (oc);
			if (err == NoError)
				err = oc.Write (roomEdge);
			if (err == NoError)
				err = oc.Write (tBeg);
			if (err == NoError)
				err = oc.Write (tEnd);
			if (err == NoError)
				err = oc.Write (flag);
			return err;
		}

		bool operator == (const ElemData& other)
		{
			return (elem == other.elem &&
					roomEdge == other.roomEdge &&
					Geometry::IsNear (tBeg, other.tBeg) &&
					Geometry::IsNear (tEnd, other.tEnd) &&
					flag == other.flag);
		}

		bool operator != (const ElemData& other)
		{
			return !(*this == other);
		}
	};


	class QUANTITYTAKEOFF_DLL_EXPORT Niche // As API_Niche
	{
	private:
		Geometry::Polygon2D		polygon;
		double					height;

	public:
		Niche (Geometry::Polygon2D inPolygon, double inHeight) : polygon (inPolygon), height (inHeight)
		{
		}

		Geometry::Polygon2D		GetPolygon ()	const { return polygon; }
		double					GetHeight ()	const { return height; }
	};


	class QUANTITYTAKEOFF_DLL_EXPORT RoomRelationData	// As API_RoomRelation
	{
		GS::Array<ElemData>					wallParts;
		GS::Array<GS::Guid>					columns;
		GS::Array<GS::Guid>					objects;
		GS::Array<GS::Guid>					lamps;
		GS::Array<GS::Guid>					windows;
		GS::Array<GS::Guid>					doors;
		GS::Array<Niche>					niches;
		GS::Array<ElemData>					beamParts;
		GS::Array<GS::Guid>					curtainWalls;
		GS::Array<GS::Guid>					cwFrames;
		GS::Array<GS::Guid>					cwPanels;
		GS::Array<GS::Guid>					cwJunctions;
		GS::Array<GS::Guid>					cwAccessories;
		GS::Array<ElemData>					cwSegmentParts;
		GS::Array<GS::Guid>					skylights;
		GS::Array<GS::Guid>					roofs;
		GS::Array<GS::Guid>					shells;
		GS::Array<GS::Guid>					morphs;
		GS::Array<GS::Guid>					stairs;
		GS::Array<GS::Guid>					risers;
		GS::Array<GS::Guid>					treads;
		GS::Array<GS::Guid>					stairStructures;
		GS::Array<GS::Guid>					railings;
		GS::Array<GS::Guid>					toprails;
		GS::Array<GS::Guid>					handrails;
		GS::Array<GS::Guid>					rails;
		GS::Array<GS::Guid>					railingPosts;
		GS::Array<GS::Guid>					innerPosts;
		GS::Array<GS::Guid>					balusters;
		GS::Array<GS::Guid>					railingPanels;
		GS::Array<GS::Guid>					railingSegments;
		GS::Array<GS::Guid>					toprailEnds;
		GS::Array<GS::Guid>					handrailEnds;
		GS::Array<GS::Guid>					railEnds;
		GS::Array<GS::Guid>					toprailConnections;
		GS::Array<GS::Guid>					handrailConnections;
		GS::Array<GS::Guid>					railConnections;
		GS::Array<GS::Guid>					railingNodes;

	public:
		RoomRelationData ();
		virtual ~RoomRelationData ();

		Int32	GetWallPartCount ()				const { return wallParts.GetSize (); }
		Int32	GetColumnCount ()				const { return columns.GetSize (); }
		Int32	GetObjectCount ()				const { return objects.GetSize (); }
		Int32	GetLampCount ()					const { return lamps.GetSize (); }
		Int32	GetWindowsCount ()				const { return windows.GetSize (); }
		Int32	GetDoorCount ()					const { return doors.GetSize (); }
		Int32	GetNicheCount ()				const { return niches.GetSize (); }
		Int32	GetBeamCount ()					const { return beamParts.GetSize (); }
		Int32	GetCurtainWallCount ()			const { return curtainWalls.GetSize (); }
		Int32	GetCWFramesCount ()				const { return cwFrames.GetSize (); }
		Int32	GetCWPanelsCount ()				const { return cwPanels.GetSize (); }
		Int32	GetCWJunctionCount ()			const { return cwJunctions.GetSize (); }
		Int32	GetCWAccessoryCount ()			const { return cwAccessories.GetSize (); }
		Int32	GetCWSegmentCount ()			const { return cwSegmentParts.GetSize (); }
		Int32	GetSkylightCount ()				const { return skylights.GetSize (); }
		Int32	GetRoofCount ()					const { return roofs.GetSize (); }
		Int32	GetShellCount ()				const { return shells.GetSize (); }
		Int32	GetMorphCount ()				const { return morphs.GetSize (); }
		Int32	GetStairCount ()				const { return stairs.GetSize (); }
		Int32	GetRiserCount ()				const { return risers.GetSize (); }
		Int32	GetTreadCount ()				const { return treads.GetSize (); }
		Int32	GetStairStructureCount ()		const { return stairStructures.GetSize (); }
		Int32	GetRailingCount ()				const { return railings.GetSize (); }
		Int32	GetToprailCount ()				const { return toprails.GetSize (); }
		Int32	GetHandrailCount ()				const { return handrails.GetSize (); }
		Int32	GetRailCount ()					const { return rails.GetSize (); }
		Int32	GetRailingPostCount ()			const { return railingPosts.GetSize (); }
		Int32	GetInnerPostCount ()			const { return innerPosts.GetSize (); }
		Int32	GetBalusterCount ()				const { return balusters.GetSize (); }
		Int32	GetRailingPanelCount ()			const { return railingPanels.GetSize (); }
		Int32	GetRailingSegmentCount ()		const { return railingSegments.GetSize (); }
		Int32	GetToprailEndCount ()			const { return toprailEnds.GetSize (); }
		Int32	GetHandrailEndCount ()			const { return handrailEnds.GetSize (); }
		Int32	GetRailEndCount ()				const { return railEnds.GetSize (); }
		Int32	GetToprailConnectionCount ()	const { return toprailConnections.GetSize (); }
		Int32	GetHandrailConnectionCount ()	const { return handrailConnections.GetSize (); }
		Int32	GetRailConnectionCount ()		const { return railConnections.GetSize (); }
		Int32	GetRailingNodesCount ()			const { return railingNodes.GetSize (); }

		void	AddWallPart (const ElemData& wallPart) { wallParts.Push (wallPart); }
		void	AddColumn (const GS::Guid& column) { columns.Push (column); }
		void	AddObject (const GS::Guid& object) { objects.Push (object); }
		void	AddLamp (const GS::Guid& lamp) { lamps.Push (lamp); }
		void	AddWindow (const GS::Guid& window) { windows.Push (window); }
		void	AddDoor (const GS::Guid& door) { doors.Push (door); }
		void	AddNiche (const Niche& niche) { niches.Push (niche); }
		void	AddBeamPart (const ElemData& beamPart) { beamParts.Push (beamPart); }
		void	AddCW (const GS::Guid& curtainWall) { curtainWalls.Push (curtainWall); }
		void	AddCWFrame (const GS::Guid& cwFrame) { cwFrames.Push (cwFrame); }
		void	AddCWPanel (const GS::Guid& cwPanel) { cwPanels.Push (cwPanel); }
		void	AddCWJunction (const GS::Guid& cwJunction) { cwJunctions.Push (cwJunction); }
		void	AddCWAccessory (const GS::Guid& cwAccessory) { cwAccessories.Push (cwAccessory); }
		void	AddCWSegment (const ElemData& cwSegment) { cwSegmentParts.Push (cwSegment); }
		void	AddSkylight (const GS::Guid& skylight) { skylights.Push (skylight); }
		void	AddRoof (const GS::Guid& roof) { roofs.Push (roof); }
		void	AddShell (const GS::Guid& shell) { shells.Push (shell); }
		void	AddMorph (const GS::Guid& morph) { morphs.Push (morph); }
		void	AddStair (const GS::Guid& stair) { stairs.Push (stair); }
		void	AddRiser (const GS::Guid& riser) { risers.Push (riser); }
		void	AddTread (const GS::Guid& tread) { treads.Push (tread); }
		void	AddStairStructure (const GS::Guid& stairStructure) { stairStructures.Push (stairStructure); }
		void	AddRailing (const GS::Guid& railing) { railings.Push (railing); }
		void	AddToprail (const GS::Guid& toprail) { toprails.Push (toprail); }
		void	AddHandrail (const GS::Guid& handrail) { handrails.Push (handrail); }
		void	AddRail (const GS::Guid& rail) { rails.Push (rail); }
		void	AddRailingPost (const GS::Guid& railingPost) { railingPosts.Push (railingPost); }
		void	AddInnerPost (const GS::Guid& innerPost) { innerPosts.Push (innerPost); }
		void	AddBaluster (const GS::Guid& baluster) { balusters.Push (baluster); }
		void	AddRailingPanel (const GS::Guid& railingPanel) { railingPanels.Push (railingPanel); }
		void	AddRailingSegment (const GS::Guid& railingSegment) { railingSegments.Push (railingSegment); }
		void	AddToprailEnd (const GS::Guid& toprailEnd) { toprailEnds.Push (toprailEnd); }
		void	AddHandrailEnd (const GS::Guid& handrailEnd) { handrailEnds.Push (handrailEnd); }
		void	AddRailEnd (const GS::Guid& railEnd) { railEnds.Push (railEnd); }
		void	AddToprailConnection (const GS::Guid& toprailConnection) { toprailConnections.Push (toprailConnection); }
		void	AddHandrailConnection (const GS::Guid& handrailConnection) { handrailConnections.Push (handrailConnection); }
		void	AddRailConnection (const GS::Guid& railConnection) { railConnections.Push (railConnection); }
		void	AddRailingNode (const GS::Guid& railingNode) { railingNodes.Push (railingNode); }

		const GS::Array<ElemData>&					GetWallPartArray ()				const { return wallParts; }
		const GS::Array<GS::Guid>&					GetColumnArray ()				const { return columns; }
		const GS::Array<GS::Guid>&					GetObjectArray ()				const { return objects; }
		const GS::Array<GS::Guid>&					GetLampArray ()					const { return lamps; }
		const GS::Array<GS::Guid>&					GetWindowArray ()				const { return windows; }
		const GS::Array<GS::Guid>&					GetDoorArray ()					const { return doors; }
		const GS::Array<Niche>&						GetNicheArray ()				const { return niches; }
		const GS::Array<ElemData>&					GetBeamPartArray ()				const { return beamParts; }
		const GS::Array<GS::Guid>&					GetCWArray ()					const { return curtainWalls; }
		const GS::Array<GS::Guid>&					GetCWFrameArray ()				const { return cwFrames; }
		const GS::Array<GS::Guid>&					GetCWPanelArray ()				const { return cwPanels; }
		const GS::Array<GS::Guid>&					GetCWJunctionArray ()			const { return cwJunctions; }
		const GS::Array<GS::Guid>&					GetCWAccessoryArray ()			const { return cwAccessories; }
		const GS::Array<ElemData>&					GetCWSegmentArray ()			const { return cwSegmentParts; }
		const GS::Array<GS::Guid>&					GetSkylightArray ()				const { return skylights; }
		const GS::Array<GS::Guid>&					GetRoofArray ()					const { return roofs; }
		const GS::Array<GS::Guid>&					GetShellArray ()				const { return shells; }
		const GS::Array<GS::Guid>&					GetMorphArray ()				const { return morphs; }
		const GS::Array<GS::Guid>&					GetStairArray ()				const { return stairs; }
		const GS::Array<GS::Guid>&					GetRiserArray ()				const { return risers; }
		const GS::Array<GS::Guid>&					GetTreadArray ()				const { return treads; }
		const GS::Array<GS::Guid>&					GetStairStructureArray ()		const { return stairStructures; }
		const GS::Array<GS::Guid>&					GetRailingArray ()				const { return railings; }
		const GS::Array<GS::Guid>&					GetToprailArray ()				const { return toprails; }
		const GS::Array<GS::Guid>&					GetHandrailArray ()				const { return handrails; }
		const GS::Array<GS::Guid>&					GetRailArray ()					const { return rails; }
		const GS::Array<GS::Guid>&					GetRailingPostArray ()			const { return railingPosts; }
		const GS::Array<GS::Guid>&					GetInnerPostArray ()			const { return innerPosts; }
		const GS::Array<GS::Guid>&					GetBalusterArray ()				const { return balusters; }
		const GS::Array<GS::Guid>&					GetRailingPanelArray ()			const { return railingPanels; }
		const GS::Array<GS::Guid>&					GetRailingSegmentArray ()		const { return railingSegments; }
		const GS::Array<GS::Guid>&					GetToprailEndArray ()			const { return toprailEnds; }
		const GS::Array<GS::Guid>&					GetHandrailEndArray ()			const { return handrailEnds; }
		const GS::Array<GS::Guid>&					GetRailEndArray ()				const { return railEnds; }
		const GS::Array<GS::Guid>&					GetToprailConnectionArray ()	const { return toprailConnections; }
		const GS::Array<GS::Guid>&					GetHandrailConnectionArray ()	const { return handrailConnections; }
		const GS::Array<GS::Guid>&					GetRailConnectionArray ()		const { return railConnections; }
		const GS::Array<GS::Guid>&					GetRailingNodeArray ()			const { return railingNodes; }

		bool	Contains (const GS::Guid& elemGuid);
	};
} // namespace


namespace GS
{
	QUANTITYTAKEOFF_DLL_EXPORT GSErrCode Read (GS::IChannel& ic, RoomRelations::ElemData& elemData);
	QUANTITYTAKEOFF_DLL_EXPORT GSErrCode Write (GS::OChannel& oc, const RoomRelations::ElemData& elemData);
} // namespace

#endif
