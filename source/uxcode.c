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
    /* INITS */
	uxgraphics_init();
	uxfilesys_init();
	uxcontrols_init();

	float theta = -90.00f;
	int cnt = 0;
	
	while (!ux_quit) {
		uxcontrols_read();
		uxgraphics_clearscreen();              //clear screen
		
		#ifdef PSP
			if (controls.psppad.held.up!=0) { dView.sync = 0; } 
			else { dView.sync = 1; }
			if (cnt==100) {
				UX_IMAGE *test;
				UX_MESH *mesh;
				printf("opening test32p.bmp...\n");
				test = uximages_loadimage("ms0:/test32.bmp");
				mesh = uxgraphics_genTexMesh(test);
				
				if (test) { 
					uxdebug("File seems ok: %i %i %u %u %u \n",test->w,test->h,((u32*)(test->ptr))[0],((u32*)(test->ptr))[1],((u32*)(test->ptr))[2]);
					while (1) {
						uxcontrols_read();
						uxgraphics_clearscreen(); 
						uxgraphics_setViewMode(dView,false,true);
						uxgraphics_modelmatrix();
						drawcube3d(50.0,0,( (controls.psppad.held.up!=0) ?-500.0f:-700.0f),0,uxdiv(theta,540.0f),0);
						uxgraphics_drawMesh(mesh);
						uxgraphics_flipscreen();
						theta += 0.01f;
					}
				}
			}
			uxgraphics_setViewMode(dView,false,true);
			drawcube3d(50.0,0,( (controls.psppad.held.up!=0) ?-500.0f:-700.0f),0,uxdiv(theta,540.0f),0);
			uxgraphics_setViewMode(dView,true,false);
			uxgraphics_modelmatrix();
			ScePspFVector3 move = { 240.0f, 136.0f, 0.0f };
			sceGumTranslate( &move );
			sceGumRotateZ(theta);		//rotar matriz
			sceGumUpdateMatrix();
			sceGuDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 3, 0, verticeses);
			cnt++;
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
			GX_Begin(GX_TRIANGLESTRIP, uxgraphics_vertex_slot(UX_TIPO_COLOREADO | UX_TIPO_RAPIDO), 4);
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
			if (controls.wiimotes[cnt].wmheld.minus) { uxfilesys_init(); /* uxgraphics_flipscreen(); */ }
			if (controls.wiimotes[cnt].wmreleased.two) { uxdebugi("UXCODE\r\n"); }
			if (controls.wiimotes[cnt].wmpressed.home) { uxdebug("home pressed\n"); }
			if (controls.wiimotes[cnt].wmreleased.home) { uxdebug("home released\n"); }
			if (controls.wiimotes[cnt].wmreleased.one) { 
				UX_IMAGE *test;
				UX_MESH *mesh;
				
				uxdebug("opening test32p.bmp...\n");
				test = uximages_loadimage("sd:/test32.bmp");
				mesh = uxgraphics_genTexMesh(test);
				if (test) { 
					uxdebug("File seems ok: %i %i %u %u %u \n",test->w,test->h,((u32*)(test->ptr))[0],((u32*)(test->ptr))[1],((u32*)(test->ptr))[2]);
					while (1) {
						uxcontrols_read();
						uxgraphics_drawMesh(mesh);
						uxgraphics_flipscreen();
						if (controls.wiimotes[cnt].wmreleased.home) { break; }
					}
				} else { uxdebug("File error\n"); }
				uxdebug("opening test24.bmp...\n");
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



/*
 #ifdef PSP
    uxdebug("Testing uxfilesys.c... OK");
    SceUID modules[8];
    uxdebug("Testing usermodules...");      
    modules[0] = pspSdkLoadStartModule("flash0:/kd/chkreg.prx", PSP_MEMORY_PARTITION_KERNEL);
    modules[1] = pspSdkLoadStartModule("flash0:/kd/npdrm.prx", PSP_MEMORY_PARTITION_KERNEL);
    modules[2] = pspSdkLoadStartModule("flash0:/kd/semawm.prx", PSP_MEMORY_PARTITION_KERNEL);
    modules[3] = pspSdkLoadStartModule("flash0:/kd/usbstor.prx", PSP_MEMORY_PARTITION_KERNEL);
    modules[4] = pspSdkLoadStartModule("flash0:/kd/usbstormgr.prx", PSP_MEMORY_PARTITION_KERNEL);
    modules[5] = pspSdkLoadStartModule("flash0:/kd/usbstorms.prx", PSP_MEMORY_PARTITION_KERNEL);
    modules[6] = pspSdkLoadStartModule("flash0:/kd/usbstorboot.prx", PSP_MEMORY_PARTITION_KERNEL);
	modules[7] = pspSdkLoadStartModule("flash0:/kd/usbdevice.prx", PSP_MEMORY_PARTITION_KERNEL); 
	for (i=0;i<8;i++) {
        uxdebug(" Usb module [%d]: 0x%08X != 0x8...",i,modules[i]);
    }
    uxdebug("Modulo PSP_NET_MODULE_COMMON [%d > 0]",sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON));
    uxdebug("Modulo PSP_NET_MODULE_INET [%d > 0]",sceUtilityLoadNetModule(PSP_NET_MODULE_INET));
    uxdebug("Modulo PSP_NET_MODULE_PARSEURI [%d > 0]",sceUtilityLoadNetModule(PSP_NET_MODULE_PARSEURI));
    uxdebug("Modulo PSP_NET_MODULE_PARSEHTTP [%d > 0]",sceUtilityLoadNetModule(PSP_NET_MODULE_PARSEHTTP));
    uxdebug("Modulo PSP_NET_MODULE_HTTP [%d > 0]",sceUtilityLoadNetModule(PSP_NET_MODULE_HTTP));
    uxdebug("Modulo PSP_NET_MODULE_SSL [%d > 0]",sceUtilityLoadNetModule(PSP_NET_MODULE_SSL));
    #endif 
*/

UXCODE_GENERATE_MAIN();
