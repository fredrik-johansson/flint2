/*
    Copyright (C) 2013 Mike Hansen

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#ifndef FQ_NMOD_SPARSE_MAT_H
#define FQ_NMOD_SPARSE_MAT_H

#ifdef FQ_NMOD_SPARSE_MAT_INLINES_C
#define FQ_SPARSE_MAT_TEMPLATES_INLINE FLINT_DLL
#define FQ_NMOD_SPARSE_MAT_INLINE FLINT_DLL
#else
#define FQ_SPARSE_MAT_TEMPLATES_INLINE static __inline__
#define FQ_NMOD_SPARSE_MAT_INLINE static __inline__
#endif


#include "fq_nmod.h"
#include "fq_nmod_vec.h"
#include "fq_nmod_sparse_vec.h"
#include "fq_nmod_mat.h"

#define T fq_nmod
#define CAP_T FQ_NMOD
#include "fq_sparse_mat_templates.h"
#undef CAP_T
#undef T

#endif
