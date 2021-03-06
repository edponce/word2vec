#ifndef _AVX512_H
#define _AVX512_H


/*
 *  Compiler and architecture specific settings
 */
#include "arch.h"


/*
 *  Include supporting header files based on compiler and architecture
 *  NOTE: currently only support x86_64, GCC and Intel compilers
 */
#include <x86intrin.h>
//#include <immintrin.h>


/*
 *  AVX512 512-bit wide vector units
 *  Define constants required for SIMD module to function properly.
 */
#define SIMD_INT __m512i
#define SIMD_FLT __m512
#define SIMD_DBL __m512d
#define SIMD_WIDTH_BYTES 64
#define SIMD_STREAMS_32  16
#define SIMD_STREAMS_64  8


#define __SIMD_FUN_ATTR__   ARCH_ATTR_INLINE // force inline when no optimizations
#define __SIMD_FUN_PREFIX__ inline static


/*
 *  Interface Legend
 *
 *  simd_*_iXX = signed XX-bit integers
 *  simd_*_uXX = unsigned XX-bit integers
 *  simd_*_fXX = floating-point XX-bit elements
 *  simd_*_XX  = unsigned/signed XX-bit integers
 *  simd_*_XX  = (set functions) specifies width to consider for integer types
 *  simd_*     = datatype obtained from function overloading and parameters
 */


