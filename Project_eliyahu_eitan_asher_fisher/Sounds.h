#pragma once
#include <map>
#include <string>
#include <SFML/Audio.hpp>

//============================================================================

class Sounds
{
public:

	// c'tor
	Sounds();
	// play sound
	static void play(const std::string & sound);
	// pause sound
	static void pause(const std::string & sound);
	// d'tor
	~Sounds();

private:

	// map to set the sound based on the string
	static std::map<std::string, sf::Sound> m_sounds;
	// sounds for the game
	static sf::SoundBuffer m_coin;
	static sf::SoundBuffer m_click;
	static sf::SoundBuffer m_hover;
	static sf::SoundBuffer m_lvlbck;
	static sf::SoundBuffer m_mnubck;
	static sf::SoundBuffer m_jump;
	static sf::SoundBuffer m_KillMario;
	static sf::SoundBuffer m_endLevel;
	static sf::SoundBuffer m_killEnemy;
	static sf::SoundBuffer m_applause;
	static sf::SoundBuffer m_explodeTile;
	static sf::SoundBuffer m_gameWon;
};

