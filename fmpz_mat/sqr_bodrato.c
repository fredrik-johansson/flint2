/*
    Copyright (C) 2012 Fredrik Johansson
    Copyright (C) 2015 Anubhav Srivastava

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "fmpz_mat.h"

#define E fmpz_mat_entry

void
fmpz_mat_sqr_bodrato(fmpz_mat_t B, const fmpz_mat_t A)
{
    slong n = A->r;
    
    if (n == 0)
    {
        return;
    }
    else if (n == 1)
    {
        fmpz_mul(E(B, 0, 0), E(A, 0, 0), E(A, 0, 0));
    }
    else if (n == 2)
    {
        fmpz_add(E(B, 0, 0), E(A, 0, 0), E(A, 1, 1));

        fmpz_mul(E(B, 0, 1), E(A, 0, 1), E(B, 0, 0));
        fmpz_mul(E(B, 1, 0), E(A, 1, 0), E(B, 0, 0));

        fmpz_mul(E(B, 0, 0), E(A, 0, 0), E(A, 0, 0));
        fmpz_mul(E(B, 1, 1), E(A, 0, 1), E(A, 1, 0));
        fmpz_add(E(B, 0, 0), E(B, 0, 0), E(B, 1, 1));

        fmpz_addmul(E(B, 1, 1), E(A, 1, 1), E(A, 1, 1));
    }
    else if (n == 3)
    {
        fmpz_t temp23;
        
        fmpz_init(temp23);
       
        fmpz_mul(E(B, 2, 2), E(A, 0, 2), E(A, 2, 0));
        fmpz_mul(E(B, 1, 1), E(A, 0, 1), E(A, 1, 0));
        fmpz_mul(temp23, E(A, 1, 2), E(A, 2, 1));

        fmpz_add(E(B, 0, 0), E(B, 2, 2), E(B, 1, 1));
        fmpz_addmul(E(B, 0, 0), E(A, 0, 0), E(A, 0, 0));
       
        fmpz_add(E(B, 1, 1), E(B, 1, 1), temp23);
        fmpz_addmul(E(B, 1, 1), E(A, 1, 1), E(A, 1, 1));
        
        fmpz_add(E(B, 2, 2), E(B, 2, 2), temp23);
        fmpz_addmul(E(B, 2, 2), E(A, 2, 2), E(A, 2, 2));
      
        
        fmpz_add(E(B, 1, 2), E(A, 0, 0), E(A, 1, 1));
        fmpz_add(E(B, 2, 1), E(A, 0, 0), E(A, 2, 2));
        fmpz_add(temp23, E(A, 1, 1), E(A, 2, 2));
        
        fmpz_mul(E(B, 0, 1), E(B, 1, 2), E(A, 0, 1));
        fmpz_addmul(E(B, 0, 1), E(A, 0, 2), E(A, 2, 1));

        fmpz_mul(E(B, 0, 2), E(B, 2, 1), E(A, 0, 2));
        fmpz_addmul(E(B, 0, 2), E(A, 0, 1), E(A, 1, 2));     
 
        fmpz_mul(E(B, 1, 0), E(B, 1, 2), E(A, 1, 0));
        fmpz_addmul(E(B, 1, 0), E(A, 2, 0), E(A, 1, 2));

        fmpz_mul(E(B, 1, 2), temp23, E(A, 1, 2));
        fmpz_addmul(E(B, 1, 2), E(A, 1, 0), E(A, 0, 2));
 
        fmpz_mul(E(B, 2, 0), E(B, 2, 1), E(A, 2, 0));
        fmpz_addmul(E(B, 2, 0), E(A, 2, 1), E(A, 1, 0));
 
        fmpz_mul(E(B, 2, 1), temp23, E(A, 2, 1));
        fmpz_addmul(E(B, 2, 1), E(A, 0, 1), E(A, 2, 0));

        fmpz_clear(temp23);
    }
    else
    {

        slong i,j;

        fmpz_mat_t window11, window12, window21, window22;
        fmpz_mat_t s1, s2, s3;
        fmpz_mat_t p1, p2, p3, p5, p6;

        slong m, x, isodd; 

        isodd = n % 2;
        m = n - isodd;

        fmpz_mat_init(s1, m/2, m/2);
        fmpz_mat_init(s2, m/2, m/2);
        fmpz_mat_init(s3, m/2, m/2);
        fmpz_mat_init(p1, m/2, m/2);
        fmpz_mat_init(p2, m/2, m/2);
        fmpz_mat_init(p3, m/2, m/2);
        fmpz_mat_init(p5, m/2, m/2);
        fmpz_mat_init(p6, m/2, m/2);

        fmpz_mat_window_init(window11, A, 0, 0, m/2, m/2);
        fmpz_mat_window_init(window12, A, 0, m/2, m/2, m);
        fmpz_mat_window_init(window21, A, m/2, 0, m, m/2);
        fmpz_mat_window_init(window22, A, m/2, m/2, m, m);

        fmpz_mat_add(s1, window22, window12);
        fmpz_mat_sqr(p1, s1);

        fmpz_mat_sub(s2, window22, window21);
        fmpz_mat_sqr(p2, s2);

        fmpz_mat_add(s3, s2, window12);
        fmpz_mat_sqr(p3, s3);    

        fmpz_mat_sub(s1, s3, window11);
        fmpz_mat_mul(p6, s1, window12);
        fmpz_mat_mul(s3, window21, s1);

        fmpz_mat_mul(p5, window12, window21);
        fmpz_mat_add(s1, p3, p5);
        fmpz_mat_sub(s2, p1, s1);

        if (isodd == 0)
        {
            i = m/2 - 1;
            do {
                j = m/2 - 1;
                do {
                    fmpz_sub(E(B, i + m/2, j), E(s2, i, j), E(s3, i, j));
                } while (--j >= 0);
            } while (--i >= 0);

            fmpz_mat_sub(s3, s1, p2);
            fmpz_mat_sqr(s1, window11);

            i = m/2 - 1;
            do {
                j = m/2 - 1;
                do {
                    fmpz_add(E(B, i, j), E(s1, i, j), E(p5, i, j));
                    fmpz_add(E(B, i + m/2, j + m/2), E(p2, i, j), E(s2, i, j));
                    fmpz_sub(E(B, i, j + m/2), E(s3, i, j), E(p6, i, j) );
                } while (--j >= 0);
            } while (--i >= 0);
        }
        else
        {
            i = m;
            do {
                fmpz_mul(E(B, n - 1, i), E(A, n - 1, 0), E(A, 0, i));
                fmpz_mul(E(B, i, n - 1), E(A, 0, n - 1), E(A, i, 0));
                x = m;
                do {
                    fmpz_addmul(E(B, n - 1, i), E(A, n - 1, x), E(A, x, i));
                    fmpz_addmul(E(B, i, n - 1), E(A, x, n - 1), E(A, i, x));
                } while (--x > 0);
            } while (--i >= 0);

            i = m/2;
            do {
                j = m/2 - 1;
                do {
                    fmpz_sub(E(B, i, j), E(s2, i - m/2, j), E(s3, i - m/2, j)); 
                    fmpz_addmul(E(B, i, j), E(A, i, n - 1), E(A, n - 1, j));
                } while (--j >= 0);
            } while (++i < m);

            fmpz_mat_sub(s3, s1, p2);
            fmpz_mat_sqr(s1, window11);

            i = m/2 - 1;
            do {
                j = m/2 - 1;
                do {
                    fmpz_add(E(B, i, j), E(s1, i, j), E(p5, i, j)); 
                    fmpz_addmul(E(B, i, j), E(A, i, n - 1), E(A, n - 1, j));
                    fmpz_add(E(B, i + m/2, j + m/2), E(p2, i, j), E(s2, i, j));
                    fmpz_addmul(E(B, i + m/2, j + m/2), E(A, i + m/2, n - 1), E(A, n - 1, j + m/2));
                    fmpz_sub(E(B, i, j + m/2), E(s3, i, j), E(p6, i, j));
                    fmpz_addmul(E(B, i, j + m/2), E(A, i, n - 1), E(A, n - 1, j + m/2));
                } while (--j >= 0);
            } while (--i >= 0);
        }

        fmpz_mat_window_clear(window11);
        fmpz_mat_window_clear(window12);
        fmpz_mat_window_clear(window21);
        fmpz_mat_window_clear(window22);
        fmpz_mat_clear(s1);
        fmpz_mat_clear(s2);
        fmpz_mat_clear(s3);
        fmpz_mat_clear(p1);
        fmpz_mat_clear(p2);
        fmpz_mat_clear(p3);
        fmpz_mat_clear(p5);
        fmpz_mat_clear(p6);
    }
}
