#ifndef _XIE2YUE_CONSOLE_2_H
#define _XIE2YUE_CONSOLE_2_H

#include "Button.h"
#include <vector>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>


class console2 {
	private:

	static int Mode;
	
	static sf::Font font;
	
	enum class CommandID{
		C_ESC, C_NaC,
		C_0, C_1, C_2, C_3, C_4, C_5, C_6, C_7, C_8, C_9, C_X, C_C,
		C_Eql, C_Pls, C_Mns, C_Mul, C_Div, C_Pow, C_Lpr, C_Rpr, C_Del,
		C_M1, C_M2, C_M3, C_M4,
		C_M2F1, C_M2F2
	};
	
	class RenderButton {
		private:
		Button body_;
		std::function<bool()> enable_;
		CommandID cid_;
		public:
		RenderButton(Button body, std::function<bool()> enable, CommandID cid): 
			body_(std::move(body)), enable_(std::move(enable)) ,cid_(cid){}
	    void draw(sf::RenderWindow& window) const {
	    	if(enable_()) body_.draw(window);
	    }
	    bool isHovered(sf::Vector2f mousePos) const{
	    	return enable_() && body_.isHovered(mousePos);
		}
		CommandID getCommandID() const{
			return cid_;
		}
		void setString(sf::String textStr) {
			body_.setString(textStr);
		}
	};
	
	std::vector<RenderButton> buttons;
	
	std::string ctos;
	
	std::map<CommandID, std::string> ctoc{
		{CommandID::C_0, "0"}, {CommandID::C_1, "1"}, {CommandID::C_2, "2"}, {CommandID::C_3, "3"},
		{CommandID::C_4, "4"}, {CommandID::C_5, "5"}, {CommandID::C_6, "6"}, {CommandID::C_7, "7"},
		{CommandID::C_8, "8"}, {CommandID::C_9, "9"}, {CommandID::C_X, "X"}, {CommandID::C_Pls, "+"},
		{CommandID::C_Mns, "-"}, {CommandID::C_Mul, "*"}, {CommandID::C_Div, "/"},
		{CommandID::C_Pow, "^"}, {CommandID::C_Lpr, "("}, {CommandID::C_Rpr, ")"}
	};
	
