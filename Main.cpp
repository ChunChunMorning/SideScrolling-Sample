
# include <Siv3D.hpp>

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
