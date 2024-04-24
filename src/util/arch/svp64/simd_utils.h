/*
 * Copyright (c) 2024, VectorCamp PC
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of Intel Corporation nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** \file
 * \brief SIMD types and primitive operations.
 */

#ifndef ARCH_SVP64_SIMD_UTILS_H
#define ARCH_SVP64_SIMD_UTILS_H

#include <Python.h>
#include <stdint.h>
#include <stdio.h>

#include "pypowersim_wrapper_common.h"

#include "util/simd_types.h"

#include "util/arch/svp64/print_simd.h"

static const char *movemask_svp64_filename = "./bin/movemask_svp64.bin";

static int movemask_epi8_svp64(m128 a) {
    printf("movemask_epi8_svp64 called:\n");
    print_u8x16("a", a);
    uint64_t _a[2];
    _mm_storeu_si128((__m128i*) _a, a);
    
    // The only argument is a 128-bit vector, which in the absense of vector registers, we're going to place it in 
    // GPRs 3 and 4
    // Create the pypowersim_state
    pypowersim_state_t *state = pypowersim_prepare();

    // Change the relevant elements, mandatory: body
    state->binary = PyBytes_FromStringAndSize(movemask_svp64_filename, strlen(movemask_svp64_filename));

    // Set GPR #3 to the high 64-bits of 'a'
    PyObject *a_hi_svp64 = PyLong_FromUnsignedLongLong(_a[0]);
    PyList_SetItem(state->initial_regs, 3, a_hi_svp64);

    // Set GPR #4 to the low 64-bits of 'a'
    PyObject *a_lo_svp64 = PyLong_FromUnsignedLongLong(_a[1]);
    PyList_SetItem(state->initial_regs, 4, a_lo_svp64);

    // Prepare the arguments object for the call
    pypowersim_prepareargs(state);

    // Call the function and get the resulting object
    state->result_obj = PyObject_CallObject(state->simulator, state->args);
    if (!state->result_obj) {
        PyErr_Print();
        printf("Error invoking 'run_a_simulation'\n");
        pypowersim_finalize(state);
        exit(1);
    }

    // Get the GPRs from the result_obj
    PyObject *final_regs = PyObject_GetAttrString(state->result_obj, "gpr");
    if (!final_regs) {
        PyErr_Print();
        printf("Error getting final GPRs\n");
        pypowersim_finalize(state);
        exit(1);
    }

    // GPR #3 holds the return value as an integer
    PyObject *key = PyLong_FromLongLong(3);
    PyObject *itm = PyDict_GetItem(final_regs, key);
    if (!itm) {
        PyErr_Print();
        printf("Error getting GPR #3\n");
        pypowersim_finalize(state);
        exit(1);
    }
    PyObject *value = PyObject_GetAttrString(itm, "value");
    if (!value) {
        PyErr_Print();
        printf("Error getting value of GPR #3\n");
        pypowersim_finalize(state);
        exit(1);
    }
    uint64_t val = PyLong_AsUnsignedLongLong(value);
    printf("return val \t: %016lx\n", val);
    pypowersim_finalize(state);

    return val;
}
 
/** \brief Return 1 if a and b are different otherwise 0 */
static really_inline int diff128(m128 a, m128 b) {
    return (movemask_epi8_svp64(_mm_cmpeq_epi8(a, b)) ^ 0xffff);
}

#define CASE_LSHIFT_VECTOR(a, count)  case count: return _mm_slli_si128((m128)(a), (count)); break;

static really_inline
m128 lshiftbyte_m128(const m128 a, int count_immed) {
    switch (count_immed) {
    case 0: return a; break;
    CASE_LSHIFT_VECTOR(a, 1);
    CASE_LSHIFT_VECTOR(a, 2);
    CASE_LSHIFT_VECTOR(a, 3);
    CASE_LSHIFT_VECTOR(a, 4);
    CASE_LSHIFT_VECTOR(a, 5);
    CASE_LSHIFT_VECTOR(a, 6);
    CASE_LSHIFT_VECTOR(a, 7);
    CASE_LSHIFT_VECTOR(a, 8);
    CASE_LSHIFT_VECTOR(a, 9);
    CASE_LSHIFT_VECTOR(a, 10);
    CASE_LSHIFT_VECTOR(a, 11);
    CASE_LSHIFT_VECTOR(a, 12);
    CASE_LSHIFT_VECTOR(a, 13);
    CASE_LSHIFT_VECTOR(a, 14);
    CASE_LSHIFT_VECTOR(a, 15);
    default: return (m128) _mm_setzero_si128(); break;
    }
}
#undef CASE_LSHIFT_VECTOR

static really_inline
m128 pshufb_m128(m128 a, m128 b) {
    return _mm_shuffle_epi8(a, b);
}

#endif // ARCH_SVP64_SIMD_UTILS_H
