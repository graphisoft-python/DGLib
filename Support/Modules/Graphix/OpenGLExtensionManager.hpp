// *****************************************************************************
// OpenGL extension manager
//
// Module:				Graphics
// Contact person:		SZI
//
// SG compatible
// *****************************************************************************

#ifndef _OPENGLEXTENSIONMANAGER_HPP_
#define _OPENGLEXTENSIONMANAGER_HPP_

// --- Includes ----------------------------------------------------------------

#include <string>
#include <cstdint>

#ifdef macintosh
#	include <OpenGL/gl3.h>
#	include <OpenGL/OpenGL.h>
#	include <OpenGL/glext.h>
#elif defined(WINDOWS)
#	pragma warning (push)
#	pragma warning (disable: 4995)
#		include <Windows.h>
#	pragma warning (pop)

#	include <gl/gl.h>

#	include "glext.h"
#	include "glcorearb.h"
#endif

#include "GraphixDefinitions.hpp"

// --- Defines -----------------------------------------------------------------

#define FRAMEBUFFER_SRGB_EXT					0x8DB9
#define FRAMEBUFFER_SRGB_CAPABLE_EXT			0x8DBA
#define WGL_FRAMEBUFFER_SRGB_CAPABLE_EXT		0x20A9
#define GLX_FRAMEBUFFER_SRGB_CAPABLE_EXT		0x20B2
#define CUBEMAP_RENDERTARGET_MASK				0x100

// for macOS
#ifndef GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS
#	define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS	0x8CD9
#endif

#ifndef GL_MIRROR_CLAMP_TO_EDGE
#	define GL_MIRROR_CLAMP_TO_EDGE				0x8743
#endif

#ifndef GL_COMPUTE_SHADER
#	define GL_COMPUTE_SHADER					0x91B9
#endif

#ifndef GL_SHADER_STORAGE_BUFFER
#	define GL_SHADER_STORAGE_BUFFER				0x90D2
#endif

#define MAKE_VERSION(major, minor)	((0xff00 & (major << 8)) | minor)

// --- Forward declarations ----------------------------------------------------

#ifdef WINDOWS
extern PFNGLACTIVETEXTUREARBPROC					glActiveTexture;
extern PFNGLCLIENTACTIVETEXTUREARBPROC				glClientActiveTexture;
extern PFNGLDELETEBUFFERSARBPROC					glDeleteBuffers;
extern PFNGLBINDBUFFERARBPROC						glBindBuffer;
extern PFNGLGENBUFFERSARBPROC						glGenBuffers;
extern PFNGLBUFFERDATAARBPROC						glBufferData;
extern PFNGLBUFFERSUBDATAARBPROC					glBufferSubData;
extern PFNGLTEXIMAGE3DPROC							glTexImage3D;
extern PFNGLTEXIMAGE2DMULTISAMPLEPROC				glTexImage2DMultisample;
extern PFNGLTEXSUBIMAGE3DPROC						glTexSubImage3D;

extern PFNGLCREATEPROGRAMOBJECTARBPROC				glCreateProgram;
extern PFNGLCREATESHADEROBJECTARBPROC				glCreateShader;
extern PFNGLSHADERSOURCEARBPROC						glShaderSource;
extern PFNGLCOMPILESHADERARBPROC					glCompileShader;
extern PFNGLATTACHOBJECTARBPROC						glAttachShader;
extern PFNGLDETACHOBJECTARBPROC						glDetachShader;
extern PFNGLLINKPROGRAMARBPROC						glLinkProgram;
extern PFNGLGETINFOLOGARBPROC						glGetShaderInfoLog;
extern PFNGLGETINFOLOGARBPROC						glGetProgramInfoLog;
extern PFNGLGETUNIFORMLOCATIONARBPROC				glGetUniformLocation;

extern PFNGLUNIFORMMATRIX2FVARBPROC					glUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVARBPROC					glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVARBPROC					glUniformMatrix4fv;

extern PFNGLUNIFORM1IARBPROC						glUniform1i;
extern PFNGLUNIFORM1FARBPROC						glUniform1f;
extern PFNGLUNIFORM2FARBPROC						glUniform2f;
extern PFNGLUNIFORM3FARBPROC						glUniform3f;
extern PFNGLUNIFORM4FARBPROC						glUniform4f;
extern PFNGLUNIFORM1FVARBPROC						glUniform1fv;
extern PFNGLUNIFORM2FVARBPROC						glUniform2fv;
extern PFNGLUNIFORM3FVARBPROC						glUniform3fv;
extern PFNGLUNIFORM4FVARBPROC						glUniform4fv;

