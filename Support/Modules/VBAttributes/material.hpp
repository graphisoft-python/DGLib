// *****************************************************************************
// Material attribute
// VBAttributes, platform-independent
//
// Namespaces:        Contact person:
//	Material				CSF
//	MaterialField			CSF
//	MaterialFieldMask		CSF
//	MaterialObserver		CSF
//	MaterialChanges			CSF
//	MaterialSet				CSF
//	MaterialSetObserver	CSF
//
// [SG compatible]
// *****************************************************************************

#if !defined (MATERIAL_HPP)
#define MATERIAL_HPP

#pragma once

//============================ Includes =================================

#include	"GSPix.h"
#include	"VBAttributesEnv.hpp"
#include	"generalattribute.hpp"
#include	"AttributeTypeSet.hpp"

//===================== Begin of the VBAttr namespace =====================

namespace VBAttr {

//========================== Definitions ================================

//========================= Class Material  =============================

#define IMAGE_ATTRIBUTES															\
	short		mtype;			/* material type					[0..7]		*/	\
	GS_RGBColor	surfaceRGB;		/* surface color								*/	\
	short		ambientPc;		/* ambient reflection				[0..100]	*/	\
	short		diffusePc;		/* diffuse reflection				[0..100]	*/	\
	short		specularPc;		/* specular reflection				[0..100]	*/	\
	short		transpPc;		/* transparency						[0..100]	*/	\
	short		shine;			/* shininess * 100					[0..10000]	*/	\
	short		transpAtt;		/* transparency attenuation * 100	[0..400]	*/	\
	GS_RGBColor	specularRGB;	/* specular color								*/	\
	GS_RGBColor	emissionRGB;	/* emission color								*/	\
	short		emissionAtt;	/* emission attenuation * 100		[0..65535]	*/

#define MATERIAL_HAS_TEXTURE  0x1000  /* 0001000000000000 */

//-----------------------------------------------------------------------

class MaterialObserver;
class MaterialSet;

class VBATTRIBUTES_DLL_EXPORT Material : public ADB::GeneralAttribute {
	DECLARE_DYNAMIC_CLASS_INFO (Material)

public:
		// constants

	enum Fields {
		MaterialType			= ADB::GeneralAttribute::Last + 1,	// First field in Material
		SurfaceColor			= ADB::GeneralAttribute::Last + 2,
		AmbientPercentage		= ADB::GeneralAttribute::Last + 3,
		DiffuseAlbedo			= ADB::GeneralAttribute::Last + 4,
		SpecularAlbedo			= ADB::GeneralAttribute::Last + 5,
		Transparency			= ADB::GeneralAttribute::Last + 6,
		Shininess				= ADB::GeneralAttribute::Last + 7,
		TransparencyAttenuation	= ADB::GeneralAttribute::Last + 8,
		SpecularColor			= ADB::GeneralAttribute::Last + 9,
		EmissionColor			= ADB::GeneralAttribute::Last + 10,
		EmissionAttenuation		= ADB::GeneralAttribute::Last + 11,
		FillIndex				= ADB::GeneralAttribute::Last + 12,
		TextureName				= ADB::GeneralAttribute::Last + 13,
		TextureStatus			= ADB::GeneralAttribute::Last + 14,
		FillColor				= ADB::GeneralAttribute::Last + 15,
		TextureWidth			= ADB::GeneralAttribute::Last + 16,
		TextureHeight			= ADB::GeneralAttribute::Last + 17,
		TextureRotationAngle	= ADB::GeneralAttribute::Last + 18,	// Last field in Material
		Last					= ADB::GeneralAttribute::Last + 18
	};

#define _MATERIAL_DATA_MEMBERS_																		\
private:																							\
		/* data members */																			\
																									\
	IMAGE_ATTRIBUTES																				\
	short			ifill;			/* fill index */												\
	GS::UniString	texName;		/* name of the texture */										\
	short			texStatus;		/* texture status */											\
	short			fillCol;		/* color number of defined 3D hatch (0 = Use BODY color) */		\
	double			xSize;			/* x size of the picture in model space */						\
	double			ySize;			/* y size of the picture in model space */						\
	double			rotAng;			/* rotation angle */											\
	Int32			dummy1;			/* not used */													\
	Int32			dummy2;			/* not used */

	_MATERIAL_DATA_MEMBERS_

// Transaction management class

private:
	class VBATTRIBUTES_DLL_EXPORT IsolatedState : public ADB::GeneralAttribute::IsolatedState {
		private:
			friend class Material;

			_MATERIAL_DATA_MEMBERS_

		public:
			virtual ~IsolatedState ();
	};

public:
		// constructors
								Material ();
								Material (const Material& source);
							   ~Material ();

		// operator overloading

	Material&					operator= (const Material& source);

		// get methods

	GSType						GetTypeId (void) const  override { return TypeId_Material; }

