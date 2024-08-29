object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 442
  ClientWidth = 628
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object IdTCPServer1: TIdTCPServer
    Active = True
    Bindings = <
      item
        IP = '127.0.0.1'
        Port = 12344
      end>
    DefaultPort = 12344
    OnExecute = IdTCPServer1Execute
    Left = 55
    Top = 48
  end
  object IdUDPServer1: TIdUDPServer
    Active = True
    Bindings = <
      item
        IP = '127.0.0.1'
        Port = 13121
      end>
    DefaultPort = 0
    OnUDPRead = IdUDPServer1UDPRead
    Left = 151
    Top = 48
  end
end
