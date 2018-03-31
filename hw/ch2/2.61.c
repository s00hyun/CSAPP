/*CS:APP Homework Problems 2.61*/

#include<stdio.h>

int equals_1(int x);
int equals_0(int x);
int get_lsb(int x);
int get_msb(int x);

int main(void){
	int x1 = 0xf0ffff00; //some test input 1
	int x2 = 0x000000ff; //some test input 2	
	
	printf("isEqualsOne == %x\n", equals_1(0xfffffff0));
	printf("isEqualsZero == %x\n", equals_0(0x00000000));
	printf("LSB == %x\n", get_lsb(x1));
	printf("MSB == %x\n", get_msb(x1));
	
	return 0;
}

/* A : any bit of x equals 1 */
int equals_1(int x){
	return !(~x);
}

/* B : any bit of x equals 0 */
int equals_0(int x){
	return !x;	
}

/* C : any bit in the least significant byte of x equals 1 */
int get_lsb(int x){
	int lsb = x & 0xff;
	
	return (x & 0xff) & 1;
}

/* D : any bit in the most significant byte of x equals 0 */
int get_msb(int x){
	int shift_val = (sizeof(int) - 1) << 3; //24 bits
	int xright = x >> shift_val;
	
	return !(xright & 0xff) & 1;
}
