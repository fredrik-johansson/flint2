/*
    Copyright (C) 2010 Fredrik Johansson

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/
#ifdef T

#include "templates.h"

#include <stdio.h>
#include <stdlib.h>
#include "ulong_extras.h"

int
main(void)
{
    slong rep, r, c;
    TEMPLATE(T, ctx_t) ctx;
    TEMPLATE(T, sparse_mat_t) A, B, C, D;
    FLINT_TEST_INIT(state);

    flint_printf("add/sub....");
    fflush(stdout);

    for (rep = 0; rep < 1000; rep++)
    {
        TEMPLATE(T, ctx_randtest) (ctx, state);
        r = n_randint(state, 200);
        c = n_randint(state, 200);

        TEMPLATE(T, sparse_mat_init) (A, r, c, ctx);
        TEMPLATE(T, sparse_mat_init) (B, r, c, ctx);
        TEMPLATE(T, sparse_mat_init) (C, r, c, ctx);
        TEMPLATE(T, sparse_mat_init) (D, r, c, ctx);

        TEMPLATE(T, sparse_mat_randtest) (A, state, 0, c, ctx);
        TEMPLATE(T, sparse_mat_randtest) (B, state, 0, c, ctx);

        TEMPLATE(T, sparse_mat_add) (C, A, B, ctx);
        TEMPLATE(T, sparse_mat_sub) (D, C, B, ctx);

        if (!TEMPLATE(T, sparse_mat_equal) (D, A, ctx))
        {
            flint_printf("FAIL\n");
            abort();
        }

        TEMPLATE(T, sparse_mat_clear) (A, ctx);
        TEMPLATE(T, sparse_mat_clear) (B, ctx);
        TEMPLATE(T, sparse_mat_clear) (C, ctx);
        TEMPLATE(T, sparse_mat_clear) (D, ctx);
        TEMPLATE(T, ctx_clear) (ctx);
    }

    FLINT_TEST_CLEANUP(state);
    
    flint_printf("PASS\n");
    return 0;
}

#endif
