/*
 * Copyright 2016 Alistair Leslie-Hughes
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>

#include <dplay8.h>
#include "wine/test.h"

#include "dpnet_test.h"

static const GUID appguid = { 0xcd0c3d4b, 0xe15e, 0x4cf2, { 0x9e, 0xa8, 0x6e, 0x1d, 0x65, 0x48, 0xc5, 0xa5 } };

static int cnt_thread_create = 0;
static int cnt_thread_destroy = 0;
static int cnt_complete       = 0;
static HANDLE enumevent       = NULL;

static HRESULT WINAPI DirectPlayThreadHandler(void *context, DWORD message_id, void *buffer)
{
    switch(message_id)
    {
        case DPN_MSGID_CREATE_THREAD:
            cnt_thread_create++;
            break;
        case DPN_MSGID_DESTROY_THREAD:
            cnt_thread_destroy++;
            break;
        case DPN_MSGID_ASYNC_OP_COMPLETE:
            cnt_complete++;
            if(cnt_complete >= 2)
                SetEvent(enumevent);
        default:
            trace("DirectPlayThreadHandler: 0x%08x\n", message_id);
    }
    return S_OK;
}

static void create_threadpool(void)
{
    HRESULT hr;
    IDirectPlay8ThreadPool *pool1 = NULL;
    IDirectPlay8ThreadPool *pool2 = NULL;
    DWORD threadcnt = 10;

    hr = CoCreateInstance( &CLSID_DirectPlay8ThreadPool, NULL, CLSCTX_ALL, &IID_IDirectPlay8ThreadPool, (void**)&pool1);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = CoCreateInstance( &CLSID_DirectPlay8ThreadPool, NULL, CLSCTX_ALL, &IID_IDirectPlay8ThreadPool, (void**)&pool2);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IDirectPlay8ThreadPool_Initialize(pool1, NULL, NULL, 0);
    todo_wine ok(hr == DPNERR_INVALIDPARAM, "got 0x%08x\n", hr);

    hr = IDirectPlay8ThreadPool_Initialize(pool1, NULL, &DirectPlayThreadHandler, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IDirectPlay8ThreadPool_Initialize(pool2, NULL, &DirectPlayThreadHandler, 0);
    todo_wine ok(hr == DPNERR_ALREADYINITIALIZED, "got 0x%08x\n", hr);

    hr = IDirectPlay8ThreadPool_GetThreadCount(pool1, -1, &threadcnt, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(threadcnt == 0, "got %d\n", threadcnt);

    hr = IDirectPlay8ThreadPool_SetThreadCount(pool1, -1, 5, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    todo_wine ok(cnt_thread_create == 5, "got %d\n", threadcnt);

    hr = IDirectPlay8ThreadPool_SetThreadCount(pool2, -1, 5, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    todo_wine ok(cnt_thread_create == 5, "got %d\n", threadcnt);

    /* Thead count must be zero before DoWork can be called. */
    hr = IDirectPlay8ThreadPool_DoWork(pool1, 100, 0);
    todo_wine ok(hr == DPNERR_NOTREADY, "got 0x%08x\n", hr);

    hr = IDirectPlay8ThreadPool_GetThreadCount(pool1, -1, &threadcnt, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    todo_wine ok(threadcnt == 5, "got %d\n", threadcnt);

    hr = IDirectPlay8ThreadPool_SetThreadCount(pool1, -1, 0, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    todo_wine ok(cnt_thread_destroy == 5, "got %d\n", threadcnt);

    hr = IDirectPlay8ThreadPool_DoWork(pool1, 100, 0);
    ok(hr == DPN_OK, "got 0x%08x\n", hr);

    hr = IDirectPlay8ThreadPool_Close(pool1, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IDirectPlay8ThreadPool_Close(pool2, 0);
    todo_wine ok(hr == DPNERR_UNINITIALIZED, "got 0x%08x\n", hr);

    IDirectPlay8ThreadPool_Release(pool1);
    IDirectPlay8ThreadPool_Release(pool2);
}

static void test_enum_hosts(void)
{
    HRESULT hr;
    IDirectPlay8Client* client = NULL;
    IDirectPlay8Address *host = NULL;
    IDirectPlay8Address *local = NULL;
    IDirectPlay8ThreadPool *pool1 = NULL;
    DPN_APPLICATION_DESC appdesc;
    DPNHANDLE async = 0, async2 = 0;
    static const WCHAR localhost[] = {'1','2','7','.','0','.','0','.','1',0};
    DWORD threadcnt;

    enumevent = CreateEventA( NULL, TRUE, FALSE, NULL);

    memset( &appdesc, 0, sizeof(DPN_APPLICATION_DESC) );
    appdesc.dwSize  = sizeof( DPN_APPLICATION_DESC );
    appdesc.guidApplication  = appguid;

    hr = CoCreateInstance( &CLSID_DirectPlay8ThreadPool, NULL, CLSCTX_ALL, &IID_IDirectPlay8ThreadPool, (void**)&pool1);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IDirectPlay8ThreadPool_Initialize(pool1, NULL, &DirectPlayThreadHandler, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IDirectPlay8ThreadPool_GetThreadCount(pool1, -1, &threadcnt, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(threadcnt == 0, "got %d\n", threadcnt);

    hr = CoCreateInstance(&CLSID_DirectPlay8Client, NULL, CLSCTX_INPROC_SERVER, &IID_IDirectPlay8Client, (void **)&client);
    ok(hr == S_OK, "CoCreateInstance failed with 0x%x\n", hr);

    hr = IDirectPlay8Client_Initialize(client, NULL, DirectPlayThreadHandler, 0);
    ok(hr == S_OK, "IDirectPlay8Client_Initialize failed with %x\n", hr);

    hr = IDirectPlay8ThreadPool_GetThreadCount(pool1, -1, &threadcnt, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    todo_wine ok(threadcnt == 1, "got %d\n", threadcnt);

    hr = CoCreateInstance( &CLSID_DirectPlay8Address, NULL, CLSCTX_ALL, &IID_IDirectPlay8Address, (LPVOID*)&local);
    ok(hr == S_OK, "IDirectPlay8Address failed with 0x%08x\n", hr);

    hr = IDirectPlay8Address_SetSP(local, &CLSID_DP8SP_TCPIP);
    ok(hr == S_OK, "IDirectPlay8Address_SetSP failed with 0x%08x\n", hr);

    hr = CoCreateInstance( &CLSID_DirectPlay8Address, NULL, CLSCTX_ALL, &IID_IDirectPlay8Address, (LPVOID*)&host);
    ok(hr == S_OK, "IDirectPlay8Address failed with 0x%08x\n", hr);

    hr = IDirectPlay8Address_SetSP(host, &CLSID_DP8SP_TCPIP);
    ok(hr == S_OK, "IDirectPlay8Address_SetSP failed with 0x%08x\n", hr);

    hr = IDirectPlay8Address_AddComponent(host, DPNA_KEY_HOSTNAME, localhost, sizeof(localhost),
                                                         DPNA_DATATYPE_STRING);
    ok(hr == S_OK, "IDirectPlay8Address failed with 0x%08x\n", hr);

    hr = IDirectPlay8Client_EnumHosts(client, &appdesc, host, local, NULL, 0, INFINITE, 0, INFINITE, NULL,  &async, 0);
    todo_wine ok(hr == DPNSUCCESS_PENDING, "IDirectPlay8Client_EnumHosts failed with 0x%08x\n", hr);
    todo_wine ok(async, "No Handle returned\n");

    hr = IDirectPlay8ThreadPool_GetThreadCount(pool1, -1, &threadcnt, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    todo_wine ok(threadcnt == 6, "got %d\n", threadcnt);

    hr = IDirectPlay8Client_EnumHosts(client, &appdesc, host, local, NULL, 0, INFINITE, 0, INFINITE, NULL,  &async2, 0);
    todo_wine ok(hr == DPNSUCCESS_PENDING, "IDirectPlay8Client_EnumHosts failed with 0x%08x\n", hr);

    WaitForSingleObject(enumevent, 1000);

    hr = IDirectPlay8ThreadPool_GetThreadCount(pool1, -1, &threadcnt, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    todo_wine ok(threadcnt == 6, "got %d\n", threadcnt);

    hr = IDirectPlay8Client_CancelAsyncOperation(client, async, 0);
    ok(hr == S_OK, "IDirectPlay8Client_CancelAsyncOperation failed with 0x%08x\n", hr);

    hr = IDirectPlay8ThreadPool_GetThreadCount(pool1, -1, &threadcnt, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    todo_wine ok(threadcnt == 6, "got %d\n", threadcnt);

    hr = IDirectPlay8Client_CancelAsyncOperation(client, async2, 0);
    ok(hr == S_OK, "IDirectPlay8Client_CancelAsyncOperation failed with 0x%08x\n", hr);

    hr = IDirectPlay8ThreadPool_GetThreadCount(pool1, -1, &threadcnt, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    todo_wine ok(threadcnt == 6, "got %d\n", threadcnt);

    IDirectPlay8Address_Release(local);
    IDirectPlay8Address_Release(host);

    hr = IDirectPlay8ThreadPool_Close(pool1, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    IDirectPlay8Client_Release(client);
    IDirectPlay8ThreadPool_Release(pool1);

    CloseHandle(enumevent);
}

START_TEST(thread)
{
    HRESULT hr;
    BOOL firewall_enabled;
    char path[MAX_PATH];

    if(!GetSystemDirectoryA(path, MAX_PATH))
    {
        skip("Failed to get systems directory\n");
        return;
    }
    strcat(path, "\\dpnet.dll");

    if (!winetest_interactive && is_stub_dll(path))
    {
        win_skip("dpnet is a stub dll, skipping tests\n");
        return;
    }

    if ((firewall_enabled = is_firewall_enabled()) && !is_process_elevated())
    {
        skip("no privileges, skipping tests to avoid firewall dialog\n");
        return;
    }

    if (firewall_enabled)
    {
        HRESULT hr = set_firewall(APP_ADD);
        if (hr != S_OK)
        {
            skip("can't authorize app in firewall %08x\n", hr);
            return;
        }
    }

    hr = CoInitialize(0);
    ok(hr == S_OK, "failed to init com\n");
    if(hr != S_OK)
        return;

    create_threadpool();
    test_enum_hosts();

    CoUninitialize();
}