/*
*
*	Projeto Analisador Lexico
*
*	TIA: 31826131	NOME: Abram Grossmann
*	TIA: 31836895	NOME: Victor Melly
*
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
/*
*	Lista de palavras reservadas
*/	
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
    
/******************************************
*	Atomos simples
*/
	ABRE_PAR,
	FECHA_PAR,
	PONTO,
	PONTO_VIRGULA,
	VIRGULA,
	
/******************************************
*	Operadores aritmeticos
*/
	SUBTRACAO,
	ADICAO,
	DIVISAO,
	MULTIPLICACAO,
	
/******************************************
*	Operadores relacionais
*/
	ME,
	MEI,
	IG,
	DI,
	MA,
	MAI,
	
/******************************************
*	Comentarios na linguagem
*/
	NOVA_LINHA,
	ASCII,
	COMENTARIO_VARIAS_LINHAS,
	COMENTARIO_UMA_LINHA,
	COMENTARIO,
	
/*******************************************
*	Constantes numericas
*/
	EXPONENCIAL,
	NUMERO,
	
/*******************************************
*	Constante caractere
*/
	CARACTERE,
	
/*******************************************
*	Erro e controle
*/
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

int linha = 1;
char *palavra;
char *leArquivo(char *nomeArquivo);
TInfoAtomo obter_atomo();
TAtomo reconhece_comentario();
void reconhece_id(TInfoAtomo *infoAtomo);
void reconhece_num(TInfoAtomo *infoAtomo);
void reconhece_char(TInfoAtomo *infoAtomo);

int main(void){
	TInfoAtomo InfoAtomo;
	palavra = leArquivo("entrada.txt");
	while(1){
		InfoAtomo = obter_atomo();
		if(InfoAtomo.atomo == COMENTARIO){
			printf("linha\t%d:comentario\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == IDENTIFICADOR){
			printf("linha\t%d:identificador - atributo:%s\n", InfoAtomo.linha, InfoAtomo.atributo_ID);
		}
		else if(InfoAtomo.atomo == SET){
			printf("linha\t%d:set\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == BEGIN){
			printf("linha\t%d:begin\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == THEN){
			printf("linha\t%d:then\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == NUMBER){
			printf("linha\t%d:number\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == ABRE_PAR){
			printf("linha\t%d:abre parenteses\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == OR){
			printf("linha\t%d:or\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == NOT){
			printf("linha\t%d:not\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == AND){
			printf("linha\t%d:and\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == TRUE){
			printf("linha\t%d:true\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == FALSE){
			printf("linha\t%d:false\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == BOOLEAN){
			printf("linha\t%d:boolean\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == IF){
			printf("linha\t%d:if\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == ELSE){
			printf("linha\t%d:else\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == CHAR){
			printf("linha\t%d:char\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == FECHA_PAR){
			printf("linha\t%d:fecha parenteses\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == ME){
			printf("linha\t%d:menor\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == MEI){
			printf("linha\t%d:menor igual\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == MA){
			printf("linha\t%d:maior\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == MAI){
			printf("linha\t%d:maior igual\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == IG){
			printf("linha\t%d:igual\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == DI){
			printf("linha\t%d:desigual\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == MOD){
			printf("linha\t%d:mod\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == READ){
			printf("linha\t%d:read\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == SET){
			printf("linha\t%d:set\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == TO){
			printf("linha\t%d:to\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == PROGRAM){
			printf("linha\t%d:program\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == PONTO_VIRGULA){
			printf("linha\t%d:ponto e virgula\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == PONTO){
			printf("linha\t%d:ponto\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == VIRGULA){
			printf("linha\t%d:virgula\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == NUMERO){
			printf("linha\t%d:numero - atributo:%s\n", InfoAtomo.linha, InfoAtomo.atributo_ID);
		}
		else if(InfoAtomo.atomo == EXPONENCIAL){
			printf("linha\t%d:exponencial:%s\n", InfoAtomo.linha, InfoAtomo.atributo_ID);
		}
		else if(InfoAtomo.atomo == DIVISAO){
			printf("linha\t%d:divisao\n", linha);
		}
		else if(InfoAtomo.atomo == ADICAO){
			printf("linha\t%d:adicao\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == SUBTRACAO){
			printf("linha\t%d:subtracao\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == MULTIPLICACAO){
			printf("linha\t%d:multiplicacao\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == DO){
			printf("linha\t%d:do\n", linha);
		}
		else if(InfoAtomo.atomo == WHILE){
			printf("linha\t%d:while\n", linha);
		}
		else if(InfoAtomo.atomo == WRITE){
			printf("linha\t%d:write\n", InfoAtomo.linha);
		}
		else if(InfoAtomo.atomo == END){
			printf("linha\t%d:end\n", linha);
		}
		else if(InfoAtomo.atomo == CARACTERE){
			printf("linha\t%d:caractere - atributo %s\n", linha, InfoAtomo.atributo_ID);
		}
		else if(*palavra == '\0')
		{
			printf("fim da analize lexica\n");
			break;
		}
		else if(InfoAtomo.atomo == ERRO){
			printf("ERRO\n");
			break;
		}
	}
	return 0;
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

/*
*	Reconhecimento de comentario de uma linha
*/
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
*	Reconhecimento de operadores relacionais
*/
	else if((*palavra) == '<' && *(palavra+1) == '='){
		infoAtomo.atomo = MEI;
		palavra+=2;
	}
	else if((*palavra) == '<'){
		infoAtomo.atomo = ME;
		palavra++;
	}
	else if((*palavra) == '/' && *(palavra+1) == '='){
		infoAtomo.atomo = DI;
		palavra+=2;
	}
	else if((*palavra) == '>' && *(palavra+1) == '='){
		infoAtomo.atomo = MAI;
		palavra+=2;
	}
	else if((*palavra) == '>'){
		infoAtomo.atomo = MA;
		palavra++;
	}
	else if((*palavra) == '='){
		infoAtomo.atomo = IG;
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
*	Reconhecimento de comentário
*/
    else if(*palavra == '{' && *(palavra+1) == '-'){
    	infoAtomo.atomo = reconhece_comentario();
	}
	
/*
*	Reconhecimento de constantes numericas
*/
	else if(isdigit(*palavra)){
		reconhece_num(&infoAtomo);
	}
	
/*
*	Reconhece caracteres constantes
*/
	else if(*palavra == 39){
		reconhece_char(&infoAtomo);
	}
	return infoAtomo;
}


TAtomo reconhece_comentario(){
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


void reconhece_char(TInfoAtomo *infoAtomo){
	palavra++;
	infoAtomo->atributo_ID[0] = *palavra;
	infoAtomo->atributo_ID[1] = '\0';
	palavra++;
   	if(*palavra != 39){
   		infoAtomo->atomo = ERRO;
   		return;
	}
	palavra++;
	infoAtomo->atomo = CARACTERE;
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
