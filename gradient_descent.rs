fn main() {
    // from : https://www.youtube.com/watch?v=sDv4f4s2SB8&t

    const OBSERVED_HEIGHT: [f64; 3] = [1.4, 1.9, 3.2];
    // The height of the three people, the height 
    // is the data we want to predicte from those
    // three samples, who is what we would expecte 
    // from the three inputs, the weights.

    const WEIGHT: [f64; 3] = [0.5, 2.3, 2.9];
    // Their weight, this is the inputs of 
    // the gradient descent.
    // Since each weight gives one height
    // I think I could say there are three 
    // propagations if I take it as a tiny
    // neural network.

    let try_number: usize = 1000;
    // This is the number of time the programme
    // will try to determine the slope and the 
    // the intrcept afterward

    let mut slope_intercept_trouve: [bool; 2] = [false, false];
    // indicate if the good slope and intercept are 
    // found or not
    let mut true_counter: usize = 0;
    
    let precision_success: f64 = 0.001;
    // The programme will stop once the derivative of the sum 
    // of square of the difference between the observed data 
    // and the predicted one is between precision_success and 
    // its negative

    let mut step_size: f64;
    // The 

    let slope_intercept_learning_rate: [f64; 2] = [0.01, 0.1];
    // for 0 :
    // The multiplicator that will determine the step size when 
    // it's use to multiply sum_derivative_square_residual.
    // The step size calaculated is to create the next value of
    // the slope of the prediction line.

    // pour 1 :
    // The multiplicator that will determine the step size when 
    // it's use to multiply sum_derivative_square_residual.
    // The step size calaculated is to create the next value of
    // the intercept of the prediction line.

    let mut sum_derivative_square_residual: f64;
    let mut derivative_square_residual: f64;
    // la somme des dérivés du carré de la différence 
    // entre la valeur observé et celle attendue
    // pour le calcule du coéficient directeur de la
    // courbes des prédictions a N-1 et N


    // <brouilon>
    // let batch_number: usize = 2;
    // pour mini batche :
    // for j in 0..= batch_number - 1 {  à la place de for j in WEIGHT.len() -1
    //  crée un nombre aléatoire x entre 0 et OBSERVED_HEIGHT.len()
    //  utilise x dans WEIGHT[x] et OBSERVED_HEIGHT[x]
    // </brouilon>


    let mut slope_intercept: [f64; 2] = [0.0, 0.0];
    // pour 0:
    // valeur de départ du coéficient directeur de la courbe
    // des prédictions

    // pour 1:
    // valeur de départ de l'intercept de la courbe
    // des prédictions

    let mut predicted_height: f64;
    // la ou sera stocké la taille prédite
    // par rapport à slope et intercept

    for _i in 0..= try_number - 1 {
    // for each number of try

        // stop the algorihtm if the values has already been found

        // I would add another for loop here :
        // for eache layer (look backward)

        for y in 0..= slope_intercept.len() - 1 {
            println!("\npour la valeur (0 = slope, 1 = intercept) : {}", y);

        // for each type of data I want to predicte, here this is the 
        // slope and the intercept, but, I think in a real neural network 
        // it would be: for the weights and for the bias afterward since
        // the bias is the constente like the intercept.

        // That would say I will have to add another for loop for each 
        // weights (weights_bias[0]) and for each bias afterward (weights_bias[1]).
            if slope_intercept_trouve[y] == false {
                // if the good value for this data have not been found.
                sum_derivative_square_residual = 0.0;
                // clean the the sum calculated from the previous iteration 
                // and give it a value (usefull for the first iteration)

                // will calculate difference of the observed datas
                // and (with a -) the datas the network would give,
                // for each pair of datas (here WEIGHT), sum it and  
                // will declare the data as the good one if the sum 
                // is between the precision (precision_success), and its
                // negative, I ask the neural network to have.
                for j in 0..= WEIGHT.len() - 1 {
                    // for each pair of datas (given and observed), samples:
                    predicted_height = (slope_intercept[0] * WEIGHT[j]) + slope_intercept[1];
                    // will try to predicte the good data, I wonder if, for a real neural network,
                    // the predicted data should be the calculation of the output(s) of the network
                    // from the multiplication between the two last layers or from all of them.

                    // in a function with let-else statements (weight or bias ?)
                    // in a match statement (wich layer ?) and by looking
                    // the layers backward (array.len() - x)
                    // or
                    // two function, one for the weights and another for the bias
                    // with a match statement

                    // the function will propably start before :
                    // for j in 0..= WEIGHT.len() - 1 {
                    // because I would like to avoid calling a function in a loop
                    if y == 0 {
                        // if the data is the slope (weights), there would be another 
                        // if to see in wich layer is the weight
                        derivative_square_residual = (-2.0 * WEIGHT[j]) * (OBSERVED_HEIGHT[j] - predicted_height);
                        sum_derivative_square_residual = derivative_square_residual + sum_derivative_square_residual;
                    }

                    if y == 1 {
                        // if the data is the intercept (bias)
                        derivative_square_residual = -2.0 * (OBSERVED_HEIGHT[j] - predicted_height);
                        sum_derivative_square_residual = derivative_square_residual + sum_derivative_square_residual;
                    }
                }

                println!("La valeur de la somme des dérivées des carrées est : {}", sum_derivative_square_residual);

                // calcule step size, le pas
                step_size = sum_derivative_square_residual * slope_intercept_learning_rate[y];
                println!("La valeur du step size est : {}", step_size);

                println!("L'ancienne valeur : {}", slope_intercept[y]);
                // determination de la prochaine valeur de la valeur
                slope_intercept[y] = slope_intercept[y] - step_size;
                println!("La nouvelle valeur : {}", slope_intercept[y]);

                if sum_derivative_square_residual <= precision_success && sum_derivative_square_residual >= -precision_success {
                    slope_intercept_trouve[y] = true;

                    if y == 0 {
                        println!("\n\nfini de trouver le bon coéficient directeur de la droite de prediction  ! ");
                        println!("Le coéficient directeur : {}", slope_intercept[y]);
                        true_counter = true_counter + 1;
                    }

                    if y == 1 {
                        println!("\n\nfini de trouver le bon intercept de la droite de prediction  ! ");
                        println!("L'intercept : {}", slope_intercept[y]);
                        true_counter = true_counter + 1;
                    }
                }
            }
        }

        if true_counter == slope_intercept_trouve.len() {
            break;
        }
        
    }
}