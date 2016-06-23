
# include <Siv3D.hpp>

class Block
{
public:

	Block() {}

	Block(const RectF& region) :
		m_region(region),
		m_texture(L"Example/Brick.jpg") {}

	// プレイヤーの現在位置を更新する関数
	void setPlayerPosition(const Vec2& pos)
	{
		m_playerPosition = pos;
	}

	// 描画以外の操作をする関数
	void update() {}

	// 点との当たり判定を取る関数
	bool intersects(const Vec2 &shape) const
	{
		return m_region.intersects(shape);
	}

	// 描画をする関数（描画操作以外行わないこと.）
	void draw()
	{
		m_region.movedBy(-m_playerPosition)(m_texture).draw();
	}


private:

	// ブロックの領域
	RectF m_region;

	// ブロックのテキスチャ（画像）
	Texture m_texture;

	// プレイヤーの現在の位置
	Vec2 m_playerPosition;
};


class Player
{
public:

	Player() :
		m_position(100, 200),
		m_texture(L"Example/Siv3D-kun.png"),
		m_isGrounded(false),
		m_jumpFrame(0) {}

	Vec2 getPos()
	{
		return m_position;
	}

	// 地面に接しているかを更新する関数
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
		if (m_isGrounded)
		{
			if (Input::KeySpace.clicked && m_jumpFrame <= 0)
			{
				m_jumpFrame = 30;
			}
		}
		else
		{
			m_position.y += 10.0;
		}

		if (m_jumpFrame > 0)
		{
			m_position.y -= 20.0;
			m_jumpFrame--;
		}
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
		RectF(Vec2(-72.5, -200), 145, 200)(m_texture).draw();
	}

private:

	// プレイヤーの座標
	Vec2 m_position;

	// プレイヤーのテクスチャ（画像）
	Texture m_texture;

	// 地面に接しているか否か
	bool m_isGrounded;

	// 残りのジャンプ時間
	int m_jumpFrame;
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
			blocks[i].setPlayerPosition(player.getPos());
			blocks[i].update();
		}

		player.checkGround(blocks);
		player.update();

		background.scale(1280.0 / 480.0).draw();

		for (size_t i = 0; i < blocks.size(); i++)
		{
			blocks[i].draw();
		}

		player.draw();
	}
}
