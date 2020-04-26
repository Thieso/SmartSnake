#include "include/Individual.h"

// constructor using the number of inputs outputs and neurons of the neural
// network as parameters
Individual::Individual(int nr_inputs, int nr_outputs, int nr_neurons) {
    this->wh.resize(nr_neurons);
    for (int i = 0; i < nr_neurons; ++i) {
        wh[i].resize(nr_inputs);
    }
    this->wo.resize(nr_outputs);
    for (int i = 0; i < nr_neurons; ++i) {
        wo[i].resize(nr_neurons);
    }
    // randomize the weights
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0, 1.0);
    for (int i = 0; i < nr_neurons; ++i) {
        for (int j = 0; j < nr_inputs; ++j) {
            wh[i][j] = distribution(generator);
        }
    }
    for (int i = 0; i < nr_outputs; ++i) {
        for (int j = 0; j < nr_neurons; ++j) {
            wh[i][j] = distribution(generator);
        }
    }
    fitness = 1;
}

// evalute the fitness of the individual by running the snake game (no GUI)
int Individual::evaluate_fitness(NN* nn) {
    // set weights for neural network
    nn->set_weights(wh, wo);

    // create a new Snake object
    Snake* snake = new Snake();

    // create the direction struct with initial moving to the right
    struct direction {
        int x;
        int y;
    }dir;
    dir.x = 1;
    dir.y = 0;

    // var for game over
    int gameOver = 0;

    // output vales of neural network
    vector<float> outputs;

    // input values for neural network
    vector<float> inputs;

    while (gameOver == 0) {
        // set input for neural network
        inputs = snake->getInputs();
        nn->set_input(inputs);

        // obtain output of neural network
        outputs = nn->forward_propagation();
        
        if (outputs[0] > 0.5 && dir.x == 0) {
            dir.x = -1;
            dir.y = 0;
        }
        else if (outputs[1] > 0.5 && dir.x == 0) {
            dir.x = 1;
            dir.y = 0;
        }
        else if (outputs[2] > 0.5 && dir.y == 0) {
            dir.x = 0;
            dir.y = -1;
        }
        else if (outputs[3] > 0.5 && dir.y == 0) {
            dir.x = 0;
            dir.y = 1;
        }

        // check for collision
        if (snake->checkCollision() == 1) {
            gameOver = 1;
        }
        
        // check if the food got eaten, if so set food to new location and grow
        // the snake
        if (snake->checkFood() == 1) {
            snake->addElement();
            snake->setFood();
        }

        // move the snake
        snake->moveSnake();
    }
    return snake->getLength();
}

int Individual::show_game(sf::RenderWindow* window, NN* nn) {
    // set weights for neural network
    nn->set_weights(wh, wo);

    // set size of the rectangles
    int xSize = 20;
    int ySize = 20;

    // create a new Snake object
    Snake* snake = new Snake();

    // set framerate
    window->setFramerateLimit(30);

    // create the direction struct with initial moving to the right
    struct direction {
        int x;
        int y;
    }dir;
    dir.x = 1;
    dir.y = 0;

    // set speed
    int speed = 50;

    // create clock
    sf::Clock clock;

    // var for game over
    int gameOver = 0;

    // output vales of neural network
    vector<float> outputs;

    // input values for neural network
    vector<float> inputs;

    while (window->isOpen() && gameOver == 0) {
        //check if window is closed
        sf::Event event;
        while(window->pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window->close();
        }

        // set input for neural network
        inputs = snake->getInputs();
        nn->set_input(inputs);


        // obtain output of neural network
        outputs = nn->forward_propagation();
        
        if (outputs[0] > 0.5 && dir.x == 0) {
            dir.x = -1;
            dir.y = 0;
        }
        else if (outputs[1] > 0.5 && dir.x == 0) {
            dir.x = 1;
            dir.y = 0;
        }
        else if (outputs[2] > 0.5 && dir.y == 0) {
            dir.x = 0;
            dir.y = -1;
        }
        else if (outputs[3] > 0.5 && dir.y == 0) {
            dir.x = 0;
            dir.y = 1;
        }
        snake->setDirection(dir.x, dir.y);

        // check for collision
        if (snake->checkCollision() == 1) {
            gameOver = 1;
        }
        
        // check if the food got eaten, if so set food to new location and grow
        // the snake
        if (snake->checkFood() == 1) {
            snake->addElement();
            snake->setFood();
        }

        // if a certain time elapsed, move and draw the snake
        if (clock.getElapsedTime().asMilliseconds() >= speed){
            window->clear();
            clock.restart();
            snake->moveSnake();
            snake->drawSnake(window, xSize, ySize);
        }

        // draw a Matrix
        drawMatrix(window, xSize, ySize);

        // Display all the changes on the screen
        window->display();
    }
    return snake->getLength();
}

void Individual::drawMatrix(sf::RenderWindow* window, int xSize, int ySize) {
    // color of matrix lines
    int grey = 50;
    sf::Color color(grey, grey, grey);

    // get window size
    sf::Vector2u wSize = window->getSize();

    // draw matrix
    for (int i = xSize; i < wSize.x; i += xSize) {
        sf::Vertex lineV[] =
        {
            sf::Vertex(sf::Vector2f(i, 0), color),
            sf::Vertex(sf::Vector2f(i, wSize.x), color)
        };
        window->draw(lineV, 2, sf::Lines);
    }
    for (int i = ySize; i < wSize.y; i += ySize) {
        sf::Vertex lineH[] =
        {
            sf::Vertex(sf::Vector2f(0, i), color),
            sf::Vertex(sf::Vector2f(wSize.y, i),color)
        };
        window->draw(lineH, 2, sf::Lines);
    }
}

// returns weights for hidden layer
vector<vector<float>> Individual::get_hidden_weights() {
    return wh;
}

// returns weights for output layer
vector<vector<float>> Individual::get_output_weights() {
    return wo;
}
