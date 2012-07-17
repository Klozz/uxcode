#ifndef UXGRAPHICS_VERTEX_H
#define UXGRAPHICS_VERTEX_H

#include "uxgraphics.h"
#include "uximages.h"

#if defined(WII)
typedef enum {
	UX_POINTS			= GX_POINTS,
	UX_LINES			= GX_LINES,
	UX_LINESTRIP		= GX_LINESTRIP,
	UX_TRIANGLES		= GX_TRIANGLES,
	UX_TRIANGLESTRIP	= GX_TRIANGLESTRIP,
	UX_TRIANGLEFAN		= GX_TRIANGLEFAN,
	UX_QUADS			= GX_QUADS
} UX_TIPO_DRAWVERTEX;
#elif defined(PSP)
typedef enum {
	UX_POINTS			= GU_POINTS,
	UX_LINES			= GU_LINES,
	UX_LINESTRIP		= GU_LINE_STRIP,
	UX_TRIANGLES		= GU_TRIANGLES,
	UX_TRIANGLESTRIP	= GU_TRIANGLE_STRIP,
	UX_TRIANGLEFAN		= GU_TRIANGLE_FAN,
	UX_QUADS			= GU_SPRITES
} UX_TIPO_DRAWVERTEX;
#elif defined(_WIN32)
typedef enum {
	UX_POINTS			= 0,
	UX_LINES			= 0,
	UX_LINESTRIP		= 0,
	UX_TRIANGLES		= 0,
	UX_TRIANGLESTRIP	= 0,
	UX_TRIANGLEFAN		= 0,
	UX_RECT				= 0
} UX_TIPO_DRAWVERTEX;
#endif

typedef enum { 
	UX_VTX_COLOR		= 0x01,
	UX_VTX_TEXTURED		= 0x02,
	UX_VTX_NORMAL		= 0x04,
	UX_VTX_FASTVERTEX	= 0x08
} UX_TIPO_VERTICES;

typedef enum {
	UX_MATRIX_PERSPECTIVE 	= 0,
	UX_MATRIX_VIEW			= 1,
	UX_MATRIX_MODELVIEW		= 2,
	UX_MATRIX_WORLD			= 3,
	UX_MATRIX_NORMAL		= 4,
	UX_MATRIX_TEXTURE		= 5,
	UX_MATRIX_COLOR			= 6
} UX_TIPO_MATRIZ;



/* Vertices precisos 3D. Luadev R0 */
typedef struct { float u, v; UX_COLORU32 color; float nx, ny, nz; float x, y, z; } V_CTNP3;
typedef struct { float u, v; float nx, ny, nz; float x, y, z; } V_TNP3;
typedef struct { UX_COLORU32 color; float nx, ny, nz; float x, y, z; } V_CNP3;
typedef struct { float u, v; UX_COLORU32 color; float x, y, z; } V_CTP3;
typedef struct { UX_COLORU32 color; float x, y, z; } V_CP3;
typedef struct { float u, v; float x, y, z; } V_TP3;
typedef struct { float nx, ny, nz; float x, y, z; } V_NP3;
typedef struct { float x, y, z; } V_P3;

/* Vertices menos precisos, pero más rápidos 3D. Luadev R1 */
typedef struct { short u, v; unsigned long color; short nx, ny, nz; short x, y, z; } VF_CTNP3;
typedef struct { short u, v; short nx, ny, nz; short x, y, z; } VF_TNP3;
typedef struct { UX_COLORU32 color; short nx, ny, nz; short x, y, z; } VF_CNP3;
typedef struct { short u, v; UX_COLORU32 color;  short x, y, z; } VF_CTP3;
typedef struct { UX_COLORU32 color; short x, y, z; } VF_CP3;
typedef struct { short u, v; short x, y, z; } VF_TP3;
typedef struct { short nx, ny, nz; short x, y, z; } VF_NP3;
typedef struct { short x, y, z; } VF_P3;

typedef struct UX_MATERIAL {
	UX_COLORU32 color;				// color
	unsigned int hasTex;			// has texture
	UX_IMAGE* tex;					// textura
} UX_MATERIAL;

typedef struct UX_MESH {
	UX_VECTOR3D traslation;
	UX_VECTOR3D rotation;
	UX_MATERIAL material;
	unsigned int in2D;				// force2D or force3D
	unsigned int dpoly;				// tipo de dibujado.
	unsigned int vtype;				// tipo de vertice de esta mesh. (Una mesh es una lista de vertices que describen algo 3D o 2D)
	unsigned int count;				// numero de vertices.
	void * next;					// siguiente mesh.
	void * data;					// puntero a los datos guardados.
} UX_MESH;


/* Exports */
#ifdef WII
extern void uxgraphics_precachevtype(int vtype,int vindex);
extern int uxgraphics_vertex_slot(int vtype);
#endif

extern void uxgraphics_drawMesh(UX_MESH *mesh);

extern UX_MESH* uxgraphics_genTexMesh(UX_IMAGE* img);

extern void uxgraphics_freeMesh(UX_MESH* mesh);

#endif