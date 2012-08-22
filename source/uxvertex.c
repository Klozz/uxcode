/*
 * uxvertex.c
 * This file is used to manage vertex formats in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#include "utils.h"

#if defined(WII)
/*
 * Seleccion del SLOT de vertices. (Frequente: precargado, Extraño: Agregar a registro 7)
 *   Precargados: 
 * 		2D	UX_TIPO_VERTICE2D|UX_VTX_COLOR														(formas solidas)			05
 * 		2D	UX_TIPO_VERTICE2D|UX_VTX_COLOR|UX_VTX_TEXTURED										(imágenes y sprites)		0D
 *
 * 		3D	UX_TIPO_VERTICE3D|UX_VTX_NORMAL|UX_VTX_COLOR|UX_VTX_TEXTURED|UX_VTX_FASTVERTEX		(full fast)					3E
 * 		3D	UX_TIPO_VERTICE3D|UX_VTX_COLOR|UX_VTX_TEXTURED|UX_VTX_FASTVERTEX					(color+tex fast)			2E
 * 		3D	UX_TIPO_VERTICE3D|UX_VTX_NORMAL|UX_VTX_COLOR|UX_VTX_TEXTURED						(full preciso)				1E
 * 		3D	UX_TIPO_VERTICE3D|UX_VTX_COLOR|UX_VTX_TEXTURED										(color+tex preciso)			0E
 * 		3D	UX_TIPO_VERTICE3D|UX_VTX_NORMAL|UX_VTX_COLOR|UX_VTX_FASTVERTEX						(celshading fast)			36
 *		
 *		??	PERSONALIZABLE																		(otro tipo)
 * 
 */

void uxgraphics_precachevtype(int vtype,int vindex) {
	if (vtype & UX_VTX_FASTVERTEX) {
		GX_SetVtxAttrFmt(vindex, GX_VA_POS,  GX_POS_XYZ,  GX_S16, 0);
		if (vtype & UX_VTX_TEXTURED){ GX_SetVtxAttrFmt(vindex, GX_VA_TEX0,  GX_TEX_ST,  GX_S16, 10); }
		if (vtype & UX_VTX_COLOR) 	{ GX_SetVtxAttrFmt(vindex, GX_VA_CLR0,  GX_CLR_RGBA,  GX_RGBA8, 0); }
		if (vtype & UX_VTX_NORMAL) 	{ GX_SetVtxAttrFmt(vindex, GX_VA_NRM,  GX_NRM_XYZ,  GX_S16, 10); }
	} else {
		GX_SetVtxAttrFmt(vindex, GX_VA_POS,  GX_POS_XYZ,  GX_F32, 0);
		if (vtype & UX_VTX_TEXTURED) 	{ GX_SetVtxAttrFmt(vindex, GX_VA_TEX0,  GX_TEX_ST,  GX_F32, 0); }
		if (vtype & UX_VTX_COLOR) 	{ GX_SetVtxAttrFmt(vindex, GX_VA_CLR0,  GX_CLR_RGBA,  GX_RGBA8, 0); }
		if (vtype & UX_VTX_NORMAL) 	{ GX_SetVtxAttrFmt(vindex, GX_VA_NRM,  GX_NRM_XYZ,  GX_F32, 0); }
	}
}
 
int uxgraphics_vertex_slot(int vtype) {
	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS,GX_DIRECT);
	if (vtype & UX_VTX_NORMAL) { GX_SetVtxDesc(GX_VA_NRM,GX_DIRECT); }
	if (vtype & UX_VTX_COLOR) { GX_SetVtxDesc(GX_VA_CLR0,GX_DIRECT); }
	if (vtype & UX_VTX_TEXTURED) { GX_SetVtxDesc(GX_VA_TEX0,GX_DIRECT); }
	
	switch (vtype) {
		case 0x0A: return GX_VTXFMT0;
		case 0x09: return GX_VTXFMT1;
		case 0x0F: return GX_VTXFMT2;
		case 0x02: return GX_VTXFMT3;
		case 0x01: return GX_VTXFMT4;
		case 0x07: return GX_VTXFMT5;
		case 0x03: return GX_VTXFMT6;
		default: uxgraphics_precachevtype(vtype,GX_VTXFMT7); return GX_VTXFMT7;
	}
}

inline void uxgraphics_vertex_drawMesh_fcol(VF_CP3* v, u32 n) {
	register u32 i = 0, j = 0;
	for (i=n;i!=0x0;i--) { GX_Position3s16(v[j].x,v[j].y,v[j].z); GX_Color1u32(v[j].color); j++; }
}

inline void uxgraphics_vertex_drawMesh_col(V_CP3* v, u32 n) {
	register u32 i = 0, j = 0;
	for (i=n;i!=0x0;i--) { GX_Position3f32(v[j].x,v[j].y,v[j].z); GX_Color1u32(v[j].color); j++; }
}

inline void uxgraphics_vertex_drawMesh_ftex(VF_TP3* v, u32 n) {
	register u32 i = 0, j = 0;
	for (i=n;i!=0x0;i--) { GX_Position3s16(v[j].x,v[j].y,v[j].z); GX_TexCoord2s16(v[j].u, v[j].v); j++; }
}

