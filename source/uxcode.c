#include "utils.h"

/* Globals */
int ux_quit 			= 0;

void ux_atexit(void) {
	uxfilesys_shutdown();
	uxgraphics_shutdown();
	/* ... */
}

/* MAIN FUNCTION, HERE FOR TESTING PURPOSES ONLY */
/* Later, it will be: */
/* int (*ux_main)(int, char *); */


int ux_main(int argc, char *argv[]) {
    /* Prepare screen by platform */
    #if defined(PSP)
		graphics_mode.width = 480;
		graphics_mode.height = 272;
		graphics_mode.w_width = 2048;
		graphics_mode.w_height = 2048;
		graphics_mode.pixelFormat = UX_PF_8888;
		graphics_mode.extras = 0;
	#elif defined(WII)
		graphics_mode.width = 678;
		graphics_mode.height = 528;
		graphics_mode.w_width = 0;
		graphics_mode.w_height = 0;
		graphics_mode.pixelFormat = UX_PF_8888;
		graphics_mode.extras = 0;
	#elif defined(_WIN32)
		graphics_mode.width = 800;
		graphics_mode.height = 600;
		graphics_mode.w_width = 0;
		graphics_mode.w_height = 0;
		graphics_mode.pixelFormat = UX_PF_8888;
		graphics_mode.extras = 0;
	#endif

    /* INITS */
	uxgraphics_init(&graphics_mode);
	uxfilesys_init();
	uxcontrols_init();
	/* ... */


	/* demo-code */
	float theta = -90.00f;
	int cnt = 0;

	

	
	while (!ux_quit) {
		uxcontrols_read();
		uxgraphics_clearscreen();              //clear screen
		
		// one for all
		
		
		#ifdef PSP
			//if (cnt==100) {
				UX_IMAGE *test;
				UX_MESH *mesh;
				printf("opening test32p.bmp...\n");
				test = uximages_loadimage("ms0:/test32.bmp");
				mesh = uxgraphics_genTexMesh(test);
				
				if (test) { 
					while (1) {
						uxcontrols_read();
						uxgraphics_clearscreen(); 
						uxgraphics_setViewMode(dView,false,true);
						uxgraphics_modelmatrix();
						//drawcube3d(50.0,0,( (controls.psppad.held.up!=0) ?-500.0f:-700.0f),0,uxdiv(theta,540.0f),0);
						uxgraphics_drawMesh(mesh);
						uxgraphics_flipscreen();
						theta += 0.01f;
					}
				}
			//}
			//uxgraphics_setViewMode(dView,false,true);
			//drawcube3d(50.0,0,( (controls.psppad.held.up!=0) ?-500.0f:-700.0f),0,uxdiv(theta,540.0f),0);
			//uxgraphics_setViewMode(dView,true,false);
			//uxgraphics_modelmatrix();
			//ScePspFVector3 move = { 240.0f, 136.0f, 0.0f };
			//sceGumTranslate( &move );
			//sceGumRotateZ(theta);		//rotar matriz
			//sceGumUpdateMatrix();
			//sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 3, 0, verticeses);
			//cnt++;
		#endif
		
		#ifdef _WIN32	
			uxgraphics_modelmatrix();
			glTranslatef(0.0f,0.0f,0.0f);        	//mover matriz vista.
			glRotatef (theta, 0.0f, 0.0f, 1.0f);   //rotar matriz vista.
			glBegin (GL_TRIANGLE_STRIP);
			glColor3f (0.0f, 0.0f, 1.0f-((4.0f*theta)/255.0f));   						glVertex2f (0.0f, 0.0f);
			glColor3f (0.0f, 1.0f-((4.0f*theta)/255.0f), 0.0f);   						glVertex2f (0.0f, 400.0f);
			glColor3f (1.0f-((4.0f*theta)/255.0f), ((4.0f*theta)/255.0f), 0.0f);   		glVertex2f (400.0f, 0.0f);
			glColor3f (0.0f, 0.0f, 1.0f-((4.0f*theta)/255.0f));   						glVertex2f (300.0f, 200.0f);
			glEnd ();
			glPopMatrix();
		#endif
			
		#ifdef WII
			uxgraphics_setViewMode(dView,false,false);
			Mtx	modelView;
			
			guMtxIdentity(modelView);
			guMtxConcat(dView.view,modelView,modelView);
			guMtxRotRad(modelView,'Z',((theta)*3.141592654f) / 180.0f);
			guMtxTransApply(modelView, modelView, 0.0F,	0.0F, -1000.0F);
			GX_LoadPosMtxImm(modelView,	GX_PNMTX0);
			
			unsigned int uf = ((255-(4*theta)>255?255:255-(4*theta))<0?0:(255-(4*theta)>255?255:255-(4*theta)));
			unsigned int af = 255-uf;
			GX_Begin(GX_TRIANGLESTRIP, uxgraphics_vertex_slot(UX_VTX_COLOR | UX_VTX_FASTVERTEX), 4);
			GX_Position3s16 ((s16)0, (s16)0, (s16)0);		GX_Color4u8(255, 255, 255, 255);
			GX_Position3s16 ((s16)0, (s16)400, (s16)0);		GX_Color4u8 (0, 255, 0, 255);   
			GX_Position3s16 ((s16)400, (s16)0, (s16)0);		GX_Color4u8 (255, 0, 0, 255);
			GX_Position3s16 ((s16)300, (s16)200, (s16)0);	GX_Color4u8 (0, 0, 0, 255);
            GX_End();
			
		#endif
			uxgraphics_flipscreen();
			theta += 1.0f;
			if (theta > 1800.0f) { theta = -900.0f; }
			
		#ifdef _WIN32
			if (cnt++ > 1) { cnt = 0; Sleep(15); }
		#endif
			
		#ifdef WII
		for (cnt=0;cnt<4;cnt++){
			if (controls.wiimotes[cnt].wmheld.minus) { uxfilesys_init(); }
			if (controls.wiimotes[cnt].wmreleased.one) {
				UX_IMAGE *test;
				UX_MESH *mesh;
				
				//uxdebug("opening test32p.bmp...\n");
				test = uximages_loadimage("sd:/test32.bmp");
				mesh = uxgraphics_genTexMesh(test);
				if (test) { 
					//uxdebug("File seems ok: %i %i %u %u %u \n",test->w,test->h,((u32*)(test->ptr))[0],((u32*)(test->ptr))[1],((u32*)(test->ptr))[2]);
					while (1) {
						uxcontrols_read();
						uxgraphics_drawMesh(mesh);
						uxgraphics_flipscreen();
						if (controls.wiimotes[cnt].wmreleased.home) { break; }
					}
				}// else { uxdebug("File error\n"); }
				//uxdebug("opening test24.bmp...\n");
				uxgraphics_freeMesh(mesh);
			}
			if (controls.wiimotes[cnt].wmpressed.plus or controls.wiimotes[cnt].wmpressed.plus) { exit(0); return 0; }
		}
		#endif
	}
	uxgraphics_shutdown();
	uxcontrols_shutdown();
	exit(0);
	return 0;
}


UXCODE_GENERATE_MAIN();