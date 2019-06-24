#pragma once
#include <SFML/Graphics.hpp>

//====================================================================

//	Name-space for all constant sizes of the game.

namespace sizes
{
	//	Window sizes
	const float win_wd = 1200;
	const float win_ht = 750;
	
	//	Button sizes
	const int bt_menu_x = 120;
	const int bt_play_x = 480;
	const int bt_play_y = 250;
	const int bt_help_y = 100;
	const int bt_crd_y = 250;
	const int bt_exit_y = 400;
	const int bt_back_x = 0;
	const int bt_back_y = 0;

	//	Font sizes
	const int font_size = 30;
	const int mes_font_size = 100;
	
	// size of the View while game is played
	const sf::FloatRect viewSize = { 0, 0, 950, 650 };

	//	num of Levels
	const int numofLevels = 3;

	// the score to add when coin is earned
	const int CoinValue = 10;
	//the score to add when enemy is killed
	const int killValue = 20;
}

//==============================================================================

//	Name-space for all constant paths

namespace paths
{
	//	path to cursor
	const std::string cursor_path = "Graphics\\cursor.png";
	//	Level TextFile Path
	const std::string level_path = "Level\\level";
	//	Background Texture Path
	const std::string backrnd_path = "Graphics\\background.jpg";
	//	Menu Texture Path
	const std::string menu_path = "Graphics\\menu.png";
	//	Help Texture Path
	const std::string help_path = "Graphics\\help.png";
	//	Credits Texture Path
	const std::string crds_path = "Graphics\\credits.png";

	//	Background Game Texture Path
	const std::string backrnd_game_path1 = "Graphics\\Game_Background1.png";
	const std::string backrnd_game_path2 = "Graphics\\Game_Background2.png";
	const std::string backrnd_game_path3 = "Graphics\\Game_Background3.png";

	// massage Images paths
	const std::string massage_game_over_path = "Graphics\\game_over.png";
	const std::string massage_game_completed_path = "Graphics\\game_completed.png";
	const std::string massage_level_up_path = "Graphics\\level_up.png";
	
	//	shapes Path
	const std::string sh_tile = "Graphics\\tile.jpg";
	const std::string sh_mario = "Graphics\\mario.png";
	const std::string sh_coinTile = "Graphics\\coinTile.png";
	const std::string sh_removableTile = "Graphics\\RemovableTile.png";
	const std::string sh_solidTile = "Graphics\\SolidTile.png";
	const std::string sh_animation_mario = "Graphics\\Mario_animation.png";
	const std::string anim_mario = "Graphics\\Mario.xml";
	const std::string sh_animation_turtle = "Graphics\\Enemys.png";
	const std::string sh_animation_gumba = "Graphics\\Enemys.png";
	const std::string anim_turtle = "Graphics\\Turtle.xml";
	const std::string anim_gumba = "Graphics\\Gumba.xml";
	const std::string sh_animation_coin = "Graphics\\coin.png";
	const std::string sh_used_tile = "Graphics/usedTile.png";
	const std::string anim_coin = "Graphics\\Coin.xml";
	const std::string anim_shot = "Graphics\\Shot.xml";
	const std::string sh_animation_elevator = "Graphics\\elevator.png";
	const std::string anim_elevator = "Graphics\\elevator.xml";
	const std::string sh_heart = "Graphics\\heart.png";


	//	Button Texture Path
	const std::string bt_v_path = "Graphics\\btn_v.png";
	const std::string bt_play_path = "Graphics\\btn_play.png";
	const std::string bt_help_path = "Graphics\\btn_help.png";
	const std::string bt_crds_path = "Graphics\\btn_crds.png";
	const std::string bt_exit_path = "Graphics\\btn_exit.png";

	//	InfoBar Font Path
	const std::string font_path = "Fonts\\Montery.ttf";

	//	Sounds Paths
	const std::string snd_coin_path = "Sounds\\coin.wav";
	const std::string snd_clk_path = "Sounds\\click.wav";
	const std::string snd_hvr_path = "Sounds\\hover.wav";
	const std::string snd_lvl_bck_path = "Sounds\\bckgrnd.ogg";
	const std::string snd_mnu_bck_path = "Sounds\\intro.ogg";
	const std::string snd_jump_path = "Sounds\\jump.wav";
	const std::string snd_KillMario_path = "Sounds\\KillMario.wav";
	const std::string snd_endLevel_path = "Sounds\\endLevel.ogg";
	const std::string snd_killEnemy_path = "Sounds\\killEnemy.wav";
	const std::string snd_applause_path = "Sounds\\applause.wav";
	const std::string snd_explodeTile_path = "Sounds\\explodeTile.wav";
	const std::string snd_gameWon_path = "Sounds\\gameWon.wav";

}

//	Name-space for all constant textures.
namespace textures
{
	static sf::Texture menu_txtr;
	static sf::Texture help_txtr;
	static sf::Texture crds_txtr;
	static sf::Texture bt_v_txtr;
	static sf::Texture bt_play_txtr;
	static sf::Texture bt_help_txtr;
	static sf::Texture bt_crds_txtr;
	static sf::Texture bt_exit_txtr;
	static sf::Texture backrnd_game_txtr1;
	static sf::Texture backrnd_game_txtr2;
	static sf::Texture backrnd_game_txtr3;
	static sf::Texture sh_heart;
	static sf::Texture game_over_txtr;
	static sf::Texture game_completed_txtr;
	static sf::Texture level_up_txtr;
}

//	Name-space for all constant fonts.
namespace fonts
{
	static sf::Font ib_font;
	static sf::Font msg_font;
}


//============================================================================
// Enums

// direction for the moves
enum Direction { Up, Down, Right, Left};
// modes for active objects
enum Mode { OnGround, Falling, Smash, Jump, Dead };

