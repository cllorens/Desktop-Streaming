//---------------------------------------------------------------------------

#include <vcl.h>
#include <jpeg.hpp>

#pragma hdrstop


#include "Unit1.h"

Graphics::TBitmap *Imagen = new Graphics::TBitmap();
TJPEGImage *jp = new TJPEGImage();
TMemoryStream *ms = new TMemoryStream();
HDC hdcScreen = CreateDC("DISPLAY", NULL, NULL, NULL);

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
AnsiString Recibido;
while(Socket->ReceiveLength()>0)
        Recibido=Recibido+Socket->ReceiveText();

//if (Text.AnsiPos("GET / HTTP/1.1")==0) return;

/*Graphics::TBitmap *Imagen = new Graphics::TBitmap();
TJPEGImage *jp = new TJPEGImage();
TMemoryStream *ms = new TMemoryStream();
HDC hdcScreen = CreateDC("DISPLAY", NULL, NULL, NULL);*/

//Socket->Data=ms;

/*Socket->SendText("HTTP/1.0 200 OK\r\n");
Socket->SendText("Cache-Control: no-cache\r\n");
Socket->SendText("Pragma: no-cache\r\n");
Socket->SendText("Expires: Thu, 01 Dec 1994 16:00:00 GMT\r\n");
Socket->SendText("Connection: close\r\n");
Socket->SendText("Content-Type: multipart/x-mixed-replace; boundary=myboundary\r\n\r\n");   */
/*
while(Socket->Connected)
        {
        Imagen->Width=Screen->Width;
        Imagen->Height=Screen->Height;

        BitBlt(Imagen->Canvas->Handle,0,0,Screen->Width,Screen->Height,hdcScreen,0,0,SRCCOPY);

        jp->Assign(Imagen);
        jp->CompressionQuality=50;
        jp->Compress();

        ms->Clear();
        jp->SaveToStream(ms);
        ms->Position=0;
        //Image1->Picture->Bitmap->Assign(Imagen);

        Socket->SendText("--myboundary\r\n");
        Socket->SendText("Content-Type: image/jpeg\r\n");
        Socket->SendText("Content-length: "+IntToStr(ms->Size)+"\r\n\r\n");


        Socket->SendBuf(ms->Memory,ms->Size);
//        Socket->SendStream(ms);
        //Sleep(100);
        Socket->SendText("\r\n");
        }    */

//Socket->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
ErrorCode=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormActivate(TObject *Sender)
{
//Form1->Visible=false;
ShowWindow(Application->Handle, SW_HIDE);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
Socket->SendText("HTTP/1.0 200 OK\r\n");
Socket->SendText("Cache-Control: no-cache\r\n");
Socket->SendText("Pragma: no-cache\r\n");
Socket->SendText("Expires: Thu, 01 Dec 1994 16:00:00 GMT\r\n");
Socket->SendText("Connection: close\r\n");
Socket->SendText("Content-Type: multipart/x-mixed-replace; boundary=myboundary\r\n\r\n");
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
if ( ServerSocket1->Socket->ActiveConnections ==0 )return;

Imagen->Width=Screen->Width;
Imagen->Height=Screen->Height;

BitBlt(Imagen->Canvas->Handle,0,0,Screen->Width,Screen->Height,hdcScreen,0,0,SRCCOPY);

jp->Assign(Imagen);
jp->CompressionQuality=30;
jp->Compress();

ms->Clear();
jp->SaveToStream(ms);
ms->Position=0;

for (int n=0;n<ServerSocket1->Socket->ActiveConnections;n++)
        {
        if (ServerSocket1->Socket->Connections[n]->Connected)
                {
                ServerSocket1->Socket->Connections[n]->SendText("--myboundary\r\n");
                ServerSocket1->Socket->Connections[n]->SendText("Content-Type: image/jpeg\r\n");
                ServerSocket1->Socket->Connections[n]->SendText("Content-length: "+IntToStr(ms->Size)+"\r\n\r\n");

                ServerSocket1->Socket->Connections[n]->SendBuf(ms->Memory,ms->Size);
                ServerSocket1->Socket->Connections[n]->SendText("\r\n");
                }
        }



}
//---------------------------------------------------------------------------

