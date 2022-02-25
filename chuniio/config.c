#include <windows.h>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "chuniio/config.h"

static const int chuni_io_default_cells[] = {
    'L', 'L', 'L', 'L',
    'K', 'K', 'K', 'K',
    'J', 'J', 'J', 'J',
    'H', 'H', 'H', 'H',
    'G', 'G', 'G', 'G',
    'F', 'F', 'F', 'F',
    'D', 'D', 'D', 'D',
    'S', 'S', 'S', 'S',
};

void chuni_io_config_load(
        struct chuni_io_config *cfg,
        const wchar_t *filename)
{
    wchar_t key[16];
    int i;

    assert(cfg != NULL);
    assert(filename != NULL);

    cfg->vk_test = GetPrivateProfileIntW(L"io3", L"test", '1', filename);
    cfg->vk_service = GetPrivateProfileIntW(L"io3", L"service", '2', filename);
    cfg->vk_coin = GetPrivateProfileIntW(L"io3", L"coin", '3', filename);

    cfg->vk_ir[0] = GetPrivateProfileIntW(L"io3", L"ir1", VK_OEM_PERIOD, filename); //1
    cfg->vk_ir[1] = GetPrivateProfileIntW(L"io3", L"ir2", VK_OEM_2, filename); //2
    cfg->vk_ir[2] = GetPrivateProfileIntW(L"io3", L"ir3", VK_OEM_1, filename); //3
    cfg->vk_ir[3] = GetPrivateProfileIntW(L"io3", L"ir4", VK_OEM_7, filename); //4
    cfg->vk_ir[4] = GetPrivateProfileIntW(L"io3", L"ir5", VK_OEM_4, filename); //5
    cfg->vk_ir[5] = GetPrivateProfileIntW(L"io3", L"ir6", VK_OEM_6, filename); //6


    for (i = 0 ; i < 32 ; i++) {
        swprintf_s(key, _countof(key), L"cell%i", i + 1);
        cfg->vk_cell[i] = GetPrivateProfileIntW(
                L"slider",
                key,
                chuni_io_default_cells[i],
                filename);
    }
}
