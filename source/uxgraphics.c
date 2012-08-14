/*
 * uxgraphics.c
 * This file is used to manage graphics subsystem in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#include "utils.h"

int uxgraphics_inited           = 0;
int uxgraphics_lastPerspective  = 0;
int uxgraphics_in3D             = 0;

/* Variables internas...*/
void *framebuffers[2] = {NULL, NULL};
int fb = 0;

/** @defgroup ux_graphics Graphics

@{
\brief Graphics subsystem.

Docs and manuals:
 - (WIN32) OpenGL: http://www.opengl.org/sdk/docs/man/
 - (PSP) PSPSDK: http://psp.jim.sh/pspsdk-doc/files.html
 - (WII) LIBOGC: http://libogc.devkitpro.org/gx_8h.html
 - (NDS) LIBNDS: http://libnds.devkitpro.org/index.html
 
 \todo
			- graphics documentation
			- unify matrixes
			- stencil buffer (pc,psp). Emulate stencil (wii)
			- multiple draw-lists.
			- initialize matrixes.
			- PSP vram 2mb handling.
*/




/* Pero de forma bonita... */
UX_GRAPHICSMODE graphics_mode;
UX_IMAGE        dispBuffer;
UX_IMAGE        drawBuffer;
//static UX_FONT defFont;               /* Fuente por defecto */
UX_RENDER       dRender;                /* Render por defecto */
UX_VIEWPORT     dView;                  /* Viewport por defecto */


#if defined(_WIN32)
	HWND        handleWnd;
	HDC         handleDC;
	HGLRC       handleRC;
	static int gl_logic_op_supported    = 0;
#endif
#if defined(WII)
	GXRModeObj *rmode                   = NULL;
	void *gp_fifo                       = NULL;
#endif
#if defined(PSP)
	#define PSP_UVRAM_BASE              ((u8*)0x04000000)
	#define PSP_UVRAM_SIZE              (2 << 20)
	#define PSP_UVRAM_END               ((u8*)((u32)PSP_UVRAM_BASE + PSP_UVRAM_SIZE))
	static unsigned int *GX_G_3Dlist    = NULL;
#endif


 /**
  * \brief Graphics initialization
  */
