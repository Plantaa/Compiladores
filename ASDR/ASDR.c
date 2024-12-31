#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{	
    AND,
    BEGIN,
    BOOLEAN,
    CHAR,
    DO,
    ELSE,
    END,
    FALSE,
    IF,
    MOD,
    NOT,
    NUMBER,
    OR,
    PROGRAM,
    READ,
    SET,
    THEN,
    TO,
    TRUE,
    WHILE,
    WRITE,
	ABRE_PAR,
	FECHA_PAR,
	PONTO,
	PONTO_VIRGULA,
	VIRGULA,
	SUBTRACAO,
	ADICAO,
	DIVISAO,
	MULTIPLICACAO,
	ME,
	MEI,
	IG,
	DI,
	MA,
	MAI,
	NOVA_LINHA,
	ASCII,
	COMENTARIO_VARIAS_LINHAS,
	COMENTARIO_UMA_LINHA,
	COMENTARIO,
	EXPONENCIAL,
	NUMERO,
	CARACTERE,
	ERRO,
	EOS,
	IDENTIFICADOR
	
}TAtomo;

typedef struct{
    TAtomo atomo;
    int linha;
    int atributo_numero;
    char atributo_ID[15];
}TInfoAtomo;

char *msgErro[] = {"AND","BEGIN","BOOLEAN","CHAR","DO","ELSE","END","FALSE","IF",
				   "MOD","NOT","NUMBER","OR","PROGRAM","READ","SET","THAN","TO",
				   "TRUE","WHILE","WRITE","ABRE_PAR","FECHA_PAR","PONTO","PONTO_VIRGULA",
				   "VIRGULA","SUBTRACAO","ADICAO","DIVISAO","MULTIPLICACAO","ME","MEI",
				   "IG","DI","MA","MAI","NOVA_LINHA","ASCII","COMENTARIO_VARIAS_LINHAS",
				   "COMENTARIO_UMA_LINHA","COMENTARIO","EXPONENCIAL","NUMERO","CARACTERE",
				   "ERRO","EOS","IDENTIFICADOR"};

/*Variaveis globais*/
TAtomo  lookahead;
TInfoAtomo info_atomo;
int linha = 1;
char *palavra;

char *leArquivo(char *nomeArquivo);

/*Funcoes do Analisador Lexico*/
TInfoAtomo obter_atomo();
TAtomo reconhece_comentario_varias_linhas();
void reconhece_id(TInfoAtomo *infoAtomo);
void reconhece_num(TInfoAtomo *infoAtomo);

/*Funcoes do Analisador Sintatico*/
void consome( TAtomo atomo );
void programa();
void bloco();
void declaracao_de_variaveis();
void tipo();
void variaveis();
void comando_composto();
void comando();
void comando_atribuicao();
void comando_condicional();
void comando_repeticao();
void comando_entrada();
void comando_saida();
void expressao();
void expressao_simples();
void operador_simples();
void termo();
void operador_termo();
void fator();

int main(void){
	palavra = leArquivo("entrada.txt");
	
    info_atomo=obter_atomo();
    lookahead = info_atomo.atomo;
    
    printf("Analisando o programa:\n%s",palavra);
    
    programa();
    
    consome(EOS);
    printf("\nAnalise terminada com Sucesso\n");
    
    return 0;
}

/* <programa>::= PROGRAM IDENTIFICADOR ";" <bloco> "." */
void programa(){
	while(lookahead == COMENTARIO){
		consome(COMENTARIO);
	}
	consome(PROGRAM);
	consome(IDENTIFICADOR);
	consome(PONTO_VIRGULA);
	bloco();
	consome(PONTO);
}

void bloco(){
	declaracao_de_variaveis();
	comando_composto();
}

void declaracao_de_variaveis(){
	tipo();
	variaveis();
	if(lookahead == NUMBER || lookahead == CHAR || lookahead == BOOLEAN){
		declaracao_de_variaveis();
	}
	consome(PONTO_VIRGULA);
}

void tipo(){
	if(lookahead == NUMBER || lookahead == CHAR || lookahead == BOOLEAN){
		consome(lookahead);
	}
}

void variaveis(){
	consome(IDENTIFICADOR);
	while(lookahead == VIRGULA){
		consome(VIRGULA);
		consome(IDENTIFICADOR);
	}
}

void comando_composto(){
	consome(BEGIN);
	comando();
	while(lookahead == PONTO_VIRGULA){
		consome(PONTO_VIRGULA);
		comando();
	}
	consome(END);
}

