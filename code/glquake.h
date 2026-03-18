/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
// disable data conversion warnings

#pragma warning(disable : 4244)     // MIPS
#pragma warning(disable : 4136)     // X86
#pragma warning(disable : 4051)     // ALPHA
  
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif

#ifndef GL_DST_ALPHA
#define GL_DST_ALPHA                0x0304
#endif

#ifndef GL_DST_COLOR
#define GL_DST_COLOR                0x0306
#endif

#ifndef GL_ONE_MINUS_DST_COLOR
#define GL_ONE_MINUS_DST_COLOR      0x0307
#endif

#ifndef GL_ONE_MINUS_DST_ALPHA
#define GL_ONE_MINUS_DST_ALPHA      0x0305
#endif

#ifndef GL_SRC_ALPHA_SATURATE
#define GL_SRC_ALPHA_SATURATE       0x0308
#endif

#ifndef GL_TEXTURE0_ARB
#define GL_TEXTURE0_ARB 0x84C0
#endif

#ifndef GL_TEXTURE1_ARB
#define GL_TEXTURE1_ARB 0x84C1
#endif

#ifndef GL_TEXTURE2_ARB
#define GL_TEXTURE2_ARB 0x84C2
#endif

#ifndef GL_TEXTURE3_ARB
#define GL_TEXTURE3_ARB 0x84C3
#endif

#ifndef GL_MAX_TEXTURE_UNITS_ARB
#define GL_MAX_TEXTURE_UNITS_ARB 0x84E2
#endif

#ifndef GL_ACTIVE_TEXTURE_ARB
#define GL_ACTIVE_TEXTURE_ARB 0x84E0
#endif

#ifndef GL_TEXTURE0_SGIS
#define GL_TEXTURE0_SGIS 0x835E
#endif

#ifndef GL_TEXTURE1_SGIS
#define GL_TEXTURE1_SGIS 0x835F
#endif

#ifndef GL_TEXTURE2_SGIS
#define GL_TEXTURE2_SGIS 0x8360
#endif

#ifndef GL_TEXTURE3_SGIS
#define GL_TEXTURE3_SGIS 0x8361
#endif

#ifndef GL_MAX_TEXTURES_SGIS
#define GL_MAX_TEXTURES_SGIS 0x83B9
#endif

#ifndef GL_SELECTED_TEXTURE_SGIS
#define GL_SELECTED_TEXTURE_SGIS 0x835C
#endif

#ifndef GL_SGIS_multitexture
#define GL_SGIS_multitexture 1
#endif

// Fake WGL context type for the shim
typedef void* QD3D12_HGLRC;

// Shim entry points
QD3D12_HGLRC WINAPI qd3d12_wglCreateContext(HDC hdc);
BOOL         WINAPI qd3d12_wglMakeCurrent(HDC hdc, QD3D12_HGLRC hglrc);
PROC         WINAPI qd3d12_wglGetProcAddress(LPCSTR name);
HDC          WINAPI qd3d12_wglGetCurrentDC(void);
QD3D12_HGLRC WINAPI qd3d12_wglGetCurrentContext(void);
BOOL         WINAPI qd3d12_wglDeleteContext(QD3D12_HGLRC hglrc);

// EXT alias we want to expose from GetProcAddress
void APIENTRY glBindTextureEXT(unsigned int target, unsigned int texture);

#ifdef __cplusplus
}
#endif

void QD3D12_SwapBuffers(HDC hdc);

// Redirect old WGL calls to the shim.
// This avoids the linker trying to import opengl32.dll WGL symbols.
#define wglCreateContext    qd3d12_wglCreateContext
#define wglMakeCurrent      qd3d12_wglMakeCurrent
#define wglGetProcAddress   qd3d12_wglGetProcAddress
#define wglGetCurrentDC     qd3d12_wglGetCurrentDC
#define wglGetCurrentContext qd3d12_wglGetCurrentContext
#define wglDeleteContext    qd3d12_wglDeleteContext
#define SwapBuffers(x) QD3D12_SwapBuffers(x)

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef ptrdiff_t GLsizeiptr;
typedef char GLchar;

