/*
 * uxfilesys.c
 * This file is used to manage files and directories in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#include "utils.h"

unsigned int uxfiles_inited     = 0;
char uxfilesCurDir[UXFILEPATHMAXLENGTH];


/** @defgroup ux_files File subsystem

	@{
		\brief File subsystem.
*/

/**
* \brief File system initialization
*/
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

/**
* \brief File system shutdown
*/
void uxfilesys_shutdown() {
	if (uxfiles_inited == false) { return; }
	
	return;
}

/**
* \brief Open a file
* \param fpath File path
* \param modes Open mode ("rb", "w+", etc...)
* \param mode Either UX_F_NORMAL (normal mode), UX_F_VIRTUAL (virtual access)
*/
extern UXFILE * uxfopen(const char *fpath, const char *modes, enum UXFILEOPENMODE mode) {
	UXFILE * file  = NULL;

	file = (UXFILE *)uxmemalloc(sizeof(UXFILE));
	uxmemset( file , 0, sizeof(UXFILE) );
	file->openmode = mode;

	if (mode == UX_F_NORMAL) {
		// Physical (normal)
		file->handle = fopen(fpath,modes);
		if (file->handle == NULL) { uxmemfree(file); return NULL; }
		file->path = uxstring_dup(fpath);
		file->buffer = NULL;
		file->buffersize = 0;
		file->filesize = uxfile_fsize(fpath);
		file->position = 0;
	} else {
		// Virtual

	}

	return file;
}

/**
* \brief Write to a file
* \param ptr Where to write
* \param data What to write
* \param size Size of data to be written
* \return Number of bytes written (May differ from size passed to the function)
*/
UXFILESIZE_T uxfwrite(UXFILE *ptr,void *data, UXFILESIZE_T size) {
	if (ptr->handle != NULL) { return fwrite(data,1,size,ptr->handle); }
	return 0;
}

/**
* \brief Read from a file
* \param ptr Where to read
* \param data Where to put data being read
* \param size How many bytes to read
* \return Number of bytes really read. (May differ from size passed to the function)
*/
UXFILESIZE_T uxfread(UXFILE *ptr, void *data, UXFILESIZE_T size) {
	if (ptr->handle != NULL) { return fread(data,1,size,ptr->handle); }
	return 0;
}

/**
* \brief Seek a file
* \param ptr File to seek
* \param s How many bytes to move / until position.
* \param t Position marker (One from SEEK_SET, SEEK_CUR, SEEK_START, SEEK_END)
* \return New position
*/
int uxfseek(UXFILE *ptr, UXFILESIZE_T s,int t) {
	if (ptr->handle != NULL) { return fseek(ptr->handle,s,t); }
	return 0;
}

/**
* \brief Close a file
* \param ptr File to close
* \return 0 if ok, error otherwise
*/
int uxfclose(UXFILE *ptr) {
	int result = 0;
	if (ptr->handle != NULL) { result = fclose(ptr->handle); }
	if (ptr->buffer != NULL) { uxmemfree(ptr->buffer); }
	if (ptr->path != NULL) { uxmemfree(ptr->path); }
	uxmemfree(ptr);
	return result;
}

/**
* \brief Flush changes to a file
* \param ptr File to flush
*/
void uxfflush(UXFILE *ptr) {
	#if defined(PSP)
		sceIoDevctl("sio:", 0, NULL, 0, NULL, 0);
		sceIoSync("ms0:",0);	/* PSP1000,2000,3000 */
		sceIoSync("usb0:",0);	/* USB */
		sceIoSync("host0:",0);	/* PSPLINK */
		sceIoSync("ef0:",0);	/* PSPGO */
	#endif
	if (ptr->handle != NULL) { fflush(ptr->handle); }
}

/**
* \brief File exists
* \param fpath File to check.
* \return 0 if not exists, otherwise it exists.
*/
int uxfile_exists(const char *fpath) {
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

/**
* \brief File size
* \param fpath File to determine size
* \return File size in bytes.
*/
UXFILESIZE_T uxfile_fsize(const char *fpath) {
	#if defined(PSP)
		SceIoStat stat;
		sceIoGetstat(fpath,&stat);
		return stat.st_size;
	#elif defined(_WIN32) || defined(WII)
		struct stat status;
		stat(fpath, &status);
		return status.st_size;
	#else
		return 0;
	#endif
}

/**
* \brief File type
* \param fpath File to determine if is file / folder.
* \return 0 = regular file, 1 = is a folder
*/
int uxfile_ftype(const char *fpath) {
	#if defined(PSP)
		SceIoStat stat;
		sceIoGetstat(fpath,&stat);
		return FIO_S_ISDIR(stat.st_mode);
	#elif defined(_WIN32) || defined(WII)
		struct stat status;
		stat(fpath, &status);
		return (status.st_mode & S_IFDIR);
	#else
		return 0;
	#endif
}

/**
* \brief File extension
* \param fpath File path
* \return Pointer to extension part of the string passed (after the last dot) or NULL if no extension found.
*/
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

/** @} */


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


UXFILEDIRHANDLE uxfile_dopen(const char *path) {
	#ifdef PSP
		return sceIoDopen(path);
	#elif defined(WII) || defined(_WIN32)
		return opendir(path);
	#endif

	return 0;
}

int uxfile_dclose(UXFILEDIRHANDLE id) {
	#ifdef PSP
		return sceIoDclose(id);
	#elif defined(WII) || defined(_WIN32)
		return closedir(id);
	#endif
	return 0;
}

int uxfile_dread(UXFILEDIRHANDLE dirp, UXFILEDIRENTRY *entry) {
	#ifdef PSP
		return sceIoDread(dirp, entry);
	#elif defined(_WIN32) || defined(WII)
		return ((entry = readdir( dirp )) != NULL);
	#endif
	return 0;
}

int uxfile_removefile(const char *path) {
	#ifdef PSP
		return sceIoRemove(path);
	#endif
	return 0;
}

int uxfile_removedir(const char *path) {
	#ifdef PSP
		return sceIoRmdir(path);
	#endif
	return 0;
}

/* FILE UTILS */
int uxfile_remove_recursive(const char *path, int recursive) {
	UXFILEDIRHANDLE filedesc;
	UXFILEDIRENTRY ent;
	char temp[1024];
	memset(&ent, 0, sizeof(UXFILEDIRENTRY));
	memset(temp, 0, 1024);
	int err = 0;

	/* OPEN */

	filedesc = uxfile_dopen(path);
	if(filedesc < 0) { return 1; }

	while (uxfile_dread(filedesc, &ent)) {
		if (ent.d_name[0] == '.' && (ent.d_name[1] == '.' || ent.d_name[1] == 0)) { continue; }
		uxmemset(temp,0, 1024);
		uxstring_copy(temp, path);
		uxstring_cat(temp,UXFILESYS_DIRSEPS);
		uxstring_cat(temp,ent.d_name);
		if (uxfile_ftype(temp)==1) {
			if ( recursive ) { err = uxfile_remove_recursive(temp, recursive); }
		}
		else { uxfile_removefile(temp); }
	}
	uxfile_dclose(filedesc);
	uxfile_removedir(path);
	return err;
}


int uxfile_tmpname(char *in) {
	return 0;
}