	inline	short				GetMaterialType (void) const { return mtype; }
	inline	const GS_RGBColor&	GetSurfaceColor (void) const { return surfaceRGB; }
	inline	short				GetAmbientPercentage (void) const { return ambientPc; }
	inline	short				GetDiffuseAlbedo (void) const { return diffusePc; }
	inline	short				GetSpecularAlbedo (void) const { return specularPc; }
	inline	short				GetTransparency (void) const { return transpPc; }
	inline	short				GetShininess (void) const { return shine; }
	inline	short				GetTransparencyAttenuation (void) const { return transpAtt; }
	inline	const GS_RGBColor&	GetSpecularColor (void) const { return specularRGB; }
	inline	const GS_RGBColor&	GetEmissionColor (void) const { return emissionRGB; }
	inline	short				GetEmissionAttenuation (void) const { return emissionAtt; }
	inline	short				GetFillIndex (void) const { return ifill; }
	inline	void				GetTextureName (GS::UniString* textureName) const { *textureName = texName; }
	inline	short				GetTextureStatus (void) const { return texStatus; }
	inline	short				GetFillColor (void) const { return fillCol; }
	inline	double				GetTextureWidth (void) const { return xSize; }
	inline	double				GetTextureHeight (void) const { return ySize; }
	inline	double				GetTextureRotationAngle (void) const { return rotAng; }

	FieldMask					Compare (ADB::GeneralAttributeConstRef attribute) const override;

	Material*					Clone (void) const override;

		// set methods

	void						SetMaterialType (short newMaterialType);
	void						SetSurfaceColor (const GS_RGBColor& newSurfaceColor);
	void						SetAmbientPercentage (short newAmbientPercentage);
	void						SetDiffuseAlbedo (short newDiffuseAlbedo);
	void						SetSpecularAlbedo (short newSpecularAlbedo);
	void						SetTransparency (short newTransparency);
	void						SetShininess (short newShininess);
	void						SetTransparencyAttenuation (short newTransparencyAttenuation);
	void						SetSpecularColor (const GS_RGBColor& newSpecularColor);
	void						SetEmissionColor (const GS_RGBColor& newEmissionColor);
	void						SetEmissionAttenuation (short newEmissionAttenuation);
	void						SetFillIndex (short newFillIndex);
	void						SetTextureName (const GS::UniString& newTextureName);
	void						SetTextureStatus (short newTextureStatus);
	void						SetFillColor (short newFillColor);
	void						SetTextureWidth (double newTextureWidth);
	void						SetTextureHeight (double newTextureHeight);
	void						SetTextureRotationAngle (double newTextureRotationAngle);

	void						Synchronize (ADB::GeneralAttributeConstRef newAttribute, const FieldMask& changes) override;

		// observer methods

	void						Attach (MaterialObserver& observer);
	void						Detach (MaterialObserver& observer);

	void						Notify (GS::EventObserver* observer, const FieldMask* changes) const override;

		// check methods

	bool						CheckAttribute (void) const override;
	GSErrCode					CorrectAttribute (void) override;

		// reindex methods

	virtual void				CollectUsedAttrs (IUsedAttrCollection&) const override;
	virtual	void				ReindAttr (ADB::IAttributeNewIndexTable* newIndexTable) override;

		// used libpart methods

	virtual void				CollectUsedLibPartNames (IUsedLibPartCollection& outputInterface) const override;

		// read / write methods

	GSErrCode					Read (GS::IChannel& ic) override;
	GSErrCode					Write (GS::OChannel& oc) const override;
	GSErrCode					WriteXML (GS::XMLOChannel& oc) const override;
	GSErrCode					ReadXML (GS::XMLIChannel& ic) override;

private:
	GSErrCode					ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode					WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode					ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode					WriteVersion2 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode					ReadVersion3 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode					WriteVersion3 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

	GSErrCode					ReadImageAttributes (GS::IChannel& ic);
	GSErrCode					WriteImageAttributes (GS::OChannel& oc) const;
	GSErrCode					WriteImageAttributesXML (GS::XMLOChannel& oc) const;
	GSErrCode					ReadImageAttributesXML (GS::XMLIChannel& ic);

public:
		// copy methods

	void						Copy (ADB::GeneralAttributeConstRef newAttribute) override;

		// Transaction management methods

	virtual	GSErrCode					StoreIsolatedState   			(ODB::Object::IsolatedState* isolatedState) const override;
	virtual	GSErrCode					RestoreIsolatedState 			(const ODB::Object::IsolatedState* isolatedState) override;
	virtual	ODB::Object::IsolatedState*	CreateIsolatedState				(void) const override;
	virtual USize						GetIsolatedSize					(void) const override;
	virtual	GSErrCode					WriteIsolatedState   			(GS::OChannel& oc) const override;
	virtual	GSErrCode					ReadIsolatedState 				(GS::IChannel& ic) override;

		// TWObject methods

	GSErrCode					ReadTWIsolatedState  (GS::IChannel& ic) override;
	GSErrCode					WriteTWIsolatedState (GS::OChannel& oc) const override;

