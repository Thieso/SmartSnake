#include "include/Individual.h"

// constructor using the number of inputs outputs and neurons of the neural
// network as parameters
Individual::Individual(int nr_inputs, int nr_outputs, int nr_neurons) {
    wh.assign(nr_neurons, vector<float>(nr_inputs));
    wo.assign(nr_outputs, vector<float>(nr_neurons));
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
            wo[i][j] = distribution(generator);
        }
    }
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
    vector<float> outputs;

    // input values for neural network
    vector<float> inputs;

    while (gameOver == 0) {
        // set input for neural network
        inputs = snake.getInputs();
        nn.set_input(inputs);

        //for (vector<float>::const_iterator i = inputs.begin(); i != inputs.end(); ++i)
            //cout << *i << ' ';
        //cout << endl;

        // obtain output of neural network
        outputs = nn.forward_propagation();

        //for (vector<float>::const_iterator i = outputs.begin(); i != outputs.end(); ++i)
            //cout << *i << ' ';
        //cout << endl;
        //cout << "------" << endl;
        
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
    vector<float> outputs;

    // input values for neural network
    vector<float> inputs;

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

// returns weights for hidden layer
vector<vector<float>> Individual::get_hidden_weights() {
    return wh;
}

// returns weights for output layer
vector<vector<float>> Individual::get_output_weights() {
    return wo;
}

// get the gene vector of the individual which are all the weights lined up in
// one vector
vector<float> Individual::get_gene_vector() {
    vector<float> gene_vector;
    // first push the hidden weights
    for (int i = 0; i < wh.size(); i++) {
        for (int j = 0; j < wh[i].size(); j++) {
            gene_vector.push_back(wh[i][j]);
        }
    }
    // now push the output weights
    for (int i = 0; i < wo.size(); i++) {
        for (int j = 0; j < wo[i].size(); j++) {
            gene_vector.push_back(wo[i][j]);
        }
    }
    return gene_vector;
}

// set the gene vector of the individual which are all the weights lined up in
// one vector, this vector is then converted into the weight matrices
void Individual::set_gene_vector(vector<float> gene_vector) {
    // first extract the output weights
    for (int i = wo.size() - 1; i >= 0; i--) {
        for (int j = wo[i].size() - 1; j >= 0; j--) {
            wo[i][j] = gene_vector[gene_vector.size() - 1];
            gene_vector.pop_back();
        }
    }
    // now extract the hidden weights
    for (int i = wh.size() - 1; i >= 0; i--) {
        for (int j = wh[i].size() - 1; j >= 0; j--) {
            wh[i][j] = gene_vector[gene_vector.size() - 1];
            gene_vector.pop_back();
        }
    }
}
