#include "../../utils.h"

UX_IMAGE* uximages_lastTexture = NULL;
 

/*
 * 	Tex utils.
 */
static inline int ux_nextpoweroftwo(int val) {
	register int i;
	for (i=15;i!=0;i--) { if (val & (1<<i)) { if (val & ~(1<<i)) { val = (1<<(i+1)); } else { val = (1<<i); } break; } }
	return val;
}

static void uximages_flushtex(UX_IMAGE *img) {
	#if defined(WII)
		DCFlushRange(img->ptr, img->dataSize);
	#elif defined(PSP)
		sceKernelDcacheWritebackInvalidateRange(img->ptr,img->dataSize);
	#endif
}

inline void ux_pixeltotexel(const int x, const int y, const int w, u8 *bp, const u32 color) {
	#if defined(WII)
		register u32 offs;
		register u32 bpad = w % 4;
		if (bpad) { bpad = 4 - bpad; }
		bpad += w;
		offs = (((y&(~3))<<2)*bpad) + ((x&(~3))<<4) + ((((y&3)<<2) + (x&3)) <<1);
		*((u16*)(bp+offs   )) = (u16)((color <<8) | (color >>24));
		*((u16*)(bp+offs+32)) = (u16) (color >>8);
	#elif defined(PSP)
		register u32 offs;
		offs = (((x>>2) + (((y>>3)) * (w>>2)))<<7) + ((x<<2)-((x>>2)<<4)) + ((y-((y>>3)<<3))<<4);
		*((u32*)(bp+offs  )) = color;
	#endif
}
 


static UX_IMAGE *uximages_imagecreate(u32 width, u32 height/*, PIXELFORMATTT */) {
	UX_IMAGE* img = NULL;
	u32 wid, hei;
	u32 rwid, rhei;
	u8* imageData = NULL;
	if (width > 512 || height > 512) { return NULL; }
	wid = ux_nextpoweroftwo(width);									rwid = wid;
	hei = ux_nextpoweroftwo(height); 								rhei = hei;
	if (wid % 4) { wid /= 4; wid++; wid *= 4; }						//32bit align.
	if (hei & 7) { hei = ((hei & (~7)) + 8); }						//8bit align.
	
	#if defined(WII)
	imageData = uxmemalign(32, wid * hei * sizeof(u32));			// wii 32bit align		attention, needs PIXELFORMAT here.
	#elif defined(PSP)
	imageData = uxmemalign(16, wid * hei * sizeof(u32));			// psp 16bit align		attention, needs PIXELFORMAT here.
	#elif defined(_WIN32)
	imageData = uxmemalloc(wid * hei * sizeof(u32));				// win auto-aligns		attention, needs PIXELFORMAT here.
	#endif
	if (!imageData) { return NULL; }
	
	img = uxmemalloc(sizeof(UX_IMAGE));
	if (!img) { uxmemfree(imageData); return NULL; }
	
	uxmemset(imageData,0,sizeof(imageData));				//transparent.
	uxmemset(img,0,sizeof(UX_IMAGE));						//clear struct
	
	img->w = width;
	img->h = height;
	img->realw=wid;
	img->realh=hei;
	img->sysw=rwid;
	img->sysh=rhei;
	img->u0 = 0.0f; img->v0 = 0.0f; 
	img->u1 = (float)img->w/(float)img->sysw; img->v1 =(float)img->h/(float)img->sysh;
	img->dataSize = wid * hei * sizeof(u32);						//attention, needs PIXELFORMAT here.
	img->ptr = imageData;
	
	return img;
}
 
#include "uximages/bmpfiles.c"

static UX_IMAGE *uximages_loadimagePNG(char *file) {
	return NULL;
}

static UX_IMAGE *uximages_loadimageJPG(char *file) {
	return NULL;
}
 
 
 
 
 
 
 /*
 typedef struct _TgaHeader {
  BYTE IDLength;        // 00h  Size of Image ID field
  BYTE ColorMapType;    // 01h  Color map type
  BYTE ImageType;       // 02h  Image type code
  WORD CMapStart;       // 03h  Color map origin
  WORD CMapLength;      // 05h  Color map length
  BYTE CMapDepth;       // 07h  Depth of color map entries
  WORD XOffset;         // 08h  X origin of image
  WORD YOffset;         // 0Ah  Y origin of image
  WORD Width;           // 0Ch  Width of image 
  WORD Height;          // 0Eh  Height of image
  BYTE PixelDepth;      // 10h  Image pixel size
  BYTE ImageDescriptor; // 11h  Image descriptor byte
} TGAHEAD;
*/
 
