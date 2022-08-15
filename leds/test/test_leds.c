/* === Inclusiones de cabeceras ============================================================================== */
#include "unity.h"
#include "leds.h"

/* === Definición de variables globales internas ============================================================== */
uint16_t leds_virtuales;        //!< Registro LEDs
gravedad_t gravedad_registrada; //!< Nivel de gravedad ocurrida
int linea_registrada;           //!< Linea de función donde se registra el error

/* === Definiciones de funciones internas ===================================================================== */

void RegistrarError(gravedad_t gravedad, const char *funcion, int linea, const char *mensaje, ...)
{
    gravedad_registrada = gravedad; //! Asigna el nivel de gravedad
    linea_registrada = linea;       //! Asigna número de linea
}

//! Función de inicio integrado en Ceedling
void setUp(void)
{
    gravedad_registrada = ERROR - 1;             //!< Comprueba el funcionamiento al asignar un valor inválido de error
    LedsCreate(&leds_virtuales, RegistrarError); //!< Inicializa los leds apagados
}

void test_todos_los_leds_inician_apagados(void)
{
    uint16_t leds_virtuales = 0xFFFF;            //!< Establece en 1 todos los bits del registro LEDs (prende)
    LedsCreate(&leds_virtuales, RegistrarError); //!< Función a testear, inicializa los leds apagados
    TEST_ASSERT_EQUAL(0x0000, leds_virtuales);
}

void test_prende_un_led_individual(void)
{
    LedsSingleTurnOn(3);                       //!< Función a testear, prende solo el led 3
    TEST_ASSERT_EQUAL(1 << 2, leds_virtuales); //!< ASSERT sin error si leds_virtuales es 0x0004
}

void test_apaga_un_led_individual(void)
{
    LedsSingleTurnOn(3);                  //!< Prende el led incializado apagado
    LedsSingleTurnOff(3);                 //!< Función a testear
    TEST_ASSERT_EQUAL(0, leds_virtuales); //!<
}

void test_prender_apagar_multiples_leds(void)
{
    LedsSingleTurnOn(3);                       //!< Prende led 3
    LedsSingleTurnOn(7);                       //!< Prende led 7
    LedsSingleTurnOff(7);                      //!< Apaga led 7
    TEST_ASSERT_EQUAL(1 << 2, leds_virtuales); //!< Verifica que se encuentre prendido led 3
}

void test_prender_todos_los_leds(void)
{
    LedsOnAllLeds();
    TEST_ASSERT_EQUAL(0xFFFF, leds_virtuales);
}

void test_apagar_todos_los_leds(void)
{
    LedsOnAllLeds(); //!< Requiere prender todos los leds iniciados apgados
    LedsOffAllLeds();
    TEST_ASSERT_EQUAL(0x0000, leds_virtuales);
}

void test_verificar_led_posicion_n_esta_encendido(void)
{
    bool isLedOn;

    LedsSingleTurnOn(12);
    isLedOn = LedsIsOnNLed(12); //!< Obtiene true si el led N esta prendido
    TEST_ASSERT_EQUAL(true, isLedOn);
}

void test_verificar_led_posicion_n_esta_apagado(void)
{
    bool isLedOff;

    isLedOff = LedsIsOffNLed(8); //!< Obtiene True si el led N esta apagado
    TEST_ASSERT_EQUAL(true, isLedOff);
}

///////////////////////////////////////////////////////////////////////////
/// ... Funciones de prueba para limites INFERIOR (1) y SUPERIOR (16) ...
///////////////////////////////////////////////////////////////////////////
void test_prende_led_individual_en_limite_inferior(void)
{
    LedsSingleTurnOn(1);
    TEST_ASSERT_EQUAL(1 << 0, leds_virtuales);
}

void test_prende_led_individual_en_limite_superior(void)
{
    LedsSingleTurnOn(16);
    TEST_ASSERT_EQUAL(1 << 15, leds_virtuales);
}

void test_apaga_un_led_individual_en_limite_inferior(void)
{
    LedsSingleTurnOn(1);
    LedsSingleTurnOff(1);
    TEST_ASSERT_EQUAL(0, leds_virtuales);
}

void test_apaga_un_led_individual_en_limite_superior(void)
{
    LedsSingleTurnOn(16);
    LedsSingleTurnOff(16);
    TEST_ASSERT_EQUAL(0, leds_virtuales);
}

void test_verificar_led_posicion_n_esta_encendido_en_limite_inferior(void)
{
    bool isLedOn;

    LedsSingleTurnOn(1);
    isLedOn = LedsIsOnNLed(1);
    TEST_ASSERT_EQUAL(true, isLedOn);
}

void test_verificar_led_posicion_n_esta_encendido_en_limite_superior(void)
{
    bool isLedOn;

    LedsSingleTurnOn(16);
    isLedOn = LedsIsOnNLed(16);
    TEST_ASSERT_EQUAL(true, isLedOn);
}

void test_verificar_led_posicion_n_esta_apagado_en_limite_inferior(void)
{
    bool isLedOff;

    isLedOff = LedsIsOffNLed(1);
    TEST_ASSERT_EQUAL(true, isLedOff);
}

void test_verificar_led_posicion_n_esta_apagado_en_limite_superior(void)
{
    bool isLedOff;

    isLedOff = LedsIsOffNLed(16);
    TEST_ASSERT_EQUAL(true, isLedOff);
}

///////////////////////////////////////////////////////////////////////////
/// ... Funciones de prueba para leds inválidos ...
///////////////////////////////////////////////////////////////////////////
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

void test_verificar_led_posicion_invalida_esta_encendido(void)
{
    bool isLedOn;

    isLedOn = LedsIsOnNLed(24);
    TEST_ASSERT_EQUAL(ALERTA, gravedad_registrada);
    TEST_ASSERT_GREATER_THAN(1, linea_registrada);
    TEST_ASSERT_EQUAL(false, isLedOn);
}

void test_verificar_led_posicion_invalida_esta_apagado(void)
{
    bool isLedOff;

    isLedOff = LedsIsOffNLed(28);
    TEST_ASSERT_EQUAL(ALERTA, gravedad_registrada);
    TEST_ASSERT_GREATER_THAN(1, linea_registrada);
    TEST_ASSERT_EQUAL(false, isLedOff);
}