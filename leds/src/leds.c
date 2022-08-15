#include "leds.h"

#define LEDS_OFFSET 1
#define FIRST_BIT_ON 1
#define LEDS_ALLF_OFF 0x0000
#define LEDS_ALLF_ON 0xFFFF

static uint16_t *puerto;
static registro_errores_t NotificarError;

static uint16_t LedToMask(uint8_t led)
{
    return (FIRST_BIT_ON << (led - LEDS_OFFSET));
}

void LedsCreate(uint16_t *address, registro_errores_t errores)
{
    puerto = address;
    NotificarError = errores;
    *address = LEDS_ALLF_OFF;
}

void LedsSingleTurnOn(uint8_t led)
{
    if (led > 16)
    {
        NotificarError(ALERTA, __FUNCTION__, __LINE__, "Numero de led invalido");
    }
    else
    {
        *puerto |= LedToMask(led);
    }
}

void LedsSingleTurnOff(uint8_t led)
{
    *puerto &= ~LedToMask(led);
}

void LedsOnAllLeds(void)
{
    *puerto = LEDS_ALLF_ON;
}

void LedsOffAllLeds(void)
{
    *puerto = LEDS_ALLF_OFF;
}

bool LedsIsOnNLed(uint8_t led)
{
    if ((LedToMask(led) & *puerto) != 0)
    {
        return true;
    }
    return false;
}

bool LedsIsOffNLed(uint8_t led)
{
    if ((LedToMask(led) & ~*puerto) != 0)
    {
        return true;
    }
    return false;
}