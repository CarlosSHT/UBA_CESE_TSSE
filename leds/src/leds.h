#include <stdint.h>
#include "errores.h"

void LedsCreate(uint16_t *address, registro_errores_t errores);

void LedsSingleTurnOn(uint8_t led);

void LedsSingleTurnOff(uint8_t led);

void LedsOnAllLeds(void);