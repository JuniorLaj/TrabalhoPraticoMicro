/*
 * File:   main.c
 * Author: junio
 *
 * Created on 12 de Dezembro de 2021, 12:01
 */


// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000 // 4MHz
#include "lcd.h"
#include "teclado.h"
#include "func.h"


void main(void) {
    unsigned char modoOperacao = 0; // 0 -> sem operação 1 -> Login 2 -> Cadastro
    unsigned char tecla;
    unsigned char infoDigitada = 0; // 0 -> login 1 -> senha
    unsigned char simbolosId[COUNT_MAX_ID];
    unsigned char countSimbolosId = 0;
    unsigned char simbolosPin[COUNT_MAX_PIN];
    unsigned char countSimbolosPin = 0;
    unsigned char initTimerDisplayMessageQ3 = 0; // para iniciar a contagem no timer 0 
    PCONbits.OSCF = 1;

    CMCON = 0x07;
    TRISA = 0x30;
    TRISB = 0xE7;

    PORTA = 0xFE;
    PORTB = 0x00;

    lcd_init();
    lcd_cmd(L_CLR);
    lcd_cmd(L_L2);
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);

    
    // LINHA 0 DA EEPROM utilizada para cabeçalho
    unsigned char countRecordedAccesses = eeprom_read(0);
    
    // LIMPANDO TODAS AS POSIÇÕES NÃO UTILIZADS DA EEPROM PARA GARANTIR CONTEÚDO
    unsigned char i;
    for(i=countRecordedAccesses; i<0xFF; i++){
        unsigned char j;
        for(j=0; j<8; j++){
            eeprom_write(i*16 + j,0x00);
        }
    }
    /* TO DO:
        LOGIN (José)
           * Testar implementação feita para Q4
           * Timer 0 após exibição da mensagem de sucesso/falha no login
           * Implementar conclusão após terminar o LOGIN (setar bits, etc..)
           * Implementar Exibição dos textos em loop
        CADASTRO (Renan)
           * Implementar entrada dos dados
           * Incrementar contador de linha utilizada da memória (countRecordedAccesses) e gravar na EEPROM o novo valor
           * Setar bit de contagem de tempo (initTimerDisplayMessageQ3) 
           * Implementar conclusão após terminar o CADASTRO (setar bits, etc..)

        EXTRAS 
           * Implementar WATCHDOG 
           * Implementar modo Sleep (?)
    */
    
    while (1) {
        tecla = tc_tecla(5000); 
        //Q1
        Questao1(tecla, modoOperacao);
        // Q2
        Questao2(tecla, &modoOperacao, &infoDigitada);
        
        //Q3
        //alternar digitação de ID para PIN e Verificar cadastro na EEPROM
        if(tecla == 35 && modoOperacao == 2) {
        //Alternar digitação de ID para PIN
            if(infoDigitada == 1){
                lcd_cmd(L_L2);
                lcd_cmd(L_CLR);
                infoDigitada = 2;
                exibirMensagemDigitarPin();
            } else if(infoDigitada == 2){
                // Setando ox00 no restante dos vetores de simbolos para garntir conteúdo
                unsigned char aux = 0;
                for(aux=countSimbolosId; aux<COUNT_MAX_ID; aux++){
                    simbolosId[aux] = 0x00;
                }
                for(aux=countSimbolosId; aux<COUNT_MAX_PIN; aux++){
                    simbolosPin[aux] = 0x00;
                }
                
                // Q4 - Iniciando login
                unsigned char i = 0; // bit de detecção de acesso correto
                unsigned char j; // contador de linha da EEPROM 
                for(j=1; j<=countRecordedAccesses; j++){
                    i = 0; 
                    unsigned char k = 0; // contador de coluna da EEPROM
                    for(k=0; k<8; k++) {
                        if(eeprom_read(j*16 + k) != simbolosId[k] ||
                                eeprom_read(8 + (j*16 + k)) != simbolosPin[k]) {
                            i = 1;
                            break;
                        }
                    }
                    if(!i){
                        // senha correta
                        exibirMensagemAcessoPermitido();
                    }
                }
                if(i) {
                    // login incorreto
                    exibirMensagemAcessoNegado();
                }
                initTimerDisplayMessageQ3 = 1; 
            }
        }
        
        // digitar Id e PIN
        if (tecla >=0 && tecla <=9) {
            // digitar ID
            if(infoDigitada == 1){
                if(countSimbolosId != COUNT_MAX_ID) { // terminei de digitar id
                    simbolosId[countSimbolosId] = tecla;
                    lcd_dat(0x2A);
                    countSimbolosId++;
                }
            // digitar PIN
            } else if (infoDigitada == 2){
                if(countSimbolosPin != COUNT_MAX_PIN) {
                    simbolosPin[countSimbolosPin] = tecla;
                    lcd_dat(0x2A);
                    countSimbolosPin++;
                }
            }
        }        
    }
}

