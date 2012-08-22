#include "utils.h"

/* Globals */
int ux_quit 			= 0;

static inline void ux_initialize() {
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
	uxaudio_init();
	uxgraphics_init(&graphics_mode);
	uxfilesys_init();
	uxcontrols_init();
	uxdraw_init();

	/* ... */
}

static inline void ux_deinitialize() {
	uxdraw_shutdown();
	uxcontrols_shutdown();
	uxfilesys_shutdown();
	uxgraphics_shutdown();
	uxaudio_shutdown();
}

/* MAIN FUNCTION, HERE FOR TESTING PURPOSES ONLY */
/* Later, it will be: */
/* int (*ux_main)(int, char *); */
int ux_main(int argc, char *argv[]) {
    /* initialize all */
    ux_initialize();
 	

	/* demo-code */
	int cnt = 0;			/* counter */
	float theta = 0.0f;		/* angle */
	UX_MESH mesh;			/* demo-mesh */

    /* screen centered 50x50 square filled gradient colored, cached vertex data */
	mesh.traslation = (UX_VECTOR3D){ graphics_mode.width / 2 , graphics_mode.height / 2, 0.0f };
	mesh.rotation = (UX_VECTOR3D){ 0.0f, 0.0f, 0.0f };
	mesh.scale = (UX_VECTOR3D){1.0f,1.0f,1.0f};
	mesh.in2D = true;
	mesh.dpoly = UX_TRIANGLESTRIP;
	mesh.vtype = UX_VTX_FASTVERTEX | UX_VTX_COLOR;
	mesh.count = 5;
	mesh.next = NULL;
	mesh.data = (VF_CP3 *)uxmemalloc(sizeof(VF_CP3) * 5);

	/* fill geometry mesh (50x50 square)*/
	VF_CP3 * ptr = mesh.data;

	ptr[0].x = 0;
	ptr[0].y = 0;
	ptr[0].z = 0;
	ptr[0].color = u32UXRGBA(255,0,0,255);

	ptr[1].x = 0;
	ptr[1].y = 50;
	ptr[1].z = 0;
	ptr[1].color = u32UXRGBA(0,255,0,255);

	ptr[2].x = 50;
	ptr[2].y = 0;
	ptr[2].z = 0;
	ptr[2].color = u32UXRGBA(0,0,255,255);

	ptr[3].x = 50;
	ptr[3].y = 50;
	ptr[3].z = 0;
	ptr[3].color = u32UXRGBA(255,255,255,255);
	
	ptr[4].x = 0;
	ptr[4].y = 50;
	ptr[4].z = 0;
	ptr[4].color = u32UXRGBA(0,255,0,255);
	
	for (cnt=0;cnt<300;cnt++) {			/* 5 secs @ 60fps */
		uxcontrols_read();				/* read controls */
		uxgraphics_clearscreen();		/* clear screen */
		uxgraphics_drawMesh(&mesh);		/* draw mesh */
		uxgraphics_flipscreen();		/* end frame */
	}

	for (cnt=0;cnt<300;cnt++) {			/* 5 secs @ 60fps, rotating time */
		uxcontrols_read();				/* read controls */
		uxgraphics_clearscreen();		/* clear screen */
		mesh.rotation.z = theta; theta += 3.0f;
		uxgraphics_drawMesh(&mesh);		/* draw mesh */
		uxgraphics_flipscreen();		/* end frame */
	}

	mesh.in2D = false;
	ptr[0].z = -1;
	ptr[1].z = -1;
	ptr[2].z = -1;
	ptr[3].z = -1;
	ptr[4].z = -1;
	mesh.traslation.z = -100.0f;
	for (cnt=0;cnt<300;cnt++) {			/* 5 secs @ 60fps, make it flip! */
		uxcontrols_read();				/* read controls */
		uxgraphics_clearscreen();		/* clear screen */
		mesh.rotation.x = theta; theta += 0.1f;
		uxgraphics_drawMesh(&mesh);		/* draw mesh */
		uxgraphics_flipscreen();		/* end frame */
	}
	
	/* deinitialize all */
	ux_deinitialize();
	exit(0);
	return 0;
}

UXCODE_GENERATE_MAIN();