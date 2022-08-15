#include <stdint.h>
#include <stdbool.h>
#include "errores.h"

/**
 * @brief   Inicaliza un registro de leds con un dirección
 * de tamaño de 16 bits con los leds apagados. Además se
 * define un nivel de error correspondiente al registro.
 *
 * @param address : Dirección correspondiente a los leds
 * @param errores : Puntero a una variable de registros de errores
 */
void LedsCreate(uint16_t *address, registro_errores_t errores);

/**
 * @brief Prende un led en la posición N
 * estableciendo el valor de 1, si es un led
 * invalido se establece el nivel de error ALERTA
 *
 * @param led : posición N de led (1-16)
 */
void LedsSingleTurnOn(uint8_t led);

/**
 * @brief Apaga un único led en la posición N
 * estableciendo el valor de 0, si es un led
 * invalido se establece el nivel de error ALERTA
 *
 * @param led : posición N de led (1-16)
 */
void LedsSingleTurnOff(uint8_t led);

/**
 * @brief Prende todos los del registro LEDs
 * estableciendo todos sus bits en 1 (0xFFFF)
 *
 */
void LedsOnAllLeds(void);

/**
 * @brief Apaga todos los del registro LEDs
 * estableciendo todos sus bits en 0 (0x0000)
 *
 */
void LedsOffAllLeds(void);

/**
 * @brief Verifica si el led se encuentra prendido
 * (valor 1) en la posición N, si es un led
 * invalido se establece el nivel de error ALERTA
 *
 * @param led   :   posición N (1-16) a verificar en el registro
 * @return true :   retorna verdadero en caso que un led valido
 *                  este prendido (valor de bit led 1)
 * @return false:   retorna falso si es un led invalido o
 *                  se encuentre apagado (valor de bit led 0)
 */
bool LedsIsOnNLed(uint8_t led);

/**
 * @brief Verifica si el led se encuentra apagado
 * (valor 0) en la posición N, si es un led
 * invalido se establece el nivel de error ALERTA
 *
 * @param led   :   posición N (1-16) a verificar en el registro
 * @return true :   retorna verdadero en caso que un led valido
 *                  este apagado (valor de bit led 0)
 * @return false:   retorna falso si es un led invalido o
 *                  se encuentre prendido (valor de bit led 1)
 */
bool LedsIsOffNLed(uint8_t led);