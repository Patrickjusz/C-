object Form3: TForm3
  Left = 416
  Top = 186
  Width = 418
  Height = 383
  BorderStyle = bsSizeToolWin
  Caption = 'Statystyki'
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 402
    Height = 33
    Align = alTop
    TabOrder = 0
    DesignSize = (
      402
      33)
    object CheckBox1: TCheckBox
      Left = 272
      Top = 8
      Width = 121
      Height = 17
      Anchors = [akTop, akRight]
      Caption = 'Aktualizuj statystyki'
      Checked = True
      State = cbChecked
      TabOrder = 0
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 33
    Width = 402
    Height = 312
    Align = alClient
    TabOrder = 1
    object ListView1: TListView
      Left = 1
      Top = 1
      Width = 400
      Height = 310
      Align = alClient
      BorderStyle = bsNone
      Columns = <
        item
          AutoSize = True
          Caption = 'Agent nr:'
          MaxWidth = 60
          MinWidth = 60
        end
        item
          Alignment = taCenter
          Caption = 'Zjedzone'
          MaxWidth = 65
          MinWidth = 65
          Width = 65
        end
        item
          Alignment = taCenter
          Caption = 'Promie'#324' widzenia'
          MaxWidth = 100
          MinWidth = 100
          Width = 100
        end
        item
          Alignment = taCenter
          Caption = 'Odleg'#322'o'#347#263' widzenia'
          MaxWidth = 110
          MinWidth = 110
          Width = 110
        end
        item
          Alignment = taCenter
          Caption = 'S'#261'siedzi'
          MaxWidth = 60
          MinWidth = 60
          Width = 60
        end>
      ReadOnly = True
      TabOrder = 0
      ViewStyle = vsReport
    end
  end
end
