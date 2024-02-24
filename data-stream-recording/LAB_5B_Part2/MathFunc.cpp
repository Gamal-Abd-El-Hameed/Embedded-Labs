/*
* Library for printing on screen
* Made by mohamed Elgreatly  26/3/2023
* Released into public domain
*/


#include "Arduino.h"
#include "MathFunc.h"


MathFunc::MathFunc(int serial)
{
	Serial.begin(serial);
}


float MathFunc::power(float number, int exponent)
{	
	float result = 1.0;
	for (int i = 0;i < abs(exponent);i++)
	{
		result = result * number;
	}
	if (exponent > 0) {
		return result;
	}
	else {
		return 1.0 / result;
	}
}

int* MathFunc::Add2_Int_Array(int arr1[], int arr2[],int size)
{
	int* result = new int[size];
  for (int i = 0;i < size;i++)
		{
			result[i] = arr1[i] + arr2[i];
		}
		return result;
	// try {
	// 	for (int i = 0;i < size;i++)
	// 	{
	// 		result[i] = arr1[i] + arr2[i];
	// 	}
	// 	return result;
	// }
	// catch (std::exception& e) {
	// 	int result[size];
	// 	cout << "check parameters correctly";
	// 	return result;
	// }
}

int* MathFunc::Multiply2_Int_Array(int arr1[], int arr2[], int size)
{
	int* result = new int[size];
  // int result[size];
  for (int i = 0;i < size;i++)
		{
			result[i] = arr1[i] * arr2[i];
		}
		return result;
	// try {
	// 	for (int i = 0;i < size;i++)
	// 	{
	// 		result[i] = arr1[i] * arr2[i];
	// 	}
	// 	return result;
	// }
	// catch (std::exception& e) {
	// 	int result[size];
	// 	cout << "check parameters correctly";
	// 	return result;
	// }
}

void MathFunc::delayIn_Second(int second)
{
	delay(1000 * second);
}