void comando(){
	switch(lookahead){
		case SET:
			comando_atribuicao();
			break;
		case IF:
			comando_condicional();
			break;
		case WHILE:
			comando_repeticao();
			break;
		case READ:
			comando_entrada();
			break;
		case WRITE:
			comando_saida();
			break;
		case BEGIN:
			comando_composto();
			break;
		default:
			consome(ERRO);
			break;
	}
}

void comando_atribuicao(){
	consome(SET);
	consome(IDENTIFICADOR);
	consome(TO);
	expressao();
}

void comando_condicional(){
	consome(IF);
	consome(ABRE_PAR);
	expressao();
	consome(FECHA_PAR);
	consome(THEN);
	comando();
	if(lookahead == ELSE){
		consome(ELSE);
		comando();
	}
}

void comando_repeticao(){
	consome(WHILE);
	consome(ABRE_PAR);
	expressao();
	consome(FECHA_PAR);
	consome(DO);
	comando();
}

void comando_entrada(){
	consome(READ);
	consome(ABRE_PAR);
	variaveis();
	consome(FECHA_PAR);

}

void comando_saida(){
	consome(WRITE);
	consome(ABRE_PAR);
	expressao();
	while(lookahead == VIRGULA){
		consome(VIRGULA);
		expressao();
	}
	consome(FECHA_PAR);
}

void expressao(){
	expressao_simples();
	if(lookahead == ME || lookahead == MEI || lookahead == IG
	|| lookahead == DI || lookahead == MA  || lookahead == MAI){
		consome(lookahead);
		expressao_simples();
	}
}

void expressao_simples(){
	if(lookahead == ADICAO || lookahead == SUBTRACAO){
		consome(lookahead);
	}
	termo();
	while(lookahead == ADICAO || lookahead == SUBTRACAO || lookahead == OR){
		consome(lookahead);
		termo();
	}
}

void operador_simples(){
	if(lookahead == ADICAO || lookahead == SUBTRACAO || lookahead == OR){
		consome(lookahead);
	}
}

void termo(){
	fator();
	while(lookahead == MULTIPLICACAO || lookahead == DIVISAO
	   || lookahead == MOD || lookahead == AND){
	   	operador_termo();
	   	fator();
	   }
}

void operador_termo(){
	if(lookahead == MULTIPLICACAO || lookahead == DIVISAO
	   || lookahead == MOD || lookahead == AND){
	   	consome(lookahead);
	   }
}

void fator(){
	switch(lookahead){
		case IDENTIFICADOR:
			consome(IDENTIFICADOR);
			break;
		case NUMERO:
			consome(NUMERO);
			break;
		case CARACTERE:
			consome(CARACTERE);
			break;
		case TRUE:
			consome(TRUE);
			break;
		case FALSE:
			consome(FALSE);
			break;
		case NOT:
			consome(NOT);
			fator();
			break;
		case ABRE_PAR:
			consome(ABRE_PAR);
			expressao();
			consome(FECHA_PAR);
			break;
		default:
			consome(ERRO);
			break;
	}
}

void consome( TAtomo atomo ){
    if( lookahead == atomo || lookahead == COMENTARIO){
        info_atomo=obter_atomo();
        lookahead = info_atomo.atomo;
        while(lookahead == COMENTARIO)
        {
        	info_atomo=obter_atomo();
        	lookahead = info_atomo.atomo;
		}
        if( lookahead == ERRO){
            printf("\nerro lexico na linha %d\n",info_atomo.linha);
            exit(1);
        }
    }
    else{
        printf("\nerro sintatico %d: esperado [%s] encontrado [%s]\n",info_atomo.linha,msgErro[atomo],msgErro[lookahead]);
        exit(1);
    }
}