extern PFNGLUSEPROGRAMOBJECTARBPROC					glUseProgram;
extern PFNGLGETPROGRAMIVPROC						glGetProgramiv;
extern PFNGLGETSHADERIVPROC							glGetShaderiv;
extern PFNGLDELETEPROGRAMPROC						glDeleteProgram;
extern PFNGLDELETESHADERPROC						glDeleteShader;

extern PFNGLGETACTIVEUNIFORMARBPROC					glGetActiveUniform;
extern PFNGLGETACTIVEATTRIBPROC						glGetActiveAttrib;
extern PFNGLGETATTRIBLOCATIONPROC					glGetAttribLocation;
extern PFNGLENABLEVERTEXATTRIBARRAYARBPROC			glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYARBPROC			glDisableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERARBPROC				glVertexAttribPointer;
extern PFNGLBINDATTRIBLOCATIONARBPROC				glBindAttribLocation;
extern PFNGLBINDFRAGDATALOCATIONPROC				glBindFragDataLocation;

extern PFNGLGENFRAMEBUFFERSEXTPROC					glGenFramebuffers;
extern PFNGLGENRENDERBUFFERSEXTPROC					glGenRenderbuffers;
extern PFNGLBINDFRAMEBUFFEREXTPROC					glBindFramebuffer;
extern PFNGLFRAMEBUFFERTEXTURE2DEXTPROC				glFramebufferTexture2D;
extern PFNGLBINDRENDERBUFFEREXTPROC					glBindRenderbuffer;
extern PFNGLRENDERBUFFERSTORAGEEXTPROC				glRenderbufferStorage;
extern PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC			glFramebufferRenderbuffer;
extern PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC			glCheckFramebufferStatus;
extern PFNGLDELETEFRAMEBUFFERSEXTPROC				glDeleteFramebuffers;
extern PFNGLDELETERENDERBUFFERSEXTPROC				glDeleteRenderbuffers;
extern PFNGLGENERATEMIPMAPEXTPROC					glGenerateMipmap;
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC	glRenderbufferStorageMultisample;
extern PFNGLBLITFRAMEBUFFEREXTPROC					glBlitFramebuffer;
extern PFNGLFRAMEBUFFERTEXTURELAYERPROC				glFramebufferTextureLayer;

extern PFNGLGETBUFFERSUBDATAARBPROC					glGetBufferSubData;
extern PFNGLMAPBUFFERARBPROC						glMapBuffer;
extern PFNGLMAPBUFFERRANGEPROC						glMapBufferRange;
extern PFNGLUNMAPBUFFERARBPROC						glUnmapBuffer;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC				glCompressedTexImage2D;
extern PFNGLCOMPRESSEDTEXIMAGE1DPROC				glCompressedTexImage1D;
extern PFNGLDRAWBUFFERSARBPROC						glDrawBuffers;
extern PFNGLDRAWRANGEELEMENTSPROC					glDrawRangeElements;
extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC				glFlushMappedBufferRange;
extern PFNGLGETVERTEXATTRIBIVPROC					glGetVertexAttribiv;
extern PFNGLGETVERTEXATTRIBFVPROC					glGetVertexAttribfv;
extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC				glGetActiveUniformBlockiv;

extern PFNGLBLENDEQUATIONSEPARATEPROC				glBlendEquationSeparate;
extern PFNGLBLENDFUNCSEPARATEPROC					glBlendFuncSeparate;
extern PFNGLSTENCILFUNCSEPARATEPROC					glStencilFuncSeparate;
extern PFNGLSTENCILMASKSEPARATEPROC					glStencilMaskSeparate;
extern PFNGLSTENCILOPSEPARATEPROC					glStencilOpSeparate;
extern PFNGLCOLORMASKIPROC							glColorMaski;
extern PFNGLISBUFFERPROC							glIsBuffer;

