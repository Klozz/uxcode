#include "utils.h"

#ifndef UXCODE_CORE_H
#define UXCODE_CORE_H



/* MAIN CORE */
extern int ux_quit;
extern int ux_main(int argc, char *argv[]);

#if defined(PSP)

/* 
 * PSP SPECIFIC MAIN INIT
 */
#define UXCODE_GENERATE_MAIN() \
PSP_MODULE_INFO("LuaDEV R1", 0, 1, 0); \
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU); \
PSP_HEAP_SIZE_KB(-3*1000); \
int main(int argc, char* argv[]) { uxfilesys_init(); int res = ux_main(0,NULL); sceKernelExitGame(); return res; }

#define uxsleep(x) /* VOID */



#elif defined(_WIN32)
/* 
 * PC SPECIFIC MAIN INIT
 */
#define uxsleep(x) Sleep(x)
extern HWND handleWnd;
extern HDC handleDC;
extern HGLRC handleRC;
#define UXCODE_GENERATE_MAIN() \
        LRESULT CALLBACK WndProc (HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam); \
        void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC) { \
            PIXELFORMATDESCRIPTOR pfd; \
            int iFormat; \
            *hDC = GetDC (hWnd); \
            ZeroMemory (&pfd, sizeof (pfd)); \
            pfd.nSize = sizeof (pfd); \
            pfd.nVersion = 1; \
            pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; \
            pfd.iPixelType = PFD_TYPE_RGBA; \
            pfd.cColorBits = 32; \
            pfd.cDepthBits = 24; \
            pfd.iLayerType = PFD_MAIN_PLANE; \
            iFormat = ChoosePixelFormat (*hDC, &pfd); \
            SetPixelFormat (*hDC, iFormat, &pfd); \
            *hRC = wglCreateContext( *hDC ); \
            wglMakeCurrent( *hDC, *hRC ); \
        } \
        void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC) { \
             wglMakeCurrent (NULL, NULL); \
             wglDeleteContext (hRC); \
             ReleaseDC (hWnd, hDC); \
        } \
        int WINAPI WinMain (HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int iCmdShow) { \
            WNDCLASS wc; \
            MSG msg; \
            wc.style = CS_OWNDC; \
            wc.lpfnWndProc = WndProc; \
            wc.cbClsExtra = 0; \
            wc.cbWndExtra = 0; \
            wc.hInstance = hInstance; \
            wc.hIcon = LoadIcon (NULL, IDI_APPLICATION); \
            wc.hCursor = LoadCursor (NULL, IDC_ARROW); \
            wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH); \
            wc.lpszMenuName = NULL; \
            wc.lpszClassName = "LuadevR1"; \
            RegisterClass (&wc); \
            handleWnd = CreateWindow ("LuadevR1", "Luadev R1", WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,0, 0, 800, 450, NULL, NULL, hInstance, NULL); \
            EnableOpenGL (handleWnd, &handleDC, &handleRC); \
            if (GLEW_OK != glewInit()) { return -1; } \
            ux_main(0,NULL); \
            DisableOpenGL (handleWnd, handleDC, handleRC); \
            DestroyWindow (handleWnd); \
            return msg.wParam; \
        } \
        LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { \
        switch (message) { \
        case WM_CREATE: return 0; \
        case WM_CLOSE: PostQuitMessage (0); ux_quit = 0; return 0; \
        case WM_DESTROY: return 0; \
        case WM_KEYDOWN: controls.keyboard.keys[wParam] = 1; return 0; \
        case WM_KEYUP:  controls.keyboard.keys[wParam] = 0; return 0; \
        case WM_MOUSEMOVE: { \
                controls.mouse.x =(unsigned int)LOWORD(lParam); \
                controls.mouse.y =(unsigned int)HIWORD(lParam); \
                controls.mouse.left_button = wParam & MK_LBUTTON; \
                controls.mouse.right_button = wParam & MK_RBUTTON; \
                return 0; } \
        case WM_LBUTTONDOWN: controls.mouse.left_button = 1; return 0; \
        case WM_LBUTTONUP: controls.mouse.left_button = 0; return 0; \
        case WM_RBUTTONDOWN: controls.mouse.right_button = 1; return 0; \
        case WM_RBUTTONUP: controls.mouse.right_button = 0; return 0; \
        default: return DefWindowProc (hWnd, message, wParam, lParam);  \
    } \
}
#elif defined(WII)
/* 
 * WII SPECIFIC MAIN INIT
 */
#define UXCODE_GENERATE_MAIN() \
int	main(void) { return ux_main(0,NULL); }
#define uxsleep(x) /* VOID */

#endif




#endif