enum : GLenum
{
    GL_FALSE = 0,
    GL_TRUE = 1,

    GL_VENDOR = 0x1F00,
    GL_RENDERER = 0x1F01,
    GL_VERSION = 0x1F02,
    GL_EXTENSIONS = 0x1F03,

    GL_MODELVIEW = 0x1700,
    GL_PROJECTION = 0x1701,
    GL_TEXTURE = 0x1702,

    GL_TEXTURE_2D = 0x0DE1,
    GL_TEXTURE_ENV = 0x2300,
    GL_TEXTURE_ENV_MODE = 0x2200,
    GL_MODULATE = 0x2100,
    GL_REPLACE = 0x1E01,
    GL_BLEND = 0x0BE2,
    GL_ALPHA_TEST = 0x0BC0,
    GL_DEPTH_TEST = 0x0B71,
    GL_CULL_FACE = 0x0B44,

    GL_FRONT = 0x0404,
    GL_BACK = 0x0405,
    GL_FRONT_AND_BACK = 0x0408,

    GL_FILL = 0x1B02,
    GL_LINE = 0x1B01,
    GL_FLAT = 0x1D00,
    GL_SMOOTH = 0x1D01,

    GL_COLOR_BUFFER_BIT = 0x00004000,
    GL_DEPTH_BUFFER_BIT = 0x00000100,

    GL_POINTS = 0x0000,
    GL_LINES = 0x0001,
    GL_LINE_LOOP = 0x0002,
    GL_LINE_STRIP = 0x0003,
    GL_TRIANGLES = 0x0004,
    GL_TRIANGLE_STRIP = 0x0005,
    GL_TRIANGLE_FAN = 0x0006,
    GL_QUADS = 0x0007,
    GL_POLYGON = 0x0009,

    GL_NEVER = 0x0200,
    GL_LESS = 0x0201,
    GL_EQUAL = 0x0202,
    GL_LEQUAL = 0x0203,
    GL_GREATER = 0x0204,
    GL_NOTEQUAL = 0x0205,
    GL_GEQUAL = 0x0206,
    GL_ALWAYS = 0x0207,

    GL_ZERO = 0,
    GL_ONE = 1,
    GL_SRC_COLOR = 0x0300,
    GL_ONE_MINUS_SRC_COLOR = 0x0301,
    GL_SRC_ALPHA = 0x0302,
    GL_ONE_MINUS_SRC_ALPHA = 0x0303,

    GL_NEAREST = 0x2600,
    GL_LINEAR = 0x2601,
    GL_NEAREST_MIPMAP_NEAREST = 0x2700,
    GL_LINEAR_MIPMAP_NEAREST = 0x2701,
    GL_NEAREST_MIPMAP_LINEAR = 0x2702,
    GL_LINEAR_MIPMAP_LINEAR = 0x2703,

    GL_TEXTURE_MAG_FILTER = 0x2800,
    GL_TEXTURE_MIN_FILTER = 0x2801,
    GL_TEXTURE_WRAP_S = 0x2802,
    GL_TEXTURE_WRAP_T = 0x2803,
    GL_REPEAT = 0x2901,
    GL_CLAMP = 0x2900,

    GL_UNSIGNED_BYTE = 0x1401,
    GL_FLOAT = 0x1406,

    GL_RGB = 0x1907,
    GL_RGBA = 0x1908,
    GL_ALPHA = 0x1906,
    GL_LUMINANCE = 0x1909,
    GL_INTENSITY = 0x8049,

    GL_PERSPECTIVE_CORRECTION_HINT = 0x0C50,
    GL_FASTEST = 0x1101,
    GL_NICEST = 0x1102,

    GL_MODELVIEW_MATRIX = 0x0BA6,
    GL_COLOR_INDEX = 0x1900,
};

