//use crate calculations::*;
//use crate calculations;
//use crate::calculations::addition::*;
//use crate::calculations::substraction::*;
//use crate::calculations::multiplication::*;
mod calculations;
//pub mod addition;
//pub mod multiplication;
//pub mod substraction;


//pub fn optimisation(true_counter: &mut usize, slope_intercept_trouve: &mut [bool; 2], input_values: &Vec<f32>, observed_values: &Vec<f32>, weights: &mut Vec<f32>, bias: &mut Vec<f32>) {
pub fn optimisation(true_counter: &mut usize, slope_intercept_trouve: &mut [bool; 2], input_values: &Vec<Vec<f32>>, observed_values: &Vec<Vec<f32>>, weights: &mut Vec<f32>, bias: &mut Vec<f32>) {
    //let mut step_size: f32;
    let mut step_size: Vec<f32>;

    let slope_intercept_learning_rate: [f32; 2] = [0.01, 0.1];

    //let mut sum_derivative_square_residual: f32;
    //let mut derivative_square_residual: f32;
    let mut sum_derivative_square_residual: Vec<f32>;
    let mut derivative_square_residual: Vec<f32>;

    let precision_success: f32 = 0.001;
    // The programme will stop once the derivative of the sum 
    // of square of the difference between the observed data 
    // and the predicted one is between precision_success and 
    // its negative

    //let mut predicted_height: f32;
    let mut predicted_height: Vec<f32>;
    // la ou sera stocké la taille prédite
    // par rapport à slope et intercept

    for y in 0..2 {

        if *true_counter == slope_intercept_trouve.len() {
            //number_end = i;  false because will count unused try
            break;
        }

        if !slope_intercept_trouve[y] { // equal to :
        //if slope_intercept_trouve[y] == false {
            // if the good value for this data have not been found.
            sum_derivative_square_residual = Vec::new();

            for j in 0..input_values.len() {
                // for each pair of datas (given and observed), samples:
                //predicted_height = (weights[0] * input_values[j]) + bias[0];
                predicted_height = calculations::addition::vec_vec(calculations::multiplication::mat_mat(weights, input_values[j]), bias);

                if y == 0 {
                    // if the data is the slope (INPUTS_VALUESs), there would be another
                    // if to see in wich layer is the INPUTS_VALUES
                    //derivative_square_residual = (-2.0 * input_values[j]) * (observed_values[j] - predicted_height);
                    derivative_square_residual = calculations::multiplication::mat_mat(&calculations::multiplication::num_mat((-2.0 as f32, input_values[j]), &calculations::substraction::vec_vec(&observed_values[j], &predicted_height)));
                    //sum_derivative_square_residual += derivative_square_residual;
                    sum_derivative_square_residual = calculations::addition::vec_vec(&sum_derivative_square_residual, &derivative_square_residual);
                }

                if y == 1 {
                    // if the data is the intercept (bias)
                    //derivative_square_residual = -2.0 * (observed_values[j] - predicted_height);
                    derivative_square_residual = calculations::multiplication::num_mat(-2.0 as f32, &calculations::substraction::vec_vec(&observed_values[j], &predicted_height));
                    //sum_derivative_square_residual += derivative_square_residual;
                    sum_derivative_square_residual = calculations::addition::vec_vec(&sum_derivative_square_residual, &derivative_square_residual);
                }
            }

            if y == 0 {
                // calcule step size, le pas
                //step_size = sum_derivative_square_residual * slope_intercept_learning_rate[y];
                step_size = calculations::multiplication::num_mat(slope_intercept_learning_rate[y], &sum_derivative_square_residual);

                // determination de la prochaine valeur de la valeur
                //weights[0] -= step_size;
                *weights = calculations::substraction::vec_vec(weights, &step_size);
            }

            if y == 1 {
                // calcule step size, le pas
                //step_size = sum_derivative_square_residual * slope_intercept_learning_rate[y];
                step_size = calculations::multiplication::num_mat(slope_intercept_learning_rate[y], &sum_derivative_square_residual);

                // determination de la prochaine valeur de la valeur
                //bias[0] -= step_size;
                *bias = calculations::substraction::vec_vec(bias, &step_size);
            }

            if sum_derivative_square_residual[0] <= precision_success && sum_derivative_square_residual[0] >= -precision_success {
                slope_intercept_trouve[y] = true;
                *true_counter += 1;

                if y == 0 {
                    println!("\n\nfini de trouver le bon coéficient directeur de la droite de prediction  ! ");
                    println!("Le coéficient directeur : {:?}", weights);
                }

                if y == 1 {
                    println!("\n\nfini de trouver le bon intercept de la droite de prediction  ! ");
                    println!("L'intercept : {:?}", bias);
                }
            }
        }
    }
}