// 3.2
extern PFNGLGENVERTEXARRAYSPROC						glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC						glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC					glDeleteVertexArrays;
extern PFNGLPATCHPARAMETERIPROC						glPatchParameteri;
extern PFNGLPATCHPARAMETERFVPROC					glPatchParameterfv;
extern PFNGLCLEARBUFFERFVPROC						glClearBufferfv;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC	glGetFramebufferAttachmentParameteriv;
extern PFNGLGETUNIFORMBLOCKINDEXPROC				glGetUniformBlockIndex;
extern PFNGLUNIFORMBLOCKBINDINGPROC					glUniformBlockBinding;
extern PFNGLENABLEIPROC								glEnablei;
extern PFNGLDISABLEIPROC							glDisablei;
extern PFNGLBINDBUFFERBASEPROC						glBindBufferBase;
extern PFNGLBINDBUFFERRANGEPROC						glBindBufferRange;
extern PFNGLDRAWELEMENTSBASEVERTEXPROC				glDrawElementsBaseVertex;
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC		glDrawElementsInstancedBaseVertex;

extern PFNGLGETSTRINGIPROC							glGetStringi;
extern PFNGLGETINTEGERI_VPROC						glGetIntegeri_v;
extern PFNGLFENCESYNCPROC							glFenceSync;
extern PFNGLWAITSYNCPROC							glWaitSync;
extern PFNGLCLIENTWAITSYNCPROC						glClientWaitSync;
extern PFNGLDELETESYNCPROC							glDeleteSync;

// 3.3
extern PFNGLGENSAMPLERSPROC							glGenSamplers;
extern PFNGLDELETESAMPLERSPROC						glDeleteSamplers;
extern PFNGLSAMPLERPARAMETERFPROC					glSamplerParameterf;
extern PFNGLSAMPLERPARAMETERFVPROC					glSamplerParameterfv;
extern PFNGLSAMPLERPARAMETERIPROC					glSamplerParameteri;
extern PFNGLSAMPLERPARAMETERIVPROC					glSamplerParameteriv;
extern PFNGLBINDSAMPLERPROC							glBindSampler;
extern PFNGLVERTEXATTRIBDIVISORPROC					glVertexAttribDivisor;

// 4.0
extern PFNGLMINSAMPLESHADINGPROC					glMinSampleShading;

// 4.3
extern PFNGLDISPATCHCOMPUTEPROC						glDispatchCompute;
extern PFNGLDISPATCHCOMPUTEINDIRECTPROC				glDispatchComputeIndirect;
extern PFNGLBINDIMAGETEXTUREPROC					glBindImageTexture;
extern PFNGLMEMORYBARRIERPROC						glMemoryBarrier;
extern PFNGLGETPROGRAMBINARYPROC					glGetProgramBinary;
extern PFNGLGETPROGRAMINTERFACEIVPROC				glGetProgramInterfaceiv;
extern PFNGLSHADERSTORAGEBLOCKBINDINGPROC			glShaderStorageBlockBinding;
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC	glDrawElementsInstancedBaseVertexBaseInstance;

extern PFNGLBLENDEQUATIONSEPARATEIPROC				glBlendEquationSeparatei;
extern PFNGLBLENDFUNCSEPARATEIPROC					glBlendFuncSeparatei;

extern PFNGLDEBUGMESSAGECONTROLPROC					glDebugMessageControl;
extern PFNGLDEBUGMESSAGECALLBACKPROC				glDebugMessageCallback;
extern PFNGLGETDEBUGMESSAGELOGPROC					glGetDebugMessageLog;

