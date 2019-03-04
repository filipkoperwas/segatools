#include <windows.h>

#include "amex/ds.h"

#include "hook/process.h"

#include "platform/nusec.h"

#include "util/clock.h"
#include "util/dprintf.h"
#include "util/spike.h"

static process_entry_t app_startup;

static DWORD CALLBACK app_pre_startup(void)
{
    dprintf("--- Begin %s ---\n", __func__);

    spike_hook_init("minispike.txt");
    clock_hook_init();
    ds_hook_init();
    nusec_hook_init();

    dprintf("---  End  %s ---\n", __func__);

    return app_startup();
}

BOOL WINAPI DllMain(HMODULE mod, DWORD cause, void *ctx)
{
    HRESULT hr;

    if (cause != DLL_PROCESS_ATTACH) {
        return TRUE;
    }

    hr = process_hijack_startup(app_pre_startup, &app_startup);

    if (!SUCCEEDED(hr)) {
        dprintf("Failed to hijack process startup: %x\n", (int) hr);
    }

    return SUCCEEDED(hr);
}