	CommandID command_;
	public:
	void initFontAndButton() {
		if(! font.openFromFile("simsun.ttc"))
		if(! font.openFromFile("C:/Windows/Fonts/simsun.ttc"))
		if(! font.openFromFile("C:/Windows/Fonts/msyc.ttc"))
		if(! font.openFromFile("C:/Windows/Fonts/tuffy.ttc")) {
			std::cout<<"请检查字体于 C:/Windows/Fonts/xxx.ttc(.ttf)\n";
			exit(-1);
		}
		
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "1", 24, sf::Vector2f{001, 101}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_1
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "4", 24, sf::Vector2f{001, 201}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_4
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "7", 24, sf::Vector2f{001, 301}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_7
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, L"退格", 24, sf::Vector2f{001, 401}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_Del
		);
		
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "2", 24, sf::Vector2f{101, 101}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_2
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "5", 24, sf::Vector2f{101, 201}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_5
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "8", 24, sf::Vector2f{101, 301}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_8
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "0", 24, sf::Vector2f{101, 401}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_0
		);
		
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "3", 24, sf::Vector2f{201, 101}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_3
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "6", 24, sf::Vector2f{201, 201}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_6
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "9", 24, sf::Vector2f{201, 301}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_9
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "=", 24, sf::Vector2f{201, 401}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_Eql
		);
		
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "+", 24, sf::Vector2f{301, 101}, sf::Color{195, 195, 195}),
			[this](){ return Mode % 2 == 1;},
			CommandID::C_Pls
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "-", 24, sf::Vector2f{301, 201}, sf::Color{195, 195, 195}),
			[this](){ return Mode % 2 == 1;},
			CommandID::C_Mns
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "*", 24, sf::Vector2f{301, 301}, sf::Color{195, 195, 195}),
			[this](){ return Mode % 2 == 1;},
			CommandID::C_Mul
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "/", 24, sf::Vector2f{301, 401}, sf::Color{195, 195, 195}),
			[this](){ return Mode % 2 == 1;},
			CommandID::C_Div
		);
		
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, L"判断\n素数", 24, sf::Vector2f{301, 101}, sf::Color{195, 195, 195}),
			[this](){ return Mode == 2;},
			CommandID::C_M2F1
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, L"生成\n素数", 24, sf::Vector2f{301, 201}, sf::Color{195, 195, 195}),
			[this](){ return Mode == 2;},
			CommandID::C_M2F2
		);
		
		
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "C", 24, sf::Vector2f{401, 101}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_C
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "(", 24, sf::Vector2f{401, 201}, sf::Color{195, 195, 195}),
			[this](){ return Mode == 1;},
			CommandID::C_Lpr
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "X", 24, sf::Vector2f{401, 201}, sf::Color{195, 195, 195}),
			[this](){ return Mode == 3;},
			CommandID::C_X
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, ")", 24, sf::Vector2f{401, 301}, sf::Color{195, 195, 195}),
			[this](){ return Mode == 1;},
			CommandID::C_Rpr
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, "^", 24, sf::Vector2f{401, 401}, sf::Color{195, 195, 195}),
			[this](){ return Mode % 2 == 1;},
			CommandID::C_Pow
		);
		
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, L"有理数\n计算器", 24, sf::Vector2f{501, 101}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_M1
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, L"数论\n工具", 24, sf::Vector2f{501, 201}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_M2
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, L"因式\n分解", 24, sf::Vector2f{501, 301}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_M3
		);
		buttons.emplace_back(
			Button(sf::Vector2f{98.f, 98.f}, font, L"图论\n工具", 24, sf::Vector2f{501, 401}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_M4
		);
		
		buttons.emplace_back(
			Button(sf::Vector2f{598.f, 98.f}, font, "", 24, sf::Vector2f{1, 1}, sf::Color{195, 195, 195}),
			[](){ return true;},
			CommandID::C_NaC
		);
	}
	
	CommandID getInputCID(const sf::Event& event) {
		if(const auto* keyEvent = event.getIf<sf::Event::KeyPressed>()) {
			if(keyEvent->scancode == sf::Keyboard::Scan::Escape) { return CommandID::C_ESC; }
			else if(keyEvent->scancode == sf::Keyboard::Scan::Num1) { return CommandID::C_1; }
			else if(keyEvent->scancode == sf::Keyboard::Scan::Num2) { return CommandID::C_2; }
			else if(keyEvent->scancode == sf::Keyboard::Scan::Num3) { return CommandID::C_3; }
			else if(keyEvent->scancode == sf::Keyboard::Scan::Num4) { return CommandID::C_4; }
			else if(keyEvent->scancode == sf::Keyboard::Scan::Num5) { return CommandID::C_5; }
			else if(keyEvent->scancode == sf::Keyboard::Scan::Num6) {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift)) {
					if(Mode % 2 == 1) return CommandID::C_Pow;/*^*/
				}
				else { return CommandID::C_6; }
			}
			else if(keyEvent->scancode == sf::Keyboard::Scan::Num7) { return CommandID::C_7; }
			else if(keyEvent->scancode == sf::Keyboard::Scan::Num8) {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift)) {
					if(Mode % 2 == 1) return CommandID::C_Mul;/***/ 
				}
				else { return CommandID::C_8; }
			}
			else if(keyEvent->scancode == sf::Keyboard::Scan::Num9) {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift)) {
					if(Mode == 1) return CommandID::C_Lpr;/*(*/
				}
				else { return CommandID::C_9; }
			}
			else if(keyEvent->scancode == sf::Keyboard::Scan::Num0) {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift)) {
					if(Mode == 1) return CommandID::C_Rpr;/*)*/
				}
				else { return CommandID::C_0; }
			}
			else if(keyEvent->scancode == sf::Keyboard::Scan::X) {
				if(Mode == 3) return CommandID::C_X;
			}
			else if(keyEvent->scancode == sf::Keyboard::Scan::Equal) {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift)) {
					if(Mode % 2 == 1) return CommandID::C_Pls;/*+*/ 
				}
				else { return CommandID::C_Eql;/*=*/ }
			}
			else if(keyEvent->scancode == sf::Keyboard::Scan::Enter) { return CommandID::C_Eql;/*Enter*/ }
			else if(keyEvent->scancode == sf::Keyboard::Scan::Hyphen) {
				if(Mode % 2 == 1) return CommandID::C_Mns;/*-*/ 
			}
			else if(keyEvent->scancode == sf::Keyboard::Scan::Slash) {
				if(Mode % 2 == 1) return CommandID::C_Div;/*/*/
			}
			else if(keyEvent->scancode == sf::Keyboard::Scan::C) { return CommandID::C_C;/*C*/ }
			else if(keyEvent->scancode == sf::Keyboard::Scan::Backspace) { return CommandID::C_Del;/*BackSpace*/ }
			else if(keyEvent->scancode == sf::Keyboard::Scan::Delete) { return CommandID::C_Del;/*Delete*/ }
		}
		
		if(const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
			if(mouseEvent->button == sf::Mouse::Button::Left) {
				sf::Vector2f mouseClickPosition = {(float)mouseEvent->position.x, (float)mouseEvent->position.y};
				
				for(const auto& btn : buttons) {
					if(btn.isHovered(mouseClickPosition)) return btn.getCommandID();
				}
			}
		}
		return CommandID::C_NaC;
	}
	
	void ClearConsole() {
		ctos.clear();
		buttons.back().setString("");
	}
	
	
	
	void Run() {
		initFontAndButton();
		
		sf::RenderWindow window(sf::VideoMode({600, 500}), L"和亿位计算器 - By Xie2Yue喵 - v0.0.2");
		
		while(window.isOpen()) {
			while(std::optional<sf::Event> event = window.pollEvent()) {
				if(event->is<sf::Event::Closed>()) window.close();
				
				command_ = getInputCID(*event);
				
				if(command_ == CommandID::C_ESC) {
					window.close();
					return;
				}
				if(command_ != CommandID::C_NaC) {
					std::cout<<(int)(command_)<<"\n";
				}
				if(command_ == CommandID::C_M1) { Mode = 1; ClearConsole(); }
				else if(command_ == CommandID::C_M2 ) { Mode = 2; ClearConsole(); }
				else if(command_ == CommandID::C_M3 ) { Mode = 3; ClearConsole(); }
				else if(command_ == CommandID::C_M4 ) { Mode = 4; ClearConsole(); }
				else if(command_ == CommandID::C_C  ) { ClearConsole(); }
				else if(command_ == CommandID::C_Del) { if(!ctos.empty()) ctos.pop_back(); }
				ctos+=ctoc[command_];
				buttons.back().setString(ctos);
			}
			window.clear(sf::Color::Black);
			for(const auto&btn : buttons) btn.draw(window);
			window.display();
		}
	}
};






#endif