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


void uxdraw_init() {
	// line allocation.
	line.traslation = (UX_VECTOR3D){ 0.0f, 0.0f, 0.0f };
	line.rotation = (UX_VECTOR3D){ 0.0f, 0.0f, 0.0f };
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
	rect.in2D = true;
	rect.dpoly = UX_LINESTRIP;
	rect.vtype = UX_VTX_FASTVERTEX | UX_VTX_COLOR;
	rect.count = 5;
	rect.next = NULL;
	rect.data = (VF_CP3 *)uxmemalloc(sizeof(VF_CP3) * 5);
}

void uxdraw_shutdown() {
	uxmemfree(line.data);
	uxmemfree(rect.data);
}


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


void uxdraw_rect(int x, int y, int w, int h, UXCOLOR color) {
	VF_CP3 * ptr = rect.data;
	
	ptr[0].x = x;
	ptr[0].y = y;
	ptr[0].color = UXCOLOR2U32COLOR(color);

	ptr[1].x = x+w;
	ptr[1].y = y;
	ptr[1].color = UXCOLOR2U32COLOR(color);

	ptr[2].x = x+w;
	ptr[2].y = y+h;
	ptr[2].color = UXCOLOR2U32COLOR(color);

	ptr[3].x = x;
	ptr[3].y = y+h;
	ptr[3].color = UXCOLOR2U32COLOR(color);
	
	ptr[4].x = x;
	ptr[4].y = y;
	ptr[4].color = UXCOLOR2U32COLOR(color);
	
	uxgraphics_drawMesh(&rect);
}