inline void uxgraphics_vertex_drawMesh_tex(V_TP3* v, u32 n) {
	register u32 i = 0, j = 0;
	for (i=n;i!=0x0;i--) { GX_Position3f32(v[j].x,v[j].y,v[j].z); GX_TexCoord2f32(v[j].u, v[j].v); j++; }
}

inline void uxgraphics_vertex_drawMesh_ffull(VF_CTNP3* v, u32 n) {
	register u32 i = 0, j = 0;
	for (i=n;i!=0x0;i--) { GX_Position3s16(v[j].x,v[j].y,v[j].z); GX_TexCoord2s16(v[j].u, v[j].v); GX_Color1u32(v[j].color); GX_Normal3s16(v[j].nx,v[j].ny,v[j].nz); j++; }
}

inline void uxgraphics_vertex_drawMesh_full(V_CTNP3* v, u32 n) {
	register u32 i = 0, j = 0;
	for (i=n;i!=0x0;i--) { GX_Position3f32(v[j].x,v[j].y,v[j].z); GX_TexCoord2f32(v[j].u, v[j].v); GX_Color1u32(v[j].color); GX_Normal3f32(v[j].nx,v[j].ny,v[j].nz); j++; }
}

inline void uxgraphics_vertex_drawMesh_coltex(V_CTP3* v, u32 n) {
	register u32 i = 0, j = 0;
	for (i=n;i!=0x0;i--) { GX_Position3f32(v[j].x,v[j].y,v[j].z); GX_TexCoord2f32(v[j].u, v[j].v); GX_Color1u32(v[j].color); j++; }
}
#endif




void uxgraphics_drawMesh(UX_MESH *mesh) {
	uxgraphics_setViewMode(dView,!(mesh->in2D));
	uxgraphics_modelmatrix();
	
	if (mesh->material.hasTex) {
		uximages_transferimage(mesh->material.tex);
		
		#if defined(WII)
		GX_SetTevOp(GX_TEVSTAGE0, GX_REPLACE);
		
		GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
		GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
		GX_SetNumTevStages(1);
		
		GX_SetNumChans(1);
		GX_SetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
		GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
		#endif
		
		#if defined(PSP)
		sceGuEnable(GU_TEXTURE_2D);
		sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA);
		//sceGuTexMapMode(GU_TEXTURE_COORDS,0,1);
		#endif
	}
	#if defined(WII)
		UX_MATRIX modelView;
		UX_MATRIX rotational;
		guMtxIdentity(modelView);
		guMtxConcat(dView.view,modelView,modelView);		//vigilar dView.view! se aplica cam?
		guMtxRotRad(modelView,'X',mesh->rotation.x);
		guMtxRotRad(rotational,'Y',mesh->rotation.y); guMtxConcat(modelView,rotational,modelView);
		guMtxRotRad(rotational,'Z',mesh->rotation.z); guMtxConcat(modelView,rotational,modelView);
		
		guMtxTransApply(modelView,modelView,mesh->traslation.x,mesh->traslation.y,mesh->traslation.z);
		GX_LoadPosMtxImm(modelView,	GX_PNMTX0);
		
		GX_Begin(mesh->dpoly, uxgraphics_vertex_slot(mesh->vtype), mesh->count);
		switch (mesh->vtype) {
			case 0x0A: uxgraphics_vertex_drawMesh_ftex((VF_TP3*)mesh->data,mesh->count); break;
			case 0x09: uxgraphics_vertex_drawMesh_fcol((VF_CP3*)mesh->data,mesh->count); break;
			case 0x0F: uxgraphics_vertex_drawMesh_ffull((VF_CTNP3*)mesh->data,mesh->count); break;
			case 0x02: uxgraphics_vertex_drawMesh_tex((V_TP3*)mesh->data,mesh->count); break;
			case 0x01: uxgraphics_vertex_drawMesh_col((V_CP3*)mesh->data,mesh->count); break;
			case 0x07: uxgraphics_vertex_drawMesh_full((V_CTNP3*)mesh->data,mesh->count); break;
			case 0x03: uxgraphics_vertex_drawMesh_coltex((V_CTP3*)mesh->data,mesh->count); break;
			default: break;
		}
		GX_End();
	#elif defined(PSP)
		unsigned int transform3d = GU_TRANSFORM_2D;
		if (!mesh->in2D) { transform3d = GU_TRANSFORM_3D; }
		sceGumPushMatrix();
		sceGumTranslate((ScePspFVector3*)(&(mesh->traslation)));
		sceGumRotateXYZ((ScePspFVector3*)(&(mesh->rotation)));
		sceGumUpdateMatrix();
		switch (mesh->vtype) {
			case 0x0A: sceGumDrawArray(mesh->dpoly, GU_TEXTURE_16BIT|GU_VERTEX_16BIT|transform3d, mesh->count, 0, mesh->data); break;	//fast texture
			case 0x09: sceGumDrawArray(mesh->dpoly, GU_COLOR_8888|GU_VERTEX_16BIT|transform3d, mesh->count, 0, mesh->data); break;		//fast color
			case 0x0F: sceGumDrawArray(mesh->dpoly, GU_TEXTURE_16BIT|GU_COLOR_8888|GU_VERTEX_16BIT|GU_NORMAL_16BIT|transform3d, mesh->count, 0, mesh->data); break;	//fast full
			case 0x02: sceGumDrawArray(mesh->dpoly, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|transform3d, mesh->count, 0, mesh->data); break;	//precise texture
			case 0x01: sceGumDrawArray(mesh->dpoly, GU_COLOR_8888|GU_VERTEX_32BITF|transform3d, mesh->count, 0, mesh->data); break;		//precise color
			case 0x07: sceGumDrawArray(mesh->dpoly, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_NORMAL_32BITF|transform3d, mesh->count, 0, mesh->data); break; //precise full
			case 0x03: sceGumDrawArray(mesh->dpoly, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|transform3d, mesh->count, 0, mesh->data); break; //color texture
			default: break;
		}
		sceGumPopMatrix();
	#elif defined(PC)
		//...
	#endif
	
	if (mesh->material.hasTex) {
		#if defined(WII)
		GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
		#endif
		#if defined(PSP)
		sceGuDisable(GU_TEXTURE_2D);
		#endif
	}
	
	return;
}

