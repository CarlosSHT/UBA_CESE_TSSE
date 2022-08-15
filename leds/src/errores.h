#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum gravedad_e
    {
        ERROR,
        ALERTA,
        INFORMACION,
        DEPURACION
    } gravedad_t;

    typedef void (*registro_errores_t)(gravedad_t gravedad, const char *funcion, int linea, const char *mensaje, ...);

    void RegistrarMensaje(gravedad_t gravedad, const char *funcion, int linea, const char *mensaje, ...);

#ifdef __cplusplus
}
#endif