int uxgraphics_init(UX_GRAPHICSMODE * window) {
	if (uxgraphics_inited) { return 0; }
	uxgraphics_in3D = 1;
	
	uxmemset(&dView,0,sizeof(UX_VIEWPORT));					// Reset viewport
	uxmemset(&dRender,0,sizeof(UX_RENDER));					// Reset render
	uxmemset(&dispBuffer,0,sizeof(UX_IMAGE));				// Reset display buffer
	uxmemset(&drawBuffer,0,sizeof(UX_IMAGE));				// Reset draw buffer

	/* CONFIGURACION DEL VIEWPORT */
	dView.sync                      = 1;
	dView.window                    = (UX_INTBOX){window->w_width,window->w_height,window->width,window->height};
	dRender.scissor_box             = (UX_INTBOX){0,0,window->width,window->height};
	dView._near                     = 0;//10000;
	dView._far                      = 60000;//50000;

	//Perspective 3D.
	dView.perspective3D.fovy        = 75.0f;
	dView.perspective3D.aspect      = 16.0f/9.0f;
	dView.perspective3D._near       = 0.5f;
	dView.perspective3D._far        = 8000.0f;//1000.0f;
	//Ortho 2D.
	dView.ortho2D.left              = 0.0f;
	dView.ortho2D.right             = dView.window.w;
	dView.ortho2D.bottom            = dView.window.h;
	dView.ortho2D.top               = 0.0f;
	dView.ortho2D._near             = -1.0f;
	dView.ortho2D._far              = 1.0f;
	//Camara 3D inicial
	dView.cam3.pos                  = (UX_VECTOR3D){ 0.0f, 0.0f, 0.0f };
	dView.cam3.up                   = (UX_VECTOR3D){ 0.0f, 1.0f, 0.0f };
	dView.cam3.look                 = (UX_VECTOR3D){ 0.0f, 0.0f, -1.0f };
	
	/* CONFIGURACION DEL RENDER POR DEFECTO */
	dRender.clear_color             = UXRGBA(0,0,0,0);
	dRender.clear_depth             = 0xFFFFFF;
	dRender.depthtest_enabled       = false;
	dRender.depthtest_function      = UX_GL_ALWAYS;
	dRender.depthtest_writes        = false;
	dRender.faceculling_enabled     = false;
	dRender.faceculling             = UX_GL_CULLBACK;
	dRender.texture3d_enabled       = false;
	dRender.texture2d_enabled       = false;
	dRender.blending_enabled        = false;
	dRender.blending_operator       = UX_BO_ADD;
	dRender.blending_src_function   = UX_BF_SRC_ALPHA;
	dRender.blending_dst_function   = UX_BF_ONE_MINUS_SRC_ALPHA;
	dRender.blending_logic          = 0;
	dRender.alphatest_enabled       = false;
	dRender.alphatest_operator      = UX_AT_ALWAYS;
	dRender.alphatest_reference     = 0;
	dRender.scissor_enabled         = false;
	
	dispBuffer.w                    = window->width;
	dispBuffer.h                    = window->height;
	dispBuffer.realw                = window->width;
	dispBuffer.realh                = window->height;
	dispBuffer.u0                   = 0.0f;
	dispBuffer.v0                   = 0.0f;
	dispBuffer.u1                   = 1.0f;
	dispBuffer.v1                   = 1.0f;
	dispBuffer.ptr                  = NULL;
	dispBuffer.dataSize             = 0;
	uxmemcopy(&drawBuffer,&dispBuffer,sizeof(UX_IMAGE));
	drawBuffer.ptr                  = NULL;

	/* MALLOC BUFFERS Y ARRANQUE DEL SISTEMA */
#if defined(_WIN32)

	if ( !GLEW_EXT_blend_func_separate ) { return -1; }
	if ( GLEW_EXT_blend_logic_op ) { gl_logic_op_supported = 1; }

#elif defined(PSP)

	uxgraphics_renderListMalloc(1 << 20);				/* 1mb lista 3D */
	sceGuInit();
	sceGuStart(GU_DIRECT, GX_G_3Dlist);
	sceGuDisplay(0);									/* SCREEN OFF */
	sceGuDrawBuffer(uxgraphics_nearestPixelFormat(window->pixelFormat),(void*)0,512);
	sceGuDispBuffer(window->width,window->height,(void*)0x88000,512);		/* Display buffer, draw buffer */
	framebuffers[0] = (void*)PSP_UVRAM_BASE;
	framebuffers[1] = (void*)(PSP_UVRAM_BASE + (0x88000));
	sceGuDepthBuffer((void*)0x110000, 512);				/* Depth buffer config */

	dispBuffer.realw                = 512;
	dispBuffer.realh                = 272;
	dispBuffer.ptr                  = framebuffers[0];
	dispBuffer.dataSize             = (0x22000 * 32)>>3;
	uxmemcopy(&drawBuffer,&dispBuffer,sizeof(UX_IMAGE));
	drawBuffer.ptr                  = framebuffers[1];
	sceGuShadeModel(GU_SMOOTH);

#elif defined(WII)
	f32 yscale;
	u32 xfbHeight;

	VIDEO_Init();
	VIDEO_SetBlack(true);
	if ( !(rmode = VIDEO_GetPreferredMode(NULL)) ) { return -1; }
	if (rmode->viTVMode==VI_DEBUG_PAL) { rmode = &TVPal528IntDf; }
	if (CONF_GetAspectRatio() == CONF_ASPECT_16_9) { rmode->viWidth = 678; rmode->viXOrigin = (VI_MAX_WIDTH_PAL - 678)/2; dView.perspective3D.aspect = 16.0f/9.0f; }
	else { rmode->viWidth = 672; rmode->viXOrigin = (VI_MAX_WIDTH_NTSC - 672)/2; dView.perspective3D.aspect = 4.0f/3.0f; }
	VIDEO_Configure(rmode);
	if ( !(framebuffers[0] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode))) )  return -1;
	if ( !(framebuffers[1] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode))) )  return -1;
	VIDEO_SetNextFramebuffer(framebuffers[fb]);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if (rmode->viTVMode & VI_NON_INTERLACE) { VIDEO_WaitVSync(); }
	
	if ( !(gp_fifo = uxmemalign(32, 256 * 1024)) )  return -1;
	uxmemset(gp_fifo, 0, (256 * 1024));
	GX_Init(gp_fifo, (256 * 1024));
	if (rmode->aa) { GX_SetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR); } else { GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR); }
	yscale    = GX_GetYScaleFactor(rmode->efbHeight, rmode->xfbHeight);
	xfbHeight = GX_SetDispCopyYScale(yscale);

	dispBuffer.w                    = rmode->fbWidth;
	dispBuffer.h                    = xfbHeight;
	dispBuffer.realw                = rmode->fbWidth;
	dispBuffer.realh                = rmode->efbHeight;
	dispBuffer.u0                   = 0.0f;
	dispBuffer.v0                   = 0.0f;
	dispBuffer.u1                   = 1.0f;
	dispBuffer.v1                   = 1.0f;
	dispBuffer.ptr                  = framebuffers[0];
	dispBuffer.dataSize             = 0;
	uxmemcopy(&drawBuffer,&dispBuffer,sizeof(UX_IMAGE));
	drawBuffer.ptr                  = framebuffers[1];
	
	// buffer copy
	GX_SetDispCopySrc(0, 0, rmode->fbWidth, rmode->efbHeight);
	GX_SetDispCopyDst(rmode->fbWidth, xfbHeight);
	GX_SetCopyFilter(rmode->aa, rmode->sample_pattern, GX_TRUE, rmode->vfilter);
	GX_SetFieldMode(rmode->field_rendering, ((rmode->viHeight == 2 * rmode->xfbHeight) ? GX_ENABLE : GX_DISABLE));
	GX_SetDispCopyGamma(GX_GM_1_0);

