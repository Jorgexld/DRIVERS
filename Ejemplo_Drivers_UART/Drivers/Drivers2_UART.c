// FileName:        Drivers2_UART.c
// Processor:       MSP432
// Board:           MSP432P401R
// Program version: 11.1.0.00011
// Company:         Texas Instruments
// Description:     Drivers del módulo UART.
// Authors:         Eduardo Gallegos Camarena y Jorge Arnoldo Hernández Hernández.
// Updated:         06/2022
// Manual de referencia: PAG. 922 en delante

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2022 by Eduardo Gallegos Camarena & Jorge Arnoldo Hernández Hernández - TecNM /IT Chihuahua
//
// Se permite la redistribución, modificación o uso de este software en formato fuente o binario
// siempre que los archivos mantengan estos derechos de autor.
//
// Los usuarios pueden modificar esto y usarlo para aprender sobre el campo de software embebido.
// Eduardo Gallegos Camarena, Jorge Arnoldo Hernández Hernández y el TecNM /IT Chihuahua no son responsables
// del mal uso de este material.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Drivers2_UART.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Constantes de baudaje considerando 12MHz.
const uint32_t BRX[]  = {78, 39, 19, 13, 6, 3, 1};                                      // Constantes UCBRx.
const uint32_t BRFX[] = {2, 1, 8, 0, 8, 4, 10};                                         // Constantes UCBRFx.
const uint32_t BRS[]  = {0x0000, 0x0000, 0x0065, 0x0025, 0x0020, 0x0002, 0x0000};       // Constantes UCBRSx.

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_Bits_de_Datos
// - Precondiciones: Ninguna.
// - Resumen: Determina si habrá 7 u 8 bits de datos escribiendo un false o un true en el bit 12 del registro CTLW0.
// - Entradas: Bool del número de bits de datos (false para 8 bits, true para 7 bits).
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_Bits_de_Datos(bool Bits_de_Datos)
{
    if(Bits_de_Datos == false)
        BITBAND_PERI(EUSCI_A0_UART -> CTLW0, UC7BIT_OFS) = 0;

    else
        BITBAND_PERI(EUSCI_A0_UART -> CTLW0, UC7BIT_OFS) = 1;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_Tipo_de_Reloj
// - Precondiciones: Ninguna.
// - Resumen: En base al enum de tipos de reloj entrará a un switch case donde escribirá
//   EUSCI_A_CTLW0_SSEL__UCLK, EUSCI_A_CTLW0_SSEL__ACLK o EUSCI_A_CTLW0_SSEL__SMCLK en
//   EUSCI_A_CMSIS(EUSCI_A0) -> CTLW0 = (EUSCI_A_CMSIS(EUSCI_A0) -> CTLW0 & ~UCSSEL_3) según sea el caso.
// - Entradas: Enum con las 3 opciones posibles de reloj.
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_Tipo_de_Reloj(Tipo_de_Reloj Tipo)
{
    switch(Tipo)
    {
        case U_CLK:
            BITBAND_PERI(EUSCI_A0_UART -> CTLW0, 7) = 0;
            BITBAND_PERI(EUSCI_A0_UART -> CTLW0, 6) = 0;
            BITBAND_PERI(EUSCI_A0_UART -> CTLW0, EUSCI_A_CTLW0_SSEL__UCLK) = 1;
            break;

        case A_CLK:
            BITBAND_PERI(EUSCI_A0_UART -> CTLW0, 7) = 0;
            BITBAND_PERI(EUSCI_A0_UART -> CTLW0, 6) = 1;
            BITBAND_PERI(EUSCI_A0_UART -> CTLW0, EUSCI_A_CTLW0_SSEL__ACLK) = 1;
            break;

        case SM_CLK:
            BITBAND_PERI(EUSCI_A0_UART -> CTLW0, 7) = 1;
            BITBAND_PERI(EUSCI_A0_UART -> CTLW0, 6) = 0;
            BITBAND_PERI(EUSCI_A0_UART -> CTLW0, EUSCI_A_CTLW0_SSEL__SMCLK) = 1;
            break;

        default:
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_Sincronia
// - Precondiciones: Ninguna.
// - Resumen: Determina si el modo será síncrono o asíncrono escribiendo un false o un true en el bit 8 del registro CTLW0.
// - Entradas: Bool que determinará si el modo será síncrono (true) o asíncrono (false).
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_Sincronia(bool Sincronia)
{
    if(Sincronia == false)
        BITBAND_PERI(EUSCI_A0_UART -> CTLW0, EUSCI_A_CTLW0_SYNC_OFS) = 0;

    else
        BITBAND_PERI(EUSCI_A0_UART -> CTLW0, EUSCI_A_CTLW0_SYNC_OFS) = 1;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_Interrupcion_CBreak
// - Precondiciones: Ninguna.
// - Resumen: Habilita o mantiene desactivada una interrupción por recibir caracteres de break escribiendo un
// - false o un true en el bit 4 del registro CTLW0.
// - Entradas: Bool de "break character". Interrupcion activada (true), desactivada (false).
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_Interrupcion_CBreak(bool Interrupcion_CBreak)
{
    if(Interrupcion_CBreak == false)
        BITBAND_PERI(EUSCI_A0_UART -> CTLW0, EUSCI_A_CTLW0_BRKIE_OFS) = 0;

    else
        BITBAND_PERI(EUSCI_A0_UART -> CTLW0, EUSCI_A_CTLW0_BRKIE_OFS) = 1;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_Interrupcion_CErroneos
// - Precondiciones: Ninguna.
// - Resumen: Habilita o mantiene desactivada una interrupción por recibir caracteres erróneos escribiendo un
// - false o un true en el bit 5 del registro CTLW0.
// - Entradas: Bool de "erroneous-character". Interrupcion activada (true), desactivada (false).
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_Interrupcion_CErroneos(bool Interrupcion_CErroneos)
{
    if(Interrupcion_CErroneos == false)
        BITBAND_PERI(EUSCI_A0_UART -> CTLW0, EUSCI_A_CTLW0_RXEIE_OFS) = 0;

    else
        BITBAND_PERI(EUSCI_A0_UART -> CTLW0, EUSCI_A_CTLW0_RXEIE_OFS) = 1;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_Sobremuestreo
// - Precondiciones: Ninguna.
// - Resumen: Habilita o mantiene desactivado el sobremuestreo escribiendo un false o un true en el bit 0
// - del registro MCTLW.
// - Entradas: Bool de sobremuestreo que indicará si habrá (true) o no sobremuestreo (false).
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_Sobremuestreo(bool Sobremuestreo)
{
    if(Sobremuestreo == false)
        BITBAND_PERI(EUSCI_A0_UART -> MCTLW, EUSCI_A_MCTLW_OS16_OFS) = 0;

    else
        BITBAND_PERI(EUSCI_A0_UART -> MCTLW, EUSCI_A_MCTLW_OS16_OFS) = 1;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_Paridad
// - Precondiciones: Ninguna.
// - Resumen: Determina el tipo de Paridad, sin Paridad, par o impar mediante un char de un enum.
// - Entradas: Char "Paridad" del enum Paridad del archivo header que indique el tipo de Paridad.
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_Paridad(char Paridad)
{
    if(Paridad > 0)
    {
        BITBAND_PERI(EUSCI_A0_UART -> CTLW0, UCPEN_OFS) = 1;
        BITBAND_PERI(EUSCI_A0_UART -> CTLW0, UCPAR_OFS) = Paridad-1;
    }

    else
        BITBAND_PERI(EUSCI_A0_UART -> CTLW0, UCPEN_OFS) = 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_Bits_de_Paro
// - Precondiciones: Ninguna.
// - Resumen: Determina si habrá uno o dos bits de paro escribiendo un false o un true en el bit 11 del
// - del registro CTLW0.
// - Entradas: Bool de Bits_de_Paro encargado de mandar un true o false para indicar en número
//   de bits de paro.
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_Bits_de_Paro(bool Bits_de_Paro)
{
    if(Bits_de_Paro == false)
        BITBAND_PERI(EUSCI_A0_UART -> CTLW0, UCSPB_OFS) = 0;

    else
        BITBAND_PERI(EUSCI_A0_UART -> CTLW0, UCSPB_OFS) = 1;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_Direccion_de_Transmision
// - Precondiciones: Ninguna.
// - Resumen: Determina si la dirección de transmisión sera MSB o LSB escribiendo un true o un false
// - en el bit 13 del registro CTLW0.
// - Entradas: Bool de direccion de transmision que seleccionará MSB (true) o LSB (false).
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_Direccion_de_Transmision(bool Direccion_de_Transmision)
{
    if(Direccion_de_Transmision == false)
        BITBAND_PERI(EUSCI_A0_UART -> CTLW0, UCMSB_OFS) = 0;

    else
        BITBAND_PERI(EUSCI_A0_UART -> CTLW0, UCMSB_OFS) = 1;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_Pines_TX_RX
// - Precondiciones: Ninguna.
// - Resumen: Establece sobre que pines de que puerto se transmitirá, en este caso se usa
// - el puerto A. Dirección (0x0004), Select 0 (0x000A) y Select 1 (0x000C).
// - Entradas: Puerto seleccionado (+OFS_PAxxx) + pines
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_Pines_TX_RX(uint32_t Puerto_Seleccionado, uint32_t Pines_Seleccionados)
{
    HWREG16(Puerto_Seleccionado + OFS_PADIR) &= ~(Pines_Seleccionados);
    HWREG16(Puerto_Seleccionado + OFS_PASEL0) |= (Pines_Seleccionados);
    HWREG16(Puerto_Seleccionado + OFS_PASEL1) &= ~(Pines_Seleccionados);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_Baudaje
// - Precondiciones: Ninguna.
// - Resumen: Selecciona el baudaje deseado y en base a ello rellena el BRX, BRS y BRFX con
//   los valores adecuados según elñ baudaje del enum.
// - Entradas: Int que seleccionará la opcion deseada dentro de un enum en el archivo header.
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_Baudaje(uint8_t Seleccion)
{
    if(Seleccion < Numero_de_Baudajes)
    {
        EUSCI_A0_UART-> BRW = BRX[Seleccion];
        EUSCI_A0_UART-> MCTLW = ((BRS[Seleccion] << 8)  + (BRFX[Seleccion] << 4) +  EUSCI_A_MCTLW_OS16);
    }
}

// BRS[Seleccion] --> UCBRSx --> CORRIMIENTO DE 8 BITS --> SEGUNDO ESTADO DE MODULACION
// BRFX[Seleccion] --> CORRIMIENTO DE 4 BITS --> PRIMER ESTADO DE MODULACION

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_Inicializar
// - Precondiciones: Ninguna.
// - Resumen: Inicializa el módulo mediante la escritura en el Software reset enable.
//   Configura la UART para el uso futuro.
// - Entradas: Ninguna.
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_Inicializar(){

    UART_Deshabilitar(MAIN_UART); // Llamada a la funcion UART_Deshabilitar

    /* Forma genérica para limpiar interrupciones, sleep, y otros registros inicialmente. */
//    EUSCI_A0_UART-> CTLW0 = (EUSCI_A0_UART-> CTLW0 & ~( UCRXEIE | UCBRKIE | UCDORM | UCTXADDR | UCTXBRK)) | EUSCI_A_CTLW0_MODE_0;

    BITBAND_PERI(EUSCI_A0_UART -> CTLW0, UCRXEIE_OFS) = 0;
    BITBAND_PERI(EUSCI_A0_UART -> CTLW0, UCBRKIE_OFS) = 0;
    BITBAND_PERI(EUSCI_A0_UART -> CTLW0, UCDORM_OFS) = 0;
    BITBAND_PERI(EUSCI_A0_UART -> CTLW0, UCTXADDR_OFS) = 0;
    BITBAND_PERI(EUSCI_A0_UART -> CTLW0, UCTXBRK_OFS) = 0;

    BITBAND_PERI(EUSCI_A0_UART -> CTLW0, 10) = 0;
    BITBAND_PERI(EUSCI_A0_UART -> CTLW0, 9) = 0;

    UART_Pines_TX_RX(Puerto_1, Pines_Puerto_1); // A la función Pines_TX_RX se le mandará de parámetros Puerto_1, el cual
                                                // esta definido con (0x40004C00) y Pines_Puerto_1 (0x0001<< 2 | 0x0001 << 3)
                                                // para utilizar el puerto 1, pines 2 y 3.

    UART_Tipo_de_Reloj(SM_CLK); // A la función UARTR_Tipo_de_Reloj se le manda un SMCLK o un 2 según su posicion en el enum.

    UART_Direccion_de_Transmision(LSB_PRIMERO); // A la función UARTR_Direccion_de_Transmision se le manda un LSB_PRIMERO, el
                                                // cual esta definido como 0.

    UART_Bits_de_Paro(UN_BIT_DE_PARO); // A la función UART_Bits_de_Paro se le manda un UN_BIT_DE_PARO, el cual esta definido
                                       // como 0.

    UART_Paridad(SIN_PARIDAD); // A la funcion UART_Paridad se le manda un SIN_PARIDAD, el cual según su órden en el enum
                                 // está definido con un 0.


    UART_Baudaje((uint8_t) Baudaje_115200); // A la funcion UART_Baudaje se le manda un Baudaje_115200, el cual según su órden
                                            // en el enum está definido con un 4, lo cual servirá para los arreglos declarados
                                            // de BRX, BRS y BRFX.

    UART_Bits_de_Datos(OCHO_BITS); // A la funcion UART_Bits_de_Datos se le manda un SIN_PARIDAD, el cual está definido como
                                   // un 0.

    UART_Sincronia(ASINCRONO); // A la funcion UART_Sincronia se le manda un ASINCRONO, el cual está definido con un 0.

    UART_Sobremuestreo(CON_SOBREMUESTREO); // A la funcion UART_Sobremuestreo se le manda un CON_SOBREMUESTREO, el cual está
                                           // definido con un 1.

    UART_Interrupcion_CBreak(SIN_INTERRUPCION); // A la funcion UART_Interrupcion_CBreak se le manda un SIN_INTERRUPCION, el
                                                // cual esta definido con un 0.

    UART_Interrupcion_CErroneos(SIN_INTERRUPCION); // A la funcion UART_Interrupcion_CErroneo se le manda un SIN_INTERRUPCION,
                                                   // el cual esta definido con un 0.

    UART_Habilitar(MAIN_UART); // Llamada a la funcion UART_Habilitar

}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_Inicializar2
// - Precondiciones: Ninguna.
// - Resumen: Inicializa el módulo mediante la escritura en el Software reset enable.
//   Configura la UART para el uso futuro escribiendo directamente en el registro.
// - Entradas: Ninguna.
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_Inicilizar2(){ // SE PUEDE CON PARAMETROS SOLO SI SE VA A ESCRIBIR DE UNO POR UNO CON BITBANDING O &=~ / |=

    EUSCI_A0_UART -> CTLW0 &= 0x0001; // REVISAR EL MANUAL Y REGISTROS PARA VER QUE SE PONE EN CERO Y QUE EN UNO.
                                      // Habilita solamente el software reset para poder hacer cambios en los campos del registro CTLW0.
                                      // Valor en binario: 0000000000000001.

    EUSCI_A0_UART -> CTLW0 &= 0x0081; // REVISAR EL MANUAL Y REGISTROS PARA VER QUE SE PONE EN CERO Y QUE EN UNO
                                      // Modifica los campos del registro CTLW0 mientras el software reset está en 1.
                                      // Valor en binario: 000000010000001.

    EUSCI_A0_UART -> CTLW0 &= 0x0080; // REVISAR EL MANUAL Y REGISTROS PARA VER QUE SE PONE EN CERO Y QUE EN UNO
                                      // Una vez que se han modificaco los campos deseados del registro CTLW0 pone el software reset en 0.
                                      // Valor en binario: 000000010000000.
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_Habilitar
// - Precondiciones: UART_Inicializar
// - Resumen: Habilita el módulo UART poniendo un 0 en el Software reset enable.
// - Entradas: uint32_t Modulo_UART. (Ejem EUSCI_A0 o EUSCI_A0_BASE).
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_Habilitar(uint32_t Modulo_UART)
{
    BITBAND_PERI(EUSCI_A0_UART -> CTLW0, EUSCI_A_CTLW0_SWRST_OFS) = 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_Desabilitar
// - Precondiciones: UART_Inicializar
// - Resumen: Deshabilita el módulo UART poniendo un 1 en el Software reset enable.
// - Entradas: uint32_t Modulo_UART. (Ejem EUSCI_A0 o EUSCI_A0_BASE).
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_Deshabilitar(uint32_t Modulo_UART)
{
    BITBAND_PERI(EUSCI_A0_UART -> CTLW0, EUSCI_A_CTLW0_SWRST_OFS) = 1;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_Enviar_Byte
// - Precondiciones: UART_Inicializar
// - Resumen: Realiza en envío de un solo byte.
// - Entradas: uint32_t Modulo_UART, char caracter
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_Enviar_Byte(uint32_t Modulo_UART, char caracter)
{
    // Funciona mediante interrupciones de la bandera de tránsito para la trasmisión.
    if(!BITBAND_PERI(((registros_uart *) Modulo_UART) -> IE, EUSCI_A_IE_TXIE_OFS))

        // Mientras no se desactive la bandera de tránsito, seguirá corriendo.
        while (!BITBAND_PERI(((registros_uart *) Modulo_UART) -> IFG, EUSCI_A_IFG_TXIFG_OFS));

    EUSCI_A0_UART -> TXBUF = caracter;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// - Funcion: UART_putsf
// - Precondiciones: UART_Inicializar
// - Resumen: Envío concatenado de datos byte a byte usando un apun6tador.
// - Entradas: uint32_t Modulo_UART, char *cadena_caracteres
// - Salidas: Ninguna.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void UART_putsf(uint32_t Modulo_UART, char *cadena_caracteres)
{
    char caracter;

    while (caracter = *cadena_caracteres++) // while mientras el apuntador va cambiando su valor para leer todos los caracteres.
        UART_Enviar_Byte(Modulo_UART, caracter);
}
