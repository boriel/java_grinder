import net.mikekohn.java_grinder.AppleIIgs;
import net.mikekohn.java_grinder.Memory;
import net.mikekohn.java_grinder.CPU;

public class AppleIIgsJavaDemo
{
  public static void rect(int x1, int y1, int x2, int y2, int color)
  {
    int x, y, address;

    for(x = x1; x <= x2; x++)
    {
      address = 0x2000 + x + 160 * y1;
      AppleIIgs.hiresPlot(address, color);
      address = 0x2000 + x + 160 * y2;
      AppleIIgs.hiresPlot(address, color);
    }

    for(y = y1; y <= y2; y++)
    {
      address = 0x2000 + x1 + 160 * y;
      AppleIIgs.hiresPlot(address, color);
      address = 0x2000 + x2 + 160 * y;
      AppleIIgs.hiresPlot(address, color);
    }
  }

  public static void rectfill(int x1, int y1, int x2, int y2, int color)
  {
    int x, y, address;

    for(y = y1; y <= y2; y++)
    {
      for(x = x1; x <= x2; x++)
      {
        address = 0x2000 + x + 160 * y;
        AppleIIgs.hiresPlot(address, color);
      }
    }
  }

  public static void main()
  {
    int recen = -8;
    int imcen = 0;
    int re, im, re2, im2, rec, imc;
    int address, address2;
    int x, y, i;

    AppleIIgs.hiresEnable();

    // make palette (api method coming soon when arrays are working)
    CPU.asm("lda #0xfff\n");
    CPU.asm("sta.l 0xe19e00\n");
    CPU.asm("lda #0xeee\n");
    CPU.asm("sta.l 0xe19e02\n");
    CPU.asm("lda #0xddd\n");
    CPU.asm("sta.l 0xe19e04\n");
    CPU.asm("lda #0xccc\n");
    CPU.asm("sta.l 0xe19e06\n");
    CPU.asm("lda #0xbbb\n");
    CPU.asm("sta.l 0xe19e08\n");
    CPU.asm("lda #0xaaa\n");
    CPU.asm("sta.l 0xe19e0a\n");
    CPU.asm("lda #0x999\n");
    CPU.asm("sta.l 0xe19e0c\n");
    CPU.asm("lda #0x888\n");
    CPU.asm("sta.l 0xe19e0e\n");
    CPU.asm("lda #0x777\n");
    CPU.asm("sta.l 0xe19e10\n");
    CPU.asm("lda #0x666\n");
    CPU.asm("sta.l 0xe19e12\n");
    CPU.asm("lda #0x555\n");
    CPU.asm("sta.l 0xe19e14\n");
    CPU.asm("lda #0x444\n");
    CPU.asm("sta.l 0xe19e16\n");
    CPU.asm("lda #0x333\n");
    CPU.asm("sta.l 0xe19e18\n");
    CPU.asm("lda #0x222\n");
    CPU.asm("sta.l 0xe19e1a\n");
    CPU.asm("lda #0x111\n");
    CPU.asm("sta.l 0xe19e1c\n");
    CPU.asm("lda #0x000\n");
    CPU.asm("sta.l 0xe19e1e\n");

    for(address = 0x2000; address < 0x9d00; address++) 
      AppleIIgs.hiresPlot(address, 255);

    address = 0x2000;
    address2 = 0x9c60;
    int yy = 0;

    for(y = 0; y < 100 * 16; y += 16, yy++, address2 -= 320)
    {
      imc = (y - 100 * 16) >> 5;
      imc += imcen;

      int xx = 0;

      for(x = 0; x < 160 * 16; x += 16, xx++, address++, address2++)
      {
        boolean skip = false;

        if((xx < 50 || xx > 110 || yy < 50 || yy > 145) ||
           (xx > 78 && xx < 93 && yy > 85 && yy < 115))
        {
          continue;
        }

        rec = (x - 80 * 16) >> 4;
        rec += recen;

        re = rec;
        im = imc;

        re2 = (re * re) >> 4;
        im2 = (im * im) >> 4;

        for(i = 0; i < 15; i++)
        {
          if((re2 + im2) > 4 * 16)
            break;

          im = (re * im) >> 3;
          im += imc;

          re = (re2 - im2) + rec;

          re2 = (re * re) >> 4;
          im2 = (im * im) >> 4;
        }

        AppleIIgs.hiresPlot(address, (i | (i << 4)));
        AppleIIgs.hiresPlot(address2, (i | (i << 4)));
      }
    }

    int x1 = 49;
    int x2 = 111;
    int y1 = 49;
    int y2 = 146;

    for(i = 0; i < 16; i++)
    {
      rect(x1, y1, x2, y2, 0);
      x1--;
      x2++;
      y1--;
      y2++;
    }

    for(i = 0; i < 16; i++)
    {
      rect(x1, y1, x2, y2, i | (i << 4));
      x1--;
      x2++;
      y1--;
      y2++;
    }

    while(true)
    {
    }
  }
}
