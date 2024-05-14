#include"../Headers/Game.h"

//Funções Privadas
void Game::initVars()
{
    this->window = nullptr;

    //Logica
    this->endGame = false;
    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;
    this->hp = 10;
}

void Game::initWindow()
{
    unsigned int windowWidth = 800;
    unsigned int windowHeight = 600; 

    //Inicializando Janela
    this->videoMode.height = windowHeight;
    this->videoMode.width = windowWidth;
    this->window = new sf::RenderWindow(this->videoMode, "Aprendendo SFML", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);

    //Centralizando no monitor
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktopMode.width;
    unsigned int screenHeight = desktopMode.height;
    int windowPosX = (screenWidth - windowWidth) / 2;
    int windowPosY = (screenHeight - windowHeight) / 2;
    this->window->setPosition(sf::Vector2i(windowPosX, windowPosY));
}

void Game::initEnemies()
{
    this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
    this->enemy.setSize(sf::Vector2f(50.f, 50.f));
    this->enemy.setFillColor(sf::Color::Cyan);
}

void Game::initFont()
{
    if(!this->font.loadFromFile("src/Retro Gaming.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONT::Failed to load font." << "\n";
    }
}

void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(12);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

//Constructors e Destructors
Game::Game()
{
    this->initVars();
    this->initEnemies();
    this->initFont();
    this->initText();
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
}

//Acessores
const bool Game::running() const
{
    return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endGame;
}

int Game::getPoints()
{
    return this->points;
}

//Funções Públicas
void Game::spawnEnemy()
{
    /*
    @return void
        Spawna inimigos e seta suas cores e posições
        - Seta uma posição aleatória
        - Seta uma cor aleatória
        - Adiciona o inimigo no vector
    */

   this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
   );

   this->enemy.setFillColor(sf::Color::Green);

    //Insere o inimigo no vector para spawna-lo
   this->enemies.push_back(this->enemy);

}

void Game::playSound(std::string filePath)
{
        if(!this->buffer.loadFromFile(filePath)) {
            std::cout << "ERROR::GAME::PLAYSOUND::Failed to load sound." << "\n";
        }

        this->sound.setBuffer(buffer);
        this->sound.setVolume(100.f);
        this->sound.play();
        if (this->sound.getStatus() != sf::Sound::Status::Playing)
        {
            std::cout << "ERROR::GAME::PLAYSOUND::Failed to play sound." << "\n";
        }
}

void Game::pollEvents()
{
    //Polling de Eventos
        while(this->window->pollEvent(this->event))
        {
            switch(this->event.type)
            {
                case sf::Event::Closed:
                    this->window->close();
                    break;
                case sf::Event::KeyPressed:
                    if(this->event.key.code == sf::Keyboard::Escape)
                    {
                        this->window->close();
                        break;
                    }
                    break;
            }
        }
}

void Game::setText(unsigned int size, sf::Color color, std::string string, sf::Vector2f position)
{
    this->uiText.setCharacterSize(size);
    this->uiText.setFillColor(color);
    this->uiText.setString(string);
    this->uiText.setPosition(position);
}

bool Game::printMenu()
{
    bool startGame = false;
    sf::Text title("FALLING BLOCKS", this->font, 50);
    title.setFillColor(sf::Color::Cyan);
    title.setPosition(400.f - title.getGlobalBounds().width / 2.f, 50.f);

    sf::Text startText("- Start Game", this->font, 30);
    startText.setFillColor(sf::Color::Cyan);
    startText.setPosition(400.f - startText.getGlobalBounds().width / 2.f, 300.f);

    sf::Text exitText("- Exit Game", this->font, 30);
    exitText.setFillColor(sf::Color::Cyan);
    exitText.setPosition(400.f - exitText.getGlobalBounds().width / 2.f, 400.f);

    bool mouseHeld = false;


    while(!startGame)
    {
        this->updateMousePos();

        this->window->clear(sf::Color::Black);
        this->window->draw(title);
        this->window->draw(startText);
        this->window->draw(exitText);
        this->window->display();

        bool mouseHoverStart = startText.getGlobalBounds().contains(this->mousePosView);
        bool mouseHoverExit = exitText.getGlobalBounds().contains(this->mousePosView);

        if(mouseHoverStart)
        {
            startText.setFillColor(sf::Color::Green);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                startGame = true;
            }
        }
        else startText.setFillColor(sf::Color::Cyan);

        if(mouseHoverExit)
        {
            exitText.setFillColor(sf::Color::Red);

            if(mouseHeld && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                this->window->close();
                return false;
            }
        } else exitText.setFillColor(sf::Color::Cyan);

        mouseHeld = sf::Mouse::isButtonPressed(sf::Mouse::Left);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            this->window->close();
            return false;
        }
    }
    return true;
}

