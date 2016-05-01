/*
 * Copyright (c) 2016 David Sunshine, <http://sunshin.es>
 * 
 * This file is part of serial-c.
 * 
 * serial-c is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * serial-c is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with serial-c.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __STD_TYPES_H_
#define __STD_TYPES_H_

/******************************************************************************
*                                   Includes                                  *
******************************************************************************/
#include "std_int.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
*                             Exported Data Types                             *
******************************************************************************/
#define STD_HIGH     1u
#define STD_LOW      0u

#define STD_ACTIVE   1u
#define STD_IDLE     0u

#define STD_ON       1u
#define STD_OFF      0u

#ifndef STATUSTYPEDEFINED
    #define STATUSTYPEDEFINED
    #define E_OK     0u
    typedef unsigned char StatusType;
#endif

#define E_NOT_OK     1u
#define E_PENDING    2u

typedef uint8_t Std_ReturnType;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STD_TYPES_H_ */