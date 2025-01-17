/*
 * Copyright 2016-2017, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *
 *     * Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stddef.h>
#include <string.h>
#include <syscall.h>
#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>

#include "libsyscall_intercept_hook_point.h"

static int hook(long syscall_number,
				long arg0, long arg1,
				long arg2, long arg3,
				long arg4, long arg5,
				long *result)
{
	(void) arg3;
	(void) arg4;
	(void) arg5;
	
	if (syscall_number == SYS_listen)
	{
		printf("listen() intercepted\n");
		printf("pid : %ld\n", (long)getpid());
		*result = syscall_no_intercept(SYS_listen, arg0, arg1);
		return 0;
	}
	if (syscall_number == SYS_bind)
	{
		printf("bind() intercepted\n");
		*result = syscall_no_intercept(SYS_bind, arg0, arg1, arg2);
		return 0;
	}
	
	if (syscall_number == SYS_epoll_create1)
	{
		printf("epoll() intercepted\n");
		printf("pid : %ld\n", (long)getpid());
		*result = syscall_no_intercept(SYS_epoll_create1, arg0, arg1, arg2);
		return 0;
	}
	else
	{
		return -1;
	}
}

static __attribute__((constructor)) void
start(void)
{
	printf("hello\n");
	printf("hello2\n");
	intercept_hook_point = &hook;
}
