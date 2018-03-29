/* 
 * CS:APP Data Lab 
 * 
 * Soohyun Choi(userID: s20155180)
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  /*use ~ and | to yield x&y*/
  return ~(~x | ~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
	 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  /*rightshift x to some extent shiftNum and do mask with 0xFF*/
  int shiftNum = n << 3;
  int shiftX = x >> shiftNum;

  return shiftX & 0xFF; 
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  /*change arithmetically shifted integer a into logically shifted result*/
  int arithmeticShift = x >> n;
  int mask = ((1 << 31) >> n) << 1;

  return arithmeticShift & ~mask;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int m = 0x55 + (0x55 << 8);
  int mask = m + (m << 16); //01010101..
  x = (x & mask) + ((x >> 1) & mask);

  m = 0x33 + (0x33 << 8);
  mask = m + (m << 16); //00110011..
  x = (x & mask) + ((x >> 2) & mask);

  m = 0x0f + (0x0f << 8);
  mask = m + (m << 16); //0000111100001111..
  x = (x & mask) + ((x >> 4) & mask);

  mask = 0xff + (0xff << 16); //00000000111111110000000011111111
  x = (x & mask) + ((x >> 8) & mask);

  mask = 0xff + (0xff << 8); //00000000000000001111111111111111
  x = (x & mask) + ((x >> 16) & mask);

  return x;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  //return 1 if x == 0. return 0 otherwise.
  //0 is the only number that both negative and positive have 0 in sign bit.
  int negORPos = ((~x) + 1) | x; //0 if x is zero
  int sign = (negORPos >> 31) & 1; 
  
  return (sign ^ 1);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /*for w=4, -8 is represented as [1000]*/
  return 1 << 31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  //if x can be represented as n-bit, then the first (32 - n + 1) bits should be identical.
  int firstSomeBits = x >> (n + ~0); //x >> (n - 1)
  int isFits = !(~firstSomeBits);
  
  //in order for x < 2^(n-1) we must not have any 1 at, or to the left of n-1
  isFits = isFits | !firstSomeBits;

  return isFits;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  /* For positive numbers, x/(2^n) == x >> n;
     for negative numbers, (x + 2^n - 1)/(2@n) == (x + (1 << n) - 1) >> n (if n != 0)*/
  int isNotPos = x >> 31; //0xffffffff if x is not positive. isNeg & 1 == 0x00000001
  int a = ((isNotPos & 1) << n) + isNotPos;

  return (x + a) >> n;  
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /*find 2's complement*/
  return ~x + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  /*find MSB(leftmost bit) and use XOR*/
  int MSB = (x >> 31) & 1; 
  
  return (!MSB) ^ (!x);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    /* all 1's if (+,-) or (+,0), all 0's if (+,+), (-,-), (-,0) or (0,0) */
  int oppSign = ((x ^ y) >> 31);
  /* all 1's if x <= 0, else all 0's */
  int xIsNegOrZero = x >> 31;
  /* all 1's if opposite sign and x <= 0, else all 0's */
  /*int x_neg_opp_pol = ( ( (x ^ y) & (x & (0x01 << 31) ) ) >> 31 );*/
  /* all 1's if x,y have same polarity and y - x is not less than 0 */
  int diff = ( ~ ((y + (~x + 1)) >> 31 ) ); //
  
  /* if sign is opposite and x < 0, mask out result of diff */
         /* opp polarity */            /* same polarity */
  return (!!(xIsNegOrZero & oppSign)) | (!!(diff & (~oppSign)));

/*
   int diff = x + (~y + 1); //x - y
   int MSB = (diff >> 31) & 1; //1 if diff is not positive. if so, should return 1

   return MSB;

   int signX = (x >> 31) & 1;
   int signY = (x >> 31) & 1;
   int signDiff = signX ^ signY;
 
   return (signDiff & signX) | (!MSB & !signDiff);
*/
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  //find the leftmost 1
  int c = 0;
  int r = 0;

  r = ((!(x >> 16)) + (~0)) & 16;
  c = c + r;
  x = x >> r;

  r = ((!(x >> 8)) + (~0)) & 8;
  c = c + r;
  x = x >> r;

  r = ((!(x >> 4)) + (~0)) & 4;
  c = c + r;
  x = x >> r;

  r = ((!(x >> 2)) + (~0)) & 2;
  c = c + r;
  x = x >> r;

  r = ((!(x >> 1)) + (~0)) & 1;
  c = c + r;
  x = x >> r;

  return c;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
   int expAllOne = 0x000000ff << 23; //0111111110000..00
   int frac = uf & 0x7fffff;

   if(((expAllOne & uf) == expAllOne) && frac) //if ((exp of uf) == expAllOne) and frac is not zero, that is, uf is NaN
      return uf;

   return uf ^ (1 << 31); //if not, change the sign bit
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  int sign = x & 0x80000000;
  
  // Store the highest bit with 1 in x
  int frac = 0, exp = 0;

  // For bits needed to be discarded
  int leftover = 0;
  int leftoverCnt = 0;
  
  int fracMask = 0;
	  
  // For operations in the middle shift
  int mid = 0;
  int shift = 0;
  int inter = 0;
		
  // Determine whether it's 0
  if(!x)
  	return 0;
	
  //Determine if it's tmin
  if(x == 0x80000000) 
  	return 0xcf000000;	

  // Determine whether x is positive or negative
  if(sign == 0x80000000) {
  	// x is negative - set it to be positive
	x = -x;
  }
  
  // Get highest bit of x
  while((x >> exp) != 1)
  	exp += 1;
 
  // Whether all the bits can be stored
  if(exp > 23){
  	leftoverCnt = exp - 23;
	shift = 1 << leftoverCnt;
	leftover = shift - 1 & x;

	frac = (x >> leftoverCnt) & 0x7fffff;
	
	mid = shift>>1;
	
	if(leftover > mid )
        	inter = 1;
	else if(leftover == mid) 
		inter = frac & 1;
	frac = frac + inter;
  } 
  else
  	frac = ((1 << exp) ^ x) << (23 - exp);
	  

  if(frac == 0x800000){
  	exp = exp + 1;
	frac = 0;
  }

  exp = exp + 127;
  exp = exp << 23;
	
  return sign + exp + frac;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  //uf = +-0 case.
  if(uf==0 || uf == 0x80000000) 
	return uf;
  //NaN case.
  if(((uf>>23) & 0xff) == 0xff) 
  	return uf;
  //Tiny value, but non-zero case.
  if(((uf>>23) & 0xff) == 0x00)
  	return (uf & (1<<31)) | (uf<<1);
  //Otherwise, Add 1 to exp value.
  return uf + (1<<23);
}
