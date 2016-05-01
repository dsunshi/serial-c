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

/******************************************************************************
*                                   Includes                                  *
******************************************************************************/
#include "serial.h"

/******************************************************************************
*                          Local Function Prototypes                          *
******************************************************************************/
static Std_ReturnType system_set_signal(uint8_t request, uint8_t command);
static Std_ReturnType set_signal(uint8_t signal);
static Std_ReturnType clear_signal(uint8_t signal);
static Std_ReturnType system_unlock(MUTEX * mutex);
static Std_ReturnType system_lock(MUTEX * mutex);

static Std_ReturnType read_lock(Serial *serial);
static Std_ReturnType read_unlock(Serial *serial);
static Std_ReturnType write_lock(Serial *serial);
static Std_ReturnType write_unlock(Serial *serial);


#define BREAK_SIGNAL       0
#define RTS_SIGNAL         1
#define DTR_SIGNAL         2

#define SET_SIGNAL_INDEX   0
#define CLR_SIGNAL_INDEX   1
#define CMD_SIGNAL_INDEX   2

static const uint8_t command_table[3][3] =
{
  /*  BREAK  */ {SET_BREAK, CLR_BREAK, TIOCM_BRK},
  /*   RTS   */ {SET_RTS,   CLR_RTS,   TIOCM_RTS},
  /*   DTR   */ {SET_DTR,   CLR_DTR,   TIOCM_DTR}
};

Std_ReturnType static system_set_signal(Serial * serial, uint8_t request, uint8_t command)
{
    Std_ReturnType result = E_NOT_OK;

    if (serial->is_open == false)
    {
        fprintf(stderr, "Serial port is not open!\n");
    }
    else
    {
        if ( IS_RESULT_FAILED( SYS_IO_CONTROL(fd_, request, &command) ) )
        {
            fprintf(stderr, "Request %d to execute command: %d FAILED!\n", request, command);
        }
        else
        {
            /* Do nothing - success */
            result = E_OK;
        }
    }

    return result;
}


static Std_ReturnType set_signal(uint8_t signal)
{
    return system_set_signal(command_table[signal][SET_SIGNAL_INDEX], command_table[signal][CMD_SIGNAL_INDEX]);
}

static Std_ReturnType clear_signal(uint8_t signal)
{
    return system_set_signal(command_table[signal][CLR_SIGNAL_INDEX], command_table[signal][CMD_SIGNAL_INDEX]);
}

static Std_ReturnType system_unlock(MUTEX * mutex)
{
    const int result      = SYS_MUTEX_UNLOCK(mutex);
    Std_ReturnType result = E_NOT_OK;
    
    if ( IS_RESULT_FAILED(result) )
    {
        fprintf(stderr, "FAILED to unlock mutex!\n");
    }
    else
    {
        /* Do nothing - unlock was successful */
        result = E_OK;
    }

    return result;
}

static Std_ReturnType system_lock(MUTEX * mutex)
{
    const int result      = SYS_MUTEX_LOCK(mutex);
    Std_ReturnType result = E_NOT_OK;
    
    if ( IS_RESULT_FAILED(result) )
    {
        fprintf(stderr, "FAILED to lock mutex!\n");
    }
    else
    {
        /* Do nothing - unlock was successful */
        result = E_OK;
    }

    return result;
}

static Std_ReturnType read_lock(Serial *serial)
{
    return system_lock(serial->read_mutex);
}

static Std_ReturnType read_unlock(Serial *serial)
{
    return system_unlock(serial->read_mutex);
}

static Std_ReturnType write_lock(Serial *serial)
{
    return system_lock(serial->write_mutex);
}

static Std_ReturnType write_unlock(Serial *serial)
{
    return system_unlock(serial->write_mutex);
}

Std_ReturnType set_break(Serial * serial, SerialLevel level)
{
    Std_ReturnType result = E_NOT_OK;

    if (level == STD_HIGH)
    {
        result = set_signal(serial,   BREAK_SIGNAL);
    }
    else
    {
        result = clear_signal(serial, BREAK_SIGNAL);
    }

    return result;
}

Std_ReturnType set_RTS(Serial * serial, SerialLevel level)
{
    Std_ReturnType result = E_NOT_OK;

    if (level == STD_HIGH)
    {
        result = set_signal(serial,   RTS_SIGNAL);
    }
    else
    {
        result = clear_signal(serial, RTS_SIGNAL);
    }

    return result;
}

Std_ReturnType set_DTR(Serial * serial, SerialLevel level)
{
    Std_ReturnType result = E_NOT_OK;

    if (level == STD_HIGH)
    {
        result = set_signal(serial,   DTR_SIGNAL);
    }
    else
    {
        result = clear_signal(serial, DTR_SIGNAL);
    }

    return result;
}