#if defined(NDS) && !defined(UXFILESIZE_T)

	// size unit
	#define UXFILESIZE_T			size_t
	
	// Vram manager
	#define VRAM_NBANKS  9
	#define VRAM_BLOCKS 80
	const UXFILESIZE_T uxvram_banksizes = [ 0x20000, 0x20000, 0x20000, 0x20000, 0x10000, 0x4000, 0x4000, 0x8000, 0x4000];
	
	extern UXFILESIZE_T uxvram_banktable_size[VRAM_NBANKS][VRAM_BLOCKS];
	extern void * uxvram_banktable_dptr[VRAM_NBANKS][VRAM_BLOCKS];
	
#endif