#endif

	uxgraphics_setViewport(dView,false);
	uxgraphics_setViewMode(dView,false,false);
	uxgraphics_setRenderMode(dRender);

	/* Finalizando... */
#if defined(PSP)
	sceGuFinish();
	sceGuSync(0,0);
	sceDisplayWaitVblankStart();
	sceGuDisplay(1);
#endif
#if defined(WII)
	GX_InvVtxCache();
	uxgraphics_precachevtype(UX_VTX_FASTVERTEX | UX_VTX_TEXTURED, GX_VTXFMT0);
	uxgraphics_precachevtype(UX_VTX_FASTVERTEX | UX_VTX_COLOR , GX_VTXFMT1);
	uxgraphics_precachevtype(UX_VTX_FASTVERTEX | UX_VTX_COLOR | UX_VTX_TEXTURED | UX_VTX_NORMAL , GX_VTXFMT2);
	uxgraphics_precachevtype(UX_VTX_TEXTURED , GX_VTXFMT3);
	uxgraphics_precachevtype(UX_VTX_COLOR , GX_VTXFMT4);
	uxgraphics_precachevtype(UX_VTX_COLOR | UX_VTX_TEXTURED | UX_VTX_NORMAL , GX_VTXFMT5);
	uxgraphics_precachevtype(UX_VTX_COLOR | UX_VTX_TEXTURED , GX_VTXFMT6);
	
	guMtxIdentity(dView.modelview);
	
	GX_SetNumChans(1);				// 1 chan... si claro... ya kisieran los demas xD. toDo: hacer el super colorman?
	GX_SetNumTexGens(1);			// Aki hay que hacer un TEXMAN! (texture manager) pq esto tiene de opciones que lloras y todo...

	GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
	
	GX_SetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
	GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);

	GX_SetColorUpdate(GX_ENABLE);
	VIDEO_SetBlack(false);
#endif

	uxgraphics_inited = 1;
	return 0;
}

/**
 ** PixelFormat
 **/
