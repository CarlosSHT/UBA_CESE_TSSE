#include "unity.h"
#include "leds.h"

/**
Prender todos los LEDs de una vez.
Apagar todos los LEDs de una vez.
Consultar el estado de un LED que está encendido
Consultar el estado de un LED que est apagado
Revisar limites de los parametros.
Revisar parámetros fuera de los limites.
 */
uint16_t leds_virtuales;
gravedad_t gravedad_registrada;
int linea_registrada;

void RegistrarError(gravedad_t gravedad, const char *funcion, int linea, const char *mensaje, ...)
{
    gravedad_registrada = gravedad;
    linea_registrada = linea;
}

void setUp(void)
{
    gravedad_registrada = ERROR - 1;
    LedsCreate(&leds_virtuales, RegistrarError);
}

// Con la inicialización todos los LEDs quedan apagados.
void test_todos_los_leds_inician_apagados(void)
{
    uint16_t leds_virtuales = 0xFFFF;
    LedsCreate(&leds_virtuales, RegistrarError);
    TEST_ASSERT_EQUAL(0x0000, leds_virtuales);
}

// Prender un LED individual.
void test_prende_un_led_individual(void)
{
    LedsSingleTurnOn(3);
    TEST_ASSERT_EQUAL(1 << 2, leds_virtuales);
}

// Apagar un LED individual.
void test_apaga_un_led_individual(void)
{
    LedsSingleTurnOn(3);
    LedsSingleTurnOff(3);
    TEST_ASSERT_EQUAL(0, leds_virtuales);
}

// Prender y apagar múltiples LED’s.
void test_prender_apagar_multiples_leds(void)
{
    LedsSingleTurnOn(3);
    LedsSingleTurnOn(7);
    LedsSingleTurnOff(7);
    TEST_ASSERT_EQUAL(1 << 2, leds_virtuales);
}

void teste_prender_un_led_invalido(void)
{
    LedsSingleTurnOn(17);
    TEST_ASSERT_EQUAL(ALERTA, gravedad_registrada);
    TEST_ASSERT_GREATER_THAN(1, linea_registrada);
}