extern "C"
{
    WINGDIAPI void APIENTRY glLoadMatrixf(const GLfloat* m);
    WINGDIAPI void APIENTRY glGetFloatv(GLenum pname, GLfloat* params);
    WINGDIAPI void APIENTRY glFrustum(GLdouble left, GLdouble right,
        GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
    WINGDIAPI void APIENTRY glDepthFunc(GLenum func);
    WINGDIAPI void APIENTRY glColor4fv(const GLfloat* v);
    WINGDIAPI const GLubyte* APIENTRY glGetString(GLenum name);
    WINGDIAPI void APIENTRY glClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
    WINGDIAPI void APIENTRY glClear(GLbitfield mask);
    WINGDIAPI void APIENTRY glViewport(GLint x, GLint y, GLsizei width, GLsizei height);

    WINGDIAPI void APIENTRY glEnable(GLenum cap);
    WINGDIAPI void APIENTRY glDisable(GLenum cap);
    WINGDIAPI void APIENTRY glBlendFunc(GLenum sfactor, GLenum dfactor);
    WINGDIAPI void APIENTRY glAlphaFunc(GLenum func, GLclampf ref);
    WINGDIAPI void APIENTRY glDepthMask(GLboolean flag);
    WINGDIAPI void APIENTRY glDepthRange(GLclampd zNear, GLclampd zFar);
    WINGDIAPI void APIENTRY glCullFace(GLenum mode);
    WINGDIAPI void APIENTRY glPolygonMode(GLenum face, GLenum mode);
    WINGDIAPI void APIENTRY glShadeModel(GLenum mode);
    WINGDIAPI void APIENTRY glHint(GLenum target, GLenum mode);
    WINGDIAPI void APIENTRY glFinish(void);

    WINGDIAPI void APIENTRY glMatrixMode(GLenum mode);
    WINGDIAPI void APIENTRY glLoadIdentity(void);
    WINGDIAPI void APIENTRY glPushMatrix(void);
    WINGDIAPI void APIENTRY glPopMatrix(void);
    WINGDIAPI void APIENTRY glTranslatef(GLfloat x, GLfloat y, GLfloat z);
    WINGDIAPI void APIENTRY glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
    WINGDIAPI void APIENTRY glScalef(GLfloat x, GLfloat y, GLfloat z);
    WINGDIAPI void APIENTRY glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);

    WINGDIAPI void APIENTRY glBegin(GLenum mode);
    WINGDIAPI void APIENTRY glEnd(void);
    WINGDIAPI void APIENTRY glVertex2f(GLfloat x, GLfloat y);
    WINGDIAPI void APIENTRY glVertex3f(GLfloat x, GLfloat y, GLfloat z);
    WINGDIAPI void APIENTRY glVertex3fv(const GLfloat* v);
    WINGDIAPI void APIENTRY glTexCoord2f(GLfloat s, GLfloat t);
    WINGDIAPI void APIENTRY glColor3f(GLfloat r, GLfloat g, GLfloat b);
    WINGDIAPI void APIENTRY glColor4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    WINGDIAPI void APIENTRY glGenTextures(GLsizei n, GLuint* textures);
    WINGDIAPI void APIENTRY glDeleteTextures(GLsizei n, const GLuint* textures);
    WINGDIAPI void APIENTRY glBindTexture(GLenum target, GLuint texture);
    WINGDIAPI void APIENTRY glTexParameterf(GLenum target, GLenum pname, GLfloat param);
    WINGDIAPI void APIENTRY glTexEnvf(GLenum target, GLenum pname, GLfloat param);
    WINGDIAPI void APIENTRY glTexImage2D(GLenum target, GLint level, GLint internalFormat,
        GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
    WINGDIAPI void APIENTRY glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
        GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels);
    WINGDIAPI void APIENTRY glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height,
        GLenum format, GLenum type, GLvoid* data);
    WINGDIAPI void APIENTRY glDrawBuffer(GLenum mode);
    WINGDIAPI void APIENTRY glReadBuffer(GLenum mode);
}

void GL_BeginRendering (int *x, int *y, int *width, int *height);
void GL_EndRendering (void);


#ifdef _WIN32
// Function prototypes for the Texture Object Extension routines
typedef GLboolean (APIENTRY *ARETEXRESFUNCPTR)(GLsizei, const GLuint *,
                    const GLboolean *);
