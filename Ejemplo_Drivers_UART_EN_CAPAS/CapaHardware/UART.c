// FileName:        UART.c
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

#include "Drivers/Drivers_UART.h"

void UART_INIT(void){
    UART_Inicializar();
}
