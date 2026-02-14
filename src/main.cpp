#include <vitasdk.h>
#include <vitaGL.h>

int main()
{
    vglInitExtended(0, 960, 544, 0x800000, SCE_GXM_MULTISAMPLE_4X);

    while (1)
    {
        vglStartRendering();

        glClearColor(0.07f, 0.07f, 0.07f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vglEndRendering();
        vglSwapBuffers(GL_FALSE);

        SceCtrlData pad;
        sceCtrlPeekBufferPositive(0, &pad, 1);

        if (pad.buttons & SCE_CTRL_START)
            break;
    }

    vglEnd();
    sceKernelExitProcess(0);
    return 0;
}
