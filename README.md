# Arduino Accelerometer Motion Counter

Arduino Pro Mini と加速度センサを用いて Z 軸方向の動きをカウント

## 必要なハードウェア

* Arduino Pro Mini
* 加速度センサ
* LED x2
* 抵抗 x2
* ボタン
* ブレッドボード
* ジャンパワイヤー

## ピンアサイン

* LED1_PIN: 10
* LED2_PIN: 9
* A_PIN: 5（加速度センサの出力）
* A_RESET_PIN: 2

## 動作

このプログラムは Arduino の main loop で次のタスクを実行：

* ボタンが押されたら、現在の加速度を正常値として設定
* 加速度センサから加速度を読み取る
* 速度と距離を積分値から計算
* 上下の移動距離によって LED を点灯
