/*
 * MIT License
 * 
 * Copyright (c) 2025 Chris Nicolls
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// -----------------------------------------------------------------------------
// USAGE:
// -This is a very simple ring buffer for storing/accessiong data elements
// -This is a lock-free structure which burns a single buffer element, so the max
// number of elements this will ever store is [len - 1]
// -This ring buffer is thread safe for a single producer and single consumer
// (i.e. one IRQ and one main application)
// -This is suitable for embedded applications without the use of divide/modulo
// ----------------------------------------------------------------------------

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#ifndef rb_data_t
#define rb_data_t uint8_t
#endif

typedef struct
{
	rb_data_t* buffer;
	uint32_t len;
	volatile uint32_t wr;
	volatile uint32_t rd;
} ring_buffer_t;

typedef enum
{
	RB_SUCCESS,
	RB_ERROR,
	RB_FULL,
	RB_EMPTY
} rb_error_t;

rb_error_t rbInit(ring_buffer_t* rb, rb_data_t* buffer, uint32_t len);
rb_error_t rbPush(ring_buffer_t* rb, rb_data_t val);
rb_error_t rbPop(ring_buffer_t* rb, rb_data_t* dest);
rb_error_t rbPeek(ring_buffer_t* rb, rb_data_t* dest);
rb_error_t rbPushMultiple(ring_buffer_t* rb, rb_data_t* source, uint32_t len);
rb_error_t rbPopMultiple(ring_buffer_t* rb, rb_data_t* dest, uint32_t len);
bool rbFull(ring_buffer_t* rb);
bool rbEmpty(ring_buffer_t* rb);
uint32_t rbFilled(ring_buffer_t* rb);
uint32_t rbFree(ring_buffer_t* rb);

#ifdef __cplusplus
}
#endif

#endif // RING_BUFFER_H_
