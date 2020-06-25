#pragma once

#include <string>
#include <SFML/Graphics.hpp>

/* other */
const float SCREEN_WIDTH{1024};
const float SCREEN_HEIGHT{576};
const std::string WINDOW_TITLE{ "Maze Game v0.5" };
const float MARGIN_SMALL{ 16 };

/* splash state */
const std::string SPLASH_STATE_BACKGROUND_FILEPATH{ "res/drawable/splash_state_background.png" };
const float SPLASH_STATE_SHOW_TIME{ 3.0 };

/* main menu state */
const std::string MAIN_MENU_BACKGROUND_FILEPATH{ "res/drawable/main_menu_state_background.png" };
const std::string GAME_TITLE_FILEPATH{ "res/drawable/game_title.png" };
const std::string BUTTON_FILEPATH{ "res/drawable/button.png" };
const std::string FONT_ARIAL_FILEPATH{ "res/fonts/arial.ttf" };
const int MENU_OPTIONS{ 5 };
const int DEFAULT_MAP_SIZE{ 5 };

/* config state */
const std::string CONFIGURATION_BACKGROUND_FILEPATH{ "res/drawable/configuration_state_background.png" };
const std::string CONFIGURATION_TITLE_FILEPATH{ "res/drawable/configuration_title.png" };
const std::string SQUARE_BUTTON_FILEPATH{ "res/drawable/square_button.png" };
const unsigned int MIN_MAP_SIZE{ 5 };
const unsigned int MAX_MAP_SIZE{ 15 };
const std::string CHANGE_MAP_SIZE_TEXT{ "WYBIERZ ROZMIAR MAPY" };

/* credits state */
const std::string CREDITS_BACKGROUND_FILEPATH{ "res/drawable/credits_state_background.png" };

/* help state */
const std::string HELP_BACKGROUND_FILEPATH{ "res/drawable/help_state_background.png" };

/* game state */
const std::string MEGA_TEXTURE_FILEPATH{ "res/drawable/mega_texture.png" };

const sf::Vector2<double> PLAYER_INITIAL_POSITION{ 1.5, 1.5 };
const sf::Vector2<double> PLAYER_INITIAL_DIRECTION{ 1.0, 0.0 };
const sf::Vector2<double> CAMERA_PLANE_INITIAL{ 0.0, -0.66 };
const float MOVE_SPEED{ 4.5 };
const float ROTATION_SPEED{ 4.5 };

	/* HUD */
	const std::string FONT_BEEF_D_FILEPATH{ "res/fonts/beef'd.ttf" };
	
/* game over state */
const std::string GAMEOVER_WIN_TITLE_FILEPATH{ "res/drawable/game_over_win_title.png" };
const std::string GAMEOVER_LOSE_TITLE_FILEPATH{ "res/drawable/game_over_lose_title.png" };

/* game paused state */
const std::string GAME_PAUSED_STATE_BACKGROUND_FILEPATH{ "res/drawable/game_paused_background.png" };

/* game init state */
const std::string GAME_INIT_STATE_BACKGROUND_FILEPATH{ "res/drawable/game_init_background.png" };

/* textures */
const float DEFAULT_TEXTURE_SIZE{ 64 };
namespace TextureId
{
	const int WallBrick{ 1 };
	const int WallDoor{ 2 };
	const int SpriteKey{ 3 };
}