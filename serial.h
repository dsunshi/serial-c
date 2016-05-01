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

#ifndef __SERIAL_H_
#define __SERIAL_H_

/******************************************************************************
*                                   Includes                                  *
******************************************************************************/
#include "std_types.h"
#include "serial_types.h"
#include "serial_priv.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
*                             Exported Data Types                             *
******************************************************************************/

//  SerialImpl (const string &port,
//              unsigned long baudrate,
//              bytesize_t bytesize,
//              parity_t parity,
//              stopbits_t stopbits,
//              flowcontrol_t flowcontrol);
//
//  string port_;               // Path to the file descriptor
//  int fd_;                    // The current file descriptor
//
//  bool is_open_;
//  bool xonxoff_;
//  bool rtscts_;
//
//  Timeout timeout_;           // Timeout for read operations
//  unsigned long baudrate_;    // Baudrate
//  uint32_t byte_time_ns_;     // Nanoseconds to transmit/receive a single byte
//
//  parity_t parity_;           // Parity
//  bytesize_t bytesize_;       // Size of the bytes
//  stopbits_t stopbits_;       // Stop Bits
//  flowcontrol_t flowcontrol_; // Flow Control
//
//  // Mutex used to lock the read functions
//  pthread_mutex_t read_mutex;
//  // Mutex used to lock the write functions
//  pthread_mutex_t write_mutex;

//  wstring port_;               // Path to the file descriptor
//  HANDLE fd_;
//
//  bool is_open_;
//
//  Timeout timeout_;           // Timeout for read operations
//  unsigned long baudrate_;    // Baudrate
//
//  parity_t parity_;           // Parity
//  bytesize_t bytesize_;       // Size of the bytes
//  stopbits_t stopbits_;       // Stop Bits
//  flowcontrol_t flowcontrol_; // Flow Control
//
//  // Mutex used to lock the read functions
//  HANDLE read_mutex;
//  // Mutex used to lock the write functions
//  HANDLE write_mutex;

typedef struct
{
    char * port;
    
    HANDLE fd;
    
    bool is_open;
    bool xonxoff;
    bool rtscts;
    
    Timeout     timeout;
    
    uint32_t    baudrate;
    uint32_t    byte_time_ns;
    
    Parity      parity;
    ByteSize    byte_size;
    StopBits    stop_bits;
    FlowControl flow_control;
    
    MUTEX       read_mutex;
    MUTEX       write_mutex;
    
} Serial;



/******************************************************************************
*                       Exported Function Prototypes                          *
******************************************************************************/

void   open(Serial * serial);
bool   is_open(Serial * serial);
void   close(Serial * serial);

size_t available(Serial * serial);

bool   wait_readable(Serial * serial);
void   wait_byte_times(Serial * serial);

void   set_port(Serial * serial, const char * port);
char  *get_port(Serial * serial, );

void     set_timeout(Serial * serial, Timeout * timeout);
Timeout  get_timeout(Serial * serial);

void     set_baudrate(Serial * serial, uint32_t baudrate);
uint32_t get_baudrate(Serial * serial);

void     set_byte_size(Serial * serial, ByteSize bytesize);
ByteSize get_byte_size(Serial * serial);

void     set_parity(Serial * serial, Parity parity);
Parity   get_parity(Serial * serial);

void     set_stop_bits(Serial * serial, StopBits stopbits);
StopBits get_stop_bits(Serial * serial);

void        set_flow_control(Serial * serial, FlowControl flowcontrol);
FlowControl get_flow_control(Serial * serial);

void flush(Serial * serial);
void flush_input(Serial * serial);
void flush_output(Serial * serial);

void send_break(Serial * serial, uint32_t duration);

Std_ReturnType set_break(Serial * serial, SerialLevel level);
Std_ReturnType set_RTS(Serial * serial, SerialLevel level);
Std_ReturnType set_DTR(Serial * serial, SerialLevel level);

SerialLevel get_CTS(Serial * serial);
SerialLevel get_DSR(Serial * serial);
SerialLevel get_RI(Serial * serial);
SerialLevel get_CD(Serial * serial);

size_t _read(       unit8_t *buffer, size_t length);
size_t _write(const unit8_t *buffer, size_t length);


#endif /* __SERIAL_H_ */