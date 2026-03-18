#include "quakedef.h"

// Your D3D12 wrapper exports
extern bool QD3D12_InitForQuake(HWND hwnd, int width, int height);
extern void QD3D12_ShutdownForQuake(void);
extern "C" void APIENTRY glSelectTextureSGIS(GLenum texture);
extern "C" void APIENTRY glMTexCoord2fSGIS(GLenum texture, GLfloat s, GLfloat t);
extern "C" void APIENTRY glActiveTextureARB(GLenum texture);
extern "C" void APIENTRY glMultiTexCoord2fARB(GLenum texture, GLfloat s, GLfloat t);

// Existing GL wrapper function from your compatibility layer
extern "C" void APIENTRY glBindTexture(unsigned int target, unsigned int texture);

struct QD3D12FakeContext
{
    HDC   dc;
    HWND  hwnd;
    bool  initialized;
};

static QD3D12FakeContext* g_currentContext = nullptr;
static HDC                g_currentDC = nullptr;

static void QD3D12_GetClientSize(HWND hwnd, int& w, int& h)
{
    RECT rc = {};
    GetClientRect(hwnd, &rc);
    w = rc.right - rc.left;
    h = rc.bottom - rc.top;

    if (w <= 0) w = 640;
    if (h <= 0) h = 480;
}

extern "C" QD3D12_HGLRC WINAPI qd3d12_wglCreateContext(HDC hdc)
{
    if (!hdc)
        return nullptr;

    HWND hwnd = WindowFromDC(hdc);
    if (!hwnd)
        return nullptr;

    QD3D12FakeContext* ctx = new QD3D12FakeContext();
    ctx->dc = hdc;
    ctx->hwnd = hwnd;
    ctx->initialized = false;
    return (QD3D12_HGLRC)ctx;
}

extern "C" BOOL WINAPI qd3d12_wglMakeCurrent(HDC hdc, QD3D12_HGLRC hglrc)
{
    if (!hdc || !hglrc)
    {
        g_currentDC = nullptr;
        g_currentContext = nullptr;
        return TRUE;
    }

    QD3D12FakeContext* ctx = (QD3D12FakeContext*)hglrc;
    ctx->dc = hdc;

    if (!ctx->initialized)
    {
        int w = 640, h = 480;
        QD3D12_GetClientSize(ctx->hwnd, w, h);

        if (!QD3D12_InitForQuake(ctx->hwnd, w, h))
            return FALSE;

        ctx->initialized = true;
    }

    g_currentDC = hdc;
    g_currentContext = ctx;
    return TRUE;
}

extern "C" PROC WINAPI qd3d12_wglGetProcAddress(LPCSTR name)
{
    if (!name)
        return nullptr;

    if (lstrcmpiA(name, "glBindTexture") == 0)
        return (PROC)&glBindTexture;

    if (lstrcmpiA(name, "glBindTextureEXT") == 0)
        return (PROC)&glBindTextureEXT;

    if (lstrcmpiA(name, "glSelectTextureSGIS") == 0)
        return (PROC)&glSelectTextureSGIS;

    if (lstrcmpiA(name, "glMTexCoord2fSGIS") == 0)
        return (PROC)&glMTexCoord2fSGIS;

    if (lstrcmpiA(name, "glActiveTextureARB") == 0)
        return (PROC)&glActiveTextureARB;

    if (lstrcmpiA(name, "glMultiTexCoord2fARB") == 0)
        return (PROC)&glMultiTexCoord2fARB;

    return nullptr;
}

extern "C" HDC WINAPI qd3d12_wglGetCurrentDC(void)
{
    return g_currentDC;
}

extern "C" QD3D12_HGLRC WINAPI qd3d12_wglGetCurrentContext(void)
{
    return (QD3D12_HGLRC)g_currentContext;
}

extern "C" BOOL WINAPI qd3d12_wglDeleteContext(QD3D12_HGLRC hglrc)
{
    if (!hglrc)
        return FALSE;

    QD3D12FakeContext* ctx = (QD3D12FakeContext*)hglrc;

    if (ctx == g_currentContext)
    {
        if (ctx->initialized)
            QD3D12_ShutdownForQuake();

        g_currentContext = nullptr;
        g_currentDC = nullptr;
    }

    delete ctx;
    return TRUE;
}

extern "C" void APIENTRY glBindTextureEXT(unsigned int target, unsigned int texture)
{
    glBindTexture(target, texture);
}