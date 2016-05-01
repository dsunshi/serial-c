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

#ifndef __SERIAL_PRIV_H_
#define __SERIAL_PRIV_H_

/******************************************************************************
*                                   Includes                                  *
******************************************************************************/
#include "std_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
*                             Exported Data Types                             *
******************************************************************************/

#if defined(_WIN32)
  #define IS_RESULT_FAILED(result) ((result) == 0)
  
  #define SET_BREAK SETBREAK
  #define CLR_BREAK CLRBREAK
  #define TIOCM_BRK 0
  
  #define SET_RTS   SETRTS
  #define CLR_RTS   CLRRTS
  #define TIOCM_RTS 0
  
  #define SET_DTR   SETDTR
  #define CLR_DTR   CLRDTR
  #define TIOCM_DTR 0
  
  #define MUTEX     HANDLE
  
#else
  #define IS_RESULT_FAILED(result) ((result) != 0)

  #define SET_BREAK TIOCSBRK
  #define CLR_BREAK TIOCCBRK
  #define TIOCM_BRK 0
  
  #define SET_RTS   TIOCMBIS
  #define CLR_RTS   TIOCMBIC
  
  #define SET_DTR   TIOCMBIS
  #define CLR_DTR   TIOCMBIC
  
  #define MUTEX     pthread_mutex_t
  #define HANDLE    int
#endif

#if defined(_WIN32)
  #define SYS_MUTEX_UNLOCK(mutex)              ReleaseMutex( (mutex) )
  #define SYS_MUTEX_LOCK(mutex)                WaitForSingleObject( (mutex), INFINITE )
  
  #define SYS_IO_CONTROL(fd, request, command) EscapeCommFunction( (fd), (request) )
  
  #define SYS_FLUSH(fd)                        FlushFileBuffers( (fd) )
#else
  #define SYS_MUTEX_UNLOCK(mutex)              pthread_mutex_unlock( (mutex) )
  #define SYS_MUTEX_LOCK(mutex)                pthread_mutex_lock( (mutex) )
  
  #define SYS_IO_CONTROL(fd, request, command) ioctl( (fd), (request), (command) )
  
  #define SYS_FLUSH(fd)                        tcdrain( (fd) )
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __SERIAL_PRIV_H_ */