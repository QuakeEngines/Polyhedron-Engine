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

// cl_null.c -- this file can stub out the entire client system
// for pure dedicated servers

#include "Shared/Shared.h"
#include "Common/CVar.h"
#include "Common/Bsp.h"
#include "Client/Client.h"

static void Key_Bind_Null_f(void)
{
}

void Key_Init(void)
{
    Cmd_AddCommand("bind", Key_Bind_Null_f);
    Cmd_AddCommand("unbind", Key_Bind_Null_f);
    Cmd_AddCommand("unbindall", Key_Bind_Null_f);
}

void bsp_add_entlights(const bsp_t* bsp)
{

}

void initlight_changed(cvar_t *self)
{
	
}
void initlightbind_changed(cvar_t *self)
{
}

int num_entlights;

cvar_t		*initlight;
cvar_t		*initlightbind;

cvar_t		*inittargetlightLSbind;
cvar_t		*inittargetlightbind;
void inittargetlightLSbind_changed(cvar_t *self)
{

}
void inittargetlightbind_changed(cvar_t *self)
{

}
