#include "MathFunc.h"

MathFunc mathFunc(9600);

void setup() {
	Serial.begin(9600);
}
void loop() {
	Serial.println(mathFunc.power(5.0, 6));
	Serial.println(mathFunc.power(-7.0, 2));
	Serial.println(mathFunc.power(7.0, -2));
	int arr1[4] = {13, 2, 5, 6};
	int arr2[4] = { 7, 8, 9, 10 };
	int *result = mathFunc.Add2_Int_Array(arr1, arr2,4);
	Serial.println(result[1]);
	Serial.println(mathFunc.Multiply2_Int_Array(arr1, arr2,4)[0]);
	mathFunc.delayIn_Second(2);
	mathFunc.delayIn_Second(-2);
}
