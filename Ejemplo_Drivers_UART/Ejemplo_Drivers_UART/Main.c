// FileName:        Main.c
// Dependencies:    Drivers_UART.h
// Processor:       MSP432
// Board:           MSP432P401R
// Program version: 11.1.0.00011
// Company:         Texas Instruments
// Description:     Drivers del módulo UART.
// Authors:         Eduardo Gallegos Camarena y Jorge Arnoldo Hernández Hernández.
// Updated:         06/2022

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

#include "Drivers/Drivers_UART.h"

int i=0;

int main(void)
{
    UART_Inicializar();

    while(1){
        UART_putsf(MAIN_UART,"Hola desde los drivers de la UART\n\r");

        for(i=0; i<3000000; i++){}
    }
}
