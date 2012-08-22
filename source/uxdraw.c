/*
 * uxdraw.c
 * This file is used to manage drawings in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */
#include "utils.h"

UX_MESH line;
UX_MESH rect;
int uxdraw_inited = false;


/** @defgroup ux_draw Drawing

	Draw routines.
	@{
*/

/** 
	\brief Initialize the drawing subsystem.
*/
void uxdraw_init() {
	// line allocation.
	line.traslation = (UX_VECTOR3D){ 0.0f, 0.0f, 0.0f };
	line.rotation = (UX_VECTOR3D){ 0.0f, 0.0f, 0.0f };
	line.scale = (UX_VECTOR3D){1.0f,1.0f,1.0f};
	line.material.hasTex = false;
	line.material.tex = NULL;
	line.in2D = true;
	line.dpoly = UX_LINES;
	line.vtype = UX_VTX_FASTVERTEX | UX_VTX_COLOR;
	line.count = 2;
	line.next = NULL;
	line.data = (VF_CP3 *)uxmemalloc(sizeof(VF_CP3) * 2);

	//rect allocation
	rect.traslation = (UX_VECTOR3D){ 0.0f, 0.0f, 0.0f };
	rect.rotation = (UX_VECTOR3D){ 0.0f, 0.0f, 0.0f };
	rect.scale = (UX_VECTOR3D){1.0f,1.0f,1.0f};
	rect.in2D = true;
	rect.dpoly = UX_TRIANGLESTRIP;
	rect.vtype = UX_VTX_FASTVERTEX | UX_VTX_COLOR;
	rect.count = 5;
	rect.next = NULL;
	rect.data = (VF_CP3 *)uxmemalloc(sizeof(VF_CP3) * 5);
}

/** 
	\brief Deinitializes the drawing subsystem.
*/
void uxdraw_shutdown() {
	uxmemfree(line.data);
	uxmemfree(rect.data);
}


/** 
	\brief Draws a line between (x1,y1) and (x2,y2).
	\param x1 Starting X point.
	\param y1 Starting Y point.
	\param x2 Ending X point.
	\param y2 Ending Y point.
	\param color Color of the line.
*/
void uxdraw_line(int x1, int y1, int x2, int y2, UXCOLOR color) {
	VF_CP3 * ptr = line.data;	// direct access to vertex data.
	
	ptr[0].x = x1;
	ptr[0].y = y1;
	ptr[0].color = UXCOLOR2U32COLOR(color);
	
	ptr[1].x = x2;
	ptr[1].y = y2;
	ptr[1].color = UXCOLOR2U32COLOR(color);
	
	uxgraphics_drawMesh(&line);
}


/** 
	\brief Draws a rectangle in (x,y) with size (w,h)
	\param x Starting X point.
	\param y Starting Y point.
	\param w Width.
	\param h Height.
	\param color Color of the lines.
*/
void uxdraw_rect(int x, int y, int w, int h, UXCOLOR color) {
	VF_CP3 * ptr = rect.data;
	
	ptr[0].x = x;
	ptr[0].y = y;
	ptr[0].z = 0;
	ptr[0].color = UXCOLOR2U32COLOR(color);

	ptr[1].x = x;
	ptr[1].y = y+h;
	ptr[1].z = 0;
	ptr[1].color = UXCOLOR2U32COLOR(color);

	ptr[2].x = x+w;
	ptr[2].y = y;
	ptr[2].z = 0;
	ptr[2].color = UXCOLOR2U32COLOR(color);

	ptr[3].x = x+w;
	ptr[3].y = y+h;
	ptr[3].z = 0;
	ptr[3].color = UXCOLOR2U32COLOR(color);
	
	ptr[4].x = x;
	ptr[4].y = y+h;
	ptr[4].z = 0;
	ptr[4].color = UXCOLOR2U32COLOR(color);
	
	uxgraphics_drawMesh(&rect);
}


/** @} */