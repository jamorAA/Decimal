#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  setNullBit(result);
  s21_long long_dec1 = from_dec_long(value_1);
  s21_long long_dec2 = from_dec_long(value_2);
  s21_long long_res = {{0, 0, 0, 0, 0, 0, 0}};
  s21_long temp = {{0, 0, 0, 0, 0, 0, 0}};
  if (testNa0(value_2)) {
    int znak = getBit(value_1, 127) ^ getBit(value_2, 127);
    longScaleVyrov(&long_dec1, &long_dec2, getScale(value_1),
                   getScale(value_2));
    longDivGetWholeAndRem(&long_dec1, long_dec2, &long_res);
    int i = 0;
    for (; i < 29 && longtestNa0(long_dec1); i++) {
      setLongNullBit(&temp);
      func_long_mul(long_dec1, _LONGDEC10, &long_dec1);
      longDivGetWholeAndRem(&long_dec1, long_dec2, &temp);
      func_long_mul(long_res, _LONGDEC10, &long_res);
      long_adder(long_res, temp, &long_res, 0);
    }
    *result = funcResultToDecimal(long_res, i, znak);
    flag = errorRead(result);
  } else {
    flag = 3;
  }
  return flag;
}