TInfoAtomo obter_atomo(){
    TInfoAtomo infoAtomo;
    infoAtomo.atomo = ERRO;
    
/*
*	Elimina os espacos em branco
*/
    while(isspace(*palavra)){
        if(*palavra == '\n')
            linha++;
        palavra++;	
    }
    infoAtomo.linha = linha;

/*
*	Reconhecimento de identificador
*/
	if(isalpha(*palavra)){
		reconhece_id(&infoAtomo);
	}
	
	else if((*palavra) == '/' && *(palavra+1) == '/'){
		infoAtomo.atomo = COMENTARIO;
		while(*palavra != '\n'){
			palavra++;
		}
	}
	
/*
*	Reconhecimento de atomos simples
*/
	else if((*palavra) == '('){
		infoAtomo.atomo = ABRE_PAR;
		palavra++;
	}
	else if((*palavra) == ')'){
		infoAtomo.atomo = FECHA_PAR;
		palavra++;
	}
	else if((*palavra) == '.'){
		infoAtomo.atomo = PONTO;
		palavra++;
	}
	else if((*palavra) == ';'){
		infoAtomo.atomo = PONTO_VIRGULA;
		palavra++;
	}
	else if((*palavra) == ','){
		infoAtomo.atomo = VIRGULA;
		palavra++;
	}

/*
*	Reconhecimento de operadores aritmeticos
*/
	else if((*palavra) == '-'){
		infoAtomo.atomo = SUBTRACAO;
		palavra++;
	}
	else if((*palavra) == '+'){
		infoAtomo.atomo = ADICAO;
		palavra++;
	}
	else if((*palavra) == '/'){
		infoAtomo.atomo = DIVISAO;
		palavra++;
	}
	else if((*palavra) == '*'){
		infoAtomo.atomo = MULTIPLICACAO;
		palavra++;
	}

/*
*	Reconhecimento de operadores relacionais
*/
	else if((*palavra) == '<'){
		infoAtomo.atomo = ME;
		palavra++;
	}
	else if((*palavra) == '<' && (*palavra+1) == '='){
		infoAtomo.atomo = MEI;
		palavra+=2;
	}
	else if((*palavra) == '='){
		infoAtomo.atomo = IG;
		palavra++;
	}
	else if((*palavra) == '/' && (*palavra+1) == '='){
		infoAtomo.atomo = DI;
		palavra+=2;
	}
	else if((*palavra) == '>'){
		infoAtomo.atomo = MA;
		palavra++;
	}
	else if((*palavra) == '>' && (*palavra+1) == '='){
		infoAtomo.atomo = MAI;
		palavra+=2;
	}
	
/*
*	Reconhecimento de comentário
*/
    else if(*palavra == '{' && *(palavra+1) == '-'){
    	infoAtomo.atomo = reconhece_comentario_varias_linhas();
	}
	
/*
*	Reconhecimento de constantes numericas
*/
	else if(isdigit(*palavra)){
		reconhece_num(&infoAtomo);
	}
	
/*
 *	Reconhecimento do fim do arquivo
 */
 	else if((*palavra) == 0)
 	{
 		infoAtomo.atomo = EOS;	
	}
	
	return infoAtomo;
}

TAtomo reconhece_comentario_varias_linhas(){
	goto q0;
	q0:
		if(*palavra != '-'){
			if(*palavra == '\0'){
				goto poco;
			}
			if(*palavra == '\n'){
				linha++;
			}
			palavra++;
			goto q0;
		}
		else{
			palavra++;
			goto q1;
		}
	q1:
		if(*palavra != '}'){
			if(*palavra == '\0'){
				goto poco;
			}
			if(*palavra == '\n'){
				linha++;
			}
			palavra++;
			goto q0;
		}
		else{
			goto q2;
		}
	q2:
		palavra++;
		return COMENTARIO;
	poco:
		return ERRO;
}

