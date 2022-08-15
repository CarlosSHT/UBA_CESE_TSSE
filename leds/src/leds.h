#include <stdint.h>
#include <stdbool.h>
#include "errores.h"

void LedsCreate(uint16_t *address, registro_errores_t errores);

void LedsSingleTurnOn(uint8_t led);

void LedsSingleTurnOff(uint8_t led);

void LedsOnAllLeds(void);

void LedsOffAllLeds(void);

bool LedsIsOnNLed(uint8_t led);

bool LedsIsOffNLed(uint8_t led);