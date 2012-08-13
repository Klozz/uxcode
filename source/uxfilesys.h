#ifndef UXFILESYS_H
#define UXFILESYS_H

#if defined(_WIN32)
    #define UXFILESYS_EXTSEP    '.'
	#define UXFILESYS_DIRSEP	'\\'
	#define UXFILESYS_DIRSEPS	"\\"
	#define UXFILEHANDLE        FILE
	#define UXFILEDIRENTRY		DIR
	#define UXFILENILHANDLE     NULL
	#define UXFILESIZE_T size_t
#elif defined(PSP)
    #define UXFILESYS_EXTSEP    '.'
	#define UXFILESYS_DIRSEP	'/'
	#define UXFILESYS_DIRSEPS	"/"
    #define UXFILEHANDLE        FILE
	#define UXFILEDIRENTRY		SceIoDirent
    #define UXFILENILHANDLE     NULL
	#define UXFILESIZE_T size_t
#elif defined(WII)
    #define UXFILESYS_EXTSEP    '.'
	#define UXFILESYS_DIRSEP	'/'
	#define UXFILESYS_DIRSEPS	"/"
    #define UXFILEHANDLE        FILE
	#define UXFILEDIRENTRY		DIR
    #define UXFILENILHANDLE     NULL
	#define UXFILESIZE_T size_t
	
	typedef enum {PI_DEFAULT, PI_SDGECKO_A, PI_SDGECKO_B, PI_INTERNAL_SD, PI_CUSTOM } PARTITION_INTERFACE;
#endif

typedef enum {UX_F_VIRTUAL, UX_F_NORMAL} UXFILEOPENMODE;
#define UXFILE_DEFAULT_BUFFER_SIZE 200000

typedef struct UXFILE {
	// handle + re-open properties
	UXFILEHANDLE * handle;
	char * path;
	char * mode;

	// buffer properties
	enum UXFILEOPENMODE openmode;
	unsigned char * buffer;
	UXFILESIZE_T buffersize;
	UXFILESIZE_T filesize;
	UXFILESIZE_T position;
	int buffermodified;
} UXFILE;

#define UXFILEPATHMAXLENGTH     256


/* initialization */
extern unsigned int uxfiles_inited;
extern int          uxfilesys_init();
extern void         uxfilesys_shutdown();

/* ansi fopen equivalents */
extern UXFILE * uxfopen(const char *fpath, const char *modes, enum UXFILEOPENMODE mode);
extern UXFILESIZE_T uxfread(UXFILE *ptr, void *data, UXFILESIZE_T size);
extern UXFILESIZE_T uxfwrite(UXFILE *ptr,void *data, UXFILESIZE_T size);
extern void uxfflush(UXFILE *ptr);
extern int uxfclose(UXFILE *ptr);
extern int uxfseek(UXFILE *ptr, UXFILESIZE_T s,int t);

/* read routines */
extern int uxf_readu32(UXFILE *ptr, u32* dest, int n, int bswap);
extern int uxf_readu16(UXFILE *ptr, u16* dest, int n, int bswap);
extern int uxf_readu8(UXFILE *ptr, u8* dest, int n, int bswap);

/* get routines */
extern u8 uxf_getByte(UXFILE *ptr);
extern u16 uxf_getWord(UXFILE *ptr);
extern u32 uxf_getDWord(UXFILE *ptr);
extern void uxf_getString(u8 * str, int len, UXFILE *ptr);

/* file/dir functions */
extern int uxfile_exists(char *fpath);
extern UXFILESIZE_T uxfile_fsize(char *fpath);
extern char *uxfile_ext(char *fpath, unsigned int * len);
extern int uxfile_tmpname(char *in);

#endif
