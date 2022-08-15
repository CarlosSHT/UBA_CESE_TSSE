#include "leds.h"

#define LEDS_OFFSET 1
#define FIRST_BIT_ON 1
#define LEDS_ALLF_OFF 0x0000
#define LEDS_ALLF_ON 0xFFFF
#define LEDS_MAX_VALUE 16
#define LEDS_MIN_VALUE 1

static uint16_t *puerto;
static registro_errores_t NotificarError;

static uint16_t LedToMask(uint8_t led)
{
    return (FIRST_BIT_ON << (led - LEDS_OFFSET));
}

static bool LedsWorkInRange(uint8_t led)
{
    if (led > LEDS_MAX_VALUE || led < LEDS_MIN_VALUE)
    {
        NotificarError(ALERTA, __FUNCTION__, __LINE__, "Numero de led invalido");
        return false;
    }
    return true;
}

void LedsCreate(uint16_t *address, registro_errores_t errores)
{
    puerto = address;
    NotificarError = errores;
    *address = LEDS_ALLF_OFF;
}

void LedsSingleTurnOn(uint8_t led)
{
    if (LedsWorkInRange(led))
    {
        *puerto |= LedToMask(led);
    }
}

void LedsSingleTurnOff(uint8_t led)
{
    if (LedsWorkInRange(led))
    {
        *puerto &= ~LedToMask(led);
    }
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
    if (!LedsWorkInRange(led))
        return false;

    if ((LedToMask(led) & *puerto) != 0)
    {
        return true;
    }
    return false;
}

bool LedsIsOffNLed(uint8_t led)
{
    if (!LedsWorkInRange(led))
        return false;

    if ((LedToMask(led) & ~*puerto) != 0)
    {
        return true;
    }
    return false;
}