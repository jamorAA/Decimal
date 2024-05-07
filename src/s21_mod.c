#include "s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  setNullBit(result);
  s21_long long_dec1 = from_dec_long(value_1);
  s21_long long_dec2 = from_dec_long(value_2);
  s21_long long_res = {{0, 0, 0, 0, 0, 0, 0}};
  s21_long temp = {{0, 0, 0, 0, 0, 0, 0}};

  if (testNa0(value_2)) {
    int scale = longScaleVyrov(&long_dec1, &long_dec2, getScale(value_1),
                               getScale(value_2));
    temp = long_dec1;
    longDivGetWholeAndRem(&temp, long_dec2, &long_res);
    *result = funcResultToDecimal(temp, scale, getBit(value_1, 127));
    flag = errorRead(result);
  } else {
    flag = 3;
  }
  return flag;
}
