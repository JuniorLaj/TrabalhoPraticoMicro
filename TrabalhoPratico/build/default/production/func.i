# 1 "func.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "D:/program files/Microchip/MPLABX/v5.50/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "func.c" 2
# 1 "./lcd.h" 1
# 35 "./lcd.h"
void lcd_init(void);
void lcd_cmd(unsigned char val);
void lcd_dat(unsigned char val);
void lcd_str(const char* str);
# 1 "func.c" 2

# 1 "./func.h" 1







void exibirMensagemInicial(void);
void exibirMensagemDigitarId(void);
void exibirMensagemDigitarPin(void);
void exibirMensagemAcessoPermitido(void);
void exibirMensagemAcessoNegado(void);
void Questao1(unsigned char tecla, unsigned char modoOperacao);
void Questao2(unsigned char tecla, unsigned char* modoOperacao, unsigned char* infoDigitada);
# 2 "func.c" 2


void exibirMensagemInicial(void) {
    lcd_cmd(0x80);


    lcd_str("Pressione * para entrar ou # para Configurar");

}

void exibirMensagemDigitarId(void){
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_cmd(0x01);

    lcd_str("Digite o ID e aperte #");

}

void exibirMensagemDigitarPin(void){
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_str("Digite o PIN e aperte #");
    lcd_cmd(0xC0);
}

void exibirMensagemAcessoPermitido(void) {
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_cmd(0x01);
    lcd_str("Acesso permitido!");
}

void exibirMensagemAcessoNegado(void) {
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_cmd(0x01);
    lcd_str("Acesso Negado!");
}

void Questao1(unsigned char tecla, unsigned char modoOperacao) {
    if(tecla != 10 && modoOperacao == 0) {
        exibirMensagemInicial();
    }
}

void Questao2(unsigned char tecla, unsigned char* modoOperacao, unsigned char* infoDigitada){
    if (tecla == 42 && *modoOperacao != 2) {
        *modoOperacao = 2;
        *infoDigitada = 1;
        exibirMensagemDigitarId();
        lcd_cmd(0xC0);
    }
}
