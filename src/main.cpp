#include "Application.h"
#include <vitasdk.h>

int main() {
    PsvitaSpot::Application app;

    if (!app.initialize()) {
        sceKernelExitProcess(1);
        return 1;
    }

    app.run();
    app.shutdown();

    sceKernelExitProcess(0);
    return 0;
}
