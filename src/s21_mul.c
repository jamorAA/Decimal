#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  setNullBit(result);
  int scale1 = getScale(value_1);
  int scale2 = getScale(value_2);
  int scale = scale1 + scale2;
  s21_long longDec1 = from_dec_long(value_1);
  s21_long longDec2 = from_dec_long(value_2);
  s21_long longRes = {{0, 0, 0, 0, 0, 0, 0}};
  // int flScale = 0;
  int flScale = func_long_mul(longDec1, longDec2, &longRes);
  // printf("%d", flScale);
  if (flScale < 0) {
    printf("aboba");
  }
  *result = funcResultToDecimal(longRes, scale,
                                getBit(value_1, 127) ^ getBit(value_2, 127));
  return errorRead(result);  //  это пока
}
