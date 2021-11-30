/*
Copyright (C) 1997-2001 Id Software, Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#pragma once

#include "Common/Net/Net.h"

#if USE_ICMP
void SV_ErrorEvent(NetAdr *from, int ee_errno, int ee_info);
#endif
void SV_Init(void);
void SV_Shutdown(const char *finalmsg, ErrorType type);
unsigned SV_Frame(unsigned msec);
#if USE_SYSCON
void SV_SetConsoleTitle(void);
#endif
//void SV_ConsoleOutput(const char *msg);
uint32_t		SV_GetServerState (void);					// WATISDEZE: Added for client game dll
void            SV_SetServerState (uint32_t serverSate);	// WATISDEZE: Added for client game dll

#if USE_CLIENT
char *SV_GetSaveInfo(const char *dir);
#endif

// user.c
void SV_PreRunCmd(void);
void SV_RunCmdCleanup(void);