typedef void (APIENTRY *BINDTEXFUNCPTR)(GLenum, GLuint);
typedef void (APIENTRY *DELTEXFUNCPTR)(GLsizei, const GLuint *);
typedef void (APIENTRY *GENTEXFUNCPTR)(GLsizei, GLuint *);
typedef GLboolean (APIENTRY *ISTEXFUNCPTR)(GLuint);
typedef void (APIENTRY *PRIORTEXFUNCPTR)(GLsizei, const GLuint *,
                    const GLclampf *);
typedef void (APIENTRY *TEXSUBIMAGEPTR)(int, int, int, int, int, int, int, int, void *);

extern	BINDTEXFUNCPTR bindTexFunc;
extern	DELTEXFUNCPTR delTexFunc;
extern	TEXSUBIMAGEPTR TexSubImage2DFunc;
#endif

extern	int texture_extension_number;
extern	int		texture_mode;

extern	float	gldepthmin, gldepthmax;

void GL_Upload32 (unsigned *data, int width, int height,  qboolean mipmap, qboolean alpha);
void GL_Upload8 (byte *data, int width, int height,  qboolean mipmap, qboolean alpha);
int GL_LoadTexture (char *identifier, int width, int height, byte *data, qboolean mipmap, qboolean alpha);
int GL_FindTexture (char *identifier);

typedef struct
{
	float	x, y, z;
	float	s, t;
	float	r, g, b;
} glvert_t;

extern glvert_t glv;

extern	int glx, gly, glwidth, glheight;

#ifdef _WIN32
extern	PROC glArrayElementEXT;
extern	PROC glColorPointerEXT;
extern	PROC glTexturePointerEXT;
extern	PROC glVertexPointerEXT;
#endif

// r_local.h -- private refresh defs

#define ALIAS_BASE_SIZE_RATIO		(1.0 / 11.0)
					// normalizing factor so player model works out to about
					//  1 pixel per triangle
#define	MAX_LBM_HEIGHT		480

#define TILE_SIZE		128		// size of textures generated by R_GenTiledSurf

#define SKYSHIFT		7
#define	SKYSIZE			(1 << SKYSHIFT)
#define SKYMASK			(SKYSIZE - 1)

#define BACKFACE_EPSILON	0.01


void R_TimeRefresh_f (void);
void R_ReadPointFile_f (void);
texture_t *R_TextureAnimation (texture_t *base);

typedef struct surfcache_s
{
	struct surfcache_s	*next;
	struct surfcache_s 	**owner;		// NULL is an empty chunk of memory
	int					lightadj[MAXLIGHTMAPS]; // checked for strobe flush
	int					dlight;
	int					size;		// including header
	unsigned			width;
	unsigned			height;		// DEBUG only needed for debug
	float				mipscale;
	struct texture_s	*texture;	// checked for animating textures
	byte				data[4];	// width*height elements
} surfcache_t;


typedef struct
{
	pixel_t		*surfdat;	// destination for generated surface
	int			rowbytes;	// destination logical width in bytes
	msurface_t	*surf;		// description for surface to generate
	fixed8_t	lightadj[MAXLIGHTMAPS];
							// adjust for lightmap levels for dynamic lighting
	texture_t	*texture;	// corrected for animating textures
	int			surfmip;	// mipmapped ratio of surface texels / world pixels
	int			surfwidth;	// in mipmapped texels
	int			surfheight;	// in mipmapped texels
} drawsurf_t;


typedef enum {
	pt_static, pt_grav, pt_slowgrav, pt_fire, pt_explode, pt_explode2, pt_blob, pt_blob2, pt_explode3, pt_smoke, pt_blood, pt_smoketrail, pt_firetrail
} ptype_t;

// !!! if this is changed, it must be changed in d_ifacea.h too !!!
typedef struct particle_s
{
// driver-usable fields
	vec3_t		org;
	float		color;
	float		size;
	float		growth;
// drivers never touch the following fields
	struct particle_s	*next;
	vec3_t		vel;
	float		ramp;
	float		start;
	float		die;
	ptype_t		type;
} particle_t;


//====================================================


extern	entity_t	r_worldentity;
extern	qboolean	r_cache_thrash;		// compatability
extern	vec3_t		modelorg, r_entorigin;
extern	entity_t	*currententity;
extern	int			r_visframecount;	// ??? what difs?
extern	int			r_framecount;
extern	mplane_t	frustum[4];
extern	int		c_brush_polys, c_alias_polys;


