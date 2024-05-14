
#include "../Headers/Game.h"


int main()
{
    //Inicializa o srand
    srand(static_cast<unsigned>(time(NULL)));

    //Inicializar a Engine
    Game game;

    //Loop do Jogo
    bool end = false;
    
    if(game.printMenu())
    {
        while(game.running() && !end)
        {

            //Update
            game.update();

            //Renderizar
            game.render();

            if(game.getEndGame())
            {
                game.printGameOver();
                end = true;
            }
        }
    } 

    //Fim
    return 0;
}
