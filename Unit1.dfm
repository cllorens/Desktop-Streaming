object Form1: TForm1
  Left = 1379
  Top = 127
  Width = 132
  Height = 97
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnShow = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object ServerSocket1: TServerSocket
    Active = True
    Port = 80
    Service = 'http'
    ServerType = stNonBlocking
    ThreadCacheSize = 100
    OnClientConnect = ServerSocket1ClientConnect
    OnClientRead = ServerSocket1ClientRead
    OnClientError = ServerSocket1ClientError
    Left = 8
    Top = 8
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 40
    Top = 8
  end
end