// WGL specific
typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALFARPROC)(int);
typedef const char* (APIENTRY *WGLGETEXTENSIONSSTRINGARBPROC)(HDC hdc);
typedef HGLRC (APIENTRY *WGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC, HGLRC hShareContext, const int *attribList);
typedef BOOL (APIENTRY *WGLGETPIXELFORMATATTRIBIVARBPROC)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, int *piValues);
typedef BOOL (APIENTRY *WGLGETPIXELFORMATATTRIBFVARBPROC)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, FLOAT *pfValues);
typedef BOOL (APIENTRY *WGLCHOOSEPIXELFORMATARBPROC)(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
typedef const GLubyte* (APIENTRY *GLGETSTRINGIPROC)(GLenum  name, GLuint index);

extern PFNWGLSWAPINTERVALFARPROC wglSwapInterval;
extern WGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribs;
extern WGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsString;
extern WGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribiv;
extern WGLGETPIXELFORMATATTRIBFVARBPROC wglGetPixelFormatAttribfv;
extern WGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormat;
#endif	// WINDOWS

#ifdef macintosh
extern "C" {
	extern void glBindVertexArray(GLuint array);
	extern void glDeleteVertexArrays(GLsizei n, const GLuint *arrays);
	extern void glGenVertexArrays(GLsizei n, GLuint *arrays);
	extern void glBindFragDataLocation(GLuint program, GLuint color, const GLchar *name);
}
#endif	// macintosh

namespace Graphix {

void CheckGLError ();

// --- Class definition --------------------------------------------------------

class GRAPHIX_DLL_EXPORT OpenGLExtensionManager
{
private:
	OpenGLExtensionManager ();

public:
	enum {
		GL_1_1 = MAKE_VERSION(1, 1),
		GL_1_2 = MAKE_VERSION(1, 2),
		GL_1_3 = MAKE_VERSION(1, 3),
		GL_1_4 = MAKE_VERSION(1, 4),
		GL_1_5 = MAKE_VERSION(1, 5),
		GL_2_0 = MAKE_VERSION(2, 0),
		GL_2_1 = MAKE_VERSION(2, 1),
		GL_3_0 = MAKE_VERSION(3, 0),
		GL_3_1 = MAKE_VERSION(3, 1),
		GL_3_2 = MAKE_VERSION(3, 2),
		GL_3_3 = MAKE_VERSION(3, 3),
		GL_4_0 = MAKE_VERSION(4, 0),
		GL_4_1 = MAKE_VERSION(4, 1),
		GL_4_2 = MAKE_VERSION(4, 2),
		GL_4_3 = MAKE_VERSION(4, 3),
		GL_4_4 = MAKE_VERSION(4, 4)
	};

	enum {
		GLSL_110 = MAKE_VERSION(1, 10),
		GLSL_120 = MAKE_VERSION(1, 20),
		GLSL_130 = MAKE_VERSION(1, 30),
		GLSL_140 = MAKE_VERSION(1, 40),
		GLSL_150 = MAKE_VERSION(1, 50),
		GLSL_330 = MAKE_VERSION(3, 30),
		GLSL_400 = MAKE_VERSION(4, 0),
		GLSL_410 = MAKE_VERSION(4, 10),
		GLSL_420 = MAKE_VERSION(4, 20),
		GLSL_430 = MAKE_VERSION(4, 30),
		GLSL_440 = MAKE_VERSION(4, 40)
	};

	static uint16_t GLVersion;
	static uint16_t GLSLVersion;
	static int32_t	MaxUniformBlockSize;
	static int32_t	MaxTextureSize;
	static int32_t	UniformBufferOffsetAlignment;
	static int32_t MaxClipDistances;

	static std::string GLVendor;
	static std::string GLRenderer;
	static std::string GLAPIVersion;

	static bool IsSupported (const char* name);
	static void QueryFeatures (void* hdc = 0, bool force = false);

	static bool ARB_vertex_buffer_object;
	static bool ARB_vertex_program;
	static bool ARB_fragment_program;
	static bool ARB_shader_objects;
	static bool ARB_texture_float;
	static bool ARB_texture_non_power_of_two;
	static bool ARB_texture_rg;
	static bool ARB_texture_compression;
	static bool ARB_texture_multisample;
	static bool ARB_draw_buffers;
	static bool ARB_vertex_array_object;
	static bool ARB_geometry_shader4;
	static bool ARB_tessellation_shader;
	static bool ARB_compute_shader;
	static bool ARB_shader_image_load_store;
	static bool ARB_shader_storage_buffer_object;
	static bool ARB_shader_atomic_counters;
	static bool ARB_debug_output;

	static bool EXT_texture_compression_s3tc;
	static bool EXT_texture_cube_map;
	static bool EXT_framebuffer_object;
	static bool EXT_framebuffer_sRGB;
	static bool EXT_texture_sRGB;
	static bool EXT_framebuffer_multisample;
	static bool EXT_framebuffer_blit;
	static bool EXT_packed_depth_stencil;

#ifdef WINDOWS
	static bool WGL_EXT_swap_control;
	static bool WGL_ARB_pixel_format;
	static bool WGL_ARB_create_context;
	static bool WGL_ARB_create_context_profile;
#endif

	static inline int GetMajorVersion ()	{ return ((GLVersion >> 8) & 0x00ff); }
	static inline int GetMinorVersion ()	{ return (GLVersion & 0x00ff); }
};

}

#endif
