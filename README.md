# Easy_Converter
ffmpegとImageMagickを用いてファイルを最低限の変換するのをQtベースのGUIで簡単に操作するアプリです。

<img width="968" height="779" alt="Screenshot_20251019_014048" src="https://github.com/user-attachments/assets/f25bdfc4-54f2-4db2-8c55-6ee2d5919bbc" />


## 依存関係
Qtで作成し、ffmpegとimagemagickをコマンドで動かしています。
環境にない場合はインストールしてください。

## 実行方法
[ここ](https://github.com/Akasakax/Easy_Converter/releases)から最新のdebをダウンロードしてください。
その後にダウンロードされたディレクトリ内で以下コマンドを実行してください。
```
sudo dpkg -i Easy_Converter[VERSION NUMBER].deb
```
アンインストールする際には以下コマンドです。
```
sudo dpkg -r Easy_Converter
```

## 使い方
タブ内を上から順に進めてください。
「変換後のファイル名を入力してください」の項目は自分が指定したいファイルの形式を含めて記述してください。
ex) hogehoge.png
