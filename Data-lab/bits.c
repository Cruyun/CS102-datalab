/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
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
// 用 ~ 和 | 实现 &
// 摩尔定律 x & y = ~(~(x & y))
int bitAnd(int x, int y) {
  return ~((~x) | (~y));
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
// 提取数x中从右数的第 n 个字节(0<= n <= 3)
 
// 1个字节是8位
int getByte(int x, int n) {
   n = n << 3; //n * 8
   x = (x >> n) & 0xff; // 右移n位
   return x;
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
  */
// 实现逻辑右移
// x 右移 n 位，和0x0fffffff 做 与运算将前 n 位置0
// 0000 0000 0000 0000 0000 0000 0000 0001
// 1000 0000 0000 0000 0000 0000 0000 0000
// 0111 1111 1111 1111 1111 1111 1111 1111
// 0000 0111 1111 1111 1111 1111 1111 1111
// 0000 1111 1111 1111 1111 1111 1111 1111
int logicalShift(int x, int n) {
  int mask;
  mask  = ~((1 << 31) >> n << 1);
  return (x >> n) & mask; //x右移n位，前n位置0
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
// 计算 x 的二进制表示里面有几个1：分治法，把每一位都当成独立的数，并求和
// 方法一：
// 参考链接 https://stackoverflow.com/questions/3815165/how-to-implement-bitcount-using-only-bitwise-operators
int bitCount(int x) {
  int tmp, mask1, mask2, mask3, mask4, mask5, sum;

  // mask1: 0x55555555
  tmp = 0x55 | (0x55 << 8);
  mask1 = tmp | (tmp << 16);

  // mask2: 0x33333333
  tmp = 0x33 | (0x33 << 8);
  mask2 = tmp | (tmp << 16);

  // mask3: 0x0f0f0f0f
  tmp = 0x0f | (0x0f << 8);
  mask3 = tmp | (tmp << 16);

  // mask4: 0x00ff00ff
  mask4 = 0xFF | (0xFF << 16);

  // mask5: 0x0000ffff
  tmp = 0xFF | (0xFF << 8);
  mask5 = tmp | (0 << 16);

  sum = (x & mask1) + ((x >> 1) & mask1);
  sum = (sum & mask2) + ((sum >> 2) & mask2);
  sum = (sum & mask3) + ((sum >> 4) & mask3);
  sum = (sum & mask4) + ((sum >> 8) & mask4);
  sum = (sum & mask5) + ((sum >> 16) & mask5);

  return sum;
}
// 方法二：
/*
int bitCount(int x) {
  int sum = 0;
  // i = 0x11111111
  int i = 0x11 | (0x11 << 8);
  i = i | (i << 16);
  
  //对于每四位，通过不停的移位运算将前三位的1加到第四位上
  sum += x & i;
  sum += (x >> 1) & i;
  sum += (x >> 2) & i;
  sum += (x >> 3) & i;

  //令i = 0xffff;
  i = 0xff | (0xff<<8);

  //将前16位与后16位相加
  sum = (sum >> 16) + (i & sum);

  //令i = 0x0f0f
  //整理每8位之和
  i = 0x0f | (0x0f<<8);
  sum = ((sum >> 4) & i) + (sum & i);

  //将前8位与后8位相加
  i = 0xff;
  sum = (sum >> 8) + (i & sum);
  
  return sum;
}
*/

/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
// 不使用! 计算! x
// if x == 0, !x = 1 ; else !x = 0
// 要把0与其它数区分开来，考虑到-0 = +0 = 0，-x只有在x=0时符号位才不会改变。故只需利用x | (-x) = x | (~x + 1)的符号位即可。
// 零的特殊之处，零和零的相反数首位都是零，所以按位或的话只有零的首位还是零，
int bang(int x) {
  int i = ~x + 1;
  int j = (i | x) >> 31; //符号相同则为0，不同为1
  return j + 1;
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
// return maximum two's complement integer  : ~(1<<31);  
int tmin(void) {
  return 0x80 << 24; // 0x80000000
  // return 1 << 31;
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
// 如果x可以表示为n位二进制补码形式,则返回1，否则返回0
// 左移32-n位，右移32-n位，若不变则 return 1
int fitsBits(int x, int n) {
  int i = 32 + (~n + 1);
  int a = (x << i) >> i;
  return !(x ^ a);
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
// 计算x/(2^n)
//正数 x >> n;
//负数 (x + 1 << n - 1) >> n
int divpwr2(int x, int n) {
  int bias = (1 << n) + ~0;
  return (x + ((x >> 31) & bias)) >> n;
}

/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
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
  int m = (x >> 31) & 1; //m的符号位
  int i = !!x;
  return i ^ m;
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
 // return 1 : x<0,y>0 or x - y <= 0
int isLessOrEqual(int x, int y) {
  int m = (~x + 1) + y; // y - x
  int p = !!(x >> 31); // x 的符号位
  int q = !!(y >> 31); // y 的符号位
  int i = !(m >> 31); // y - x >=0 时 i == 1
  int j = ! (p ^ q); // 判断是否同号
  return (i & j) | (p & !q );
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
 //返回不超过以2为底x对数的最小整数。找最高位的1出现的位置
int ilog2(int x) {
  int mark;
  mark = (!!(x >> 16)) << 4;
  mark +=  ((!!(x >> (mark + 8))) << 3);
  mark += ((!!(x >> (mark + 4))) << 2);
  mark += ((!!(x >> (mark + 2))) << 1);
  mark += ((!!(x >> (mark + 1))) << 0);

  mark += (!!mark) + (~0) + (!(1 ^ x)); //考虑x=0

  return mark;
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
 //NaN时返回NaN,否则改变符号位
unsigned float_neg(unsigned uf) {
  unsigned result;
  unsigned m;

  result = uf ^ 0x80000000;
  m = uf & 0x7fffffff;
  if (m > 0x7f800000) {
    result = uf;
  }
  return result;
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
  unsigned s = 0, exp = 31, frac = 0, d = 0;
  if (x == 0) return 0;
  if (x & 0x80000000) {
    s = 0x80000000;
    x = -x;
  }
  while (1) {
    if (x & 0x80000000) break;
      exp -= 1;    //exp记录最高位的位置
      x <<= 1;
  }
  if ((x & 0x1ff) == 0x180) d = 1;   //最后舍掉的8位若最高位为1且低七位仍有数，要进位
  else if ((x & 0xff) > 0x80) d = 1;
  frac = ((x & 0x7fffffff) >> 8) + d;   //franc记录尾数

  return s + ((exp + 127) << 23) + frac;
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
  if((uf & 0x7F800000) == 0)   // 若是指数为0情况
    return (uf << 1) | (0x80000000 & uf);//特殊情况0x80000000
  else if((uf & 0x7fffffff) >= 0x7f800000)   //若数为NaN
    return uf;
  return uf + 0x00800000;
}