int uxgraphics_nearestPixelFormat(enum UX_PIXELFORMAT pf) {
	#if defined(PSP)
		switch (pf) {
			case UX_PF_5650: return GU_PSM_5650;		
			case UX_PF_5551: return GU_PSM_5551;
			case UX_PF_4444: return GU_PSM_4444;
			case UX_PF_6666: return GU_PSM_8888;
			case UX_PF_8880: return GU_PSM_8888;
			case UX_PF_8888: return GU_PSM_8888;
			case UX_PF_2BIT: return GU_PSM_T4;
			case UX_PF_4BIT: return GU_PSM_T4;
			case UX_PF_8BIT: return GU_PSM_T8;
			case UX_PF_DXT1: return GU_PSM_DXT1;
			case UX_PF_DXT3: return GU_PSM_DXT3;
			case UX_PF_DXT5: return GU_PSM_DXT5;
		}
	#elif defined(WII)
		switch (pf) {
			case UX_PF_5650: return GX_PF_RGB565_Z16;		
			case UX_PF_8880: return GX_PF_RGB8_Z24;
			default: return GX_PF_RGBA6_Z24;
		}
	#elif defined(NDS)
		switch (pF) {
			case UX_PF_4BIT: return 4;
			case UX_PF_8BIT: return 8;
			default: return 1555;
		}
	#elif defined(_WIN32)
		return 1;
	#endif
}


/*
 *  Algo de memoria para las listas 3D.
 */
void uxgraphics_renderListMalloc(int size) {
#if defined(PSP)
	if (GX_G_3Dlist!=NULL) { uxmemfree(GX_G_3Dlist); }
	GX_G_3Dlist = (unsigned int*)uxmemalign(16,size);
#endif
}


/*
 *  Setea la ventana de vision al mundo...
 */
void uxgraphics_setViewport(UX_VIEWPORT view, int mode) {
#if defined(_WIN32)
	glViewport(view.window.x,view.window.y,view.window.w,view.window.h);
	glDepthRange((double)(view._near / 0xFFFF),(double)(view._far / 0xFFFF));
#endif
#if defined(PSP)
	sceGuOffset(view.window.x - (view.window.w >> 1),view.window.y - (view.window.h >> 1));
	sceGuViewport(view.window.x,view.window.y,view.window.w,view.window.h);
	sceGuDepthRange(view._far, view._near);
#endif
#if defined(WII)
	GX_SetViewport((float)view.window.x, (float)view.window.y, (float)view.window.w, (float)view.window.h, (float)(view._near/0xFFFF), (float)(view._far/0xFFFF) );
#endif
}

/*
 * Setea la proyeccion.
 */
static void uxgraphics_projection(UX_VIEWPORT view, int mode) {
#if defined(_WIN32)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (mode) { gluPerspective(view.perspective3D.fovy,view.perspective3D.aspect,view.perspective3D._near,view.perspective3D._far); }
	else { gluOrtho2D(view.ortho2D.left,view.ortho2D.right+6,view.ortho2D.bottom,view.ortho2D.top-30); }
#endif
#if defined(WII)
	if (mode) { guPerspective(view.proypers, view.perspective3D.fovy, view.perspective3D.aspect, view.perspective3D._near, view.perspective3D._far); GX_LoadProjectionMtx(view.proypers, GX_PERSPECTIVE); }
	else { guOrtho(view.proyort2, view.ortho2D.top, view.ortho2D.bottom, view.ortho2D.left, view.ortho2D.right, view.ortho2D._near, view.ortho2D._far); GX_LoadProjectionMtx(view.proyort2, GX_ORTHOGRAPHIC); }
#endif
#if defined(PSP)
	sceGumMatrixMode(GU_PROJECTION);
	sceGumLoadIdentity();
	if (mode) { sceGumPerspective( view.perspective3D.fovy, view.perspective3D.aspect, view.perspective3D._near, view.perspective3D._far); }
	else { sceGumOrtho(view.ortho2D.left,view.ortho2D.right,view.ortho2D.bottom,view.ortho2D.top,view.ortho2D._near,view.ortho2D._far); }
#endif
}

void uxgraphics_viewmatrix(UX_VIEWPORT view, int mode) {
#if defined(_WIN32)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Apply cam.
#endif
#if defined(WII)
	guMtxIdentity(view.view);
	if (mode) { guLookAt(view.view, (guVector *)&(view.cam3.pos), (guVector *)&(view.cam3.up),(guVector *)&(view.cam3.look)); }
	else { 
		guVector pos = (guVector){0.0f,0.0f,0.0f};
		guVector up = (guVector){0.0f,1.0f,0.0f};
		guVector look = (guVector){0.0f,0.0f,1.0f};
		guLookAt(view.view,&pos,&up,&look);
	}
#endif
#if defined(PSP)
	sceGumMatrixMode(GU_VIEW);
	sceGumLoadIdentity();
	if (mode) { sceGumLookAt((ScePspFVector3 *)&(view.cam3.pos),(ScePspFVector3 *)&(view.cam3.look),(ScePspFVector3 *)&(view.cam3.up)); }
#endif
}