/**************************
 *  Arithmetic intrinsics
 **************************/
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_add_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm512_add_epi32(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_add_i64(const SIMD_INT va, const SIMD_INT vb)
{ return _mm512_add_epi64(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_add(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm512_add_ps(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_add(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm512_add_pd(va, vb); }

/*!
 *  Fused multiply-add for 32/64-bit floating-point elements
 */
#if defined(__FMA__)
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_fmadd(const SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{ return _mm512_fmadd_ps(va, vb, vc); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_fmadd(const SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{ return _mm512_fmadd_pd(va, vb, vc); }

#else
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_fmadd(const SIMD_FLT va, const SIMD_FLT vb, const SIMD_FLT vc)
{
    const SIMD_FLT vab = _mm512_mul_ps(va, vb);
    return _mm512_add_ps(vab, vc);
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_fmadd(const SIMD_DBL va, const SIMD_DBL vb, const SIMD_DBL vc)
{
    const SIMD_DBL vab = _mm512_mul_pd(va, vb);
    return _mm512_add_pd(vab, vc);
}
#endif

/*!
 *  Multiply low unsigned 32-bit integers from each packed 64-bit elements
 *  and store the unsigned 64-bit results
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_mul_u32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm512_mul_epu32(va, vb); }

/*!
 *  Multiply low signed 32-bit integers from each packed 64-bit elements
 *  and store the signed 64-bit results
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_mul_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm512_mul_epi32(va, vb); }

/*!
 *  Perform 64-bit integer multiplication
 *  NOTE: requires at least AVX512DQ for _mm512_mullo_epi64()
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
//SIMD_INT simd_mul_i64(const SIMD_INT va, const SIMD_INT vb)
SIMD_INT simd_mul_u64(const SIMD_INT va, const SIMD_INT vb)
{ return _mm512_mullo_epi64(va, vb); }

/*!
 *  Multiply packed 32-bit integers, produce intermediate 64-bit integers,
 *  and store the low 32-bit results
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_mullo_i32(const SIMD_INT va, const SIMD_INT vb)
{ return _mm512_mullo_epi32(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_mul(const SIMD_FLT va, const SIMD_FLT vb)
{ return _mm512_mul_ps(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_mul(const SIMD_DBL va, const SIMD_DBL vb)
{ return _mm512_mul_pd(va, vb); }


/********************************
 *  Integral logical intrinsics
 ********************************/
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_or(const SIMD_INT va, const SIMD_INT vb)
{ return _mm512_or_si512(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_xor(const SIMD_INT va, const SIMD_INT vb)
{ return _mm512_xor_si512(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_and(const SIMD_INT va, const SIMD_INT vb)
{ return _mm512_and_si512(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_and(const SIMD_FLT va, const SIMD_INT vb)
{ return _mm512_and_ps(va, vb); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_and(const SIMD_DBL va, const SIMD_INT vb)
{ return _mm512_and_pd(va, vb); }


/*****************************
 *  Shift/Shuffle intrinsics
 *****************************/
/*
 *  Shift left (logical) packed 32/64-bit integers
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_sll_32(const SIMD_INT va, const int shft)
{ return _mm512_slli_epi32(va, (unsigned int)shft); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_srl_32(const SIMD_INT va, const int shft)
{ return _mm512_srli_epi32(va, (unsigned int)shft); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_sll_64(const SIMD_INT va, const int shft)
{ return _mm512_slli_epi64(va, (unsigned int)shft); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_srl_64(const SIMD_INT va, const int shft)
{ return _mm512_srli_epi64(va, (unsigned int)shft); }

/*
 *  Shuffle 32-bit elements using control value
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_shuffle_i32(const SIMD_INT va, const int ctrl)
{ return _mm512_shuffle_epi32(va, ctrl); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_shuffle_f32(const SIMD_FLT va, const SIMD_FLT vb, const int ctrl)
{ return _mm512_shuffle_ps(va, vb, ctrl); }

/*
 *  Merge either low/high parts from pair of registers
 *  into a single register
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_merge_lo(const SIMD_INT va, const SIMD_INT vb)
{
    const __m256i vb_lo = _mm512_castsi512_si256(vb);
    return _mm512_inserti64x4(va, vb_lo, 0x1);
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_merge_lo(const SIMD_FLT va, const SIMD_FLT vb)
{
    const __m256d vb_lo = _mm512_castpd512_pd256(vb);
    const SIMD_DBL vc = _mm512_insertf64x4(va, vb_lo, 0x1);
    return _mm512_castpd_ps(vc);
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_merge_lo(const SIMD_DBL va, const SIMD_DBL vb)
{
    const __m256d vb_lo = _mm512_castpd512_pd256(vb);
    return _mm512_insertf64x4(va, vb_lo, 0x1);
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_merge_hi(const SIMD_INT va, const SIMD_INT vb)
{
    const __m256i va_hi = _mm512_extracti64x4_epi64(va, 0x1);
    return _mm512_inserti64x4(vb, va_hi, 0x0);
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_merge_hi(const SIMD_FLT va, const SIMD_FLT vb)
{
    const __m256d va_hi = _mm512_extractf64x4_pd(va, 0x1);
    const SIMD_DBL vc = _mm512_insertf64x4(vb, va_hi, 0x0);
    return _mm512_castpd_ps(vc);
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_merge_hi(const SIMD_DBL va, const SIMD_DBL vb)
{
    const __m256d va_hi = _mm512_extractf64x4_pd(va, 0x1);
    return _mm512_insertf64x4(vb, va_hi, 0x0);
}

/*!
 *  Pack and merge a pair of registers
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_packmerge_i32(const SIMD_INT va, const SIMD_INT vb)
{
    // Pack va
    const int SIMD_INT va_pk = _mm512_maskz_compress_epi32(0x5555U, va);

    // Pack vb
    const int SIMD_INT vb_pk = _mm512_maskz_compress_epi32(0x5555U, vb);

    // Merge
    const __m256i vb_pk_lo = _mm512_castsi512_si256(vb_pk);
    return _mm512_inserti64x4(va_pk, vb_pk_lo, 0x1);
}


/*******************
 *  Set intrinsics
 *******************/
/*
 *  Set vector to zero.
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_set_zero(SIMD_INT * const va)
{ *va = _mm512_setzero_si512(); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_set_zero(SIMD_FLT * const va)
{ *va = _mm512_setzero_ps(); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_set_zero(SIMD_DBL * const va)
{ *va = _mm512_setzero_pd(); }

/*
 *  Set 32-bit integers to either 32/64 slots.
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set(const int sa)
{ return _mm512_set1_epi32(sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set_64(const int sa)
{ return _mm512_set1_epi64((long int)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set(const unsigned int sa)
{ return _mm512_set1_epi32((int)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set_64(const unsigned int sa)
{ return _mm512_set1_epi64((long int)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set(const long int sa)
{ return _mm512_set1_epi64(sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set(const unsigned long int sa)
{ return _mm512_set1_epi64((long int)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_set(const float sa)
{ return _mm512_set1_ps(sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_set(const double sa)
{ return _mm512_set1_pd(sa); }

/*!
 *  Set vector given an array.
 *  Only required for non-contiguous 32-bit elements due to in-between padding,
 *  64-bit elements can use load instructions.
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set(const int * const sa, const int n)
{
    if (n == SIMD_STREAMS_64)
        return _mm512_set_epi64((long int)sa[7], (long int)sa[6], (long int)sa[5], (long int)sa[4], (long int)sa[3], (long int)sa[2], (long int)sa[1], (long int)sa[0]);
    else if (n == SIMD_STREAMS_32)
        return _mm512_load_si512((SIMD_INT *)sa);
    else
        return _mm512_setzero_si512();
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set(const unsigned int * const sa, const int n)
{
    if (n == SIMD_STREAMS_64)
        return _mm512_set_epi64((long int)sa[7], (long int)sa[6], (long int)sa[5], (long int)sa[4], (long int)sa[3], (long int)sa[2], (long int)sa[1], (long int)sa[0]);
    else if (n == SIMD_STREAMS_32)
        return _mm512_load_si512((SIMD_INT *)sa);
    else
        return _mm512_setzero_si512();
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set(const long int * const sa, const int n)
{
    if (n == SIMD_STREAMS_64)
        return _mm512_set_epi64(sa[7], sa[6], sa[5], sa[4], sa[3], sa[2], sa[1], sa[0]);
    else
        return _mm512_setzero_si512();
}

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_set(const unsigned long int * const sa, const int n)
{
    if (n == SIMD_STREAMS_64)
        return _mm512_set_epi64((long int)sa[7], (long int)sa[6], (long int)sa[5], (long int)sa[4], (long int)sa[3], (long int)sa[2], (long int)sa[1], (long int)sa[0]);
    else
        return _mm512_setzero_si512();
}


/***********************
 *  Convert intrinsics
 ***********************/
/*!
 *  Convert packed 32-bit integer elements
 *  to packed single-precision floating-point elements.
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_cvt_i32_f32(const SIMD_INT va)
{ return _mm512_cvtepi32_ps(va); }

/*!
 *  Convert packed 32-bit integer elements
 *  to packed double-precision floating-point elements.
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_cvt_i32_f64(const SIMD_INT va)
{ return _mm512_cvtepi32lo_pd(va); }

/*!
 *  Convert packed unsigned 64-bit integer elements
 *  to packed 32-bit floating-point elements, the high half of the register is set to 0.0.
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_cvt_u64_f32(const SIMD_INT va)
{
/*
    const __m256 fa = _mm512_cvtepu64_ps(va);
    return _mm512_castps256_ps512(fa); // upper half is undefined
*/
/*
    const __m256 fa = _mm512_cvtepu64_ps(va);
    const SIMD_FLT zero = _mm512_setzero_ps();
    return _mm512_mask_mov_ps(fa, 0xFF00U, zero);
*/
    const __m256 va_flt = _mm512_cvtepu64_ps(va);
    return _mm512_mask_xor_ps(va_flt, 0xFF00U, va_flt);
}

/*!
 *  Convert unsigned 64-bit integers to 64-bit floating-point elements.
 */
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_cvt_u64_f64(const SIMD_INT va)
{ return _mm512_cvtepu64_pd(va); }


/********************
 *  Load intrinsics
 ********************/
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_load(const int * const sa)
{ return _mm512_load_si512((SIMD_INT *)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_loadu(const int * const sa)
{ return _mm512_loadu_si512((SIMD_INT *)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_load(const unsigned int * const sa)
{ return _mm512_load_si512((SIMD_INT *)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_loadu(const unsigned int * const sa)
{ return _mm512_loadu_si512((SIMD_INT *)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_load(const long int * const sa)
{ return _mm512_load_si512((SIMD_INT *)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_loadu(const long int * const sa)
{ return _mm512_loadu_si512((SIMD_INT *)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_load(const unsigned long int * const sa)
{ return _mm512_load_si512((SIMD_INT *)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_INT simd_loadu(const unsigned long int * const sa)
{ return _mm512_loadu_si512((SIMD_INT *)sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_load(const float * const sa)
{ return _mm512_load_ps(sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_FLT simd_loadu(const float * const sa)
{ return _mm512_loadu_ps(sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_load(const double * const sa)
{ return _mm512_load_pd(sa); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
SIMD_DBL simd_loadu(const double * const sa)
{ return _mm512_loadu_pd(sa); }


/*******************************
 *  Store intrinsics
 *******************************/
__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_store(int * const sa, const SIMD_INT va)
{ _mm512_store_si512((SIMD_INT *)sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_storeu(int * const sa, const SIMD_INT va)
{ _mm512_storeu_si512((SIMD_INT *)sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_store(unsigned int * const sa, const SIMD_INT va)
{ _mm512_store_si512((SIMD_INT *)sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_storeu(unsigned int * const sa, const SIMD_INT va)
{ _mm512_storeu_si512((SIMD_INT *)sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_store(long int * const sa, const SIMD_INT va)
{ _mm512_store_si512((SIMD_INT *)sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_storeu(long int * const sa, const SIMD_INT va)
{ _mm512_storeu_si512((SIMD_INT *)sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_store(unsigned long int * const sa, const SIMD_INT va)
{ _mm512_store_si512((SIMD_INT *)sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_storeu(unsigned long int * const sa, const SIMD_INT va)
{ _mm512_storeu_si512((SIMD_INT *)sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_store(float * const sa, const SIMD_FLT va)
{ _mm512_store_ps(sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_storeu(float * const sa, const SIMD_FLT va)
{ _mm512_storeu_ps(sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_store(double * const sa, const SIMD_DBL va)
{ _mm512_store_pd(sa, va); }

__SIMD_FUN_ATTR__ __SIMD_FUN_PREFIX__
void simd_storeu(double * const sa, const SIMD_DBL va)
{ _mm512_storeu_pd(sa, va); }


#endif  // _AVX512_H

