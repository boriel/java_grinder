/**
 *  Java Grinder
 *  Author: Michael Kohn
 *   Email: mike@mikekohn.net
 *     Web: http://www.mikekohn.net/
 * License: GPLv3
 *
 * Copyright 2014-2018 by Michael Kohn
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "JavaClass.h"
#include "JavaCompiler.h"
#include "invoke.h"
#include "invoke_virtual.h"
#include "java_lang_string.h"
#include "java_lang_system.h"
#include "draw3d.h"

#define DRAW3D "net/mikekohn/java_grinder/Draw3D"
#define DRAW3D_LEN (sizeof(DRAW3D) - 1)

static void get_virtual_function(char *function, char *method_name, char *method_sig, char *field_name, char *field_class)
{
  char *s;
  int ptr = 0;

  s = field_class;
  while(*s != 0)
  {
    if (*s == '/') { ptr = 0; s++; continue; }
    function[ptr++] = *s | 32;
    s++;
  }

  function[ptr++] = '_';
  s = field_name;
  while (*s != 0) { function[ptr++] = *s; s++; }

  function[ptr++] = '_';
  s = method_name;
  while (*s != 0) { function[ptr++] = *s; s++; }

  function[ptr++] = '_';
  s = method_sig + 1;
  while(*s != 0)
  {
    if (*s == ')') { break; }
    function[ptr++] = *s;
    s++;
  }

  function[ptr] = 0;
}

int invoke_virtual(JavaClass *java_class, int method_id, int field_id, Generator *generator)
{
  char field_name[128];
  char field_type[128];
  char field_class[128];
  char method_name[128];
  char method_sig[128];
  char method_class[128];
  char function[256];

  printf("invoke_virtual() (static)\n");

  if (java_class->get_ref_name_type(field_name, field_type, sizeof(field_name), field_id) != 0 ||
      java_class->get_class_name(field_class, sizeof(field_class), field_id) != 0)
  {
    printf("Error: Could not field info for field_id %d\n", field_id);
    return -1;
  }

  if (java_class->get_class_name(method_class, sizeof(method_class), method_id) != 0 ||
      java_class->get_ref_name_type(method_name, method_sig, sizeof(method_name), method_id) != 0)
  {
    printf("Error: Couldn't get name and type for method_id %d\n", method_id);
    return -1;
  }

  printf("field: '%s as %s' from %s\n", field_name, field_type, field_class);
  printf("method: '%s as %s' from %s\n", method_name, method_sig, method_class);

  get_virtual_function(function, method_name, method_sig, field_name, field_class);

  printf("function: %s()\n", function);

  int ret = -1;
  if (strcmp(field_class, "java/lang/System") == 0)
  {
    ret = java_lang_system(java_class, generator, function);
  }

  get_static_function(function, method_name, method_sig);
  printf("function=%s  %s field_class=%s\n", function, field_name, method_class);

  if (strcmp(method_class, "java/lang/String") == 0)
  {
    ret = java_lang_string(java_class, generator, function, field_name, field_id);
  }

  if (ret == 0) { return 0; }

  printf("--> Function not implemented '%s'\n", function);

  return -1;
}

int invoke_virtual(JavaClass *java_class, int method_id, Generator *generator)
{
  char method_name[128];
  char method_sig[128];
  char method_class[128];
  char function[256];
  bool is_constructor = false;

  printf("invoke_virtual() (pushed)\n");

  if (java_class->get_class_name(method_class, sizeof(method_class), method_id) != 0 ||
      java_class->get_ref_name_type(method_name, method_sig, sizeof(method_name), method_id) != 0)
  {
    printf("Error: Couldn't get name and type for method_id %d\n", method_id);
    return -1;
  }

  printf("method: '%s as %s' from %s\n", method_name, method_sig, method_class);

  if (strcmp(method_name, "<init>") == 0)
  {
    strcpy(method_name, "Constructor");
    is_constructor = true;
  }

  get_static_function(function, method_name, method_sig);

  printf("function: %s()\n", function);

  int ret = -1;

#if 0
  if (strcmp(method_class, "java/lang/System") == 0)
  {
    ret = java_lang_system(java_class, generator, function);
  }
#endif

  //get_static_function(function, method_name, method_sig);
  printf("function=%s  method_class=%s\n", function, method_class);

  if (strcmp(method_class, "java/lang/String") == 0)
  {
    ret = java_lang_string(java_class, generator, function);
  }
  else if (strncmp(method_class, DRAW3D, DRAW3D_LEN) == 0)
  {
    const char *cls = method_class + DRAW3D_LEN + 1;
    int draw3d_type = -1;

    if (strcmp(cls, "Draw3DPoints") == 0) { draw3d_type = 0; }
    else if (strcmp(cls, "Draw3DTriangle") == 0) { draw3d_type = 3; }

    if (is_constructor == true)
    {
      if (draw3d_type != -1)
      {
        if (strcmp(method_sig, "(Ljava/lang/String;)V") == 0)
        {
          ret = generator->draw3d_Constructor_X(draw3d_type);
        }
        else if (strcmp(method_sig, "(I)V") == 0)
        {
          ret = generator->draw3d_Constructor_I(draw3d_type);
        }
      }
    }
      else
    {
      if (strcmp(cls, "Draw3DPoints") == 0 ||
          strcmp(cls, "Draw3DTriangle") == 0)
      {
        ret = draw3d(java_class, generator, function);
      }
    }
  }

  if (ret == 0) { return 0; }

  printf("--> Function not implemented '%s'\n", function);

  return -1;
}

