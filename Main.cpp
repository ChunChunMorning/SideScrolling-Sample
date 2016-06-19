
# include <Siv3D.hpp>

class Block
{
public:

	// 引数のないコンストラクタも作っておくといろいろ便利.
	Block() {}

	Block(const RectF& region) :
		m_region(region),
		m_texture(L"Example/Brick.jpg") {}

	// 描画以外の操作をする関数
	void update()
	{
		// 今回は何もない
	}

	// 描画をする関数（描画操作以外行わないこと.）
	void draw()
	{
		m_region(m_texture).draw();
	}


private:

	// ブロックの領域
	RectF m_region;

	// ブロックのテキスチャ（画像）
	Texture m_texture;

};

void Main()
{
	Window::Resize(1280, 720);

	Texture background(L"Example/Windmill.png");

	while (System::Update())
	{
		// 本来ならリサイズしなくていいように画像を用意すべき.
		background.scale(1280.0 / 480.0).draw();
	}
}
