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

#include "ring_buffer.h"
#include <string.h>

void rbInit(ring_buffer_t* rb, rb_data_t* buffer, uint32_t len)
{
	rb->buffer = buffer;
	rb->len    = len;
	rb->wr     = 0;
	rb->rd     = 0;
}

rb_error_t rbPush(ring_buffer_t* rb, rb_data_t val)
{
	if(rbFull(rb))
		return RB_FULL;

	rb->buffer[rb->wr] = val;

	uint32_t wr = rb->wr + 1;
	if(wr >= rb->len)
		wr = 0;
	rb->wr = wr;

	return RB_SUCCESS;
}

rb_error_t rbPop(ring_buffer_t* rb, rb_data_t* dest)
{
	if(rbEmpty(rb))
		return RB_EMPTY;

	*dest = rb->buffer[rb->rd];

	uint32_t rd = rb->rd + 1;
	if(rd >= rb->len)
		rd = 0;
	rb->rd = rd;

	return RB_SUCCESS;
}

rb_error_t rbPeek(ring_buffer_t* rb, rb_data_t* dest)
{
	if(rbEmpty(rb))
		return RB_EMPTY;

	*dest = rb->buffer[rb->rd];

	return RB_SUCCESS;
}

rb_error_t rbPushMultiple(ring_buffer_t* rb, rb_data_t* source, uint32_t len)
{
	if(rbFree(rb) < len)
		return RB_ERROR;

	uint32_t count = len;
	while(count)
	{
		uint32_t chunk = rb->len - rb->wr;
		if(count < chunk)
			chunk = count;

		memcpy(rb->buffer[rb->wr], source + (len - count), chunk * sizeof(rb_data_t));
		count -= chunk;

		uint32_t wr = rb->wr;
		wr += chunk;
		if(wr >= rb->len)
			wr = 0;
		rb->wr = wr;
	}

	return RB_SUCCESS;
}

rb_error_t rbPopMultiple(ring_buffer_t* rb, rb_data_t* dest, uint32_t len)
{
	if( (rbFilled(rb) < len) || (len == 0) )
		return RB_ERROR;

	uint32_t count = len;
	while(count)
	{
		uint32_t chunk = rb->len - rb->rd;
		if(count < chunk)
			chunk = count;

		memcpy(dest + (len - count), rb->buffer[rb->rd], chunk * sizeof(rb_data_t));
		count -= chunk;

		uint32_t rd = rb->rd;
		rd += chunk;
		if(rd >= rb->len)
			rd = 0;
		rb->rd = rd;
	}

	return RB_SUCCESS;
}

bool rbFull(ring_buffer_t* rb)
{
	uint32_t wr = rb->wr + 1;
	if(wr >= rb->len)
		wr = 0;
	return (wr == rb->rd);
}

bool rbEmpty(ring_buffer_t* rb)
{
	return (rb->wr == rb->rd);
}

uint32_t rbFilled(ring_buffer_t* rb)
{
	int32_t len = rb->wr - rb->rd;
	if(len < 0)
		len += rb->len;
	return (uint32_t)len;
}

uint32_t rbFree(ring_buffer_t* rb)
{
	return(rb->len - 1 - rbFilled(rb));
}