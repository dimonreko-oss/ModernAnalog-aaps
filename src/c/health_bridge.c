#include <pebble.h>
#include <stdint.h>
#include <stdio.h>
#include "aaps_link.h"

// AAPS display values for JS as "bg|trend|delta|iob|cob|age_min" (the FFI cannot
// return a struct). Static buffer, declared "const char*": the FFI glue does not
// copy it (and has no malloc to fail, which would abort the face), so JS must
// copy the text before the next call.
const char *aaps_display_text(void) {
  static char s[48];
  AapsLinkDisplay d;
  aaps_link_display(&d);
  snprintf(s, sizeof(s), "%s|%s|%s|%s|%s|%d", d.bg, d.trend, d.delta, d.iob, d.cob, d.age_min);
  return s;
}

int32_t health_steps_today(void) {
  HealthValue value = health_service_sum_today(HealthMetricStepCount);
  return value >= 0 ? (int32_t)value : -1;
}

int32_t health_heart_rate(void) {
  HealthValue value = health_service_peek_current_value(HealthMetricHeartRateBPM);
  return value > 0 ? (int32_t)value : -1;
}