void uxgraphics_modelmatrix() {
#if defined(_WIN32)
	glPushMatrix();
#endif
#if defined(WII)
	
#endif
#if defined(PSP)
	sceGumMatrixMode(GU_MODEL);
	sceGumLoadIdentity();
#endif
}

/*
 * Setea el color para el limpiado de la pantalla, y el buffer de profundidad.
 */
static void uxgraphics_clearmode(UXCOLOR clear_color, unsigned int clear_depth) {
#if defined(_WIN32)
	glClearColor(UXR(clear_color), UXG(clear_color), UXB(clear_color), UXA(clear_color));
	glClearDepth( (float)(clear_depth / 0xffffff) ); // 24bits 0.0f - 1.0f
#endif
#if defined(WII)
	GX_SetCopyClear( clear_color, clear_depth );
#endif
#if defined(PSP)
	sceGuClearColor(clear_color);
	sceGuClearDepth(clear_depth & 0xFFFF); // 16bits.
#endif
}

/*
 * Setea la function para el test de profundidad.
 */
static void uxgraphics_depthtest(int enabled, int test_function, int canwrite) {
#if defined(_WIN32)
	/* DEPTH TEST CONFIG */
#endif
#if defined(WII)
	GX_SetZMode(enabled, test_function,canwrite);
#endif
#if defined(PSP)
	sceGuDepthMask(canwrite);
	sceGuDepthFunc(test_function);
	sceGuSetStatus(GU_DEPTH_TEST,enabled);
#endif
}

/*
 *  Face Culling
 */
static void uxgraphics_faceCulling(int mode, int enabled) {
#if defined(_WIN32)
	glCullFace(mode);
	if (enabled) { glEnable(GL_CULL_FACE); } else { glDisable(GL_CULL_FACE); }
#endif
#if defined(PSP)
	sceGuSetStatus(GU_CULL_FACE,enabled);
	sceGuFrontFace(mode);
#endif
#if defined(WII)
	GX_SetCullMode( (enabled?mode:GX_CULL_NONE) );
#endif
}

/*
 * Alpha Test
 */ 
static void uxgraphics_alphatest(int enabled, int op, int reference) {
#if defined(_WIN32)
	if (!enabled) { glDisable(GL_ALPHA_TEST); return; }
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(op,reference);
#endif
#if defined(WII)
	GX_SetAlphaUpdate(enabled);
	GX_SetAlphaCompare(op,reference,GX_AOP_AND,GX_ALWAYS,0);	// wii puede combinar dos alphatest. por defecto, ((val op ref) AND (1)). limitamos a una función.
#endif
#if defined(PSP) 
	sceGuSetStatus(GU_ALPHA_TEST,enabled);
	sceGuAlphaFunc(op,reference,0xFF);							// and mask 0xFF (full value).
#endif
}

/*
 *  Blending Effects:
 */
static void uxgraphics_blending(int enabled, int op, int srcf, int dstf, int logic) {
#if defined(_WIN32)
	if (!enabled) { glDisable(GL_BLEND); return; }
	if (op==UX_BO_BIT) { glEnable(GL_COLOR_LOGIC_OP); glLogicOp(logic); } else { glDisable(GL_COLOR_LOGIC_OP); }
	if (op==-1 || srcf==-1 || dstf==-1) { return; }
	glEnable(GL_BLEND);
	glBlendEquation(op);
	glBlendFunc(srcf,dstf);
#endif
#if defined(PSP)
	if (!enabled) { sceGuDisable(GU_BLEND); return; }
	if (op==UX_BO_BIT) { sceGuEnable(GU_COLOR_LOGIC_OP); sceGuLogicalOp(logic); } else { sceGuDisable(GU_COLOR_LOGIC_OP); }
	if (op==-1 || srcf==-1 || dstf==-1) { return; }
	sceGuEnable(GU_BLEND);
	sceGuBlendFunc(op,srcf,dstf,0x0,0x0);
#endif
#if defined(WII)
	if (!enabled) { GX_SetBlendMode(GX_BM_NONE,0,0,0); return; }
	if (op==-1 || srcf==-1 || dstf==-1 || logic==-1) { return; }
	GX_SetBlendMode(op,srcf,dstf,(op==UX_BO_BIT?logic:0));
#endif
}

