
/*
 * Copyright 2012 Yichun "agentzh" Zhang
 * Copyright 2007-2009 Russ Cox.  All Rights Reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */


#ifndef _SRE_REGEX_PARSER_H_INCLUDED_
#define _SRE_REGEX_PARSER_H_INCLUDED_


#include <sre_regex.h>


sre_regex_t *sre_regex_parse(sre_pool_t *pool, u_char *src, unsigned *ncaps);


#endif /* _SRE_REGEX_PARSER_H_INCLUDED_ */
