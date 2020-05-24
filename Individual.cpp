#include "include/Individual.h"

// constructor using the number of inputs outputs and neurons of the neural
// network as parameters
Individual::Individual(int nr_inputs, int nr_outputs, int nr_neurons_1, int nr_neurons_2) {
    this->nr_inputs = nr_inputs;
    this->nr_outputs = nr_outputs;
    this->nr_neurons_1 = nr_neurons_1;
    this->nr_neurons_2 = nr_neurons_2;
    wh_1.resize(nr_neurons_1, nr_inputs + 1);
    wh_2.resize(nr_neurons_2, nr_neurons_1 + 1);
    wo.resize(nr_outputs, nr_neurons_2 + 1);
    inputs.resize(nr_inputs);
    outputs.resize(nr_outputs);
    // randomize the weigths
    random_device rd;
    uniform_real_distribution<float> distribution(-3.0, 3.0);
    for (int i = 0; i < wh_1.size(); i++) {
        wh_1(i) = distribution(rd);
    }
    for (int i = 0; i < wh_2.size(); i++) {
        wh_2(i) = distribution(rd);
    }
    for (int i = 0; i < wo.size(); i++) {
        wo(i) = distribution(rd);
    }
    // set initial fitness
    fitness = 1;
    // set maximum number of steps
    maxSteps = 2000;
}

// destructor
Individual::~Individual() {
}

