//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <Math.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
class Podaci {
public:
    double visina;
	double tezina;
	int godine;
    int spol;
    double bmr;
};

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::IdTCPServer1Execute(TIdContext *AContext)
{

	AnsiString visinaStr = AContext->Connection->Socket->ReadLn();
	AnsiString tezinaStr = AContext->Connection->Socket->ReadLn();
	double tezina = StrToFloat(tezinaStr);
	double visina = StrToFloat(visinaStr) / 100;
	double SqrtOfHeight = visina * visina;
	double rezultat = tezina / SqrtOfHeight;
	// Zaokružujemo rezultat na jedan decimalni broj
	double zaokruzenRezultat = RoundTo(rezultat, -1);
	AContext->Connection->Socket->WriteLn(FloatToStr(zaokruzenRezultat));
	AContext->Connection->Disconnect();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
		  TIdSocketHandle *ABinding)
{
  Podaci korisnik;
	memcpy(&korisnik, AData.data(), sizeof(korisnik));
	// Izračunavanje BMR-a
	double bmr;
	// Harris-Benedictova formula
	if (korisnik.spol == 0) { // Muškarci
		bmr = 66.4730 + (13.7516 * korisnik.tezina) + (5.0033 * korisnik.visina) - (6.7550 * korisnik.godine);
	} else { // Žene
		bmr = 655.0955 + (9.5634 * korisnik.tezina) + (1.8496 * korisnik.visina) - (4.6756 * korisnik.godine);
	}
	// Zaokruživanje BMR-a na jednu decimalu
	double zaokruzenBMR = RoundTo(bmr, -1);
	// Priprema podataka za slanje (samo BMR)
	TIdBytes sendData;
	sendData.Length = sizeof(zaokruzenBMR);
	memcpy(sendData.data(), &zaokruzenBMR, sizeof(zaokruzenBMR));
	// Slanje podataka klijentu
	ABinding->SendTo(ABinding->PeerIP, ABinding->PeerPort, sendData);
}
//---------------------------------------------------------------------------