/*
 * Scissoring
 */
void uxgraphics_scissor(int enabled, UX_INTBOX box) {
#if defined(_WIN32)
	if (!enabled) { glDisable(GL_SCISSOR_TEST); return; }
	glEnable(GL_SCISSOR_TEST);
	glScissor(box.x,box.y,box.w,box.h);
#endif
#if defined(PSP)
	sceGuSetStatus(GU_SCISSOR_TEST,enabled);
	sceGuScissor(box.x,box.y,box.x+box.w,box.y+box.h);
#endif
#if defined(WII)
	GX_SetClipMode((enabled?GX_CLIP_ENABLE:GX_CLIP_DISABLE));
	GX_SetScissor(box.x, box.y, box.w, box.h);
#endif
}



/*
 *  Configura la vista y las matrices.
 */
void uxgraphics_setViewMode(UX_VIEWPORT view, int f2D, int f3D) {
	int mode = ((uxgraphics_in3D && !f2D) || f3D);
	uxgraphics_projection(view,mode);
	uxgraphics_viewmatrix(view,mode);
}

/*
 *  Configura el render
 */
void uxgraphics_setRenderMode(UX_RENDER render) {
	/* clear */ uxgraphics_clearmode(render.clear_color, render.clear_depth);
	/* depth */ uxgraphics_depthtest(render.depthtest_enabled, render.depthtest_function, render.depthtest_writes );
	/* faces */ uxgraphics_faceCulling(render.faceculling,render.faceculling_enabled);
	/* blend */ uxgraphics_blending(render.blending_enabled,render.blending_operator,render.blending_src_function,render.blending_dst_function,render.blending_logic);
	/* alpha */ uxgraphics_alphatest(render.alphatest_enabled, render.alphatest_operator, render.alphatest_reference );
	/* polys */ uxgraphics_scissor(render.scissor_enabled, render.scissor_box);
	/* stncl */
}




/*
 *  Funciones gráficas
 */ 

void uxgraphics_clearscreen() {
#if defined(_WIN32)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
#endif
#if defined(WII)
	// drawrect? no hay clear.
#endif
#if defined(PSP)
	sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT | GU_STENCIL_BUFFER_BIT );
#endif
}

void uxgraphics_flipscreen() {
#if defined(_WIN32)
	SwapBuffers (handleDC);
#endif
#if defined(WII)
	GX_Flush();
	GX_DrawDone();          								// Tell the GX engine we are done drawing
	fb ^= 1;  												// Toggle framebuffer index
	GX_CopyDisp(framebuffers[fb], GX_TRUE);					// Copy to screen, and clear.
	VIDEO_SetNextFramebuffer(framebuffers[fb]);  			// Select eXternal Frame Buffer
	VIDEO_Flush();                     						// Flush video buffer to screen
	//GX_InvVtxCache(); 
	GX_InvalidateTexAll();									// solo si indexo vertices
	if (dView.sync) VIDEO_WaitVSync();     					// Wait for screen to update
	//if (rmode->viTVMode &VI_NON_INTERLACE) VIDEO_WaitVSync();
#endif
#if defined(PSP)
	sceGuFinish();
	sceGuSync(0,0);
	if (dView.sync) sceDisplayWaitVblankStart();
	sceGuSwapBuffers();
	fb^=1;
	sceGuStart(GU_DIRECT, GX_G_3Dlist);
	printf("Fps: %d\n",uxrtc_fps());
#endif
}

void uxgraphics_shutdown() {
#if defined(WII)
	GX_SetCopyClear(UXRGBA(0,0,0,255), 0xFFFFFF );
	uxgraphics_flipscreen();
	uxgraphics_flipscreen();
	GX_Flush();
	GX_DrawDone();
	GX_AbortFrame();
	VIDEO_Flush();	
	VIDEO_SetBlack(true);
	GX_ClearVtxDesc();
	uxmemfree(framebuffers[1]);
	uxmemfree(framebuffers[0]);
	uxmemfree(gp_fifo);
#endif
}

/**	@} */