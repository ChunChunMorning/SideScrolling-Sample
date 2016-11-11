# SideScrolling-Sample
Siv3Dで横スクロールゲームを作るときのサンプル

詳細な解説はSiv3D公式リファレンス、入門チュートリアルから見ることができます。

[Siv3Dリファレンス 横スクロールゲームを作ろう](https://github.com/Siv3D/Reference-JP/wiki/%E6%A8%AA%E3%82%B9%E3%82%AF%E3%83%AD%E3%83%BC%E3%83%AB%E3%82%B2%E3%83%BC%E3%83%A0%E3%82%92%E4%BD%9C%E3%82%8D%E3%81%86)

## 改良案
### 1. ゲームオーバーの実装
プレイヤーのy座標が一定を超える（下に落ち過ぎる）とアプリを終了する等で実現できます。

### 2. 速度を実装する
サンプルは移動分をそのまま座標に足していますが、新たにメンバ変数として速度を作り、毎ループ座標に速度を加える設計にして、キーボードの入力や重力を速度に加えるようにすれば、加速度などを実装できるようになります。

### 3. キャラの向きを変える
キャラの画像を向きによって複数用意し、進行方向によって描画する画像を切り替えると、よりゲームっぽくなります。

### 4. 下以外の当たり判定を実装する
サンプルは下方向のみに当たり判定があるので、それを上下左右に適応し、衝突した方向の速度を0にすることで実装できます。

### 5. 乗ると落ちるブロックを作る
プレイヤーが乗ったのを検知したら、ブロック側のupdate関数内でプレイヤーを落とす時と同じ処理をすれば実装できます。

### 6. ブロックを削除できるようにする
ブロックにメンバ変数として死亡フラグを持たせ、Siv3Dの[Erase_if関数](https://github.com/Reputeless/Siv3D-Reference/blob/master/Programming%20Guide/Headers/Siv3D/Utility.hpp)と組み合わせることにより実装できます。

### 7. アイテムを実装する
基本的にはブロックと同じで、プレイヤーが触れたら消えて、何かの効果を発揮するようにすれば実装できます。

### 8. シーン管理をする
実際のゲームはタイトル画面やリザルト画面などがゲーム画面以外にも存在し、それらが切り替わっていると思います。

[HamFrameworkのSceneManager](http://play-siv3d.hateblo.jp/entry/ref/scenemanager)に対応させると、簡単にそれらが実装できます。

### 9. ポーズを実装する
こちらの記事で紹介しています。

[Siv3Dでポーズ画面を簡単に実装する with HamFramework](http://chungames.hateblo.jp/entry/2015/04/01/001347)

### 10. 複数のクラスをまとめて扱う
今はPlayerとBlockだけでしたが、今後たくさんのクラスを実装した時に、その度にArrayを追加するのは大変です。なので、それらをまとめて扱えるようにしましょう。

その前に、今はPlayerクラスはcheckGround関数、BlockクラスはsetPlayerPos関数を使用していますが、ポインタや参照を用いることによって、引数で渡していたものをメンバに保存させると、Main関数からこれらの関数を呼ぶ必要がなくなります。

となると、PlayerクラスとBlockクラスはupdate関数、draw関数を有しているという共通点が生まれます。なので、これらの関数を有する親クラスを作成、PlayerとBlockはその子クラスとして継承させることができます。

後はMain関数にあったArrayをArray<"親クラスのポインタ">とすると一つのArrayで管理することが可能になります。

この例の場合は微妙ですが、落ちるブロックと普通のブロックをまとめて扱う等はすごく便利だと思います。
