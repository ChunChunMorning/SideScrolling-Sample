
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

	// 点との当たり判定を取る関数
	bool intersects(const Vec2 &shape) const
	{
		return m_region.intersects(shape);
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


class Player
{
public:

	Player() :
		m_position(100, 200),
		m_texture(L"Example/Siv3D-kun.png") {}

	void checkGround(const Array<Block>& blocks)
	{
		m_isGrounded = false;

		for (size_t i = 0; i < blocks.size(); i++)
		{
			if (blocks[i].intersects(m_position))
			{
				m_isGrounded = true;
			}
		}
	}

	// 描画以外の操作をする関数
	void update()
	{
		m_position.y += 10.0;

		if (Input::KeyRight.pressed)
		{
			m_position.x += 5.0;
		}
		if (Input::KeyLeft.pressed)
		{
			m_position.x -= 5.0;
		}
	}

	// 描画をする関数（描画操作以外行わないこと.）
	void draw()
	{
		RectF(m_position.x - 72.5, m_position.y - 200, 145, 200)(m_texture).draw();
	}

private:

	// プレイヤーの座標
	Vec2 m_position;

	// プレイヤーのテクスチャ（画像）
	Texture m_texture;

	// 地面に接しているか否か
	bool m_isGrounded;
};


void Main()
{
	Window::Resize(1280, 720);

	Texture background(L"Example/Windmill.png");
	Player player;
	Array<Block> blocks;

	blocks.push_back(Block({-400, 400, 200, 200}));
	blocks.push_back(Block({-200, 400, 200, 200}));
	blocks.push_back(Block({0, 400, 200, 200}));
	blocks.push_back(Block({200, 400, 200, 200}));
	blocks.push_back(Block({200, 200, 200, 200}));
	blocks.push_back(Block({400, 400, 200, 200}));
	blocks.push_back(Block({800, 400, 200, 200}));
	blocks.push_back(Block({1000, 400, 200, 200}));
	blocks.push_back(Block({1300, 200, 400, 30}));

	while (System::Update())
	{
		for (size_t i = 0; i < blocks.size(); i++)
		{
			blocks[i].update();
		}

		player.update();


		// 本来ならリサイズしなくていいように画像を用意すべき.
		background.scale(1280.0 / 480.0).draw();

		for (size_t i = 0; i < blocks.size(); i++)
		{
			blocks[i].draw();
		}

		player.draw();
	}
}
