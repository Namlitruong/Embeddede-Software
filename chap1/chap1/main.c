#include <libepc.h>

int main(int argc, char *argv[])
{
   ClearScreen(0x07);
   SetCursorPosition(0, 0);
   
   PutString("Date: 04/1/2019 -- Nam Truong -- namtr042\r\n");
   
   return 0;
}
