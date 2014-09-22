/**
 *  Java Grinder
 *  Author: Michael Kohn
 *   Email: mike@mikekohn.net
 *     Web: http://www.mikekohn.net/
 * License: GPL
 *
 * Copyright 2014 by Michael Kohn
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "TI99.h"

TI99::TI99() : need_vdp_command(false)
{
}

TI99::~TI99()
{
  if (need_vdp_command)
  {
    insert_vdp_command();
  }
}

int TI99::open(const char *filename)
{
  if (TMS9900::open(filename) != 0) { return -1; }

  fprintf(out, ".include \"ti99.inc\"\n\n");
  fprintf(out, "ram_start equ RAM\n");
  fprintf(out, "heap_ptr equ ram_start\n");

  return 0;
}

int TI99::start_init()
{
  fprintf(out, "\n");
  fprintf(out, ".org 0x6000\n");

  fprintf(out, "  .db 0xaa, 0x01, 0x01, 0x00\n");
  fprintf(out, "  .dw 0x0000\n");
  fprintf(out, "  .dw _prog\n");
  fprintf(out, "  .dw 0x0000\n");
  fprintf(out, "  .dw 0x0000\n");
  fprintf(out, "  .dw 0x0000\n");
  fprintf(out, "  .dw 0x0000\n");
  fprintf(out, "_prog:\n");
  fprintf(out, "  .dw 0x0000\n");
  fprintf(out, "  .dw main\n");
  fprintf(out, "  .db 4, \"TEST\"\n");

  fprintf(out, ".align 16\n\n");

  // Add any set up items (stack, registers, etc).
  fprintf(out, "start:\n");

  return 0;
}

int TI99::ti99_print()
{
  return -1;
}

int TI99::ti99_printChar()
{
  return -1;
}

int TI99::ti99_printChar(int c)
{
  fprintf(out, "  li r0, 0x%02x\n", c << 8);
  fprintf(out, "  mov r0, @VDP_WRITE\n");

  return 0;
}

int TI99::ti99_setCursor()
{

  return -1;
}

int TI99::ti99_setCursor(int x, int y)
{
  need_vdp_command = true;
  int address = (y * 40) + x + 0x4000;

  fprintf(out, "  li r0, 0x%04x   ; set write byte to 0\n", address);
  fprintf(out, "  bl @_vdp_command\n");

  return 0;
}

void TI99::insert_write_string()
{
  fprintf(out, "_write_string:\n");
  fprintf(out, "  movb *r2+, r0\n");
  fprintf(out, "  jeq _write_string_exit\n");
  fprintf(out, "  mov r0, @VDP_WRITE\n");
  fprintf(out, "  jmp write_string\n");
  fprintf(out, "_write_string_exit:\n");
  fprintf(out, "  b *r11\n\n");
}

void TI99::insert_vdp_command()
{
  fprintf(out, "_vdp_command:\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  swpb r0\n");
  fprintf(out, "  movb r0, @VDP_COMMAND\n");
  fprintf(out, "  b *r11\n\n");
}


