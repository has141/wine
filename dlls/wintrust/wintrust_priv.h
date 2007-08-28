/*
 * Copyright 2007 Juan Lang
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
#ifndef __WINTRUST_PRIV_H__
#define __WINTRUST_PRIV_H__

void * WINAPI WINTRUST_Alloc(DWORD cb);
void * WINAPI WINTRUST_ReAlloc(void *ptr, DWORD cb);
void WINAPI WINTRUST_Free(void *p);
BOOL WINAPI WINTRUST_AddStore(CRYPT_PROVIDER_DATA *data, HCERTSTORE store);
BOOL WINAPI WINTRUST_AddSgnr(CRYPT_PROVIDER_DATA *data,
 BOOL fCounterSigner, DWORD idxSigner, CRYPT_PROVIDER_SGNR *sgnr);

#endif /* ndef __WINTRUST_PRIV_H__ */
