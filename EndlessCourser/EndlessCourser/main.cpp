#include <SFML/Graphics.hpp>

using namespace sf;
 

class Players //����� ����� ��� ���������� ��������
{
	public:
		int Ground;
		float x,y,w,h,dx,dy,speed; //���������� ������ ������ ��������
		int dir;  //����������� 
		String File; //��� �����
		Image image;  // ���� �������� , �������� , ������
		Texture texture;
		Sprite sprite;

		Players(String F, float X, float Y, float H, float W) // �����������
		{
			dx=0;	dy=0;	speed=0;	dir=0;
			x=X;	y=Y;	w=W;	h=H;
			File = F;	Ground=500;
			image.loadFromFile("IM/" + File);
			//image.createMaskFromColor(Color(41, 33, 59));  ������� ���, ������� �� ������� ��������
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
			void update(float time) // ������������� 
			{
				switch (dir) // ����������� ��������
				{
					case 0: dx = speed; dy = 0; break; // 0 - ������
					case 1: dx = -speed; dy = 0; break; // 1 - �����
					case 2: /*dy = -0.5;*/ break;	// 2 - ������
				
				}
 
			x += dx*time; // �������� = ��������� �� �����
			y += dy*time;
			//if(x<Ground)
				//dy = dy + 0.0015*time;
			speed = 0; // ��������� ��������
			sprite.setPosition(x,y); // ����� �������
			}
	
};

class Backround //����� ����
{
	public:
		float x,w,h; // Y ����������� �.�. �������� ���� ���������� ������ �� X
		String File;
		Image image;  // ���� �������� , �������� , ������
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
			Hero.dir = 1; Hero.speed = 0.2;//dir =1 - ����������� �����, speed =0.1 - �������� ��������. �������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
			CurFrame += 0.005*time;
			if (CurFrame > 4) CurFrame -= 4; 
			Hero.sprite.setTextureRect(IntRect(64 * int(CurFrame), 128, 64, 64)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
		} 
		else
		{
			CurFrame += 0.008*time;
			if (CurFrame > 4) CurFrame -= 4; 
			Hero.sprite.setTextureRect(IntRect(64 * int(CurFrame), 128, 64, 64));
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) 
		{
			Hero.dir = 0; Hero.speed = 0.2;//����������� ������, �� ����
			 //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
		}
 
		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) 
		{ 
			Hero.dir = 2; Hero.speed = 0.2;//������
			//CurrentFrame += 0.005*time;
			//if (CurrentFrame > 3) CurrentFrame -= 3;
			//p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));  //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
			
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