//
// view origin
//
extern	vec3_t	vup;
extern	vec3_t	vpn;
extern	vec3_t	vright;
extern	vec3_t	r_origin;

//
// screen size info
//
extern	refdef_t	r_refdef;
extern	mleaf_t		*r_viewleaf, *r_oldviewleaf;
extern	texture_t	*r_notexture_mip;
extern	int		d_lightstylevalue[256];	// 8.8 fraction of base light value

extern	qboolean	envmap;
extern	int	currenttexture;
extern	int	cnttextures[2];
extern	int	particletexture;
extern	int	playertextures;

extern	int	skytexturenum;		// index in cl.loadmodel, not gl texture object

extern	cvar_t	r_norefresh;
extern	cvar_t	r_drawentities;
extern	cvar_t	r_drawworld;
extern	cvar_t	r_drawviewmodel;
extern	cvar_t	r_speeds;
extern	cvar_t	r_waterwarp;
extern	cvar_t	r_fullbright;
extern	cvar_t	r_lightmap;
extern	cvar_t	r_shadows;
extern	cvar_t	r_mirroralpha;
extern	cvar_t	r_wateralpha;
extern	cvar_t	r_dynamic;
extern	cvar_t	r_novis;

extern	cvar_t	gl_clear;
extern	cvar_t	gl_cull;
extern	cvar_t	gl_poly;
extern	cvar_t	gl_texsort;
extern	cvar_t	gl_smoothmodels;
extern	cvar_t	gl_affinemodels;
extern	cvar_t	gl_polyblend;
extern	cvar_t	gl_keeptjunctions;
extern	cvar_t	gl_reporttjunctions;
extern	cvar_t	gl_flashblend;
extern	cvar_t	gl_nocolors;
extern	cvar_t	gl_doubleeyes;

extern	int		gl_lightmap_format;
extern	int		gl_solid_format;
extern	int		gl_alpha_format;

extern	cvar_t	gl_max_size;
extern	cvar_t	gl_playermip;

extern	int			mirrortexturenum;	// quake texturenum, not gltexturenum
extern	qboolean	mirror;
extern	mplane_t	*mirror_plane;

extern	float	r_world_matrix[16];

extern	const char *gl_vendor;
extern	const char *gl_renderer;
extern	const char *gl_version;
extern	const char *gl_extensions;

void R_TranslatePlayerSkin (int playernum);
void GL_Bind (int texnum);

// Multitexture
#define    TEXTURE0_SGIS				0x835E
#define    TEXTURE1_SGIS				0x835F

#ifndef _WIN32
#define APIENTRY /* */
#endif

typedef void (APIENTRY *lpMTexFUNC) (GLenum, GLfloat, GLfloat);
typedef void (APIENTRY *lpSelTexFUNC) (GLenum);
extern lpMTexFUNC qglMTexCoord2fSGIS;
extern lpSelTexFUNC qglSelectTextureSGIS;

extern qboolean gl_mtexable;

void GL_DisableMultitexture(void);
void GL_EnableMultitexture(void);

int R_LightPoint(const vec3_t & p);
void R_DrawBrushModel(entity_t* e);
void R_AnimateLight(void);
void V_CalcBlend(void);
void R_DrawWorld(void);
void R_RenderDlights(void);
void R_DrawParticles(void);
void R_DrawWaterSurfaces(void);
void R_RenderBrushPoly(msurface_t* fa);
void R_InitParticles(void);
void R_ClearParticles(void);
void GL_BuildLightmaps(void);
void EmitWaterPolys(msurface_t* fa);
void EmitSkyPolys(msurface_t* fa);
void EmitBothSkyLayers(msurface_t* fa);
void R_DrawSkyChain(msurface_t* s);
qboolean R_CullBox(const vec3_t & mins, const vec3_t & maxs);
void R_MarkLights(dlight_t* light, int bit, mnode_t* node);
void R_RotateForEntity(entity_t* e);
void R_StoreEfrags(efrag_t** ppefrag);
void GL_Set2D(void);