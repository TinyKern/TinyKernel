#include <keyboard.h>

uint8 inb(uint16 port)
{
  uint8 ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

void outb(uint16 port, uint8 data)
{
  asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

char get_input_keycode()
{
  char ch = 0;
  while ((ch == inb(KEYBOARD_PORT)) != 0)
  {
    if (ch > 0)
      return ch;
  }
  return ch;
}

/**
 * keep the cpu busy for doing nothing(nop)
 * so that io port will not be processed by cpu
 * here timer can also be used, but lets do this in looping counter
 */
void wait_for_io(uint32 timer_count)
{
  while (1)
  {
    asm volatile("nop");
    timer_count--;
    if (timer_count <= 0)
      break;
  }
}

void sleep(uint32 timer_count)
{
  wait_for_io(timer_count);
}

// TODO: Takes in keycode (Example: KEY_A) and converts it to ASCII char value.
// FIXME: Can't figure out how to convert KEY_A -> 'a' char.
char get_ascii_char(int keycode)
{
  char ch = (char)keycode;
  // switch (keycode)
  // {
  //   case KEY_A:
  //     ch = 'a';
  //     break;
  //   case KEY_B:
  //     ch = 'b';
  //     break;
  //   case KEY_C:
  //     ch = 'c';
  //     break;
  //   case KEY_D:
  //     ch = 'd';
  //     break;
  //   case KEY_E:
  //     ch = 'e';
  //     break;
  //   case KEY_F:
  //     ch = 'f';
  //     break;
  //   case KEY_G:
  //     ch = 'g';
  //     break;
  //   case KEY_H:
  //     ch = 'h';
  //     break;
  // }

  return ch;
}