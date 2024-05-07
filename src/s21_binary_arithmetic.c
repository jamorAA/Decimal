#include "s21_decimal.h"

int half_adder(int a, int b, int *c) {  //  полусумматор
  int flag = (a ^ b) ^ *c;
  *c = (a & b) | ((a ^ b) & *c);
  return flag;
}

void adder(s21_decimal dec1, s21_decimal dec2, s21_decimal *res,
           int op) {  //  суматор с функцией вычитания
  int c = op;
  for (int i = 0; i < 96; i++) {
    setBit(res, i, half_adder(getBit(dec1, i), op ^ getBit(dec2, i), &c));
    setBit(res, i + 1, c);
  }
}

void long_adder(s21_long dec1, s21_long dec2, s21_long *res,
                int op) {  //  суматор с функцией вычитания
  int c = op;
  for (int i = 0; i < 223; i++) {
    setLongBit(res, i,
               half_adder(getLongBit(dec1, i), op ^ getLongBit(dec2, i), &c));
    setLongBit(res, i + 1, c);
  }
}

// получение остатка dec1 получение результата при деление res
void longDivGetWholeAndRem(s21_long *dec1, s21_long dec2, s21_long *res) {
  setLongNullBit(res);
  s21_long temp_1 = {{0, 0, 0, 0, 0, 0, 0}};
  s21_long temp_2 = {{0, 0, 0, 0, 0, 0, 0}};
  int firstBitDec = getLongFirstIndexBit(*dec1) - getLongFirstIndexBit(dec2);
  for (int i = 0; i <= firstBitDec; i++) {
    setLongNullBit(&temp_1);
    temp_2 = dec2;
    shift_long(&temp_2, firstBitDec - i);
    long_adder(*dec1, temp_2, &temp_1, 1);
    if (getLongBit(temp_1, 223)) {
      setLongBit(res, 0, 1);
      setLongBit(&temp_1, 223, 0);
      long_adder(*dec1, temp_2, dec1, 1);
      setLongBit(dec1, 223, 0);
    }
    if (i < firstBitDec) {
      shift_long(res, 1);
    }
  }
}

// функция умножения
int func_long_mul(s21_long dec1, s21_long dec2, s21_long *res) {
  setLongNullBit(res);
  int flag = 1;
  for (int i = 0; i < 221 && flag; i++) {
    s21_long temp_1 = {{0, 0, 0, 0, 0, 0, 0}};
    setLongNullBit(&temp_1);
    for (int j = 0; j < 221 && flag; j++) {
      if (getLongBit(dec2, i)) {
        setLongBit(&temp_1, j + i, getLongBit(dec1, j) & getLongBit(dec2, i));
        if (getLongBit(dec1, j) && i + j >= 221) {
          flag = 0;
        }
      }
    }
    if (getLongBit(dec2, i)) {
      long_adder(*res, temp_1, res, 0);
    }
  }
  return flag;
}
