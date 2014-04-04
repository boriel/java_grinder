/**
 *  Java Grinder
 *  Author: Michael Kohn
 *   Email: mike@mikekohn.net
 *     Web: http://www.naken.cc/
 * License: GPL
 *
 * Copyright 2014 by Michael Kohn
 *
 */

package net.mikekohn.java_grinder;

// http://wikiti.brandonw.net/index.php?title=84PCSE:OS:Applications

abstract public class TI84C
{
  protected TI84C()
  {
  }

  public static void centerPutS(String text) { }
  public static void dispHL() { }
  public static void clearRect(int x0, int x1, int y0, int y1) { }
  public static void fillRect(int x0, int x1, int y0, int y1) { }
  public static void iLine(int x0, int y0, int x1, int y1, int operation) { }
  public static void iPoint(int x, int y, int operation) { }
  public static void putS(String text) { }
  public static void setPenBGWhite() { }

  public static final int OPERATION_ERASE_PIXEL = 0;
  public static final int OPERATION_DRAW_PIXEL = 1;
  public static final int OPERATION_INVERT_PIXEL = 2;
  public static final int OPERATION_TEST_PIXEL = 3;
  public static final int OPERATION_RESTORE_PIXEL = 4;
}

