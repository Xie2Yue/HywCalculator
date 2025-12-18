#ifndef _XIE2YUE_BUTTON_H
#define _XIE2YUE_BUTTON_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define uint unsigned int

class Button {
	private:
		sf::RectangleShape body_;
		sf::Text text_;
		
	    void centerText() {
		    sf::FloatRect textBounds = text_.getLocalBounds();
		    sf::FloatRect bodyBounds = body_.getGlobalBounds();
		    
		    auto textPos = textBounds.position;
		    auto textSize = textBounds.size;
		    auto bodyPos = bodyBounds.position;
		    auto bodySize = bodyBounds.size;
		    
		    text_.setOrigin({textPos.x + textSize.x / 2.0f,
		                   textPos.y + textSize.y / 2.0f});
		    text_.setPosition({bodyPos.x + bodySize.x / 2.0f,
		                     bodyPos.y + bodySize.y / 2.0f});
	    }

	public:
		
		Button(sf::Vector2f bodySize, sf::Font& font, sf::String textStr, uint textSize): body_(bodySize), text_({font, textStr, textSize}) {}
		
		Button(sf::RectangleShape body, sf::Text text): body_(std::move(body)), text_(std::move(text)) {}
		
		Button(sf::RectangleShape body, sf::Text text, sf::Vector2f pos): body_(std::move(body)), text_(std::move(text)) { setPosition(pos); }
		
		Button(sf::Vector2f bodySize, sf::Font& font, sf::String textStr, uint textSize, sf::Vector2f pos):
			body_(bodySize), text_({font, textStr, textSize}) { setPosition(pos); }
		
		Button(sf::Vector2f bodySize, sf::Font& font, sf::String textStr, uint textSize,
				sf::Vector2f pos, sf::Color bodyColor = {195, 195, 195}, sf::Color textColor = sf::Color::Black):
			body_(bodySize), text_({font, textStr, textSize}) { setPosition(pos); setFillColor(bodyColor, textColor); }
			
		Button(sf::RectangleShape body, sf::Text text, sf::Vector2f pos, sf::Color bodyColor = {195, 195, 195}, sf::Color textColor = sf::Color::Black):
			body_(std::move(body)), text_(std::move(text)) { setPosition(pos); setFillColor(bodyColor, textColor); }
		
		void setFillColor(sf::Color bodyColor, sf::Color textColor) {
	        body_.setFillColor(bodyColor);
	        text_.setFillColor(textColor);
	    }
	    
	    void setPosition(sf::Vector2f pos) {
	        body_.setPosition(pos);
	        centerText();
	    }
    
	    bool isHovered(const sf::Vector2f& mousePos) const {
	        return body_.getGlobalBounds().contains(mousePos);
	    }
    
	    void draw(sf::RenderWindow& window) const {
	        window.draw(body_);
	        window.draw(text_);
	    }
	    void setString(sf::String textStr) {
	    	text_.setString(textStr);
	    	centerText();
		}
};


#undef uint
#endif