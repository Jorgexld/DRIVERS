// FileName:        Drivers_UART.h
// Dependencies:    Drivers_UART.c
// Processor:       MSP432
// Board:           MSP432P401R
// Program version: 11.1.0.00011
// Company:         Texas Instruments
// Description:     Drivers del m�dulo UART.
// Authors:         Eduardo Gallegos Camarena y Jorge Arnoldo Hern�ndez Hern�ndez.
// Updated:         06/2022

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2022 by Eduardo Gallegos Camarena & Jorge Arnoldo Hern�ndez Hern�ndez - TecNM /IT Chihuahua
//
// Se permite la redistribuci�n, modificaci�n o uso de este software en formato fuente o binario
// siempre que los archivos mantengan estos derechos de autor.
//
// Los usuarios pueden modificar esto y usarlo para aprender sobre el campo de software embebido.
// Eduardo Gallegos Camarena, Jorge Arnoldo Hern�ndez Hern�ndez y el TecNM /IT Chihuahua no son responsables
// del mal uso de este material.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#ifndef DRIVERS_DRIVERS_UART_H_
#define DRIVERS_DRIVERS_UART_H_

///////////////////////////////////////////////////////////////////////////////
// DEFINICIONES ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Tipo de reloj.
#define UCLK 0
#define ACLK 1
#define SMCLK 2

// Bits de datos.
#define OCHO_BITS 0
#define SIETE_BITS 1

// Direcci�n de transmisi�n.
#define LSB_PRIMERO 0
#define MSB_PRIMERO 1

// Bits de paro.
#define UN_BIT_DE_PARO 0
#define DOS_BITS_DE_PARO 1

// Sobremuestreo.
#define SIN_SOBREMUESTREO 0
#define CON_SOBREMUESTREO 1

// Interrupciones.
#define SIN_INTERRUPCION 0
#define CON_INTERRUPCION 1

// Sincron�a.
#define ASINCRONO 0
#define SINCRONO 1

#define Numero_de_Baudajes 7

/* Uso de pines UART 1.1 y 1.2. */
#define Pines_Puerto_1 (0x0001 << 2 | 0x0001 << 3)
#define Puerto_1 (0x40004C00)

///////////////////////////////////////////////////////////////////////////////
// MACROS DE FUNCIONES ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#define EUSCI_A_CMSIS(x) ((EUSCI_A_Type *) x)
#define EUSCI_B_CMSIS(x) ((EUSCI_B_Type *) x)

///////////////////////////////////////////////////////////////////////////////
// ENUMS PARA LAS OPCIONES DE BAUDAJE Y PARIEDAD //////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Enum que habilita los posibles tipos de reloj como opciones.
typedef enum
{
   U_CLK = 0,
   A_CLK,
   SM_CLK
}  Tipo_de_Reloj;

// Enum que habilita los posibles baudajes como opciones (CONSIDERANDO 12MHz).
typedef enum
{
   Baudaje_9600 = 0,
   Baudaje_19200,
   Baudaje_38400,
   Baudaje_57600,
   Baudaje_115200,
   Baudaje_230400,
   Baudaje_460800
}  Baudaje;

// Enum que habilita las posibles pariedades como opciones.
typedef enum
{
   SIN_PARIEDAD = 0,
   IMPAR,
   PAR
} Pariedad;

///////////////////////////////////////////////////////////////////////////////
// CONFIGURACION DEL MODULO ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Determina si habr� 7 u 8 bits de datos.
void UART_Bits_de_Datos(bool Bits_de_Datos);

// Determina cual reloj se utilizar� de las psoibles 3 opciones.
void UART_Tipo_de_Reloj(Tipo_de_Reloj Tipo);

// Determina si el modo de transmisi�n ser� s�ncrono o as�ncrono.
void UART_Sincronia(bool Sincronia);

// Representa la interrupci�n por car�cteres break.
void UART_Interrupcion_CBreak(bool Interrupcion_CBreak);

// Representa la interrupci�n por car�cteres err�neos.
void UART_Interrupcion_CErroneos(bool Interrupcion_CErroneos);

// Determina si habr� o no un sobremuestreo.
void UART_Sobremuestreo(bool Sobremuestreo);

// Determina la paridad.
void UART_Pariedad(char Pariedad);

// Determina si habr� uno o dos bits de paro en la comunicaci�n.
void UART_Bits_de_Paro(bool Bits_de_Paro);

// Determina la direcci�n de transmisi�n (MSB o LSB).
void UART_Direccion_de_Transmision(bool Direccion_de_Transmision);

// Establece los pines para la transmisi�n y recepci�n de datos.
void UART_Pines_TX_RX(uint32_t Puerto_Seleccionado, uint32_t Pines_Seleccionados);

// Determina el baudaje de entre las posibles 7 opciones para 12MHz.
void UART_Baudaje(uint8_t Seleccion);

// Inicializaci�n y configuraci�n de la UART.
void UART_Inicializar(void);

///////////////////////////////////////////////////////////////////////////////
// USO DEL MODULO /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Habilita el m�dulo UART mandando un 0 al software reset enable denominado EUSCI_A_CTLW0_SWRST
void UART_Habilitar(uint32_t Modulo_UART);

// Deshabilita el m�dulo UART mandando un 1 al software reset enable denominado EUSCI_A_CTLW0_SWRST
void UART_Deshabilitar(uint32_t Modulo_UART);

// Se encarga de enviar solamente un byte.
void UART_Enviar_Byte(uint32_t Modulo_UART, char c);

// Se encarga de enviar una cadena de caracteres.
void UART_putsf(uint32_t Modulo_UART, char *s);

///////////////////////////////////////////////////////////////////////////////

#endif /* DRIVERS_DRIVERS_UART_H_ */
