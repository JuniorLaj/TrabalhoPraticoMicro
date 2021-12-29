#include "lcd.h"
#include "func.h"

void exibirMensagemInicial(void) {
    lcd_cmd(L_L1);
    //unsigned char text[43] = "Pressione * para entrar ou # para Configurar";
    // exibir mensagem de forma circular
    lcd_str("Pressione * para entrar ou # para Configurar");

}

void exibirMensagemDigitarId(void){
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_cmd(L_CLR);
    // exibir mensgaem de forma circular
    lcd_str("Digite o ID e aperte *");

}

void exibirMensagemDigitarPin(void){
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Digite o PIN e aperte *");
    lcd_cmd(L_L2);
}

void exibirMensagemAcessoPermitido(void) {
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_cmd(L_CLR);
    lcd_str("Acesso permitido!");
}

void exibirMensagemAcessoNegado(void) {
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_cmd(L_CLR);
    lcd_str("Acesso Negado!");
}

void Questao1(unsigned char tecla, unsigned char modoOperacao) {
    if(tecla != VALUE_IGNORE_KEYBOARD && modoOperacao == 0) {
        exibirMensagemInicial();
    }
}

void Questao2(unsigned char tecla, unsigned char* modoOperacao, unsigned char* infoDigitada){
    if (tecla == 42 && *modoOperacao != 2) { // botão * -> Entrar
        *modoOperacao = 2;
        *infoDigitada = 1;
        exibirMensagemDigitarId();
        lcd_cmd(L_L2);
    }
}