UX_MESH* uxgraphics_genTexMesh(UX_IMAGE* img) {
	UX_MESH* damesh;
	V_TP3* meshdata;
	
	damesh = (UX_MESH*)uxmemalloc(sizeof(UX_MESH));
	uxmemset(damesh,0,sizeof(UX_MESH));
	damesh->traslation 			= (UX_VECTOR3D){ 0.0f, 0.0f, 0.0f };
	damesh->rotation 			= (UX_VECTOR3D){ 0.0f, 0.0f, 0.0f };
	damesh->scale 				= (UX_VECTOR3D){ 1.0f, 1.0f, 1.0f };

	damesh->material.hasTex 	= true;
	damesh->material.tex 		= img;
	damesh->in2D 				= true;
	damesh->dpoly 				= UX_QUADS;
	damesh->vtype 				= UX_VTX_TEXTURED;
	damesh->count 				= 4;
	damesh->next 				= NULL;
	
	#ifdef PSP
	damesh->dpoly 				= UX_TRIANGLESTRIP;
	meshdata	 				= (V_TP3*)uxmemalloc(sizeof(V_TP3)*4); 
	if(!meshdata) { uxmemfree(damesh); return NULL; }
	meshdata[0].u = 0.0f;
	meshdata[0].v = 0.0f;
	meshdata[0].x = -(img->w / 2.0f); 
	meshdata[0].y = -(img->h / 2.0f); 
	meshdata[0].z = 0.0f;
	
	meshdata[1].u = 1.0f;
	meshdata[1].v = 0.0f;
	meshdata[1].x = (img->w / 2.0f); 
	meshdata[1].y = -(img->h / 2.0f); 
	meshdata[1].z = 0.0f;
	
	meshdata[3].u = 1.0f;
	meshdata[3].v = 1.0f;
	meshdata[3].x = (img->w / 2.0f); 
	meshdata[3].y = (img->h / 2.0f); 
	meshdata[3].z = 0.0f;
	
	meshdata[2].u = 0.0f;
	meshdata[2].v = 1.0f;
	meshdata[2].x = -(img->w / 2.0f);
	meshdata[2].y = (img->h / 2.0f); 
	meshdata[2].z = 0.0f;
	
	#else
	meshdata	 				= (V_TP3*)uxmemalloc(sizeof(V_TP3)*4);
	if(!meshdata) { uxmemfree(damesh); return NULL; }
	meshdata[0].u = 0.0f;
	meshdata[0].v = 0.0f;
	meshdata[0].x = -(img->w / 2.0f); 
	meshdata[0].y = -(img->h / 2.0f); 
	meshdata[0].z = 0.0f;
	
	meshdata[1].u = 1.0f;
	meshdata[1].v = 0.0f;
	meshdata[1].x = (img->w / 2.0f); 
	meshdata[1].y = -(img->h / 2.0f); 
	meshdata[1].z = 0.0f;
	
	meshdata[2].u = 1.0f;
	meshdata[2].v = 1.0f;
	meshdata[2].x = (img->w / 2.0f); 
	meshdata[2].y = (img->h / 2.0f); 
	meshdata[2].z = 0.0f;
	
	meshdata[3].u = 0.0f;
	meshdata[3].v = 1.0f;
	meshdata[3].x = -(img->w / 2.0f);
	meshdata[3].y = (img->h / 2.0f); 
	meshdata[3].z = 0.0f;
	#endif

	damesh->data = (void*)meshdata;
	return damesh;
}


void uxgraphics_freeMesh(UX_MESH* mesh) {
	if(mesh) {
		if (mesh->data) { uxmemfree(mesh->data); }
		uxmemfree(mesh->data);
	}
}