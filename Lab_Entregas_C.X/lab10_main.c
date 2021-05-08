/*
 * Archivo:   lab10_main.c
 * Dispositivo: PIC16F887
 * Autor: Brandon Garrido 
 * 
 * Programa: Laboratorio 10 - modulo ccp
 * Hardware:Potenciómetros en PORTA y servos en PORTC
 * 
 * Creado: Abril 26, 2021
 * Última modificación: Abril 20, 2021
 */

//------------------------------------------------------------------------------
//                          Importación de librerías
//------------------------------------------------------------------------------    
#include <xc.h>

//------------------------------------------------------------------------------
//                          Directivas del compilador
//------------------------------------------------------------------------------
#define _XTAL_FREQ 1000000 //Para delay

//------------------------------------------------------------------------------
//                          Palabras de configuración
//------------------------------------------------------------------------------    
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT//Oscillator Selection bits(INTOSCIO 
                              //oscillator: I/O function on RA6/OSC2/CLKOUT pin, 
                              //I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled and 
                          //can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR  
                                //pin function is digital input, MCLR internally 
                                //tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code 
                                //protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code 
                                //protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit 
                                //Internal/External Switchover mode is disabled
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit 
                                //(Fail-Safe Clock Monitor is disabled)
#pragma config LVP = ON         //Low Voltage Programming Enable bit(RB3/PGM pin 
                                //has PGM function, low voltage programming 
                                //enabled)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out 
                                //Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits 
                                //(Write protection off)

//------------------------------------------------------------------------------
//                          Prototipos
//------------------------------------------------------------------------------
void setup(void);  //Configuración

//------------------------------------------------------------------------------
//                          Variables
//------------------------------------------------------------------------------

const char data = 97;
char flag = 1;


//------------------------------------------------------------------------------
//                          Loop principal
//------------------------------------------------------------------------------
void main(void) {
    setup(); //Configuración
    
       
    while(1)//loop forever
    {
        __delay_ms(300);
        
        if (PIR1bits.TXIF){
            if(flag){
                TXREG = data;
                flag = 0;
            }else {
                TXREG = 58; // realiza el muestreo en pantalla de a:0x61
                __delay_ms(300);
                TXREG = 48;
                __delay_ms(300);
                TXREG = 120;
                __delay_ms(300);
                TXREG = 54;
                __delay_ms(300);
                TXREG = 49;
                __delay_ms(300);
                TXREG = 255;
                
                flag = 1; 
            }
            
        }
    }

}

void __interrupt() isr(void){
    
    if (PIR1bits.RCIF){
        PORTB = RCREG;
    }

}

//------------------------------------------------------------------------------
//                          Configuración
//------------------------------------------------------------------------------
void setup(){
    
    //Configuracion reloj
    OSCCONbits.IRCF2 = 1; //Frecuencia a 1MHz
    OSCCONbits.IRCF1 = 0;
    OSCCONbits.IRCF0 = 0;
    OSCCONbits.SCS = 1;
    
    //Configurar entradas y salidas
    ANSELH = 0x00;//Pines digitales
    ANSEL = 0x03; //Primeros dos pines con entradas analógicas
    
    TRISB = 0x00;
    PORTB = 0x00;

    //Configurar la interrupcion
    INTCONbits.GIE = 1;  //Enable interrupciones globales
    INTCONbits.PEIE = 1; //Enable interrupciones periféricas
    PIE1bits.RCIE = 1;
    PIR1bits.RCIF = 0;
             
    
    //Configuración de TX y RX
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;
    
    BAUDCTLbits.BRG16 = 1;
    
    SPBRG = 25;
    SPBRGH = 0;
    
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
    RCSTAbits.CREN = 1;
    
    TXSTAbits.TXEN = 1;
    
    

 } 



