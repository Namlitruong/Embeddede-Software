#include <libepc.h>

unsigned long int Carry (unsigned long int Cur, unsigned long int Pre){
  return ((Cur < Pre) ? 1 : 0);
}

void llmultiply(unsigned long long int l1,
                unsigned long long int l2,
                unsigned char *result);

void llmultiplyC(unsigned long long int l1,
                unsigned long long int l2,
                unsigned char *result){

    unsigned long long int AL = (unsigned long long int) *(unsigned long int *)&l1;
    unsigned long long int AH = (unsigned long long int) *((unsigned long int *)&l1 + 1);
    unsigned long long int BL = (unsigned long long int) *(unsigned long int *)&l2;
    unsigned long long int BH = (unsigned long long int) *((unsigned long int *)&l2 + 1);

    unsigned long long int Mul;
    unsigned long int * mulP = (unsigned long int *)&Mul;
    unsigned long int* ML = mulP;
    unsigned long int* MH = (mulP + 1);

    unsigned long int* resultP = (unsigned long int *)result;
    unsigned long int* RLL = resultP;
    unsigned long int* RLH = (resultP+1);
    unsigned long int* RHL = (resultP+2);
    unsigned long int* RHH = (resultP+3);
    unsigned long int tempMem, tempMem1;

    *RLL = 0;
    *RLH = 0;
    *RHL = 0;
    *RHH = 0;
    // AL * BL
    Mul = AL * BL;
    *RLL += *ML;
    *RLH += *MH;

    // AL * BH
    Mul = AL * BH;
    tempMem = *RLH;
    *RLH += *ML;
    *RHL += *MH + Carry (*RLH, tempMem);

    // AH * BL
    Mul = AH * BL;
    tempMem = *RLH;
    *RLH += *ML;
    tempMem1 = *RHL;
    *RHL += *MH + Carry (*RLH, tempMem);
    *RHH += Carry (*RHL, tempMem1);

    // AH * BH
    Mul = AH * BH;
    tempMem = *RHL;
    *RHL += *ML;
    *RHH += *MH + Carry (*RHL, tempMem);
}

struct test_case {
  unsigned long long int a;
  unsigned long long int b;
  unsigned long long int rh;
  unsigned long long int rl;
};

struct test_case cases[6] = {

  { 0x0000111122223333ULL, 0x0000555566667777ULL,
    0x0000000005B061D9ULL, 0x58BF0ECA7C0481B5ULL },

  { 0x3456FEDCAAAA1000ULL, 0xEDBA00112233FF01ULL,
    0x309A912AF7188C57ULL, 0xE62072DD409A1000ULL },

  { 0xFFFFEEEEDDDDCCCCULL, 0xBBBBAAAA99998888ULL,
    0xBBBB9E2692C5DDDCULL, 0xC28F7531048D2C60ULL },

  { 0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL,
    0xFFFFFFFFFFFFFFFEULL, 0x0000000000000001ULL },

  { 0x00000001FFFFFFFFULL, 0x00000001FFFFFFFFULL,
    0x0000000000000003ULL, 0xFFFFFFFC00000001ULL },

  { 0xFFFEFFFFFFFFFFFFULL, 0xFFFF0001FFFFFFFFULL,
    0xFFFE0002FFFDFFFEULL, 0x0001FFFE00000001ULL }
};

void PutUnsignedLongLong(unsigned long long int* ulli)
{
  unsigned long int* uli = (unsigned long long int*)ulli;
  PutUnsigned(uli[1], 16, 8);
  PutUnsigned(uli[0], 16, 8);
}

void Program (){
  unsigned char result[16];
  int i;

  ClearScreen(0x07);
  SetCursorPosition(0, 0);

  for (i = 0; i < 6; ++i)
  {
    PutString("Test : ");
    PutUnsignedLongLong(&cases[i].a);
    PutString(" * ");
    PutUnsignedLongLong(&cases[i].b);
    PutString("\r\n");

    PutString("    == ");
    PutUnsignedLongLong(&cases[i].rh);
    PutUnsignedLongLong(&cases[i].rl);
    PutString("\r\n");

    //llmultiplyC(cases[i].a, cases[i].b, result);
    llmultiply(cases[i].a, cases[i].b, result);

    PutString("Result ");
    PutUnsignedLongLong(&result[8]);
    PutUnsignedLongLong(&result[0]);
    PutString("\r\n");

    PutString("\r\n");
  }
}

void Performance (){
  QWORD64 initialCount = 0;
  QWORD64 finalCount = 0;
  QWORD64 Assembly = 0;
  QWORD64 Cprogramming = 0;
  unsigned char result[16];

  initialCount = CPU_Clock_Cycles();

  for (int i = 0; i < 6; i++){
    llmultiply(cases[i].a, cases[i].b, result);;
  }

  finalCount = CPU_Clock_Cycles();
  Assembly = finalCount - initialCount;

  initialCount = CPU_Clock_Cycles();

  for (int i = 0; i < 6; i++){
    llmultiplyC(cases[i].a, cases[i].b, result);;
  }

  finalCount = CPU_Clock_Cycles();
  Cprogramming = finalCount - initialCount;

  SetCursorPosition(1, 1);
  PutString("Assembly: ");
  PutUnsigned(Assembly, 10, 8);
  PutString("\r\n");

  SetCursorPosition(2, 1);
  PutString("Cprogramming: ");
  PutUnsigned(Cprogramming, 10, 8);
  PutString("\r\n");

  PutString("\r\n");

  return 0;
}

int main(int argc, char *argv[])
{
  //Program ();
 Performance ();
  return 0;
}
