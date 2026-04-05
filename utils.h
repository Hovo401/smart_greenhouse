#pragma once

String pad4(int val) {
  String s = String(val);
  while (s.length() < 4) s += '_';
  return s;
}