
#ifndef _OPENGLMAPS_HPP_
#define _OPENGLMAPS_HPP_

#include "OpenGLExtensionManager.hpp"

namespace Graphix {

class OpenGLMaps
{
private:
	OpenGLMaps ()	{}
	~OpenGLMaps ()	{}

public:
	static GLenum map_TextureType[];
	static GLint map_InternalFormat[];
	static GLint map_MinFilter[3][2];
	static GLint map_MagFilter[];
	static GLint map_AddressMode[];
	static GLenum map_Format[];
	static GLenum map_Type[];
	static GLenum map_ShaderStage[];
	static GLenum map_PrimitiveType[];
	static GLenum map_PolygonMode[];
	static GLenum map_CullMode[];
	static GLenum map_BlendOperation[];
	static GLenum map_BlendFactor[];
	static GLenum map_CompareFunction[];
	static GLenum map_StencilOperation[];
	static GLenum map_VertexInputType[];
	static GLint map_VertexInputType_Size[];
};

}

#endif
