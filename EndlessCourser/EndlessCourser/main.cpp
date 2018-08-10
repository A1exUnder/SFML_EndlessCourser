#include <SFML/Graphics.hpp>

using namespace sf;
 

class Players //общий класс для движущихся объектов
{
	public:
		int Ground;
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
			File = F;	Ground=500;
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
					case 2: /*dy = -0.5;*/ break;	// 2 - прыжок
				
				}
 
			x += dx*time; // движение = ускорение на время
			y += dy*time;
			//if(x<Ground)
				//dy = dy + 0.0015*time;
			speed = 0; // обнуление скорости
			sprite.setPosition(x,y); // вывод спрайта
			}
	
};

class Backround //Класс фона
{
	public:
		float x,w,h; // Y отсутствует т.к. анимация фона происходит только по X
		String File;
		Image image;  // СФМЛ картинка , текстура , спрайт
		Texture texture, texture1;
		Sprite sprite, sprite1;

		Backround(String F)
		{
			x=0; w=1280; h=720; File = F;
			image.loadFromFile("BG/" + File);
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, 1280, 720));
		}
		void BgUpdate(float time)
		{
			texture1.loadFromImage(image);
			sprite1.setTexture(texture1);
			sprite1.setTextureRect(IntRect(0, 0, 1280, 720));
		
			if(x<0)
				x=1280;
			x-=0.1*time;
			sprite1.setPosition(x-1280,0);
			sprite.setPosition(x,0);
		}
};

int main()
{
	RenderWindow window(sf::VideoMode(1280, 720), "EndlessCourser <3");
	float CurFrame=0;
	Clock clock;
	Backround Fon("Forest.png");
	Players Hero("lowadi.png",500,500,64,64);

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
 
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)			
			window.close();
		}
		
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) 
		{
			Hero.dir = 1; Hero.speed = 0.2;//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
			CurFrame += 0.005*time;
			if (CurFrame > 4) CurFrame -= 4; 
			Hero.sprite.setTextureRect(IntRect(64 * int(CurFrame), 128, 64, 64)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
		} 
		else
		{
			CurFrame += 0.008*time;
			if (CurFrame > 4) CurFrame -= 4; 
			Hero.sprite.setTextureRect(IntRect(64 * int(CurFrame), 128, 64, 64));
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) 
		{
			Hero.dir = 0; Hero.speed = 0.2;//направление вправо, см выше
			 //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
		}
 
		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) 
		{ 
			Hero.dir = 2; Hero.speed = 0.2;//прыжок
			//CurrentFrame += 0.005*time;
			//if (CurrentFrame > 3) CurrentFrame -= 3;
			//p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));  //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
			
		}
			
			
		Fon.BgUpdate(time);
		Hero.update(time);
 
		window.clear();
		window.draw(Fon.sprite1);
		window.draw(Fon.sprite);
		window.draw(Hero.sprite);
		window.display();
	}
 
	return 0;
}