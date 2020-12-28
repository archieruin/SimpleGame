#include <SFML/Graphics.hpp>
#include <windows.h>

using namespace sf;

int screen_width = 720;
int screen_height = 480;

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	RenderWindow window(VideoMode(screen_width, screen_height), "Simple Game");
	CircleShape shape(50.0f);

	Image player_idle_image;
	Image player_run_image;
	Texture player_idle_texture;
	Texture player_run_texture;
	Sprite player_sprite;
	
	player_idle_image.loadFromFile("res/herochar_idle_anim_strip_4.png");
	player_run_image.loadFromFile("res/herochar_run_anim_strip_6.png");
	player_idle_texture.loadFromImage(player_idle_image);
	player_run_texture.loadFromImage(player_run_image);
	
	player_sprite.setTexture(player_idle_texture);
	player_sprite.setTextureRect(IntRect(0, 0, 16, 16));
	player_sprite.setScale(2, 2);
	player_sprite.setPosition(screen_width / 2 - 8, screen_height - 60);

	float playerSpeed = 0.2f;
	float animationSpeed = 0.008f;
	float currentFrame = 0;
	Clock clock;

	while (window.isOpen())
	{
		float delta = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		delta /= 800;
		
		Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			player_sprite.setTexture(player_run_texture);
			currentFrame += animationSpeed * delta;
			if (currentFrame > 7) currentFrame -= 6;
			if (currentFrame < 1) currentFrame = 1;
			player_sprite.setTextureRect(IntRect(int(currentFrame) * 16, 0, -16, 16));
			player_sprite.move(-playerSpeed * delta, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			player_sprite.setTexture(player_run_texture);
			currentFrame += animationSpeed * delta;
			if (currentFrame > 6) currentFrame -= 6;
			player_sprite.setTextureRect(IntRect(int(currentFrame) * 16, 0, 16, 16));
			player_sprite.move(playerSpeed * delta, 0);
		}

		if (!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D))
		{
			player_sprite.setTexture(player_idle_texture);
			currentFrame += animationSpeed * delta;
			if (currentFrame > 4) currentFrame -= 4;
			player_sprite.setTextureRect(IntRect(int(currentFrame) * 16, 0, 16, 16));
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			player_sprite.setColor(Color::Red);
		}
		else
		{
			player_sprite.setColor(Color::White);
		}

		window.clear(Color(250, 220, 100, 0));
		window.draw(player_sprite);
		window.display();
	}

	return 0;
}
