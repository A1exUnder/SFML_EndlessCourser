#include <SFML/Graphics.hpp>

using namespace sf;
 

class Players //общий класс для движущихся объектов
{
	public:
		float x,y,w,h,dx,dy,speed; //координаты ширина высота скорость
		int dir;  //направление 
		String File; //имя файла
		Image image;  // СФМЛ картинка , текстура , спрайт
		Texture texture;
		Sprite sprite;

		Players(String F, float X, float Y, float H, float W) // конструктор
		{
			dx=0;	dy=0;	speed=0;	dir=0;
			x=X;	y=Y;	w=W;	h=H;
			File = F;
			image.loadFromFile("IM/" + File);
			//image.createMaskFromColor(Color(41, 33, 59));  убирает фон, сделать по наличию картинок
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
			void update(float time) // инициализация 
			{
				switch (dir) // направления движения
				{
					case 0: dx = speed; dy = 0; break; // 0 - вправо
					case 1: dx = -speed; dy = 0; break; // 1 - влево
					case 2: dx = 0; dy = speed; break;	// 2 - вниз
					case 3: dx = 0; dy = -speed; break;	// 3 - вверх
				}
 
			x += dx*time; // движение = ускорение на время
			y += dy*time;
 
			speed = 0; // обнуление скорости
			sprite.setPosition(x,y); // вывод спрайта
			}
	
		
};

int main()
{
	RenderWindow window(sf::VideoMode(1280, 720), "Lesson 5. kychka-pc.ru");
 
 
	
	Texture herotexture;
	herotexture.loadFromFile("IM/lowadi.png");
 
	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 0, 64, 64));//получили нужный нам прямоугольник с котом
	herosprite.setPosition(250,250); //выводим спрайт в позицию x y 
 
	
 
	while (window.isOpen())
	{
		
 
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)			
			window.close();
		}
 
		if (Keyboard::isKeyPressed(Keyboard::Left)) { herosprite.move(-0.1, 0); } 
		if (Keyboard::isKeyPressed(Keyboard::Right)) { herosprite.move(0.1, 0); } 
		if (Keyboard::isKeyPressed(Keyboard::Up)) { herosprite.move(0, -0.1); } 
		if (Keyboard::isKeyPressed(Keyboard::Down)) { herosprite.move(0, 0.1); } 
 
		window.clear();
		window.draw(herosprite);
		window.display();
	}
 
	return 0;
}