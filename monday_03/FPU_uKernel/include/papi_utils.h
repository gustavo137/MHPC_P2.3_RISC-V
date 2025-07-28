/* Copyright (c) 2020, Barcelona Supercomputing Center
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met: 
 * redistributions of source code must retain the above copyright notice, this 
 * list of conditions and the following disclaimer; redistributions in binary form
 * must reproduce the above copyright notice, this list of conditions and the 
 * following disclaimer in the documentation and/or other materials provided with 
 * the distribution; neither the name of the copyright holder nor the names of its 
 * contributors may be used to endorse or promote products derived from this 
 * software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <papi.h>
#include <stdio.h>

inline int papi_init() {
	/*
	 * Initialize library
	 */
	int ret = PAPI_library_init(PAPI_VER_CURRENT);
	int EventSet = PAPI_NULL;
	if ( ret != PAPI_VER_CURRENT ) {
		fprintf(stderr, "PAPI library init error!\n");
		exit(1);
	}

	/*
	 * Initialize the EventSet
	 */
	if ( PAPI_create_eventset(&EventSet) != PAPI_OK ) {
		fprintf(stderr, "PAPI create EventSet error!\n");
		exit(1);
	}

	/*
	 * Add events
	 */
	// Instructions
	if ( PAPI_add_event(EventSet, PAPI_TOT_INS) != PAPI_OK ) {
		fprintf(stderr, "PAPI error adding PAPI_TOT_INS!\n");
		exit(1);
	}
	// FP instructions
	if ( PAPI_add_event(EventSet, PAPI_FP_INS) != PAPI_OK ) {
		fprintf(stderr, "PAPI error adding PAPI_FP_INS!\n");
		exit(1);
	}
	// SIMD instructions
	if ( PAPI_add_event(EventSet, PAPI_VEC_INS) != PAPI_OK ) {
		fprintf(stderr, "PAPI error adding PAPI_VEC_INS!\n");
		exit(1);
	}
	// Cycles
	if ( PAPI_add_event(EventSet, PAPI_TOT_CYC) != PAPI_OK ) {
		fprintf(stderr, "PAPI error adding PAPI_TOT_CYC!\n");
		exit(1);
	}
#if 0
	// Stalled cycles in backend
	if ( PAPI_add_named_event(EventSet, "r40000015") != PAPI_OK ) {
		fprintf(stderr, "PAPI error adding PAPI_STALLED_BACKEND!\n");
		exit(1);
	}
	// Stalled cycles in frontend
	if ( PAPI_add_named_event(EventSet, "r40000016") != PAPI_OK ) {
		fprintf(stderr, "PAPI error adding PAPI_STALLED_FRONTEND!\n");
		exit(1);
	}
#endif

	return EventSet;
}

inline void papi_init_read(int *EventSet) {
	if ( PAPI_start(*EventSet) != PAPI_OK ) {
		fprintf(stderr, "PAPI error starting counters!\n");
		exit(1);
	}
}

inline void papi_print_events(int *EventSet) {
#if 0
	long long values[6];
#endif
	long long values[4];
	if (PAPI_stop(*EventSet, values) != PAPI_OK) {
		fprintf(stderr, "PAPI error stoping counters!\n");
		exit(1);
	}

	// Print
	fprintf(stdout, "PAPI_CYC         = %llu\n", values[3]);
	fprintf(stdout, "PAPI_TOT_INS     = %llu\n", values[0]);
	fprintf(stdout, "PAPI_FP_INS      = %llu\n", values[1]);
	fprintf(stdout, "PAPI_VEC_INS     = %llu\n", values[2]);
#if 0
	fprintf(stdout, "STALLED_FRONTEND = %llu\n", values[4]);
	fprintf(stdout, "STALLED_BACKEND  = %llu\n", values[5]);
#endif
}
