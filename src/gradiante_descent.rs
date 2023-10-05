/*
 * change of weights
 */

fn change_weights(true_counter: &mut usize, slope_intercept_trouve: &mut [bool; 2], input_values: &f32, observed_values: &Vec<f32>, weight: &mut f32, bias: &mut f32) {
    
    let weights_learning_rate: f32 = 0.01;

    let precision_success: f32 = 0.001;
    // The programme will stop once the derivative of the sum 
    // of square of the difference between the observed data 
    // and the predicted one is between precision_success and 
    // its negative

    //let mut step_size: f32 = 0.0;
    let mut sum_derivative_square_residual: f32 = 0.0;
    //let mut derivative_square_residual: f32 = 0.0;

    let predicted_height: f32 = (*weight * input_values) + *bias;
    // la ou sera stocké la taille prédite
    // par rapport à slope et intercept

    
    for value in 0..= observed_values.len() - 1 {
        // if the data is the slope (INPUTS_VALUESs), there would be another 
        // if to see in wich layer is the INPUTS_VALUES
        let derivative_square_residual: f32 = (-2.0 * input_values) * (observed_values[value] - predicted_height);
        sum_derivative_square_residual += derivative_square_residual;
        //println!("changement de la somme des carrées {}", sum_derivative_square_residual);
    }

    // calcule step size, le pas
    //println!("step size avent le changement {}", &step_size);
    let step_size: f32 = sum_derivative_square_residual * weights_learning_rate;
    //println!("step size après le changement {}", step_size);

    // determination de la prochaine valeur de la valeur
    // if the data is the slope (INPUTS_VALUESs), there would be another 
    // if to see in wich layer is the INPUTS_VALUES
    *weight -= step_size;


    if sum_derivative_square_residual <= precision_success && sum_derivative_square_residual >= -precision_success {
        slope_intercept_trouve[0] = true;
        *true_counter += 1;

        println!("\n\nfini de trouver le bon coéficient directeur de la droite de prediction  ! ");
        println!("Le coéficient directeur : {}", weight);
    }
}

/*
 * change of bias
 */

fn change_bias(true_counter: &mut usize, slope_intercept_trouve: &mut [bool; 2], input_values: &f32, observed_values: &Vec<f32>, weight: &mut f32, bias: &mut f32) {
    
    let bias_learning_rate: f32 = 0.1;

    let precision_success: f32 = 0.001;
    // The programme will stop once the derivative of the sum 
    // of square of the difference between the observed data 
    // and the predicted one is between precision_success and 
    // its negative

    //let mut step_size: f32 = 0.0;
    //let mut derivative_square_residual: f32 = 0.0;
    let mut sum_derivative_square_residual: f32 = 0.0;

    let predicted_height: f32 = (*weight * input_values) + *bias;
    // la ou sera stocké la taille prédite
    // par rapport à slope et intercept

    for value in 0..= observed_values.len() - 1 {
        // if the data is the intercept (bias)
        let derivative_square_residual: f32 = -2.0 * (observed_values[value] - predicted_height);
        sum_derivative_square_residual += derivative_square_residual;
        //test_derivative_square_residual = -2.0 * (observed_values[j] - *predicted_height);
        //test_sum_derivative_square_residual += *derivative_square_residual;
    }
    
    // calcule step size, le pas
    let step_size: f32 = sum_derivative_square_residual * bias_learning_rate;

    // determination de la prochaine valeur de la valeur
    // if the data is the intercept (bias)
    *bias -= step_size;

    if sum_derivative_square_residual <= precision_success && sum_derivative_square_residual >= -precision_success {
        slope_intercept_trouve[1] = true;
        *true_counter += 1;

        println!("\n\nfini de trouver le bon intercept de la droite de prediction  ! ");
        println!("L'intercept : {}", bias);
    }
}


/*
 * optimisation
 */

pub fn optimisation(true_counter: &mut usize, slope_intercept_trouve: &mut [bool; 2], input_values: &Vec<f32>, observed_values: &Vec<f32>, weight: &mut f32, bias: &mut f32) {

    for y in 0..= slope_intercept_trouve.len() - 1 {
        // pour chaque paras

        if *true_counter == slope_intercept_trouve.len() {
            break;
        }

        if !slope_intercept_trouve[y] { // equal to :
        //if slope_intercept_trouve[y] == false {
            // if the good value for this data have not been found.
            //sum_derivative_square_residual = 0.0;
            //println!("{}", sum_derivative_square_residual);

            //println!("debut changement du para {}", y);
            if y == 0 {
                //println!("debut changement du poid{}", y);
                //change_weights(true_counter, slope_intercept_trouve, &mut predicted_height, &input_values, &mut derivative_square_residual, &mut sum_derivative_square_residual, &observed_values, weight);
                change_weights(true_counter, slope_intercept_trouve, &input_values[y], &observed_values, weight, bias);
                //println!("fin changement du poid{}", y);
            }

            if y == 1 {
                //change_bias(true_counter, slope_intercept_trouve, &mut predicted_height, &input_values, &mut derivative_square_residual, &mut sum_derivative_square_residual, &observed_values, bias);
                change_bias(true_counter, slope_intercept_trouve, &input_values[y], &observed_values, weight, bias);
            }
            //println!("fin changement du para {}", y);

        /*
            for j in 0..= input_values.len() - 1 {
                // for each pair of datas (given and observed), samples:
                predicted_height = (*weight * input_values[j]) + *bias;

                if y == 0 {
                    // if the data is the slope (INPUTS_VALUESs), there would be another 
                    // if to see in wich layer is the INPUTS_VALUES
                    derivative_square_residual = (-2.0 * input_values[j]) * (observed_values[j] - predicted_height);
                    sum_derivative_square_residual += derivative_square_residual;
                }

                if y == 1 {
                    // if the data is the intercept (bias)
                    derivative_square_residual = -2.0 * (observed_values[j] - predicted_height);
                    sum_derivative_square_residual += derivative_square_residual;
                }
            }

            // calcule step size, le pas
            step_size = sum_derivative_square_residual * slope_intercept_learning_rate[y];

            // determination de la prochaine valeur de la valeur
            if y == 0 {
                // if the data is the slope (INPUTS_VALUESs), there would be another 
                // if to see in wich layer is the INPUTS_VALUES
                *weight -= step_size;
            }

            if y == 1 {
                // if the data is the intercept (bias)
                *bias -= step_size;
            }

            if sum_derivative_square_residual <= precision_success && sum_derivative_square_residual >= -precision_success {
                slope_intercept_trouve[y] = true;
                *true_counter += 1;

                if y == 0 {
                    println!("\n\nfini de trouver le bon coéficient directeur de la droite de prediction  ! ");
                    println!("Le coéficient directeur : {}", weight);
                }

                if y == 1 {
                    println!("\n\nfini de trouver le bon intercept de la droite de prediction  ! ");
                    println!("L'intercept : {}", bias);
                }
            }
            */
        }
    }
}