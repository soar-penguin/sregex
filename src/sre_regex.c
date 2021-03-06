
/*
 * Copyright 2012 Yichun "agentzh" Zhang
 * Copyright 2007-2009 Russ Cox.  All Rights Reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */


#include <sre_regex.h>


sre_regex_t *
sre_regex_create(sre_pool_t *pool, sre_regex_type_t type, sre_regex_t *left,
    sre_regex_t *right)
{
    sre_regex_t   *r;

    r = sre_pcalloc(pool, sizeof(sre_regex_t));
    if (r == NULL) {
        return NULL;
    }

    r->type = type;
    r->left = left;
    r->right = right;

    return r;
}


void
sre_regex_dump(sre_regex_t *r)
{
    sre_regex_range_t       *range;

    switch (r->type) {
    case SRE_REGEX_TYPE_ALT:
        printf("Alt(");
        sre_regex_dump(r->left);
        printf(", ");
        sre_regex_dump(r->right);
        printf(")");
        break;

    case SRE_REGEX_TYPE_CAT:
        printf("Cat(");
        sre_regex_dump(r->left);
        printf(", ");
        sre_regex_dump(r->right);
        printf(")");
        break;

    case SRE_REGEX_TYPE_LIT:
        printf("Lit(%d)", (int) r->ch);
        break;

    case SRE_REGEX_TYPE_DOT:
        printf("Dot");
        break;

    case SRE_REGEX_TYPE_PAREN:
        printf("Paren(%d, ", r->group);
        sre_regex_dump(r->left);
        printf(")");
        break;

    case SRE_REGEX_TYPE_STAR:
        if (!r->greedy) {
            printf("Ng");
        }

        printf("Star(");
        sre_regex_dump(r->left);
        printf(")");
        break;

    case SRE_REGEX_TYPE_PLUS:
        if (!r->greedy) {
            printf("Ng");
        }

        printf("Plus(");
        sre_regex_dump(r->left);
        printf(")");
        break;

    case SRE_REGEX_TYPE_QUEST:
        if (!r->greedy) {
            printf("Ng");
        }

        printf("Quest(");
        sre_regex_dump(r->left);
        printf(")");
        break;

    case SRE_REGEX_TYPE_NIL:
        printf("Nil");
        break;

    case SRE_REGEX_TYPE_CLASS:
        printf("CLASS(");

        for (range = r->range; range; range = range->next) {
            printf("[%d, %d]", range->from, range->to);
        }

        printf(")");
        break;

    case SRE_REGEX_TYPE_NCLASS:
        printf("NCLASS(");

        for (range = r->range; range; range = range->next) {
            printf("[%d, %d]", range->from, range->to);
        }

        printf(")");
        break;

    case SRE_REGEX_TYPE_ASSERT:
        printf("ASSERT(");
        switch (r->assertion_type) {
            case SRE_REGEX_ASSERTION_BIG_A:
                printf("\\A");
                break;

            case SRE_REGEX_ASSERTION_CARET:
                printf("^");
                break;

            case SRE_REGEX_ASSERTION_DOLLAR:
                printf("$");
                break;

            case SRE_REGEX_ASSERTION_SMALL_Z:
                printf("\\z");
                break;

            case SRE_REGEX_ASSERTION_BIG_B:
                printf("\\B");
                break;

            case SRE_REGEX_ASSERTION_SMALL_B:
                printf("\\b");
                break;

            default:
                printf("???");
                break;
        }
        printf(")");
        break;

    default:
        printf("???");
        break;
    }
}


void
sre_regex_error(char *fmt, ...)
{
    va_list     arg;

    va_start(arg, fmt);

    fprintf(stderr, "[error] ");
    vfprintf(stderr, fmt, arg);
    fprintf(stderr, "\n");

    va_end(arg);
}