// evalute the fitness of the individual by running the snake game (no GUI)
int Individual::evaluate_fitness(NN* nn, Snake* snake) {
    // reset the snake
    snake->reset();

    // set weights for neural network
    nn->set_weights(wh_1, wh_2, wo);

    // create the initial direction randomly
    random_device rd;
    uniform_int_distribution<int> distribution(1, 4);
    int int_dir = distribution(rd);
    Vector2d dir;
    if (int_dir == 1)
        dir << 1, 0;
    else if (int_dir == 2)
        dir << -1, 0;
    else if (int_dir == 3)
        dir << 0, 1;
    else if (int_dir == 4)
        dir << 0, -1;
    snake->setDirection(dir);

    // previous direction checking
    int count_prev_dir = 0;
    Vector2d prev_dir = dir;

    // var for game over
    int gameOver = 0;

    // step counter
    int step = 0;

    // score 
    int score = 0;

    // maximum output value and its ID
    int max_output_id;
    float max_output;

    while (gameOver == 0) {
        // increase step variable
        step++;

        // set input for neural network
        inputs = snake->getInputs();
        nn->set_input(inputs);

        // obtain output of neural network
        outputs = nn->forward_propagation();
        // find id of maximum output
        max_output_id = 0;
        max_output = outputs(0);
        for (int i = 1; i < outputs.size(); i++) {
            if (outputs(i) > max_output)
                max_output_id = i;
        }

        //set direction of snake depending on the maximum output id
        if (max_output_id == 0) {
            // turn left
            if (dir(0) != 0) {
                dir(1) = dir(0);
                dir(0) = 0;
            }
            else if (dir(1) != 0) {
                dir(0) = dir(1);
                dir(1) = 0;
            }
        }
        else if (max_output_id == 1) {
            // turn right
            if (dir(0) != 0) {
                dir(1) = -dir(0);
                dir(0) = 0;
            }
            else if (dir(1) != 0) {
                dir(0) = -dir(1);
                dir(1) = 0;
            }
        }
        else if (max_output_id == 2) {
            // sticks on the same path 
            // so do nothing to the direction
        } 
        snake->setDirection(dir);

        // check prev direction 
        if (prev_dir == dir)
            count_prev_dir++;
        else
            count_prev_dir = 0;

        // increase score for longer runtime 
        if (count_prev_dir > 7)
            score -= 2;
        else
            score += 1;

        // check for collision
        if (snake->checkCollision(snake->getHead()) == 1) {
            gameOver = 1;
            score -= 2500;
        }

        // check for maximum number of steps
        if (step > maxSteps) {
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
    // compute score
    score += snake->getLength() * 3000;
    // return score
    return score;
}

void Individual::show_game(sf::RenderWindow* window, NN* nn, Snake* snake, int generation) {
    // reset snake
    snake->reset();

    // set weights for neural network
    nn->set_weights(wh_1, wh_2, wo);

    // set size of the rectangles
    int xSize = 20;
    int ySize = 20;

    // create the direction struct with initial moving to the right
    random_device rd;
    uniform_int_distribution<int> distribution(1, 4);
    int int_dir = distribution(rd);
    Vector2d dir;
    if (int_dir == 1)
        dir << 1, 0;
    else if (int_dir == 2)
        dir << -1, 0;
    else if (int_dir == 3)
        dir << 0, 1;
    else if (int_dir == 4)
        dir << 0, -1;
    snake->setDirection(dir);

    // previous direction checking
    int count_prev_dir = 0;
    Vector2d prev_dir = dir;

    // set speed in ms/step
    int speed = 50;

    // create text object for information
    sf::Text info_text;
    sf::Font font;
    font.loadFromFile("NotoMono-Regular.ttf");
    info_text.setFont(font);
    info_text.setCharacterSize(15); 
    info_text.setFillColor(sf::Color::White);
    info_text.setStyle(sf::Text::Bold);

    // text string to display
    string text_string;

    // create clock
    sf::Clock clock;

    // var for game over
    int gameOver = 0;

    // step counter
    int step = 0;

    // score 
    int score = 0;

    while (window->isOpen() && gameOver == 0) {
        // only draw the snake when a certain time has elapsed
        if (clock.getElapsedTime().asMilliseconds() >= speed){
            // increase step variable
            step++;
            // restart the clock
            clock.restart();
            // set input for neural network
            inputs = snake->getInputs();
            nn->set_input(inputs);

            // obtain output of neural network
            outputs = nn->forward_propagation();
            // find id of maximum output
            int max_output_id = 0;
            float max_output = outputs(0);
            for (int i = 1; i < outputs.size(); i++) {
                if (outputs(i) > max_output)
                    max_output_id = i;
            }

            //set direction of snake depending on the m(0)imum output id
            if (max_output_id == 0) {
                // turn left
                if (dir(0) != 0) {
                    dir(1) = dir(0);
                    dir(0) = 0;
                }
                else if (dir(1) != 0) {
                    dir(0) = dir(1);
                    dir(1) = 0;
                }
            }
            else if (max_output_id == 1) {
                // turn right
                if (dir(0) != 0) {
                    dir(1) = -dir(0);
                    dir(0) = 0;
                }
                else if (dir(1) != 0) {
                    dir(0) = -dir(1);
                    dir(1) = 0;
                }
            }
            else if (max_output_id == 2) {
                // sticks on the same path 
                // so do nothing to the direction
            } 
            snake->setDirection(dir);


            // check prev direction 
            if (prev_dir == dir)
                count_prev_dir++;
            else
                count_prev_dir = 0;

            // increase score for longer runtime 
            if (count_prev_dir > 7)
                score -= 2;
            else
                score += 1;

            // check for collision
            if (snake->checkCollision(snake->getHead()) == 1) {
                gameOver = 1;
                score -= 2500;
            }

            // check if the food got eaten, if so set food to new location and grow
            // the snake
            if (snake->checkFood() == 1) {
                snake->addElement();
                snake->setFood();
            }

            // move and draw the snake
            snake->moveSnake();
            window->clear();
            // get food location and draw the food
            sf::RectangleShape drawingShape = snake->getFoodDrawingShape(xSize, ySize);
            window->draw(drawingShape);
            // get snake location and draw it
            for (unsigned int i = 0; i < snake->getLength(); i++) {
                drawingShape = snake->getSnakeDrawingShape(xSize, ySize, i);
                window->draw(drawingShape);
            }
            // draw text to indicate the generation, score and steps
            text_string = "Generation: " + to_string(generation) + "\n";
            text_string += "Fitness: " + to_string(score + snake->getLength() * 3000) + "\n";
            //text_string += "Steps: " + to_string(step) + "\n";
            //text_string += "Blocked Front: " + to_string((int) inputs(0)) + "\n";
            //text_string += "Blocked Left: " + to_string((int) inputs(1)) + "\n";
            //text_string += "Blocked Right: " + to_string((int) inputs(2)) + "\n";
            //text_string += "Rel. Pos. x: " + to_string(inputs(3)) + "\n";
            //text_string += "Rel. Pos. y: " + to_string(inputs(4)) + "\n";
            //text_string += "Snake Dir. x: " + to_string((int) inputs(5)) + "\n";
            //text_string += "Snake Dir. y: " + to_string((int) inputs(6)) + "\n";
            //text_string += "Dist. Food x: " + to_string(inputs(7)) + "\n";
            //text_string += "Dist. Food. y: " + to_string(inputs(8)) + "\n";
            info_text.setString(text_string);
            info_text.setPosition(20, 20);
            window->draw(info_text);

            // Display all the changes on the screen
            window->display();
        }
    }
}

// get the gene vector of the individual which are all the weights lined up in
// one vector 
VectorXd Individual::get_gene_vector() {
    Map<VectorXd> gene_vector_1(wh_1.data(), wh_1.size());
    Map<VectorXd> gene_vector_2(wh_2.data(), wh_2.size());
    Map<VectorXd> gene_vector_3(wo.data(), wo.size());
    VectorXd gene_vector(wh_1.size() + wh_2.size() + wo.size());
    gene_vector << gene_vector_1, gene_vector_2, gene_vector_3;
    return gene_vector;
}

// set the gene vector of the individual which are all the weights lined up in
// one vector, this vector is then converted into the weight matrices
void Individual::set_gene_vector(VectorXd gene_vector) {
    VectorXd tmp_vec;
    // hidden layer 1 weights
    tmp_vec = gene_vector.topRows(wh_1.size());
    Map<MatrixXd> wh_1_tmp(tmp_vec.data(), wh_1.rows(), wh_1.cols());
    wh_1 = wh_1_tmp;
    // hidden layer 2 weights
    tmp_vec = gene_vector.topRows(wh_1.size() + wh_2.size());
    tmp_vec = tmp_vec.bottomRows(wh_2.size());
    Map<MatrixXd> wh_2_tmp(tmp_vec.data(), wh_2.rows(), wh_2.cols());
    wh_2 = wh_2_tmp;
    // hidden layer 2 weights
    tmp_vec = gene_vector.bottomRows(wo.size());
    Map<MatrixXd> wo_tmp(tmp_vec.data(), wo.rows(), wo.cols());
    wo = wo_tmp;
}

// move assignment operator
Individual& Individual::operator=(Individual&& ind) {
    this->fitness = ind.fitness;
    this->maxSteps = ind.maxSteps;
    this->inputs = ind.inputs;
    this->outputs = ind.outputs;
    this->wh_1 = ind.wh_1;
    this->wh_2 = ind.wh_2;
    this->wo = ind.wo;
    this->nr_inputs = ind.nr_inputs;
    this->nr_outputs = ind.nr_outputs;
    this->nr_neurons_1 = ind.nr_neurons_1;
    this->nr_neurons_2 = ind.nr_neurons_2;
    return *this;
}

// copy assignment operator
Individual& Individual::operator=(const Individual& ind) {
    this->fitness = ind.fitness;
    this->maxSteps = ind.maxSteps;
    this->inputs = ind.inputs;
    this->outputs = ind.outputs;
    this->wh_1 = ind.wh_1;
    this->wh_2 = ind.wh_2;
    this->wo = ind.wo;
    this->nr_inputs = ind.nr_inputs;
    this->nr_outputs = ind.nr_outputs;
    this->nr_neurons_1 = ind.nr_neurons_1;
    this->nr_neurons_2 = ind.nr_neurons_2;
    return *this;
}

// move constructor
Individual::Individual(Individual&& ind)
    : fitness(ind.fitness)
    , nr_inputs(ind.nr_inputs)
    , nr_outputs(ind.nr_outputs)
    , nr_neurons_1(ind.nr_neurons_1)
    , nr_neurons_2(ind.nr_neurons_2)
    , maxSteps(ind.maxSteps)
    , inputs(ind.inputs)
    , outputs(ind.outputs)
    , wh_1(ind.wh_1)
    , wh_2(ind.wh_2)
    , wo(ind.wo)
{
}

// copy constructor
Individual::Individual(const Individual& ind)
    : fitness(ind.fitness)
    , nr_inputs(ind.nr_inputs)
    , nr_outputs(ind.nr_outputs)
    , nr_neurons_1(ind.nr_neurons_1)
    , nr_neurons_2(ind.nr_neurons_2)
    , maxSteps(ind.maxSteps)
    , inputs(ind.inputs)
    , outputs(ind.outputs)
    , wh_1(ind.wh_1)
    , wh_2(ind.wh_2)
    , wo(ind.wo)
{
}
