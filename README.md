WeatherNoiseRemover
WeatherNoiseRemoverは、点群データに含まれる環境ノイズを除去するためのROS2パッケージです。特に、雨や霧によるノイズに対応しており、センサーの精度向上やデータのクリーンアップに役立ちます。本パッケージは、ボクセルグリッドフィルタを利用して点群データをダウンサンプリングし、占有率に基づいて一定以上の密度を持たないボクセルのデータを削除します。

特徴
雨と霧に対応
点群データに影響を与える雨や霧を効果的に除去することができます。これにより、センサーデータの精度が向上し、誤検知やノイズの影響を低減します。
ボクセルグリッドフィルタ
点群をダウンサンプリングしてデータ量を削減し、処理効率を向上させます。
占有率フィルタ
各ボクセルに含まれる点の数を評価し、閾値以下のボクセルをフィルタリングすることで、ノイズを効果的に除去します。
インストール
このパッケージを利用するためには、以下の手順でインストールを行ってください。

bash
コードをコピーする
git clone https://github.com/yourusername/WeatherNoiseRemover.git
cd WeatherNoiseRemover
colcon build --packages-select weather_noise_remover
使用方法
WeatherNoiseRemoverは、以下のコマンドで起動することができます。

```
ros2 run weather_noise_remover weather_noise_remover_node
```

サブスクライバー
/input_point_cloud
センサーから入力される点群データを購読します。
パブリッシャー
/filtered_point_cloud
フィルタリング後の点群データを配信します。
パラメータ
WeatherNoiseRemoverは、以下のパラメータを調整することができます。

leaf_size
ボクセルグリッドの解像度を設定します。デフォルトは0.1 (メートル)です。

occupancy_threshold
各ボクセル内で保持する最小の点数を設定します。この閾値以下のボクセルは削除されます。デフォルトは5です。

使用例
センサーデータに対して雨や霧のノイズを除去する場合、以下のようにしてパラメータを調整することが可能です。

```
ros2 run weather_noise_remover weather_noise_remover_node --ros-args -p leaf_size:=0.2 -p occupancy_threshold:=10
```
この設定では、20cmのボクセルグリッドサイズでダウンサンプリングを行い、各ボクセルに10点以上の点群が存在する場合にのみ、そのボクセルを保持します。

ライセンス
このパッケージはMITライセンスの下で提供されています。詳しくは、LICENSEファイルをご覧ください。
