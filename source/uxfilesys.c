#include "utils.h"

/** @defgroup ux_files Filesys

	File routines.
	@{
		\todo
			- Encapsulate file object.
			- Virtual files.
			- Test wii filesys.
			- file documentation
	@} */

unsigned int uxfiles_inited     = 0;
char uxfilesCurDir[UXFILEPATHMAXLENGTH];

int uxfilesys_init() {
	if (uxfiles_inited == true) return true;
	
	#if defined(WII)
		u32 stat;
		if (uxfiles_inited == 1) {
			stat=IRQ_Disable();
			fatUnmount("sd:");
			__io_wiisd.shutdown();
			__io_wiisd.startup();
			fatMount("sd", &__io_wiisd, 0, 8, 64);
			IRQ_Restore(stat);
		}
		stat=IRQ_Disable();
		fatInitDefault();
		IRQ_Restore(stat);
		uxmemset(uxfilesCurDir,0,sizeof(256));
		getcwd(uxfilesCurDir,255);
		DIR *dir;
		dir = opendir("sd:/"); if (dir) { closedir(dir); uxfiles_inited = true; }
	#endif
	
	return uxfiles_inited;
}

void uxfilesys_shutdown() {
	if (uxfiles_inited == false) { return; }
	
	return;
}

UXFILE *uxfopen(char *fpath, char *modes) {
	return fopen(fpath,modes);
}

UXFILESIZE_T uxfwrite(UXFILE *ptr,void *data, UXFILESIZE_T size) {
	return fwrite(data,1,size,ptr);
}

UXFILESIZE_T uxfread(UXFILE *ptr, void *data, UXFILESIZE_T size) {
	return fread(data,1,size,ptr);
}

int uxfseek(UXFILE *ptr, UXFILESIZE_T s,int t) {
	return fseek(ptr,s,t);
}

int uxfclose(UXFILE *ptr) {
	return fclose(ptr);
}

void uxfflush(UXFILE *ptr) {
	#if defined(PSP)
		sceIoDevctl("sio:", 0, NULL, 0, NULL, 0);
		sceIoSync("ms0:",0);	/* PSP1000,2000,3000 */
		sceIoSync("usb0:",0);	/* USB */
		sceIoSync("host0:",0);	/* PSPLINK */
		sceIoSync("ef0:",0);	/* PSPGO */
	#endif
	fflush(ptr);
}

//  read routines
int uxf_readu32(UXFILE *ptr, u32* dest, int n, int bswap) {
	int i = 0, r = 0;
	r += uxfread(ptr,dest,sizeof(u32)*n);
	if (bswap) { for (i=0;i<n;i++) { dest[i] = intswap(dest[i]); } }
	return r;
}

int uxf_readu16(UXFILE *ptr, u16* dest, int n, int bswap) {
	int i = 0, r = 0;
	r += uxfread(ptr,dest,sizeof(u16)*n);
	if (bswap) { for (i=0;i<n;i++) { dest[i] = shortswap(dest[i]); }  }
	return r;
}

int uxf_readu8(UXFILE *ptr, u8* dest, int n, int bswap) {
	return uxfread(ptr,dest+(sizeof(u8)*n),sizeof(u8));
}

// get routines
u8 uxf_getByte(UXFILE *ptr) { u8 a = '\0'; uxf_readu8(ptr,&a,1,0); return a; }

u16 uxf_getWord(UXFILE *ptr) {
	u16 a = 0;
#if defined(WII)
	uxf_readu16(ptr,&a,1,1);
#else
	uxf_readu16(ptr,&a,1,0);
#endif
	return a;
}

u32 uxf_getDWord(UXFILE *ptr) {
	u32 a = 0;
#if defined(WII)
	uxf_readu32(ptr,&a,1,1);
#else
	uxf_readu32(ptr,&a,1,0);
#endif
	return a;
}

void uxf_getString(u8 * str, int len, UXFILE *ptr) {
	uxf_readu8(ptr,str,len,0);
}


/* file utils */
int uxfile_exists(char *fpath) {
	#if defined(PSP)
		SceIoStat stat;
		return (sceIoGetstat(fpath,&stat) >= 0);
	#elif defined(_WIN32)
		DWORD fileAttr;
		fileAttr = GetFileAttributes(fpath);
		return (fileAttr != 0xFFFFFFFF);
	#else
		return 0;
	#endif
}

UXFILESIZE_T uxfile_fsize(char *fpath) {
	#if defined(PSP)
		UXFILESIZE_T size;
		SceIoStat stat;
		sceIoGetstat(fpath,&stat);
		size = stat.st_size;
		return size;
	#elif defined(_WIN32) || defined(WII)
		UXFILESIZE_T size;
		UXFILEHANDLE file = fopen(fpath,"rb");
		fseek(file,0,SEEK_END);
		size = ftell(file);
		fclose(file);
		return size;
	#else
		return 0;
	#endif
}

/* FILE EXTENSION */
char *uxfile_ext(char *fpath, UXFILESIZE_T * len) {
	int l = strlen(fpath);
	int c = 0;
	for (;l>0;l--) {
		c++;
		if (fpath[l] == UXFILESYS_EXTSEP) { *len = (c-2); return fpath+l+1; }
		if (fpath[l] == UXFILESYS_DIRSEP) { *len = 0;     return NULL; }
	}
	*len = 0;
	return NULL;
}

int uxfile_dopen(const char *path) {
	#ifdef PSP
		return sceIoDopen(path);
	#endif
}

int uxfile_dclose(int id) {
	return sceIoDclose(id);
}

int uxfile_dread(const char *path, UXFILEDIRENTRY *entry) {
	#ifdef PSP
		return sceIoDread(path,entry);
	#endif
}

int uxfile_removedir(const char *path) {
	#ifdef PSP
		return sceIoRmdir(path);
	#endif
}

/* FILE UTILS */
int uxfile_remove_recursive(const char *path, int recursive) {
	int filedesc;
	UXFILEDIRENTRY ent;
	char temp[1024];
	memset(&ent, 0, sizeof(UXFILEDIRENTRY));
	memset(temp, 0, 1024);
	int err = 0;

	/* OPEN */

	filedesc = uxfile_dopen(path);
	if(filedesc < 0) { return 1; }

	while (uxfile_dread(filedesc,&ent)) {
		if (ent.d_stat.st_attr & FIO_SO_IFDIR) {
			if (ent.d_name[0] == '.' && (ent.d_name[1] == '.' || ent.d_name[1] == 0)) { continue; }
			else {
				if ( recursive ) {
					uxmemset(temp,0, 1024);
					strcpy(temp, path);
					strcat(temp,UXFILESYS_DIRSEPS);
					strcat(temp,ent.d_name);
					err = uxfile_remove_recursive(temp, recursive);
				}
			}
		}
		else {
			uxmemset(temp,0, 1024);
			strcpy(temp, path);
			strcat(temp,UXFILESYS_DIRSEPS);
			strcat(temp,ent.d_name);
			sceIoRemove(temp);
		}
	}
	uxfile_dclose(filedesc); 
	uxfile_removedir(path);
	return err;
}


int uxfile_tmpname(char *in) {
	return 0;
}