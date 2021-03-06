/**
 *  Java Grinder
 *  Author: Michael Kohn
 *   Email: mike@mikekohn.net
 *     Web: http://www.mikekohn.net/
 * License: GPL
 *
 * Copyright 2014-2015 by Michael Kohn
 *
 */

#ifndef _INVOKE_H
#define _INVOKE_H

#include "Generator.h"
#include "JavaClass.h"

void get_signature(char *signature, int *params, int *is_void);
void get_static_function(char *function, char *method_name, char *method_sig);

#endif

