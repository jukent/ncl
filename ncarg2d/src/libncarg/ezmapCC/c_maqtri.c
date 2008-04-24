/*
 *	$Id: c_maqtri.c,v 1.1 2008-04-18 04:09:20 kennison Exp $
 */
/************************************************************************
*                                                                       *
*                Copyright (C)  2000                                    *
*        University Corporation for Atmospheric Research                *
*                All Rights Reserved                                    *
*                                                                       *
* This file is free software; you can redistribute it and/or modify     *
* it under the terms of the GNU General Public License as published     *
* by the Free Software Foundation; either version 2 of the License, or  *
* (at your option) any later version.                                   *
*                                                                       *
* This software is distributed in the hope that it will be useful, but  *
* WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
* General Public License for more details.                              *
*                                                                       *
* You should have received a copy of the GNU General Public License     *
* along with this software; if not, write to the Free Software         *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307   *
* USA.                                                                  *
*                                                                       *
************************************************************************/

#include <ncarg/ncargC.h>

extern void NGCALLF(maqtri,MAQTRI)(float*,float*,float*,float*);

void c_maqtri
#ifdef NeedFuncProto
(
    float uval,
    float vval,
    float *rlat,
    float *rlon
)
#else
(uval,vval,rlat,rlon)
    float uval;
    float vval;
    float *rlat;
    float *rlon;
#endif
{
    NGCALLF(maqtri,MAQTRI)(&uval,&vval,rlat,rlon);
}