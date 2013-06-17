float getTime() {
  const unsigned long MAX_LONG = 0xFFFFFFFF;
  static float time;
  static unsigned long lastTimeMillis = 0;
  unsigned long timeMillis = millis();
  if (timeMillis != lastTimeMillis) {
    if (timeMillis < lastTimeMillis) {
      time += (float)(MAX_LONG - lastTimeMillis + timeMillis) / 1000.0;
    } else {
      time += (float)(timeMillis - lastTimeMillis) / 1000.0;
    }
    lastTimeMillis = timeMillis;
  }
  return time;
}
