#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#include<iostream>
#include<memory>
#include<fstream>
#include<string>
#include<vector>
class Win {
public:
	unsigned int wWid;
	unsigned int wHei;
	Win(unsigned int ww, unsigned int wh) :wWid(ww), wHei(wh) {}
};
class Font {
public:
	std::string filename;
	int fontsize;
	int r;
	int g;
	int b;
	Font(std::string fn, int fs, int rr, int gg, int bb) :filename(fn), fontsize(fs), r(rr), g(gg), b(bb) {}
};
class Shape {
public:
	std::string name;
	float x;
	float y;
	float speed_x;
	float speed_y;
	int R;
	int B;
	int G;
	float scale = 1.0f;
	bool DrawShape;
	Shape(std::string na, float X, float Y, float sx, float sy, int r, int g, int b) :name(na), x(X), y(Y), speed_x(sx), speed_y(sy), R(r), G(b), B(g) { DrawShape = true; }
};
class Circle :public Shape {
public:
	float Radius;
	Circle(std::string na, float xx, float yy, float sx, float sy, int r, int g, int b, float rr) :Shape(na, xx, yy, sx, sy, r, g, b), Radius(rr) {}
	bool isCircle() { return true; }
	bool isRec() { return false; }

};
class Rectangle :public Shape {
public:
	float Width;
	float Height;
	Rectangle(std::string na, float xx, float yy, float sx, float sy, int r, int g, int b, float wi, float he) :Shape(na, xx, yy, sx, sy, r, g, b), Width(wi), Height(he) {}
	bool isCircle() { return false; }
	bool isRec() { return true; }

};
void loadFromFile(const std::string& filename, Font& f, std::vector<Circle>& Cir, std::vector<Rectangle>& Rec, Win& w) {
	std::ifstream fin(filename);
	std::string first;
	while (fin >> first) {
		if (first == "Window") {
			int www, hhh;
			fin >> www >> hhh;
			w.wWid = www;
			w.wHei = hhh;
		}
		else if (first == "Font") {
			std::string name;
			int size, r, g, b;
			fin >> name >> size >> r >> g >> b;
			f.filename = name;
			f.fontsize = size;
			f.r = r;
			f.g = g;
			f.b = b;
		}
		else if (first == "Rectangle") {  // Removed extra space
			std::string name;
			int r, g, b;
			float xx, yy, sx, sy, w, h;
			fin >> name >> xx >> yy >> sx >> sy >> r >> g >> b >> w >> h;
			Rec.emplace_back(name, xx, yy, sx, sy, r, g, b, w, h);
		}
		else if (first == "Circle") {
			std::string name;
			float xx, yy, sx, sy, radius;
			int r, g, b;
			fin >> name >> xx >> yy >> sx >> sy >> r >> g >> b >> radius;
			Cir.emplace_back(name, xx, yy, sx, sy, r, g, b, radius);
		}
	}
}


