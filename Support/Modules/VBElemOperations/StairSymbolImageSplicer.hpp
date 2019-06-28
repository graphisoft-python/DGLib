#ifndef __STAIR_SYMBOL_IMAGE_SPLICER_HPP__
#define __STAIR_SYMBOL_IMAGE_SPLICER_HPP__

// from GSRoot
#include "HashTable.hpp"
#include "Object.hpp"
#include "Md5.hpp"

// from ObjectDatabase
#include "ODBObject.hpp"

// from VectorImage
#include "VectorImage.hpp"

// from VBElements
#include "VBElements/Stair.hpp"
#include "VBElements/Symb.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"
#include "StairBreakMarkDescription.hpp"
#include "StairDrawingContext.hpp"
#include "GDLGlobalCalculations.hpp"



namespace VBCalculations
{

struct BreakMarkCalcData;

struct VB_ELEM_OPERATIONS_DLL_EXPORT StairSymbolImageSplicePart : public GS::Object
{
DECLARE_CLASS_INFO
public:
	enum SymbType {
		Grid,
		BreakMark,
		WalkingLine,
		Numbering,
		UpDownText,
		Description,
		TreadAccessories,
		Structure,
	};

public:
	VectorImage				image;
	TRANMAT					imageTransform;
	VBElem::SymbConstRef	symbConstRef;
	short					layer;
	SymbType				symbType;
	double					sideBoundaryEdgeOffset;
	double					nonBreakMarkEdgeOffset;
	bool					missing;

public:
	StairSymbolImageSplicePart ();

public:
	virtual Object*			Clone (void) const override;
	virtual GSErrCode		Read (GS::IChannel& ic) override;
	virtual GSErrCode		Write (GS::OChannel& oc) const override;

private:
	GSErrCode ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

};


class VB_ELEM_OPERATIONS_DLL_EXPORT StairSymbolImageSplicer /* final */
{
public:
	enum CutType {
		NoCut,
		ToLowerPart,
		ToMiddlePart,
		ToUpperPart,
		ToEntireStair
	};

	typedef GS::Pair<CutType,StairSymbolImageSplicePart>												PartWithCutType;

private:
	typedef GS::HashTable<StairDrawingContext::StairDrawAttributeSet, StairSymbolImageSplicePart>		GridTable;
	typedef GS::Array<PartWithCutType>																	DrawingParts;

public:
	typedef GS::HashTable<StairBreakMarkDescription::BreakMarkPosition, Geometry::Polyline2D>			BreakMarkTable;

	typedef GS::Ref<GridTable>																			GridTableRef;
	typedef GS::Ref<DrawingParts>																		DrawingPartsRef;

	enum ExistingCutPart {
		AnyPart,
		LowerPart,
		MiddlePart,
		UpperPart,
		EntireStair
	};

	enum SplicerDataSource {
		FromScreenStair,
		FromDrwStair
	};

	class VB_ELEM_OPERATIONS_DLL_EXPORT Data : public ODB::Object {
	DECLARE_DYNAMIC_CLASS_INFO (Data)
	
	#define StairSymbolImageSplicer_Data_MEMBERS														\
	private:																							\
		GS::Array<StairSymbolImageSplicePart>	m_cutSymbolsSpliced;									\
		VBElem::StairPolygon					m_lowerCutPolygon;										\
		VBElem::StairPolygon					m_middleCutPolygon;										\
		VBElem::StairPolygon					m_upperCutPolygon;

	StairSymbolImageSplicer_Data_MEMBERS

		class IsolatedState : public ODB::Object::IsolatedState
		{
		private:
			friend class Data;
			StairSymbolImageSplicer_Data_MEMBERS

		public:
			virtual ~IsolatedState ();
		};

	public:
		Data ();
		virtual ~Data ();

	public:
		virtual Data*										Clone (void) const override;
		virtual	GSErrCode									StoreIsolatedState (ODB::Object::IsolatedState* iState) const override;
		virtual	GSErrCode									RestoreIsolatedState (const ODB::Object::IsolatedState* iState) override;
		virtual	void										Isolate (void) override;
		virtual	ODB::Object::IsolatedState*					CreateIsolatedState (void) const override;
		virtual USize										GetIsolatedSize (void) const override;
		virtual	GSErrCode									WriteIsolatedState (GS::OChannel& oc) const override;
		virtual	GSErrCode									ReadIsolatedState (GS::IChannel& ic) override;

	private:
		GSErrCode											WriteIsolatedStateVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
		GSErrCode											ReadIsolatedStateVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);

		void												Clear (void);
	public:
		const GS::Array<StairSymbolImageSplicePart>&		GetCutSymbolsSpliced () const;
		GS::Array<StairSymbolImageSplicePart>&				GetCutSymbolsSpliced ();

		const VBElem::StairPolygon&							GetLowerCutPolygon () const;
		VBElem::StairPolygon&								GetLowerCutPolygon ();

