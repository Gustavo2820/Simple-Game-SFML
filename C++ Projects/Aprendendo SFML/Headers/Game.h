#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Window/Event.hpp>

/*
    Classe que atua como a "engine" do jogo
*/

class Game {
    private:
        //Variáveis
        //Window
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event event;

        //Posições do Mouse 
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;

        //Recursos
        sf::Font font;
        sf::Text uiText;

        //Logica
        bool endGame;
        int hp;
        unsigned int points;
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        unsigned int maxEnemies;
        bool mouseHeld;

        //Objetos do Jogo
        std::vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy;

        //Funções Privadas
        void initVars();
        void initWindow();
        void initEnemies();
        void initFont();
        void initText();
        
    public:
        //Constructors e Destructors
        Game();
        virtual ~Game();

        //Acessores
        const bool running() const;
        const bool getEndGame() const;
        int getPoints();

        //Funções
        void spawnEnemy();

        void pollEvents();

        void printGameOver();

        void update();
        void updateEnemies();
        void updateMousePos();
        void updateText();

        void render();
        void renderEnemies(sf::RenderTarget& target);
        void renderText(sf::RenderTarget& target);
};      


#endif