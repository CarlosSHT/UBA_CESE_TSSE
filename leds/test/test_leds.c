#include "unity.h"
#include "leds.h"

/**
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
void test_verificar_led_posicion_n_esta_encendido(void)
{
    bool isLedOn;

    LedsSingleTurnOn(12);
    isLedOn = LedsIsOnNLed(12);
    TEST_ASSERT_EQUAL(true, isLedOn);
}

// Consultar el estado de un LED que est apagado
void test_verificar_led_posicion_n_esta_apagado(void)
{
    bool isLedOff;

    isLedOff = LedsIsOffNLed(8);
    TEST_ASSERT_EQUAL(true, isLedOff);
}

// Revisar limites de los parametros.
/// Limite inferior LedsSingleTurnOn
void test_prende_led_individual_en_limite_inferior(void)
{
    LedsSingleTurnOn(1);
    TEST_ASSERT_EQUAL(1 << 0, leds_virtuales);
}
/// Limite superior LedsSingleTurnOn
void test_prende_led_individual_en_limite_superior(void)
{
    LedsSingleTurnOn(16);
    TEST_ASSERT_EQUAL(1 << 15, leds_virtuales);
}

/// Limite inferior LedsSingleTurnOff
void test_apaga_un_led_individual_en_limite_inferior(void)
{
    LedsSingleTurnOn(1);
    LedsSingleTurnOff(1);
    TEST_ASSERT_EQUAL(0, leds_virtuales);
}
/// Limite superior LedsSingleTurnOff
void test_apaga_un_led_individual_en_limite_superior(void)
{
    LedsSingleTurnOn(16);
    LedsSingleTurnOff(16);
    TEST_ASSERT_EQUAL(0, leds_virtuales);
}

/// Limite inferior LedsIsOnNLed
void test_verificar_led_posicion_n_esta_encendido_en_limite_inferior(void)
{
    bool isLedOn;

    LedsSingleTurnOn(1);
    isLedOn = LedsIsOnNLed(1);
    TEST_ASSERT_EQUAL(true, isLedOn);
}
/// Limite superior LedsIsOnNLed
void test_verificar_led_posicion_n_esta_encendido_en_limite_superior(void)
{
    bool isLedOn;

    LedsSingleTurnOn(16);
    isLedOn = LedsIsOnNLed(16);
    TEST_ASSERT_EQUAL(true, isLedOn);
}

/// Limite inferior LedsIsOffNLed
void test_verificar_led_posicion_n_esta_apagado_en_limite_inferior(void)
{
    bool isLedOff;

    isLedOff = LedsIsOffNLed(1);
    TEST_ASSERT_EQUAL(true, isLedOff);
}
/// Limite superior LedsIsOffNLed
void test_verificar_led_posicion_n_esta_apagado_en_limite_superior(void)
{
    bool isLedOff;

    isLedOff = LedsIsOffNLed(16);
    TEST_ASSERT_EQUAL(true, isLedOff);
}

void test_prender_un_led_invalido(void)
{
    LedsSingleTurnOn(17);
    TEST_ASSERT_EQUAL(ALERTA, gravedad_registrada);
    TEST_ASSERT_GREATER_THAN(1, linea_registrada);
}

void test_apagar_un_led_invalido(void)
{
    LedsSingleTurnOff(24);
    TEST_ASSERT_EQUAL(ALERTA, gravedad_registrada);
    TEST_ASSERT_GREATER_THAN(1, linea_registrada);
}

// Consultar el estado de un LED que está encendido
void test_verificar_led_posicion_invalida_esta_encendido(void)
{
    bool isLedOn;

    isLedOn = LedsIsOnNLed(24);
    TEST_ASSERT_EQUAL(ALERTA, gravedad_registrada);
    TEST_ASSERT_GREATER_THAN(1, linea_registrada);
    TEST_ASSERT_EQUAL(false, isLedOn);
}

// Consultar el estado de un LED que est apagado
void test_verificar_led_posicion_invalida_esta_apagado(void)
{
    bool isLedOff;

    isLedOff = LedsIsOffNLed(28);
    TEST_ASSERT_EQUAL(ALERTA, gravedad_registrada);
    TEST_ASSERT_GREATER_THAN(1, linea_registrada);
    TEST_ASSERT_EQUAL(false, isLedOff);
}