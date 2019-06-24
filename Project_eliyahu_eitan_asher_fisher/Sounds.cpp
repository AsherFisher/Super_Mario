#include "Sounds.h"
#include "Constants.h"


Sounds::Sounds()
{
	m_KillMario.loadFromFile(paths::snd_KillMario_path);
	m_coin.loadFromFile(paths::snd_coin_path);
	m_click.loadFromFile(paths::snd_clk_path);
	m_hover.loadFromFile(paths::snd_hvr_path);
	m_lvlbck.loadFromFile(paths::snd_lvl_bck_path);
	m_mnubck.loadFromFile(paths::snd_mnu_bck_path);
	m_endLevel.loadFromFile(paths::snd_endLevel_path);
	m_killEnemy.loadFromFile(paths::snd_killEnemy_path);
	m_applause.loadFromFile(paths::snd_applause_path);
	m_explodeTile.loadFromFile(paths::snd_explodeTile_path);
	m_jump.loadFromFile(paths::snd_jump_path);
	m_gameWon.loadFromFile(paths::snd_gameWon_path);


	m_sounds["endLevel"] = sf::Sound(m_endLevel);
	m_sounds["explodeTile"] = sf::Sound(m_explodeTile);
	m_sounds["applause"] = sf::Sound(m_applause);
	m_sounds["killEnemy"] = sf::Sound(m_killEnemy);
	m_sounds["jump"] = sf::Sound(m_jump);
	m_sounds["KillMario"] = sf::Sound(m_KillMario);
	m_sounds["coin"] = sf::Sound(m_coin);
	m_sounds["click"] = sf::Sound(m_click);
	m_sounds["hover"] = sf::Sound(m_hover);
	m_sounds["game"] = sf::Sound(m_lvlbck);
	m_sounds["menu"] = sf::Sound(m_mnubck);
	m_sounds["gameWon"] = sf::Sound(m_gameWon);

	m_sounds["game"].setLoop(true);
	m_sounds["menu"].setLoop(true);
}


//=======================================================================

void Sounds::play(const std::string & sound)
{
	m_sounds[sound].stop();
	m_sounds[sound].play();
}

//========================================================================

void Sounds::pause(const std::string & sound)
{
	m_sounds[sound].pause();
}

//==========================================================================

std::map<std::string, sf::Sound> Sounds::m_sounds;
sf::SoundBuffer Sounds::m_coin;
sf::SoundBuffer Sounds::m_click;
sf::SoundBuffer Sounds::m_hover;
sf::SoundBuffer Sounds::m_lvlbck;
sf::SoundBuffer Sounds::m_mnubck;
sf::SoundBuffer Sounds::m_jump;
sf::SoundBuffer Sounds::m_KillMario;
sf::SoundBuffer Sounds::m_endLevel;
sf::SoundBuffer Sounds::m_killEnemy;
sf::SoundBuffer Sounds::m_applause;
sf::SoundBuffer Sounds::m_explodeTile;
sf::SoundBuffer Sounds::m_gameWon;

//============================================================================

Sounds::~Sounds()
{}
