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

#ifndef __SERIAL_TYPES_H_
#define __SERIAL_TYPES_H_

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
typedef uint8_t SerialLevel;

typedef enum
{
  five_bits  = 5,
  six_bits   = 6,
  seven_bits = 7,
  eight_bits = 8
} ByteSize;

typedef enum
{
  parity_none  = 0,
  parity_odd   = 1,
  parity_even  = 2,
  parity_mark  = 3,
  parity_space = 4
} Parity;

typedef enum
{
  stopbits_one = 1,
  stopbits_two = 2,
  stopbits_one_point_five
} StopBits;

typedef enum
{
  flowcontrol_none = 0,
  flowcontrol_software,
  flowcontrol_hardware
} FlowControl;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __SERIAL_TYPES_H_ */