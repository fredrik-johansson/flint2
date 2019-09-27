/*
    Copyright (C) 2017 Luca De Feo

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#ifndef FQ_EMBED_H
#define FQ_EMBED_H

#ifdef FQ_EMBED_INLINES_C
#define FQ_EMBED_INLINE FLINT_DLL
#define FQ_EMBED_TEMPLATES_INLINE FLINT_DLL
#else
#define FQ_EMBED_INLINE static __inline__
#define FQ_EMBED_TEMPLATES_INLINE static __inline__
#endif

#include "fq.h"
#include "fmpz_mod_mat.h"

#define T fq
#define B fmpz_mod
#include "fq_embed_templates.h"
#undef B
#undef T

#endif
