「ふつうのLinuxプログラミング」の例題(catコマンド実装)を、  
機能を変えず、自分好みにリファクタリングした。  
そのときの生成物を置く。

# 主要ファイル
 cat.c          catコマンド本体  
 SConstruct     ビルドに必要なファイル

# ビルド方法
 cat.c および SConstruct があるカレントディレクトリで以下を実行する。  
 $ scons .

# sconsのインストール方法
 $ sudo apt-get install scons  

