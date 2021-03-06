
/*
 * Copyright 2012 Yichun "agentzh" Zhang
 * Copyright 2007-2009 Russ Cox.  All Rights Reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */


#ifndef DDEBUG
#define DDEBUG 0
#endif
#include <ddebug.h>


#include <sre_capture.h>


sre_capture_t *
sre_capture_create(sre_pool_t *pool, unsigned ovecsize, unsigned clear)
{
    u_char              *p;
    sre_capture_t       *cap;

    p = sre_pnalloc(pool, sizeof(sre_capture_t) + ovecsize);
    if (p == NULL) {
        return NULL;
    }

    cap = (sre_capture_t *) p;

    cap->ovecsize = ovecsize;
    cap->ref = 1;
    cap->next = NULL;

    p += sizeof(sre_capture_t);
    cap->vector = (int *) p;

    if (clear) {
        (void) memset(cap->vector, -1, ovecsize);
    }

    return cap;
}


sre_capture_t *
sre_capture_update(sre_pool_t *pool, sre_capture_t *cap, unsigned group,
    int pos, sre_capture_t **freecap)
{
    sre_capture_t       *newcap;

    dd("update cap %u to %d", group, pos);

    if (cap->ref > 1) {
        if (*freecap) {
            dd("reusing cap %p", *freecap);
            newcap = *freecap;
            *freecap = newcap->next;
            newcap->next = NULL;
            newcap->ref = 1;

        } else {
            newcap = sre_capture_create(pool, cap->ovecsize, 0);
            if (newcap == NULL) {
                return NULL;
            }
        }

        memcpy(newcap->vector, cap->vector, cap->ovecsize);

        cap->ref--;

        dd("!! cap %p: set group %u to %d", newcap, group, pos);
        newcap->vector[group] = pos;
        return newcap;
    }

    dd("!! cap %p: set group %u to %d", cap, group, pos);
    cap->vector[group] = pos;
    return cap;
}


void
sre_capture_dump(sre_capture_t *cap)
{
    unsigned            i, n;

    n = cap->ovecsize / sizeof(int);

    for (i = 0; i < n; i += 2) {
        fprintf(stderr, " (%d, %d)", cap->vector[i], cap->vector[i + 1]);
    }
}

