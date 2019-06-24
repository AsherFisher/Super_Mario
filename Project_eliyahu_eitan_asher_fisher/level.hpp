#pragma once

#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio.lib")
#else
#error "Unrecognized configuration!"
#endif

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tinyxml.h"

// This struct represents a game object
struct Object
{
    int GetPropertyInt(std::string name);
    float GetPropertyFloat(std::string name);
    std::string GetPropertyString(std::string name);

    std::string name;
    std::string type;
    sf::Rect<float> rect;
    std::map<std::string, std::string> properties;

	sf::Sprite sprite;
};

// This struct represents a tmx level layer
struct Layer
{
    int opacity;
    std::vector<sf::Sprite> tiles;
};

// This class represents a tmx level
class Level
{
public:
    bool LoadFromFile(std::string filename);
    Object GetObject(std::string name);
    std::vector<Object> GetObjects(std::string name);
	std::vector<Object> GetAllObjects();
    void Draw(sf::RenderWindow &window);
	sf::Vector2i GetTileSize();

private:
    int width, height, tileWidth, tileHeight;
    int firstTileID;
    sf::Rect<float> drawingBounds;
    sf::Texture tilesetImage;
    std::vector<Object> objects;
    std::vector<Layer> layers;
};