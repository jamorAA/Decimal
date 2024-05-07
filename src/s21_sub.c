#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int znak = 0;
  s21_long long_dec1 = from_dec_long(value_1);
  s21_long long_dec2 = from_dec_long(value_2);
  s21_long long_res = {{0, 0, 0, 0, 0, 0, 0}};
  int scale = longScaleVyrov(&long_dec1, &long_dec2, getScale(value_1),
                             getScale(value_2));
  int flagOne = longFuncSrav(long_dec1, long_dec2);
  if (getBit(value_1, 127) ^ getBit(value_2, 127)) {
    long_adder(long_dec1, long_dec2, &long_res, 0);
    znak = getBit(value_1, 127);
  } else {
    if (flagOne == 1) {
      long_adder(long_dec1, long_dec2, &long_res, 1);
      znak = getBit(value_1, 127);
    } else if (flagOne == 2) {
      long_adder(long_dec2, long_dec1, &long_res, 1);
      znak = !getBit(value_2, 127);
    }
  }
  setLongBit(&long_res, 223, 0);
  *result = funcResultToDecimal(long_res, scale, znak);
  return errorRead(result);
}
