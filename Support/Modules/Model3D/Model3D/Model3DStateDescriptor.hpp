// *****************************************************************************
// Data for model generation and visualization.
// GSModeler, platform-independent
//
// Namespaces:        Contact person:
//    Modeler          CsA
//
// SG compatible
// *****************************************************************************

#if !defined (MODEL3DSTATEDESCRIPTOR_HPP)
#define MODEL3DSTATEDESCRIPTOR_HPP


// ----------------------- Includes --------------------------------------------

// ----------------------- Class declaration -----------------------------------

class Model3DStateDescriptor {
public:
	short			agenMode;
	short			lastlayer, lastetype, laststory, lastbstat;
	Int32			lastlongval1, lastlongval2;	
	Int32			nsbody, nsvert, nsvect, nsteve, nspgon, nspedg, nsedge, nshots;
	bool			gSimpleVM, gWriteSightFile;

	Model3DStateDescriptor ();
};

inline Model3DStateDescriptor::Model3DStateDescriptor () :
	agenMode (M_SOLID),
	lastlayer (0), lastetype (0), laststory (0), lastbstat (0), lastlongval1 (0), lastlongval2 (0),
	nsbody (0), nsvert (0), nsvect (0), nsteve (0), nspgon (0), nspedg (0), nsedge (0), nshots (0),
	gSimpleVM (0), gWriteSightFile (0)
{
}

#endif // MODEL3DSTATEDESCRIPTOR_HPP
