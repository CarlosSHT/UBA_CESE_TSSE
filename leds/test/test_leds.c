#include "unity.h"
#include "leds.h"

/**
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

void test_todos_los_leds_inician_apagados(void)
{
    uint16_t leds_virtuales = 0xFFFF;
    LedsCreate(&leds_virtuales, RegistrarError);
    TEST_ASSERT_EQUAL(0x0000, leds_virtuales);
}

void test_prende_un_led_individual(void)
{
    LedsSingleTurnOn(3);
    TEST_ASSERT_EQUAL(1 << 2, leds_virtuales);
}

void test_apaga_un_led_individual(void)
{
    LedsSingleTurnOn(3);
    LedsSingleTurnOff(3);
    TEST_ASSERT_EQUAL(0, leds_virtuales);
}

void test_prender_apagar_multiples_leds(void)
{
    LedsSingleTurnOn(3);
    LedsSingleTurnOn(7);
    LedsSingleTurnOff(7);
    TEST_ASSERT_EQUAL(1 << 2, leds_virtuales);
}

void test_prender_un_led_invalido(void)
{
    LedsSingleTurnOn(17);
    TEST_ASSERT_EQUAL(ALERTA, gravedad_registrada);
    TEST_ASSERT_GREATER_THAN(1, linea_registrada);
}

// Prender todos los LEDs de una vez.
void test_prender_todos_los_leds(void)
{
    LedsOnAllLeds();
    TEST_ASSERT_EQUAL(0xFFFF, leds_virtuales);
}

// Apagar todos los LEDs de una vez.
void test_apagar_todos_los_leds(void)
{
    LedsOnAllLeds();
    LedsOffAllLeds();
    TEST_ASSERT_EQUAL(0x0000, leds_virtuales);
}

// Consultar el estado de un LED que está encendido
void test_led_pos_n_esta_encendido(void)
{
    bool isLedOn;
    LedsSingleTurnOn(12);
    isLedOn = LedsIsOnNLed(12);
    TEST_ASSERT_EQUAL(true, isLedOn);
}

// Consultar el estado de un LED que est apagado
void test_led_pos_n_esta_apagado(void)
{
    bool isLedOff;
    // LedsSingleTurnOn(4);
    isLedOff = LedsIsOffNLed(12);
    TEST_ASSERT_EQUAL(true, isLedOff);
}