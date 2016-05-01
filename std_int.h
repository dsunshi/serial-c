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

#ifndef __STD_INT_H_
#define __STD_INT_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
*                             Exported Data Types                             *
******************************************************************************/
#ifndef UINT8_MAX
    typedef unsigned char  uint8_t;
    #define UINT8_MAX      0xFFu
#endif

#ifndef UINT16_MAX
    typedef unsigned short uint16_t;
    #define UINT16_MAX     0xFFFFu
#endif

#ifndef UINT32_MAX
    typedef unsigned int   uint32_t;
    #define UINT32_MAX     0xFFFFFFFFul
#endif

#if (__bool_true_false_are_defined == 1)
    /* Use C99 built-in bool*/
#else
  #if defined(_WIN32) && !defined(__MINGW32__)
    /* MS VS only supports C89 C, so define our own bool */
    #pragma once

    #define false   0u
    #define true    1u
    #define bool    int
  #else
    #ifdef __cplusplus
        /* Use built-in C++ bool */
    #else
        typedef uint8_t        bool;
        #define false          ( (bool) 0u     )
        #define true           ( (bool) !false )
    #endif /* C++ */
  #endif   /* C89 */
#endif     /* C99 */

#ifndef __SIZE_TYPE__
    #define __SIZE_TYPE__ uint32_t
#endif

#if !( defined(__GNUG__) && defined(size_t) )
    typedef __SIZE_TYPE__ size_t;
#endif /* !(defined (__GNUG__) && defined (size_t)) */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STD_INT_H_ */