/**
 * librouteros - src/ros_parse.c
 * Copyright (C) 2009  Florian octo Forster
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; only version 2 of the License is applicable.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * Authors:
 *   Florian octo Forster <octo at verplant.org>
 **/

#ifndef _ISOC99_SOURCE
# define _ISOC99_SOURCE
#endif

#ifndef _POSIX_C_SOURCE
# define _POSIX_C_SOURCE 200112L
#endif

#include "config.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <errno.h>
#include <assert.h>

#include "routeros_api.h"

_Bool sstrtob (const char *str) /* {{{ */
{
	if (str == NULL)
		return (false);

	if (strcasecmp ("true", str) == 0)
		return (true);
	return (false);
} /* }}} _Bool sstrtob */

unsigned int sstrtoui (const char *str) /* {{{ */
{
	unsigned int ret;
	char *endptr;

	if (str == NULL)
		return (0);

	errno = 0;
	endptr = NULL;
	ret = (unsigned int) strtoul (str, &endptr, /* base = */ 10);
	if ((endptr == str) || (errno != 0))
		return (0);

	return (ret);
} /* }}} unsigned int sstrtoui */

double sstrtod (const char *str) /* {{{ */
{
	double ret;
	char *endptr;

	if (str == NULL)
		return (NAN);

	errno = 0;
	endptr = NULL;
	ret = strtod (str, &endptr);
	if ((endptr == str) || (errno != 0))
		return (NAN);

	return (ret);
} /* }}} double sstrtod */

int sstrto_rx_tx_counters (const char *str, /* {{{ */
		uint64_t *rx, uint64_t *tx)
{
	const char *ptr;
	char *endptr;

	if ((rx == NULL) || (tx == NULL))
		return (EINVAL);

	*rx = 0;
	*tx = 0;

	if (str == NULL)
		return (EINVAL);

	ptr = str;
	errno = 0;
	endptr = NULL;
	*rx = (uint64_t) strtoull (ptr, &endptr, /* base = */ 10);
	if ((endptr == str) || (errno != 0))
	{
		*rx = 0;
		return (EIO);
	}

	assert (endptr != NULL);
	if ((*endptr != '/') && (*endptr != ','))
		return (EIO);

	ptr = endptr + 1;
	errno = 0;
	endptr = NULL;
	*tx = (uint64_t) strtoull (ptr, &endptr, /* base = */ 10);
	if ((endptr == str) || (errno != 0))
	{
		*rx = 0;
		*tx = 0;
		return (EIO);
	}

	return (0);
} /* }}} int sstrto_rx_tx_counters */

/* vim: set ts=2 sw=2 noet fdm=marker : */