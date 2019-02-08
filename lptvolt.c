//---------------------------------------------------------------------------
// Objetivo: Medir tensão elétrica entre 0 à 5v através da porta EPP.
// Autor: Antonio Rogério Messias
// Data Criação: 12/11/2001
// E-Mail: rogercom@rogercom.com
// Todos os Direitos Reservados
//---------------------------------------------------------------------------
//#include  "vcl.h"
#include  "stdio.h"
#pragma hdrstop
#include "UnitPrincipal.h"
#include "Porta.h"
#include "ClassBinario.h"
#define B0 0x01
#define B1 0x02
#define B2 0x04
#define B3 0x08
#define B4 0x10
#define B5 0x20
#define B6 0x40
#define B7 0x80
#define S3 B3
#define S4 B4
#define S5 B5
#define S6 B6
#define S7 B7
#define BASE     0x378
#define DADOS    BASE + 0
#define STATUS   BASE + 1
#define CONTROLE BASE + 2
#define EPPDATA  BASE + 4
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformPrincipal *formPrincipal;
TPorta *Porta;      //Declara objeto para controle da porta paralela.
TBinario *Binario;  //Declara objeto p/ converter um int numa string binária.
unsigned char ByteADC; //Variável para armazenar o byte recebido através da porta.
int TimeOut;           //Váriável para armazenar o tempo de resposta do circuito.
//---------------------------------------------------------------------------
__fastcall TformPrincipal::TformPrincipal(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TformPrincipal::TimerAquisicaoTimer(TObject *Sender)
{
  char buf[7]; //Vriável para armazenar uma string de números.
  //IMPORTANTE: Para ativar um pino no ADC envia um 0 (zero) e para desativar 1 (um).

  //Inicializa a conversão do ADC enviando um pulso Baixo(0) no pino 14 C1,
  //momentaneamente.

  Porta->Envia(CONTROLE,34);   //34 0010-0010 aguarda mais ou menos 100 micro segundos.
  Porta->Envia(CONTROLE,32);   //32 0010-0000 habilita a conversão.
  TimeOut=0;

  do{     //Loop para verificar o Sinal INTR do ADC0804.
     TimeOut++;
  }while(((Porta->Recebe(STATUS) & S3) == S3) && (TimeOut != 256)); //0000-1000.
  if(TimeOut == 256)
  {
    formPrincipal->Caption = "Erro!";
  }else
  {                              //35 0010-0011
     Porta->Envia(CONTROLE,35);  //Pino 1 C0 Baixo(0),Habilita a saída(leitura) do ADC.
     ByteADC =  Porta->Recebe(DADOS); //34 0010-0010
     Porta->Envia(CONTROLE,34); //Pino 1 C0 Alto(1),Desabilita a saída(leitura) do ADC.
     sprintf(buf,"%0.2f",ByteADC*0.0196); //Calcula: Byte recebido x 0.0196v.
     labeVisor->Caption = buf;  //Exibe valor.
  }
}
//---------------------------------------------------------------------------

void __fastcall TformPrincipal::SpeedButtonSairClick(TObject *Sender)
{
  Porta->Envia(CONTROLE,0); //Desabilita a leitura EPP.
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TformPrincipal::SpeedButtonMiniClick(TObject *Sender)
{
    WindowState = wsMinimized;
}
//---------------------------------------------------------------------------
