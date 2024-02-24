
/*
* Library for printing on screen
* Made by mohamed Elgreatly 26/3/2023
* Released into public domain
*/

#ifndef MathFunc_h
#define MathFunc_h
#include "Arduino.h"

class  MathFunc {
    public:MathFunc(int serial);
	  float power(float number, int exponent);
	  int* Add2_Int_Array(int arr1[], int arr2[],int size);
	  int* Multiply2_Int_Array(int arr1[], int arr2[], int size);
	  void delayIn_Second(int second);
};

#endif


