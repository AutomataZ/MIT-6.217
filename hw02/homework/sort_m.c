/**
 * Copyright (c) 2012 MIT License by 6.172 Staff
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 **/


#include "./util.h"

#define INSERTION_THRESHOLD 64

void isort(data_t* begin, data_t* end);

// Function prototypes
static inline void merge_m(data_t* A, int p, int q, int r);
static inline void copy_m(data_t* source, data_t* dest, int n);

void sort_m(data_t* A, int p, int r) {
  assert(A);

  if (p >= r) {
    return;
  }

  int n = r + 1 - p;
  if (n <= INSERTION_THRESHOLD) {
    isort(A + p, A + r);
    return;
  }
  
  int q = (p + r) / 2;
  sort_m(A, p, q);
  sort_m(A, q + 1, r);
  merge_m(A, p, q, r);
}

static inline void merge_m(data_t* A, int p, int q, int r) {
  assert(A);
  assert(p <= q);
  assert((q + 1) <= r);

  int nleft = q - p + 1;

  data_t* left = NULL;
  mem_alloc(&left, nleft);
  if (left == NULL) {
    return;
  }

  copy_m(A + p, left, nleft);

  data_t* lptr = left;
  data_t* lend = left + nleft;
  data_t* rptr = A + q + 1;
  data_t* rend = A + r + 1;
  data_t* out = A + p;

  while (lptr != lend && rptr != rend) {
    if (*lptr < *rptr) {
      *out = *lptr;
      lptr++;
    }
    else {
      *out = *rptr;
      rptr++;
    }
    out++;
  }
  // 右边先用完要把左边写回
  while(lptr != lend) {
    *out = *lptr;
    out++;
    lptr++;
  }

  mem_free(&left);
}

static inline void copy_m(data_t* source, data_t* dest, int n) {
  assert(dest);
  assert(source);

  for (int remaining = n; remaining > 0; remaining--) {
    *dest = *source;
    dest++;
    source++;
  }
}