#pragma once

#include <SDL.h>
#include <glm/glm.hpp>

#include "Utility/Log.hpp"
#include "GameObjects/GameObject.hpp"
#include "GameObjects/ModelObject.hpp"
#include "Camera/Camera.hpp"

#include <memory>
#include <vector>


/**
 * @brief Tryb okna.
 * 
 */
enum WindowMode
{
    WINDOWED_MODE,
    BORDERLESS_MODE = SDL_WINDOW_FULLSCREEN_DESKTOP,
    FULLSCREEN_MODE = SDL_WINDOW_FULLSCREEN
};

class Engine
{
public:
	// returns the previously created or default instance	/**
	 /** @brief Przekazuje wskaźnik na obiekt Engine (Singleton).
	 * 
	 * @return Engine* 
	 */
	static Engine * get_instance();
		/**
	 * @brief Przekazuje wskaźnik na obiekt Engine (Singleton), skonfigurowany z argumentami.
	 * @param title Tytuł okna
	 * @param x Składowa x lewego górnego rogu okna.
	 * @param y Składowa y lewego górnego rogu okna.
	 * @param w Szerokość okna.
	 * @param h Wysokość okna.
	 * @param window_mode Tryb okna.
	 * @param frame_rate Częstotliwość odświeżania.
	 * @return Engine* 
	 */
	static Engine * get_instance(const char * title, int x, int y, int w, int h, WindowMode window_mode, unsigned frame_rate);
	~Engine();

		/**
	 * @brief Flaga oznaczająca czy silnik (i gra z nim związana) jest uruchomiony.
	 * 
	 */
	bool is_running;

			/**
	 * @brief Funkcja gospodarująca wydarzeniami związanymi z czasem w silniku.
	 * 
	 */
	void schedule();

		/**
	 * @brief Funkcja przetwarzająca wydarzenia związane z SDL oraz właściwą grą.
	 * 
	 */
	void process_events();

		/**
	 * @brief Funkcja aktualizująca stan wszystkich obiektów w grze, które są Updateable.
	 * 
	 */
	void update();

		/**
	 * @brief Funkcja czyszcząca ekran oraz rysująca obiekty, które są Drawable.
	 * 
	 */
	void draw();

	// Adds object to engine's game object pool
	// If you want the engine to let go of ther pointer, set is_alive to false in the object
	// Shares ownership over the pointer with the called
		/**
	 * @brief Funkcja dodająca obiekt związany z grą do puli obiektów.
	 * @param go Dodawany obiekt.
	 */
	void add_game_object( std::shared_ptr<GameObject> go );
	// Adds object to engine's game object pool
	// If you want the engine to let go of ther pointer, set is_alive to false in the object
	// Depending on renounce_ownership value, takes the ownership or only weakly references the pointer
		/**
	 * @brief Funkcja dodająca obiekt związany z grą do puli obiektów.
	 * @param go Dodawany obiekt.
	 * @param renounce_ownership Jesli ta flaga jest ustawiona na true, silnik staje sie właścicielem wskaźnika i może wykonać na nim delete.
	 */
	void add_game_object( GameObject *go, bool renounce_ownership = true );

	// Negative range to search through all objects
	/**
	 * @brief Poszukuje obiektów w zadanym zasięgu.
	 * 
	 * @param target Obiekt, względem którego odbywa się wyszukiwanie.
	 * @param range Zasięg.
	 * @return std::vector< std::shared_ptr<ModelObject> > 
	 */
	std::vector< std::shared_ptr<ModelObject> > find_game_objects_in_range( const std::shared_ptr<ModelObject>& target, float range ) const;
	std::vector< std::shared_ptr<ModelObject> > find_game_objects_in_range( const ModelObject *target, float range ) const;
	std::vector< std::shared_ptr<GameObject> > find_game_objects_with_tag( const char *tag ) const;

	/**
	 * @brief Pozyskuje referencję na obiekt kamery.
	 * 
	 * @return Camera& 
	 */
	Camera& get_camera();

	/**
	 * @brief Pozyskuje rozmiar okna.
	 * 
	 * @return glm::ivec2 
	 */
	glm::ivec2 get_window_size() const;

	
public:
	/**
	 * @brief Okno z biblioteki SDL.
	 * 
	 */
	SDL_Window * sdl_window;

	/**
	 * @brief Renderer z biblioteki SDL.
	 * 
	 */
	SDL_Renderer * sdl_renderer;


private:
/**
 * @brief Sparametryzowany konstruktor silnika, niewykorzystywany bezpośrednio.
 * 
 * @param title Tytuł okna.
 * @param x Lewy górny róg, współrzędna x.
 * @param y Lewy górny róg, współrzędna y.
 * @param w Szerokość okna.
 * @param h Wysokość okna.
 * @param window_mode Typ okna.
 * @param frame_rate Ilość klatek na sekundę.
 */
	Engine(const char * title, int x, int y, int w, int h, WindowMode window_mode, unsigned frame_rate);

	/**
	 * @brief Wskaźnik na silnik, zwracany na zasadzie singletonu.
	 * 
	 */
	static Engine * engine;

	/**
	 * @brief Poprzedni czas związany z pętlą czasu.
	 * 
	 */
	uint32_t previous_time;

		/**
	 * @brief Docelowy czas związany z pętlą czasu.
	 * 
	 */
	uint32_t target_time;
	
	/**
	 * @brief Wektor obiektów gry.
	 * 
	 */
	std::vector< std::shared_ptr<GameObject> > vec_game_objects;

	/**
	 * @brief Funkcja usuwająca nieużywane obiekty gry.
	 * 
	 */
	void remove_dead_game_objects();


	/**
	 * @brief Funkcja przeprowadzająca kolizje obiektów gry.
	 * 
	 */
	void do_collisions();

	/**
	 * @brief Obiekt kamery.
	 * 
	 */
	Camera camera;
};