void Game::printGameOver()
{
    bool closeGame = false;

    std::string textString = "Score: " + std::to_string(this->getPoints());

    sf::Text text("GAME OVER\n", this->font, 60);
    text.setFillColor(sf::Color::Red);
    text.setPosition(400.f - text.getGlobalBounds().width / 2.f, 300.f - text.getGlobalBounds().height / 2.f - 50.f);

    sf::Text points(textString, this->font, 40);
    points.setFillColor(sf::Color::Red);
    points.setPosition(400.f - points.getGlobalBounds().width / 2.f, 350.f - points.getGlobalBounds().height / 2.f - 50.f);

    while(!closeGame)
    {
        this->window->clear(sf::Color::Black);
        this->window->draw(text);
        this->window->draw(points);
        this->window->display();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            closeGame = true;
        }
    }
    this->window->close();
}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    for(int i = 0; i < this->enemies.size(); i++)
    {
        target.draw(this->enemies[i]);
    }
}


void Game::render()
{

    /*
        @return void

        - Limpa os frames antigos
        - Renderiza os objetos novos
        - Mostra o novo frame na janela
    */

    this->window->clear(sf::Color::Black);

    //Desenhar objetos do jogo
    this->renderEnemies(*this->window);
    this->renderText(*this->window);
    this->window->display();
}


void Game::updateEnemies()
{

    /*
    @return void
        Atualiza o timer de spawnar inimigos e 
        spawna inimigos quando o timer é menor que o máximo
        Move os inimigos para baixo
        Remove do canto da tela
    */

    //Atualizando o timer pros inimigos spawnarem
    if(this->enemies.size() < this->maxEnemies)
    {
        if(this->enemySpawnTimer <= this->enemySpawnTimerMax)
        {
            //Spawna o inimigo e reseta o timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f; //Aumenta o timer
    }

    for (int i = 0; i < this->enemies.size(); i++)
    {

        //Move os inimigos para baixo
        this->enemies[i].move(0.f, 3.f);

        //Verifica se o inimigo saiu da tela (por baixo)
        if(this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->hp -= 1;
        }
    }
    


    //Verifica se o inimigo foi clicado
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(this->mouseHeld == false)
        {
            this->mouseHeld = true;
            bool deleted = false;
            for (int i = 0; i < this->enemies.size() && deleted == false; i++)
            {
                if(this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {   
                    //Deleta o inimigo
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);

                    //Ganha pontos
                    this->points += 1.f;

                }
            }
        }

    }
    else this->mouseHeld = false;

}

void Game::updateMousePos()
{
    /*
    @return void
        Atualiza as posições do mouse
        - Atualiza as posições do mouse relativas a janela (Vector2i)
    */

   this->mousePosWindow = sf::Mouse::getPosition(*this->window);
   this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
    std::stringstream string;

    string << "Points: " << this->points;
    sf::Vector2f position;
    position.x = 0.f;
    position.y = 0.f;
    this->setText(12, sf::Color::White, string.str(), position);
}

void Game::update()
{

    this->pollEvents();

    if(this->endGame == false)
    {
        this->updateMousePos();

        this->updateText();

        this->updateEnemies();
    }

    if(this->hp <=0)
        this->endGame = true;
}