int main(int argc, char* argv[]) {

	//create a new window of size w*h pixels
	//top - left of the window is (0,0) and bootom right is (w,h)

	//you wil have to read these from the config file 
	std::vector<Circle> vc;
	std::vector<Rectangle> vr;
	Font fn("Roboto/static/Roboto_Condensed-Bold.ttf", 0, 0, 0, 0);
	Win  w(1280, 720);
	std::cout << (int)w.wWid << " " << (int)w.wHei << " " << std::endl;
	loadFromFile("config.txt", fn, vc, vr, w);
	std::cout << w.wWid << " " << w.wHei << " " << std::endl;
	std::cout << fn.filename << " " << fn.fontsize << " " << fn.r << " " << fn.g << " " << fn.b << std::endl;
	for (auto& it : vc) {
		std::cout << it.name << " " << it.speed_x << " " << it.speed_y << " " << it.x << " " << it.y << " " << it.R << " " << it.G << " " << it.B << " " << it.Radius << " " << it.DrawShape << std::endl;
	}
	for (auto& it : vr) {
		std::cout << it.name << " " << it.x << " " << it.y << " " << it.speed_x << " " << it.speed_y << " " << it.R << " " << it.G << " " << it.B << " " << it.Width << " " << it.Height << " " << it.DrawShape << std::endl;
	}
	int item_selected_idx = 0;


	sf::RenderWindow window(sf::VideoMode({ w.wWid,w.wHei }), "SFML works!");
	window.setFramerateLimit(60);
	//intialize Imgui and create a clock used for internal timing
	ImGui::SFML::Init(window);
	sf::Clock deltaClock;
	//scale the imgui ui and text size by 2
	ImGui::GetStyle().ScaleAllSizes(2.0f);
	ImGui::GetIO().FontGlobalScale = 2.0f;
	//the imgui color {r,g,b}wheel require flolats from 0-1 instead of ints form 0-255
	//float c[3] = { 0.0f,1.0f,1.0f };
	//let make shape we will draw to the screen
	//float circleRadius = 50;//radius to draw a circle
	//int circleSegments = 32;//number of segments to draw the circle with
	//float circleSpeedX = 1.0f;//we will use this to move the circle later
	//float circleSpeedY = 0.5f;//whether or not to draw the circle
	//bool drawCircle = true;
	//bool drawText = true;
	float scale = 1.0f;
	//create the sfml circle based on our parameters
	std::vector<sf::CircleShape> cicles;
	for (auto& it : vc) {
		sf::CircleShape newcircle(it.Radius, 60);
		newcircle.setPosition({ it.x,it.y });
		cicles.emplace_back(newcircle);
	}
	std::vector<sf::RectangleShape> rectangles;
	for (auto& it : vr) {
		sf::RectangleShape newrec(sf::Vector2f(it.Width, it.Height));
		newrec.setPosition({ it.x,it.y });
		rectangles.emplace_back(newrec);
	}
	//sf::CircleShape circle(circleRadius, circleSegments);
	//circle.setPosition({ 10.0f, 10.0f });
	//lets load a font so we can display some text
	sf::Font myFont;

	//attemts to load the font from a file 
	if (!myFont.openFromFile(fn.filename))
	{
		//if we cannot load the font print an error to error console
		std::cerr << "could not load the font\n";
		exit(-1);
	}
	sf::Text text(myFont, "Sample Text", 24);
	//position the top-left corner of the text so that text aligns on the bottom
	//text charactger size is in pixels so move the text up from the bottom by its height
	text.setPosition({ 0, w.wHei - (float)text.getCharacterSize() });
	//set up char array to set the text
	char displayString[255] = "Sample Text";
	//main loop continues for eaach frame while window is open
	while (window.isOpen()) {
		//event handling 

		while (const auto eventOpt = window.pollEvent())
		{
			ImGui::SFML::ProcessEvent(window, *eventOpt);  // Dereference here
			if (eventOpt->is<sf::Event::Closed>())
				window.close();
			/*if (eventOpt->is<sf::Event::KeyPressed>())
			{
				if (auto keyEvent = eventOpt->getIf<sf::Event::KeyPressed>())
				{
					if (keyEvent->code == sf::Keyboard::Key::X)
						circleSpeedX *= -1.0f;
				}
			}*/
		}
		//update imgui for this frame with the time that the last frame took
		ImGui::SFML::Update(window, deltaClock.restart());
		//draw the ui
		ImGui::Begin("Shape Properties");
		ImGui::Text("window text!");
		//const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
		//static int item_selected_idx = 0; // Here we store our selection data as an index.
		std::vector<const char*> items;
		for (auto& s : vc) { items.emplace_back(s.name.c_str()); }
		for (auto& s : vr) { items.emplace_back(s.name.c_str()); }

		// Pass in the preview value visible before opening the combo (it could technically be different contents or not pulled from items[])


		const char* combo_preview_value = items[item_selected_idx];
		if (ImGui::Combo("shape", &item_selected_idx, items.data(), (int)items.size()))
		{
			combo_preview_value = items[item_selected_idx];
		};

		for (auto& it : vc) {
			if (it.name == combo_preview_value) {
				ImGui::Checkbox("Draw Shape", &it.DrawShape);
				ImGui::SliderFloat("Scale", &scale, 0.0f, 4.0f);
				float v[2] = { it.speed_x,it.speed_y };
				float vec3i[3] = { it.R / 255.0f,it.G / 255.0f,it.B / 255.0f };
				if (ImGui::SliderFloat2("Velocity", v, -8.0f, 8.0f)) {
					it.speed_x = v[0];
					it.speed_y = v[1];
				}
				//ImGui::SliderInt3("slider int3", vec3i, 0, 255)
				if (ImGui::ColorEdit3("Color Shape", vec3i)) {
					it.R = static_cast<int>(vec3i[0] * 255);
					it.G = static_cast<int>(vec3i[1] * 255);
					it.B = static_cast<int>(vec3i[2] * 255);
				}
				if (ImGui::InputText("Text", displayString, 255)) {
					for (auto& jt : items) {
						if (jt == it.name) {
							jt = displayString;
						}

					}
					it.name = { displayString };
				}



				it.scale = scale;

			}
		}
		for (auto& it : vr) {
			if (it.name == combo_preview_value) {
				ImGui::Checkbox("Draw Shape", &it.DrawShape);
				ImGui::SliderFloat("Scale", &scale, 0.0f, 4.0f);
				float v[2] = { it.speed_x,it.speed_y };
				float vec3i[3] = { it.R / 255.0f,it.G / 255.0f,it.B / 255.0f };
				if (ImGui::SliderFloat2("Velocity", v, -8.0f, 8.0f)) {
					it.speed_x = v[0];
					it.speed_y = v[1];
				}
				//ImGui::SliderInt3("slider int3", vec3i, 0, 255)
				if (ImGui::ColorEdit3("Color Shape", vec3i)) {
					it.R = static_cast<int>(vec3i[0] * 255);
					it.G = static_cast<int>(vec3i[1] * 255);
					it.B = static_cast<int>(vec3i[2] * 255);
				}
				if (ImGui::InputText("Text", displayString, 255)) {
					for (auto& jt : items) {
						if (jt == it.name) {
							jt = displayString;
						}

					}
					it.name = { displayString };
				}



				it.scale = scale;
			}
		}
		combo_preview_value = items[item_selected_idx];


		//ImGui::SameLine();
		//ImGui::Checkbox("Draw Text", &drawText);

		/*ImGui::SliderFloat("Radius", &circleRadius, 0.0f, 300.0f);
		ImGui::SliderInt("Slides", &circleSegments, 3, 64);
		ImGui::ColorEdit3("Color Circle", c);*/


		/*	if (ImGui::Button("Set Text"))
			{
				text.setString(displayString);
			}
			ImGui::SameLine();
			if (ImGui::Button("Reset Circle"))
			{
				circle.setPosition({ 0, 0 });
			}*/
		ImGui::End();
		//set the circle properties because they may have been updated with the ui
		for (int i = 0;i < cicles.size();i++) {
			//it.setScale(sf::Vector2f())
			if (cicles[i].getPosition().x < 0 || cicles[i].getPosition().x > w.wWid) vc[i].speed_x *= -1;
			if (cicles[i].getPosition().y < 0 || cicles[i].getPosition().y > w.wHei) vc[i].speed_y *= -1;


			cicles[i].setScale(sf::Vector2f({ vc[i].scale,vc[i].scale }));
			cicles[i].setPosition({ cicles[i].getPosition().x + vc[i].speed_x,cicles[i].getPosition().y + vc[i].speed_y });
			cicles[i].setFillColor(sf::Color(static_cast<std::uint8_t>(vc[i].R), static_cast<std::uint8_t>(vc[i].G), static_cast<std::uint8_t>(vc[i].B)));


		}
		for (int i = 0;i < rectangles.size();i++) {
			// And for rectangles
			if (rectangles[i].getPosition().x < 0 || rectangles[i].getPosition().x > w.wWid) vr[i].speed_x *= -1;
			if (rectangles[i].getPosition().y < 0 || rectangles[i].getPosition().y > w.wHei) vr[i].speed_y *= -1;
			rectangles[i].setScale(sf::Vector2f({ vr[i].scale,vr[i].scale }));
			rectangles[i].setPosition({ rectangles[i].getPosition().x + vr[i].speed_x,rectangles[i].getPosition().y + vr[i].speed_y });
			rectangles[i].setFillColor(sf::Color(static_cast<std::uint8_t>(vr[i].R), static_cast<std::uint8_t>(vr[i].G), static_cast<std::uint8_t>(vr[i].B)));
		}
		/*	circle.setPointCount(circleSegments);
			circle.setRadius(circleRadius);*/
			//imgui uses 0-1 float for colors ,sfml usess0-255 for colors
			//we must convert fromt the ui floats to sfml Uint8
		/*	circle.setFillColor(sf::Color(static_cast<std::uint8_t>(c[0] * 255),static_cast<std::uint8_t>(c[1] * 255),static_cast<std::uint8_t>(c[2] * 255) ));
			circle.setPosition({ circle.getPosition().x + circleSpeedX, circle.getPosition().y + circleSpeedY })*/;
			//basiz rendering funciton calls
		window.clear();//clear the winow of anyting previously draws
		//it is imp to call window .clear else it become a paint brust
		//and it is 
		for (int i = 0;i < cicles.size();i++) {
			if (vc[i].DrawShape == true) {
				window.draw(cicles[i]);
			}
		}
		for (int i = 0;i < rectangles.size();i++) {
			if (vr[i].DrawShape == true)window.draw(rectangles[i]);
		}
		//if (drawCircle)//darw the circle if boolean is true
		//{
		//	window.draw(circle);
		//}
		//if (drawText) {
		//	window.draw(text);
		//}
		ImGui::SFML::Render(window);//draw the ui last so it is on the top
		window.display();//call the window funtion
	}
	return 0;

}