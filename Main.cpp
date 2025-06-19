# include <Siv3D.hpp>

void Main()
{
    // タイルサイズ
    const int32 tileSize = 40;

    // 0: 草原, 1: 水
    Grid<int> map
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    const int32 mapWidth  = (map[0].size() * tileSize);
    const int32 mapHeight = (map.size() * tileSize);
    Window::Resize(mapWidth, mapHeight);

    const double speed = 200.0; // 移動速度 (pixel / sec)
    const double radius = tileSize * 0.4;
    Vec2 playerPos(Window::Center());
    Circle player(playerPos, radius);

    while (System::Update())
    {
        Vec2 velocity;
        if (KeyLeft.pressed())  velocity.x -= speed;
        if (KeyRight.pressed()) velocity.x += speed;
        if (KeyUp.pressed())    velocity.y -= speed;
        if (KeyDown.pressed())  velocity.y += speed;

        Vec2 nextPos = playerPos + velocity * Scene::DeltaTime();
        nextPos.x = Clamp(nextPos.x, radius, Window::Width() - radius);
        nextPos.y = Clamp(nextPos.y, radius, Window::Height() - radius);

        Point index = (nextPos / tileSize).asPoint();
        if (map.inBounds(index) && map[index] == 0)
        {
            playerPos = nextPos;
        }

        // マップ描画
        for (int32 y = 0; y < map.height(); ++y)
        {
            for (int32 x = 0; x < map.width(); ++x)
            {
                const RectF rect(x * tileSize, y * tileSize, tileSize, tileSize);
                if (map[y][x] == 0)
                {
                    rect.draw(Palette::Green);
                }
                else
                {
                    rect.draw(Palette::Blue);
                }
            }
        }

        player.setPos(playerPos).draw(Palette::Orange);
    }
}