		const VBElem::StairPolygon&							GetMiddleCutPolygon () const;
		VBElem::StairPolygon&								GetMiddleCutPolygon ();

		const VBElem::StairPolygon&							GetUpperCutPolygon () const;
		VBElem::StairPolygon&								GetUpperCutPolygon ();
	};

public:
	static GridTableRef			CreateGridTable ();
	static DrawingPartsRef		CreateDrawingParts ();

private:
	VBElem::StairConstRef								m_stairRef;
	bool												m_isReflectedCeilingPlanDisplay;
	VBCalculations::GDLGlobalCalcEnvir					m_gdlCalcEnvir;
	GridTableRef										m_gridTable;
	BreakMarkTable										m_breakMarkTable;
	StairSymbolImageSplicePart							m_breakMarksImage;
	DrawingPartsRef										m_stairSymbsToCut;

	VBElem::StairGridType								m_stairGridTypeToDraw;
	SplicerDataSource									m_splicerDataSource;

	bool												m_cuttingPolygonsPresent;
	bool												m_spliceDone;

	ODB::Ref<Data>										m_data;
	ODB::ConstRef<Data>									m_dataCached;

	bool												m_cacheSplicer;
	StairBreakMarkDescription							m_breakMarkDescription;
	MD5::FingerPrint									m_archicadStateChecksum;

//	GS::Lock				m_resultLock;
private:
	StairSymbolImageSplicer (VBElem::StairConstRef stairRef, const SplicerDataSource splicerDataSource, ODB::ConstRef<Data> cachedData);
public:
	StairSymbolImageSplicer (VBElem::StairConstRef stairRef,
							 const bool isReflectedCeilingPlanDisplay,
							 const SplicerDataSource splicerDataSource,
							 const VBCalculations::GDLGlobalCalcEnvir& gdlCalcEnvir,
							 GridTableRef stairGridParts,
							 const StairSymbolImageSplicePart& breakMarksImage,
							 DrawingPartsRef stairSymbsToCut,
							 const MD5::FingerPrint& archicadStateChecksum,
							 const bool cacheSplicer = true);
	~StairSymbolImageSplicer ();

private:
	void	FillData ();
	void	CalculateBreakMarks ();
	bool	CalculateCuttingPolygons ();
	void	CutImageIfNessecary (const VectorImage& original, ExistingCutPart part, VectorImage& result, const bool clearIfNotExisting = false, const bool forgiving = false, const double offsetSideEdges = 0.0, const double offsetNonBreakMarkEdges = 0.0) const;
	bool	GetBreakMarkLine (const StairBreakMarkDescription::BreakMarkPosition breakMarkPosition, GS::Array<BreakMarkCalcData>& breakMarks) const;
	void	SpliceGrid ();
	void	RemoveLinesUnderBreakMarks (VectorImage& image);
	void	SpliceBreakMark ();
	void	SpliceCutSymbols ();
	void	FreeUnnecessaryData ();
	void	SetDrawingOrder ();
	void	CacheSplicedDataIfNeeded ();
	void	Splice () const; //Lazy evaluation, logical const

public:
	bool											HasCutPart (ExistingCutPart part, const bool forgiving = false) const;
	StairDrawingContext::StairDrawAttributeSet		StairPartAttributeSet (ExistingCutPart part) const;
	StairSymbolImageSplicePart&						GetSplicePart (ExistingCutPart part);
public:
	void	EnumerateSplicedSymbols (std::function<void (const VectorImage&, VBElem::SymbConstRef, const TRANMAT&, const short&, const bool)> callback) const;
	
	VectorImage	GetSplicedGridSymbolImage () const;

public:
	static ODB::Id							GetContentId (VBElem::StairConstRef stairRef, const VBCalculations::GDLGlobalCalcEnvir& gdlCalcEnvir, SplicerDataSource splicerDataSource, const MD5::FingerPrint& archicadStateChecksum);
	static GS::Ref<StairSymbolImageSplicer>	GetCachedSplicerIfExists (VBElem::StairConstRef stairRef, const VBCalculations::GDLGlobalCalcEnvir& gdlCalcEnvir, SplicerDataSource splicerDataSource, const MD5::FingerPrint& archicadStateChecksum);
};


VB_ELEM_OPERATIONS_DLL_EXPORT bool												StairHasCutPart (VBElem::StairGridType gridType, StairSymbolImageSplicer::ExistingCutPart part, const bool lowerBreakMarkValid, const bool upperBreakMarkValid);
VB_ELEM_OPERATIONS_DLL_EXPORT StairDrawingContext::StairDrawAttributeSet		StairPartAttributeSet (VBElem::StairGridType gridType, StairSymbolImageSplicer::ExistingCutPart part, const bool lowerBreakMarkValid, const bool upperBreakMarkValid);
}

#endif // __STAIR_SYMBOL_IMAGE_SPLICER_HPP__