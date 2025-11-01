// firmware/master/src/logger.cpp (Arduino)
#include "logger.h"
#if defined(USE_SD_LOG) && (USE_SD_LOG==1)
  #include <SPI.h>
  #include <SD.h>
  #include "pins.h"
  static File g_log;
#endif

bool logger_begin(){
#if defined(USE_SD_LOG) && (USE_SD_LOG==1)
  SPI.begin(SD_SCK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);
  if (!SD.begin(SD_CS_PIN)) return false;
  g_log = SD.open("/log.csv", FILE_APPEND);
  if (!g_log) return false;
  if (g_log.size() == 0) g_log.println("ts_ms,tag,msg");
  g_log.flush();
  return true;
#else
  return true; // fallback to Serial only
#endif
}

void logger_write_line(const char* line){
#if defined(USE_SD_LOG) && (USE_SD_LOG==1)
  if (g_log) { g_log.println(line); g_log.flush(); }
#endif
  // Always mirror to Serial for visibility
  // (safe kahit walang SD)
  // Note: Serial.begin() must be called in setup()
  Serial.println(line);
}