void reconhece_id(TInfoAtomo *infoAtomo){
    int i = 0;
    infoAtomo->atributo_ID[i] = tolower(*palavra);
    palavra++;
    i++;
    goto q0;
	q0:
		if((isalnum((*palavra)) || *palavra == '_') && i < 14){
			infoAtomo->atributo_ID[i] = tolower(*palavra);
			palavra++;
    		i++;
    		goto q0;
		}
		else if(isspace(*palavra) || (*palavra) == '(' ||
				(*palavra) == ')' || (*palavra) == '.' ||
				(*palavra) == ',' || (*palavra) == ';'){

			goto q1;
		}
		else{
			goto poco;
		}
	q1:
		infoAtomo->atributo_ID[i] = '\0';
		if(strcmp(infoAtomo->atributo_ID, "and") == 0){
			infoAtomo->atomo = AND;
		}
		else if(strcmp(infoAtomo->atributo_ID, "begin") == 0){
			infoAtomo->atomo = BEGIN;
		}
		else if(strcmp(infoAtomo->atributo_ID, "boolean") == 0){
			infoAtomo->atomo = BOOLEAN;
		}
		else if(strcmp(infoAtomo->atributo_ID, "char") == 0){
			infoAtomo->atomo = CHAR;
		}
		else if(strcmp(infoAtomo->atributo_ID, "do") == 0){
			infoAtomo->atomo = DO;
		}
		else if(strcmp(infoAtomo->atributo_ID, "else") == 0){
			infoAtomo->atomo = ELSE;
		}
		else if(strcmp(infoAtomo->atributo_ID, "end") == 0){
			infoAtomo->atomo = END;
		}
		else if(strcmp(infoAtomo->atributo_ID, "false") == 0){
			infoAtomo->atomo = FALSE;
		}
		else if(strcmp(infoAtomo->atributo_ID, "if") == 0){
			infoAtomo->atomo = IF;
		}
		else if(strcmp(infoAtomo->atributo_ID, "mod") == 0){
			infoAtomo->atomo = MOD;
		}
		else if(strcmp(infoAtomo->atributo_ID, "not") == 0){
			infoAtomo->atomo = NOT;
		}
		else if(strcmp(infoAtomo->atributo_ID, "number") == 0){
			infoAtomo->atomo = NUMBER;
		}
		else if(strcmp(infoAtomo->atributo_ID, "or") == 0){
			infoAtomo->atomo = OR;
		}
		else if(strcmp(infoAtomo->atributo_ID, "program") == 0){
			infoAtomo->atomo = PROGRAM;
		}
		else if(strcmp(infoAtomo->atributo_ID, "read") == 0){
			infoAtomo->atomo = READ;
		}
		else if(strcmp(infoAtomo->atributo_ID, "set") == 0){
			infoAtomo->atomo = SET;
		}
		else if(strcmp(infoAtomo->atributo_ID, "then") == 0){
			infoAtomo->atomo = THEN;
		}
		else if(strcmp(infoAtomo->atributo_ID, "to") == 0){
			infoAtomo->atomo = TO;
		}
		else if(strcmp(infoAtomo->atributo_ID, "true") == 0){
			infoAtomo->atomo = TRUE;
		}
		else if(strcmp(infoAtomo->atributo_ID, "while") == 0){
			infoAtomo->atomo = WHILE;
		}
		else if(strcmp(infoAtomo->atributo_ID, "write") == 0){
			infoAtomo->atomo = WRITE;
		}
		else {
			infoAtomo->atomo = IDENTIFICADOR;	
		}
		return;
	poco:
		infoAtomo->atomo = ERRO;
	
}

void reconhece_num(TInfoAtomo *infoAtomo){
	int i = 0;
    infoAtomo->atributo_ID[i] = *palavra;
    palavra++;
    i++;
    goto q0;
	q0:
		if(isdigit(*palavra) && i < 13){
			infoAtomo->atributo_ID[i] = *palavra;
			i++;
			palavra++;
			goto q0;
		}
		else if(isspace(*palavra) || *palavra == '\0' || *palavra == ';'){
			infoAtomo->atributo_ID[i] = '\0';
			infoAtomo->atomo = NUMERO;
			return;
		}
		else if(*palavra == 'e' && i < 13){
			infoAtomo->atributo_ID[i] = *palavra;
			i++;
			palavra++;
			goto q1;
		}
		else{
			goto poco;
		}
	q1:
		if(isdigit(*palavra) && i < 13){
			infoAtomo->atributo_ID[i] = *palavra;
			i++;
			palavra++;
			goto q3;
		}
		else if(*palavra == '+' || *palavra == '-'){
			infoAtomo->atributo_ID[i] = *palavra;
			i++;
			palavra++;
			goto q2;
		}
		else{
			goto poco;
		}
	q2:
		if(isdigit(*palavra) && i < 13){
			infoAtomo->atributo_ID[i] = *palavra;
			i++;
			palavra++;
			goto q3;
		}
		else{
			goto poco;
		}
	q3:
		if(isdigit(*palavra) && i < 13){
			infoAtomo->atributo_ID[i] = *palavra;
			i++;
			palavra++;
			goto q3;
		}
		else if(isspace(*palavra) || *palavra == '\0' || *palavra == ';'){
			infoAtomo->atributo_ID[i] = '\0';
			infoAtomo->atomo = EXPONENCIAL;
			return;
		}
		else{
			goto poco;
		}
	poco:
		infoAtomo->atomo = ERRO;
		return;
}

char *leArquivo(char *nomeArquivo){
    int tamArquivo;
    char *buffer;
    FILE *fp;
    fp = fopen(nomeArquivo,"r"); 
    if( fp == NULL ){
        printf("Erro na abertura do arquivo %s",nomeArquivo);
        exit(-1);
    }
    fseek (fp, 0, SEEK_END);  
    tamArquivo = ftell(fp);
    rewind (fp);
    
    buffer = (char *) calloc(tamArquivo+1, sizeof(char));

    
    fread(buffer,1,tamArquivo,fp);
    fclose(fp);
    return buffer;
}
