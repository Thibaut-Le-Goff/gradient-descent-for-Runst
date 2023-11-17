mod graph;
mod cache;
mod gradiante_descent;

use std::process::Command;

/*
extern crate engiffen;

use engiffen::{load_images, engiffen, Gif, Quantizer};
use std::fs::File;
*/
////////// ALGORITM  GRADIENT DESCENT ////////////

fn main() {
    cache::clear_cache();
    cache::create_cache();

    // from : https://www.youtube.com/watch?v=sDv4f4s2SB8&t

    let observed_values: Vec<f32> = vec![1.4, 1.9, 3.2];


    let input_values: Vec<f32> = vec![0.5, 2.3, 2.9];


    ////  GRAPHIQUE //////////////////////////////////
    let mut samples: Vec<(f32, f32)> = Vec::new();

    for i in 0..= observed_values.len() - 1 {
        samples.push((input_values[i], observed_values[i]));
    }

    ///// To determine the length of the prediction ligne on the x and y axis: ////////////////
    let x_y_min_max: [f32; 4] = graph::choose_x_y_min_max(&samples, &input_values[0]);


    ////////////////////////////////////////////////////////////

    let mut slope_intercept: [f32; 2] = [0.0, 0.0];
    // pour 0:
    // valeur de départ du coéficient directeur de la courbe
    // des prédictions

    // pour 1:
    // valeur de départ de l'intercept de la courbe
    // des prédictions

    let mut slope_intercept_trouve: [bool; 2] = [false, false];
    // indicate if the good slope and intercept are 
    // found or not
    let mut true_counter: usize = 0;
    

    let try_nb_bettween_graphs: usize = 10;

    let mut number_end: usize = 0;

    ////////////// GRAPHIQUE /////////////////
    
    let prediction_line: Vec<(f32, f32)> = vec![(x_y_min_max[0], (slope_intercept[0] * x_y_min_max[0]) + slope_intercept[1]), (x_y_min_max[1], (slope_intercept[0] * x_y_min_max[1]) + slope_intercept[1])];
        
    //let tittle: Box<String> = Box::new(format!("graphs/gradient_descent-graph-number-0.jpeg"));

    graph::create((samples).to_vec(), (prediction_line).to_vec(), x_y_min_max, 0).ok();

    ///////////////////////////////////
    //let try_number: usize = 1000;
    // This is the number of time the programme
    // will try to determine the slope and the 
    // the intrcept afterward
    for trial in 0..= 1000 {
    // for each number of try

        // stop the algorihtm if the values has already been found

        // I would add another for loop here :
        // for eache layer (look backward)

        gradiante_descent::optimisation(&mut true_counter, &mut slope_intercept_trouve, &input_values, &observed_values, &mut slope_intercept);

        if true_counter == slope_intercept_trouve.len() {
            number_end = trial;
            break;
        }

        ////////////////// Graphic ///////////////////////
        if (trial + 1) % try_nb_bettween_graphs == 0 {
            let prediction_line: Vec<(f32, f32)> = vec![(x_y_min_max[0], (slope_intercept[0] * x_y_min_max[0]) + slope_intercept[1]), (x_y_min_max[1], (slope_intercept[0] * x_y_min_max[1]) + slope_intercept[1])];
            graph::create((samples).to_vec(), (prediction_line).to_vec(), x_y_min_max, trial+1).ok();
        }
        /////////////////////////////////////////////////////
    }
    
    if true_counter == slope_intercept_trouve.len() {
        println!("\nl'équation de la droite de prédiction est : y = a{} + {}", slope_intercept[0], slope_intercept[1]);
        println!("L'algorithme a fait {} essaies pour trouver les bonnes données.", number_end + 1);
        // + 1 because I want to count the first try which is with i = 0

        //////////////////// Graphic ////////////////
        let prediction_line: Vec<(f32, f32)> = vec![(x_y_min_max[0], (slope_intercept[0] * x_y_min_max[0]) + slope_intercept[1]), (x_y_min_max[1], (slope_intercept[0] * x_y_min_max[1]) + slope_intercept[1])];
            
        graph::create((samples).to_vec(), (prediction_line).to_vec(), x_y_min_max, number_end + 1).ok();
        //////////////////////////////////////////
        
        //// Creation of the gif ////////////
        Command::new("convert")
            .arg("-delay")
            .arg("200")
            .arg("-loop")
            .arg("0")
            .arg("graphs/*.jpeg")
            .arg("gradient_descent.gif")
            .spawn()
            .expect("command convert failed to start");
    }
}