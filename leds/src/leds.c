#include "leds.h"

#define LEDS_OFFSET 1
#define FIRST_BIT_ON 1
#define LEDS_ALLF_OFF 0x0000
#define LEDS_ALLF_ON 0xFFFF
#define LEDS_MAX_VALUE 16
#define LEDS_MIN_VALUE 1

static uint16_t *puerto;
static registro_errores_t NotificarError;

/**
 * @brief Crea una mascara de 16 bits a través
 * de un corrimiento hacia la izquierda
 *
 * @param led       : posición N del registro de LEDs
 * @return uint16_t : mascara de 16 bits con un único
 *                    bit de valor 1
 */
static uint16_t LedToMask(uint8_t led)
{
    return (FIRST_BIT_ON << (led - LEDS_OFFSET));
}

/**
 * @brief Verifica que la posición ingresada "led" sea válida
 * correspondiente al tamaño del registro (16bits).
 *
 * @param led       : posición N del registro de LEDs
 * @return true     : El valor de posición es desde 1 a 16
 * @return false    : El valor de posición es menor a 1 o mayor a 16
 */
static bool LedsWorkInRange(uint8_t led)
{
    if (led > LEDS_MAX_VALUE || led < LEDS_MIN_VALUE)
    {
        NotificarError(ALERTA, __FUNCTION__, __LINE__, "Numero de led invalido");
        return false;
    }
    return true;
}

/**
 * @brief En caso sea un valor válido de posición, comprueba
 * que el bit dado en la posición N tenga un valor 1, permite
 * la verificación en dos casos "prendido" y "apagado" al recibir
 * un valor normal o negado del registro LEDs y aplicar la mascara
 * para realizar la comparación.
 *
 * @param led       : Posición N del registro de LEDs
 * @param port_val  : Valor a verificar del registro, puede ser original o negado
 * @return true     : En caso el bit de la posición tenga valor 1
 * @return false    : Se retorna en caso sea una posición inválida o
 *                    el bit de la posición tenga valor 0
 */
static bool LedsCheckStateLed(uint8_t led, uint16_t port_val)
{
    if (!LedsWorkInRange(led))
        return false;

    if ((LedToMask(led) & port_val) != 0)
    {
        return true;
    }
    return false;
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
    return (LedsCheckStateLed(led, *puerto));
}

bool LedsIsOffNLed(uint8_t led)
{
    return (LedsCheckStateLed(led, ~*puerto));
}