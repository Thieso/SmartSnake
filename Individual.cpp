#include "include/Individual.h"

// constructor using the number of inputs outputs and neurons of the neural
// network as parameters
Individual::Individual(int nr_inputs, int nr_outputs, int nr_neurons) {
    wh.resize(nr_neurons, nr_inputs);
    wo.resize(nr_outputs, nr_neurons);
    // randomize the weigths
    wh.setRandom();
    wo.setRandom();
    // set initial fitness
    fitness = 1;
}

// evalute the fitness of the individual by running the snake game (no GUI)
int Individual::evaluate_fitness(int nr_inputs, int nr_outputs, int nr_neurons) {
    // create neural network
    NN nn(nr_inputs, nr_outputs, nr_neurons);

    // set weights for neural network
    nn.set_weights(wh, wo);

    // create a new Snake object
    Snake snake;

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
    VectorXd outputs;

    // input values for neural network
    VectorXd inputs;

    while (gameOver == 0) {
        // set input for neural network
        inputs = snake.getInputs();
        nn.set_input(inputs);

        // obtain output of neural network
        outputs = nn.forward_propagation();

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
        if (snake.checkCollision() == 1) {
            gameOver = 1;
        }
        
        // check if the food got eaten, if so set food to new location and grow
        // the snake
        if (snake.checkFood() == 1) {
            snake.addElement();
            snake.setFood();
        }

        // move the snake
        snake.setDirection(dir.x, dir.y);
        snake.moveSnake();
    }
    return snake.getLength();
}

int Individual::show_game(int nr_inputs, int nr_outputs, int nr_neurons) {
    // create neural network
    NN nn(nr_inputs, nr_outputs, nr_neurons);

    // create window
    sf::RenderWindow window(sf::VideoMode(500, 500), "Snake");

    // set weights for neural network
    nn.set_weights(wh, wo);

    // set size of the rectangles
    int xSize = 20;
    int ySize = 20;

    // create a new Snake object
    Snake snake;

    // set framerate
    window.setFramerateLimit(30);

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
    VectorXd outputs;

    // input values for neural network
    VectorXd inputs;

    while (window.isOpen() && gameOver == 0) {
        //check if window is closed
        sf::Event event;
        while(window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // set input for neural network
        inputs = snake.getInputs();
        nn.set_input(inputs);

        // obtain output of neural network
        outputs = nn.forward_propagation();

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
        snake.setDirection(dir.x, dir.y);

        // check for collision
        if (snake.checkCollision() == 1) {
            gameOver = 1;
        }
        
        // check if the food got eaten, if so set food to new location and grow
        // the snake
        if (snake.checkFood() == 1) {
            snake.addElement();
            snake.setFood();
        }

        // if a certain time elapsed, move and draw the snake
        if (clock.getElapsedTime().asMilliseconds() >= speed){
            window.clear();
            clock.restart();
            snake.setDirection(dir.x, dir.y);
            snake.moveSnake();
            // get food location and draw the food
            sf::RectangleShape drawingShape = snake.getFoodDrawingShape(xSize, ySize);
            window.draw(drawingShape);
            // get snake location and draw it
            vector<sf::RectangleShape> drawingShapes = snake.getSnakeDrawingShapes(xSize, ySize);
            for (auto i = drawingShapes.begin(); i < drawingShapes.end(); i++) {
                window.draw(*i);
            }
        }

        // Display all the changes on the screen
        window.display();
    }
    return snake.getLength();
}

// get the gene vector of the individual which are all the weights lined up in
// one vector (hidden layer)
VectorXd Individual::get_gene_vector_hidden() {
    Map<VectorXd> gene_vector(wh.data(), wh.size());
    return gene_vector;
}

// get the gene vector of the individual which are all the weights lined up in
// one vector (output layer)
VectorXd Individual::get_gene_vector_output() {
    Map<VectorXd> gene_vector(wo.data(), wo.size());
    return gene_vector;
}

// set the gene vector of the individual which are all the weights lined up in
// one vector, this vector is then converted into the weight matrices (hidden
// layer)
void Individual::set_gene_vector_hidden(VectorXd gene_vector) {
    Map<MatrixXd> wh_tmp(gene_vector.data(), wh.rows(), wh.cols());
    wh = wh_tmp;
}

// set the gene vector of the individual which are all the weights lined up in
// one vector, this vector is then converted into the weight matrices (hidden
// layer)
void Individual::set_gene_vector_output(VectorXd gene_vector) {
    Map<MatrixXd> wo_tmp(gene_vector.data(), wo.rows(), wo.cols());
    wo = wo_tmp;
}
