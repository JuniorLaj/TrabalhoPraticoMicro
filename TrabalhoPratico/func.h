

#define COUNT_MAX_ID 7
#define COUNT_MAX_PIN 7
#define VALUE_IGNORE_KEYBOARD 10


void exibirMensagemInicial(void);
void exibirMensagemDigitarId(void);
void exibirMensagemDigitarPin(void);
void exibirMensagemAcessoPermitido(void);
void exibirMensagemAcessoNegado(void);
void Questao1(unsigned char tecla, unsigned char modoOperacao);
void Questao2(unsigned char tecla, unsigned char* modoOperacao, unsigned char* infoDigitada);
