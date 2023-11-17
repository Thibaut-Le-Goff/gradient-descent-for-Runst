pub fn optimisation(true_counter: &mut usize, slope_intercept_trouve: &mut [bool; 2], input_values: &Vec<f32>, observed_values: &Vec<f32>, slope_intercept: &mut [f32; 2]) {
    let mut step_size: f32;

    let slope_intercept_learning_rate: [f32; 2] = [0.01, 0.1];

    let mut sum_derivative_square_residual: f32;
    let mut derivative_square_residual: f32;

    let precision_success: f32 = 0.001;
    // The programme will stop once the derivative of the sum 
    // of square of the difference between the observed data 
    // and the predicted one is between precision_success and 
    // its negative

    let mut predicted_height: f32;
    // la ou sera stocké la taille prédite
    // par rapport à slope et intercept

    for y in 0..= slope_intercept.len() - 1 {

        if *true_counter == slope_intercept_trouve.len() {
            //number_end = i;  false because will count unused try
            break;
        }

        if !slope_intercept_trouve[y] { // equal to :
        //if slope_intercept_trouve[y] == false {
            // if the good value for this data have not been found.
            sum_derivative_square_residual = 0.0;

            for j in 0..= input_values.len() - 1 {
                // for each pair of datas (given and observed), samples:
                predicted_height = (slope_intercept[0] * input_values[j]) + slope_intercept[1];

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
            slope_intercept[y] -= step_size;

            if sum_derivative_square_residual <= precision_success && sum_derivative_square_residual >= -precision_success {
                slope_intercept_trouve[y] = true;
                *true_counter += 1;

                if y == 0 {
                    println!("\n\nfini de trouver le bon coéficient directeur de la droite de prediction  ! ");
                    println!("Le coéficient directeur : {}", slope_intercept[y]);
                }

                if y == 1 {
                    println!("\n\nfini de trouver le bon intercept de la droite de prediction  ! ");
                    println!("L'intercept : {}", slope_intercept[y]);
                }
            }
        }
    }
}