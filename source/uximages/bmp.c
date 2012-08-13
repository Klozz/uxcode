/*
 * BMP loading routine (standard 16,24,32bpp. uncompressed)
 * 
 * ToDo:
 * 		RLE4 compression.
 * 		RLE8 compression.
 * 		Paletted fileformat.
 * 
 * Resources:
 * 		http://www.fileformat.info/format/bmp/egff.htm
 */

static UX_IMAGE *uximages_loadimageBMP(char *file, u32* result, int mipmap) {
	#if defined(WII)
		#define BS 1
	#else
		#define BS 0
	#endif
	
	UXFILE *archivo 		= NULL;
	UX_IMAGE *img 			= NULL;
	u8 *imageData = NULL;
	u32 finfo[4] 			= {0,0,0,0};
	s32 width = 0, height	= 0;
	u16 cp = 0, bpp			= 0;
	u32 cmp					= 0;
	
	int n 					= 0;
	signed int yinc			= 0;
	unsigned int rowsize 	= 0;
	int rgbasize			= 4;
	
	unsigned int x 			= 0;
	unsigned int y 			= 0;
	unsigned int j			= 0;
	unsigned int i 			= 0;

	char *pixelData 		= NULL;
	
	unsigned int crow 		= 0;
	
	archivo = uxfopen(file,"rb",UX_F_NORMAL); if (!archivo) { *result = UX_MSG_CNT_OPN; return NULL; }
	uxfseek(archivo,0x02,SEEK_SET);
	uxf_readu32(archivo,finfo,4,BS);
	switch (finfo[3]) {
		case 12: 
			uxf_readu16(archivo,(u16*)&width,1,BS);
			uxf_readu16(archivo,(u16*)&height,1,BS);
			uxf_readu16(archivo, &cp,1,BS);
			uxf_readu16(archivo,&bpp,1,BS);
			break;
		default: //24, 32
			uxf_readu32(archivo,(u32*)&width,1,BS);
			uxf_readu32(archivo,(u32*)&height,1,BS);
			uxf_readu16(archivo, &cp,1,BS);
			uxf_readu16(archivo,&bpp,1,BS);
			uxfseek(archivo,0x1E,SEEK_SET);
			uxf_readu32(archivo,&cmp,1,BS);
			break;
	}

	if ( cmp != 0 && cmp != 3 ) { uxfclose(archivo); *result = UX_MSG_NOT_SUP; return NULL; } 
	if ( bpp!=16 && bpp!=24 && bpp!=32 ) { uxfclose(archivo); *result = UX_MSG_NOT_SUP; return NULL; } 
	if ( height<0 ) { height=-height; yinc = 1; n = -height; } else { yinc = -1; n = height; }
	if ( width > 512 || height > 512 ) { uxfclose(archivo); *result = UX_MSG_TOO_BIG; return NULL; }
	
	rowsize = ceil( (bpp * width) / 32 ) * sizeof(u32);
	if (bpp == 24) { rgbasize = 3; }						//padding...
	if (bpp == 16) { rgbasize = 2; }						//padding...
	crow = rgbasize * width;								//size to read
	pixelData = (char *)uxmemalloc(rowsize+1);				//read buffer
	if (!pixelData) { uxmemfree(imageData); *result = UX_MSG_NOT_MEM; return NULL; }
	
	img = uximages_imagecreate(width,height);
	if (!img) { uxmemfree(pixelData); uxfclose(archivo); *result = UX_MSG_NOT_MEM; return NULL; }
	
	y = n;
	uxfseek(archivo,finfo[2],SEEK_SET);
	while ( n > 0 ) {
		uxfread(archivo,pixelData,rowsize);
		j = 0;
		x = 0;
		while (j < crow) {
			#if defined(WII)
			if (rgbasize == 4) { ux_pixeltotexel(x,y,img->w,img->ptr,u32UXRGBA(pixelData[j+2],pixelData[j+1],pixelData[j+0],0xFF)); j += 4; }
			if (rgbasize == 3) { ux_pixeltotexel(x,y,img->w,img->ptr,u32UXRGBA(pixelData[j+2],pixelData[j+1],pixelData[j+0],0xFF)); j += 3; }
			if (rgbasize == 2) { i = ((pixelData[j] << 8) | (pixelData[j+1] << 4) | pixelData[j+2]); ux_pixeltotexel(x,y,img->w,img->ptr,((((i & 0xF800) >> 11) * 255 / 31) << 24) + ((((i & 0x7C0) >> 6) * 255 / 31) << 16) + ((((i & 0x3E) >> 1) * 255 / 31) << 8) +  (0xFF));; j += 2; }
			#elif defined(PSP)
			if (rgbasize == 4) { ux_pixeltotexel(x,y,img->sysw,img->ptr,u32UXRGBA(pixelData[j+3]&0xFF,pixelData[j+2]&0xFF,pixelData[j+1]&0xFF,0xFF)); j += 4; }
			if (rgbasize == 3) { ux_pixeltotexel(x,y,img->sysw,img->ptr,u32UXRGBA(pixelData[j+3]&0xFF,pixelData[j+2]&0xFF,pixelData[j+1]&0xFF,0xFF)); j += 3; }
			if (rgbasize == 2) { i = (((pixelData[j+1]&0xFF) << 8) | ((pixelData[j+2]&0xFF) << 4) | (pixelData[j+3]&0xFF)); ux_pixeltotexel(x,y,img->sysw,img->ptr,((((i & 0xF800) >> 11) * 255 / 31) << 24) + ((((i & 0x7C0) >> 6) * 255 / 31) << 16) + ((((i & 0x3E) >> 1) * 255 / 31) << 8) +  (0xFF));; j += 2; }
			#endif
			x++;
		}
		n--;
		if (yinc>0) { y++; } else { y--; }
	}
	uxmemfree(pixelData);
	uxfclose(archivo);
	*result = UX_MSG_OK;
	#undef BS
	return img;
}