	virtual	bool				IsEqual (ADB::GeneralAttributeConstRef attrib) const override;

private:
		// memo methods

	GSErrCode					Destruct (void) override;

};

//--------------------------------------------------------------------

typedef ODB::Ref<Material>			MaterialRef;
typedef ODB::ConstRef<Material>		MaterialConstRef;

//--------------------------------------------------------------------

#define MaterialField(idx) FieldIDT<VBAttr::Material>(ADB::GeneralAttribute::GetClassInfoStatic ()->GetId (), idx)
typedef FieldMaskT<VBAttr::Material>		MaterialFieldMask;

//======================= Class MaterialObserver ===========================
//
// Observer class for Material
//
//==========================================================================

class VBATTRIBUTES_DLL_EXPORT MaterialObserver : public ADB::GeneralAttributeObserver {
protected:
		// destructor

	virtual ~MaterialObserver () {}

public:
		// changed methods

	virtual void	MaterialTypeChanged (MaterialConstRef);
	virtual void	SurfaceColorChanged (MaterialConstRef);
	virtual void	AmbientPercentageChanged (MaterialConstRef);
	virtual void	DiffuseAlbedoChanged (MaterialConstRef);
	virtual void	SpecularAlbedoChanged (MaterialConstRef);
	virtual void	TransparencyChanged (MaterialConstRef);
	virtual void	ShininessChanged (MaterialConstRef);
	virtual void	TransparencyAttenuationChanged (MaterialConstRef);
	virtual void	SpecularColorChanged (MaterialConstRef);
	virtual void	EmissionColorChanged (MaterialConstRef);
	virtual void	EmissionAttenuationChanged (MaterialConstRef);
	virtual void	FillIndexChanged (MaterialConstRef);
	virtual void	TextureNameChanged (MaterialConstRef);
	virtual void	TextureStatusChanged (MaterialConstRef);
	virtual void	FillColorChanged (MaterialConstRef);
	virtual void	TextureWidthChanged (MaterialConstRef);
	virtual void	TextureHeightChanged (MaterialConstRef);
	virtual void	TextureRotationAngleChanged (MaterialConstRef);
};

//========================= Class MaterialChanges ==========================
//
// An implemented observer class for Material
//
//==========================================================================

class VBATTRIBUTES_DLL_EXPORT MaterialChanges : public MaterialObserver {
private:
		// data members

	MaterialFieldMask	changes;

public:
		// constructors

	MaterialChanges (Material* material);
   ~MaterialChanges ();

		// set methods

	void	ResetChanges (void);

		// get methods

	const MaterialFieldMask&	GetChanges (void) const;

		// changed methods (ADB::GeneralAttributeObserver interface)

	void	NameChanged (ADB::GeneralAttributeConstRef) override;
	void	IndexChanged (ADB::GeneralAttributeConstRef) override;
	void	FlagsChanged (ADB::GeneralAttributeConstRef) override;
	void	ModificationTimeChanged (ADB::GeneralAttributeConstRef) override;
	void	UserDataChanged (GSType owner1, GSType owner2) override;

		// changed methods (MaterialObserver interface)

	void	MaterialTypeChanged (MaterialConstRef) override;
	void	SurfaceColorChanged (MaterialConstRef) override;
	void	AmbientPercentageChanged (MaterialConstRef) override;
	void	DiffuseAlbedoChanged (MaterialConstRef) override;
	void	SpecularAlbedoChanged (MaterialConstRef) override;
	void	TransparencyChanged (MaterialConstRef) override;
	void	ShininessChanged (MaterialConstRef) override;
	void	TransparencyAttenuationChanged (MaterialConstRef) override;
	void	SpecularColorChanged (MaterialConstRef) override;
	void	EmissionColorChanged (MaterialConstRef) override;
	void	EmissionAttenuationChanged (MaterialConstRef) override;
	void	FillIndexChanged (MaterialConstRef) override;
	void	TextureNameChanged (MaterialConstRef) override;
	void	TextureStatusChanged (MaterialConstRef) override;
	void	FillColorChanged (MaterialConstRef) override;
	void	TextureWidthChanged (MaterialConstRef) override;
	void	TextureHeightChanged (MaterialConstRef) override;
	void	TextureRotationAngleChanged (MaterialConstRef) override;
};

//====================== End of the VBAttr namespace ======================

}

//============== External functions for class Material  ===============

namespace VBAttr {
	VBATTRIBUTES_DLL_EXPORT MaterialRef				GetMaterial (ADB::AttributeSetConstRef attributeSet, short index);
	VBATTRIBUTES_DLL_EXPORT MaterialConstRef		GetConstMaterial (ADB::AttributeSetConstRef attributeSet, short index);
	VBATTRIBUTES_DLL_EXPORT GS::UniString			GetMaterialName (ADB::AttributeSetConstRef attributeSet, short index);
	VBATTRIBUTES_DLL_EXPORT void					CorrectMaterialName (ADB::AttributeSetConstRef attributeSet, VBAttr::MaterialRef material);
}

#endif