static UX_IMAGE *uximages_loadimageTGA(char *file, u32* result, int mipmap) {
	/*
	#if defined(WII)
		#define BS 1
	#else
		#define BS 0
	#endif
	
	UXFILE *archivo 		= NULL;
	UX_IMAGE *img 			= NULL;
	u8 *imageData = NULL;
	u32 read				= 0;
	s32 width = 0, height	= 0;
	u32 wid = 0, hei 		= 0;
	u32 rwid = 0, rhei 		= 0;
	char *pixelData 		= NULL;
	
	char header1[3];
	short cmap1[2];
	char cmap2;
	short dims[4];
	char pixdes[2];
	
	// go for it.
	archivo = uxfopen(file,"rb"); if (!archivo) { *result = UX_MSG_CNT_OPN; return NULL; }			// abrir archivo.
	uxfseek(archivo,0x00,SEEK_SET);																	// al inicio.
	
	read += uxf_readu8(archivo,header1,3,BS);
	read += uxf_readu16(archivo,cmap1,2,BS);
	read += uxf_readu8(archivo,&cmap2,1,BS);
	read += uxf_readu16(archivo,dims,4,BS);
	read += uxf_readu8(archivo,pixdes,2,BS);
	
	if (read != 12) {  }
	if (header1[2] < 2 && header1[2] > 3) {  }
	
	
	
	#undef BS
	*/
	return NULL;
}

static UX_IMAGE *uximages_loadimagePCX(char *file) {
	//
	return NULL;
}
  

/*
 *  Carga de imágenes.
 */
UX_IMAGE *uximages_loadimage(char *file) {
	/* variables */
	UX_IMAGE *img	= NULL;
	UXFILE *archivo	= NULL;
	u8 header[512];
	u32 extlen 		= 0;
	u32 readd 		= 0;
	u32 r			= 0;

	uxmemset(header,0,sizeof(header)); archivo = uxfopen(file,"rb"); if (!archivo) { return NULL; }								/* abrir archivo */
	readd = uxfread(archivo,&header,24);																						/* leer header   */
	if ( readd < 8 ) { uxfclose(archivo); return NULL; }																		/* min(8 bytes)  */
	uxfclose(archivo);																											/* close 		 */
	/* BMP */ if ( header[0] == 'B' and header[1] == 'M' ) { img = uximages_loadimageBMP(file,&r,0); }
	/* PNG */ if ( header[0] == 0x89 and header[1]==0x50 and header[2]==0x4E and header[3]==0x47 and header[4]==0x0D and header[5]==0x0A and header[6]==0x1A and header[7]==0x0A) { img = uximages_loadimagePNG(file); }
	/* JPG */ if ( header[0] == 0xFF and header[1]==0xD8 and header[2]==0xFF) { img = uximages_loadimageJPG(file); }
	/* GIF */ if ( !strncmp((char*)header,"GIF8",4) ) { img = uximages_loadimageGIF(file,&r,0); }
	/* TGA */ if ( !strncmp(str_lower(uxfile_ext(file,&extlen)),"tga",3) ) { img = uximages_loadimageTGA(file,&r,0); }
	/* PCX */ if ( header[0] == 0x0A ) { img = uximages_loadimagePCX(file); }
	if ( !img ) { r = UX_MSG_NOT_SUP; return NULL; }
	/* flush image */
	uximages_flushtex(img);
	return img;
}

/*
 *  image transfer to GPU ( image, need cache, cache pos result )
 */
void uximages_transferimage(UX_IMAGE *img) {
	if (img == uximages_lastTexture) { return; }
	uximages_lastTexture = img;
	#if defined(WII)
		GXTexObj texObj;
		GX_InvalidateTexAll();
		GX_InitTexObj(&texObj,img->ptr,img->w,img->h,GX_TF_RGBA8,GX_CLAMP,GX_CLAMP,GX_FALSE);
		GX_InitTexObjLOD(&texObj,GX_LINEAR,GX_LINEAR, 0, 0, 0, 0, 0, GX_ANISO_4);
		GX_LoadTexObj(&texObj, GX_TEXMAP0);
	#elif defined(PSP)
		sceGuTexMode(GU_PSM_8888, 0, 0, true);
		sceGuTexImage(0, img->sysw, img->sysh, img->sysw, img->ptr);
		//sceGuTexSync();
		sceGuTexWrap(GU_CLAMP, GU_CLAMP);
		sceGuTexFilter(GU_LINEAR,GU_LINEAR);
		sceGuTexOffset(0.0f, 0.0f);
		sceGuTexScale(img->u1, img->v1);
		//sceGuTexMapMode(GU_TEXTURE_COORDS,0,1);
		//sceGuShadeModel(GU_SMOOTH); 
	#endif
}

/*
 * image blit
 */

void uximages_blitimage(UX_IMAGE *img) { return; }		// por eliminar.