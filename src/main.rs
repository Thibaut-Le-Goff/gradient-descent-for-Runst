use plotters::prelude::*;

pub fn graph(samples: Vec<(f32, f32)>, prediction_line: Vec<(f32, f32)>, prediction_line_dot: Vec<(f32, f32)>, x_y_min_max_graph: [f32; 4], i: usize) -> Result<(), Box<dyn std::error::Error>> {
    // send the result of the function in a result containing:
    //  - the result in case of succes = ()
    //  - a box (a pointer but its keeps ownership, in short)

    //let samples: Vec<(f32, f32)> = vec![(1.0, 3.3), (2., 2.1), (3., 1.5), (4., 1.9), (5., 1.0)];
   
    //let mut chart_builder = ChartBuilder::on(&drawing_area);

    let tittle: String = format!("graphs/gradient_descent-graph-number-{}.jpeg", i);

    let root = BitMapBackend::new(&tittle, (1280, 960)).into_drawing_area();
    root.fill(&WHITE);

    //determine the size between the chart and the end of the image
    let root = root.margin(20, 20, 20, 30);

    let tittle_chart: String = format!("Gradient descent, try number {}", i);
    // After this point, we should be able to draw construct a chart context
    let mut chart = ChartBuilder::on(&root)
        // Set the caption of the chart
        .caption(&tittle_chart, ("sans-serif", 40))//.into_font())
        // Set the size of the label region
        // the size of the between values
        .x_label_area_size(20)
        .y_label_area_size(40)
        // length of values of the x and y axis
        .build_cartesian_2d(x_y_min_max_graph[0]..x_y_min_max_graph[1], x_y_min_max_graph[2]..x_y_min_max_graph[3])?;

    // Then we can draw a mesh
    // configuration du quadrillage
    chart.configure_mesh()
        .max_light_lines(5)
        // We can customize the maximum number of labels allowed for each axis
        .x_labels(5)
        //&GREEN
        .max_light_lines(5)

        .y_labels(10)
        //.max_light_lines(5)
        // We can also change the format of the label text
        // show number of zero after the dot
        //.y_label_formatter(&|x| format!("{:.3}", x))
        .draw()?;

    // And we can draw something in the drawing area
    // put the red line 
    //let samples: Vec<(f32, f32)> = vec![(1.0, 3.3), (2., 2.1), (3., 1.5), (4., 1.9), (5., 1.0)];
    chart.draw_series(LineSeries::new(
        prediction_line,
        //vec![(x_y_min_max[0], (slope_intercept[0] * x_y_min_max[0]) + slope_intercept[1]), (x_y_min_max[1], (slope_intercept[0] * x_y_min_max[1]) + slope_intercept[1])],
        //chart_context.draw_series(LineSeries::new(data, BLACK)).unwrap()
        &GREEN,
    ))?;
    // Similarly, we can draw point series

    chart.draw_series(PointSeries::of_element(
        prediction_line_dot,
        5,
        &GREEN,
        &|c, s, st| {
            return EmptyElement::at(c)    // We want to construct a composed element on-the-fly
            + Circle::new((0,0),s,st.filled()) // At this point, the new pixel coordinate is established
            + Text::new(format!("{:?}", c), (10, 0), ("sans-serif", 15).into_font());
        },
    ))?;

    // put the red dot
    chart.draw_series(PointSeries::of_element(
        samples,
        5,
        &BLACK,
        &|c, s, st| {
            return EmptyElement::at(c)    // We want to construct a composed element on-the-fly
            + Circle::new((0,0),s,st.filled()) // At this point, the new pixel coordinate is established
            + Text::new(format!("{:?}", c), (10, 0), ("sans-serif", 15).into_font());
        },
    ))?;
    root.present()?;
    Ok(())
}




////////// ALGORITM  GRADIENT DESCENT ////////////

fn main() {

    // to create the gif, we have to use Command:
    use std::process::Command;

    // from : https://www.youtube.com/watch?v=sDv4f4s2SB8&t

    const OBSERVED_HEIGHT: [f32; 3] = [1.4, 1.9, 3.2];
    // The height of the three people, the height 
    // is the data we want to predicte from those
    // three samples, who is what we would expecte 
    // from the three inputs, the weights.

    const WEIGHT: [f32; 3] = [0.5, 2.3, 2.9];
    // Their weight, this is the inputs of 
    // the gradient descent.
    // Since each weight gives one height
    // I think I could say there are three 
    // propagations if I take it as a tiny
    // neural network.


    ////  GRAPHIQUE //////////////////////////////////
    let mut samples: Vec<(f32, f32)> = Vec::new();

    for i in 0..= OBSERVED_HEIGHT.len() - 1 {
        samples.push((WEIGHT[i], OBSERVED_HEIGHT[i]));
    }

    ///// To determine the length of the prediction ligne on the x and y axis: ////////////////
    let mut x_y_min_max: [f32; 4] = [0.0; 4];
    
    // determine what are the min and max values in the samples, on the xy axis
    for i in 0..= samples.len() - 1 {
        if samples[i].0 < x_y_min_max[0] {
            x_y_min_max[0] = samples[i].0;
        }
        if samples[i].0 > x_y_min_max[1] {
            x_y_min_max[1] = samples[i].0;
        }
        if samples[i].1 < x_y_min_max[2] {
            x_y_min_max[2] = samples[i].1;
        }
        if samples[i].1 > x_y_min_max[3] {
            x_y_min_max[3] = samples[i].1;
        }
    }

    ///// To determine the length of the graph on the x and y axis: ////////////////
    let mut x_y_min_max_graph: [f32; 4] = [0.0; 4];

    for i in 0..= x_y_min_max.len() - 1 {
        x_y_min_max_graph[i] = x_y_min_max[i] * 1.5;
    }
    
    ////////////////////////////////////////////////////////////

    let try_number: usize = 1000;
    // This is the number of time the programme
    // will try to determine the slope and the 
    // the intrcept afterward

    let mut slope_intercept_trouve: [bool; 2] = [false, false];
    // indicate if the good slope and intercept are 
    // found or not
    let mut true_counter: usize = 0;
    
    let precision_success: f32 = 0.001;
    // The programme will stop once the derivative of the sum 
    // of square of the difference between the observed data 
    // and the predicted one is between precision_success and 
    // its negative

    let mut step_size: f32;
    // The 

    let power_dif : f32 = 2.0;
    let slope_intercept_learning_rate: [f32; 2] = [0.01, 0.1];
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

    let mut sum_derivative_square_residual: f32;
    let mut derivative_square_residual: f32;
    // la somme des d??riv??s du carr?? de la diff??rence 
    // entre la valeur observ?? et celle attendue
    // pour le calcule du co??ficient directeur de la
    // courbes des pr??dictions a N-1 et N


    // <brouilon>
    // let batch_number: usize = 2;
    // pour mini batche :
    // for j in 0..= batch_number - 1 {  ?? la place de for j in WEIGHT.len() -1
    //  cr??e un nombre al??atoire x entre 0 et OBSERVED_HEIGHT.len()
    //  utilise x dans WEIGHT[x] et OBSERVED_HEIGHT[x]
    // </brouilon>


    let mut slope_intercept: [f32; 2] = [0.0, 0.0];
    // pour 0:
    // valeur de d??part du co??ficient directeur de la courbe
    // des pr??dictions

    // pour 1:
    // valeur de d??part de l'intercept de la courbe
    // des pr??dictions

    let mut predicted_height: f32;
    // la ou sera stock?? la taille pr??dite
    // par rapport ?? slope et intercept

    let mut number_end: usize = 0;

    ////////////// GRAPHIQUE /////////////////
    
    let prediction_line: Vec<(f32, f32)> = vec![(x_y_min_max[0], (slope_intercept[0] * x_y_min_max[0]) + slope_intercept[1]), (x_y_min_max[1], (slope_intercept[0] * x_y_min_max[1]) + slope_intercept[1])];
        
    //let tittle: Box<String> = Box::new(format!("graphs/gradient_descent-graph-number-0.jpeg"));

    graph((samples).to_vec(), (prediction_line).to_vec(), (prediction_line).to_vec(), x_y_min_max_graph, 0).ok();

    ///////////////////////////////////

    for i in 0..= try_number - 1 {
    // for each number of try

        // stop the algorihtm if the values has already been found

        // I would add another for loop here :
        // for eache layer (look backward)

        for y in 0..= slope_intercept.len() - 1 {

            if true_counter == slope_intercept_trouve.len() {
                //number_end = i;  false because will count unused try
                break;
            }

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
                        derivative_square_residual = (-power_dif * WEIGHT[j]) * (OBSERVED_HEIGHT[j] - predicted_height);
                        sum_derivative_square_residual = derivative_square_residual + sum_derivative_square_residual;
                    }

                    if y == 1 {
                        // if the data is the intercept (bias)
                        derivative_square_residual = -power_dif * (OBSERVED_HEIGHT[j] - predicted_height);
                        sum_derivative_square_residual = derivative_square_residual + sum_derivative_square_residual;
                    }
                }

                // calcule step size, le pas
                step_size = sum_derivative_square_residual * slope_intercept_learning_rate[y];

                // determination de la prochaine valeur de la valeur
                slope_intercept[y] = slope_intercept[y] - step_size;

                if sum_derivative_square_residual <= precision_success && sum_derivative_square_residual >= -precision_success {
                    slope_intercept_trouve[y] = true;
                    true_counter = true_counter + 1;

                    if y == 0 {
                        println!("\n\nfini de trouver le bon co??ficient directeur de la droite de prediction  ! ");
                        println!("Le co??ficient directeur : {}", slope_intercept[y]);
                    }

                    if y == 1 {
                        println!("\n\nfini de trouver le bon intercept de la droite de prediction  ! ");
                        println!("L'intercept : {}", slope_intercept[y]);
                    }
                }
            }
        }

        // can't add the break here because there are the for loop which will
        // go to the next type (weight or bias) of value
        //if true_counter == slope_intercept_trouve.len() {
        //    break;
        //}

        // need here anyway to avoid to use the others try available 
        if true_counter == slope_intercept_trouve.len() {
            number_end = i;
            break;
        }

        ////////////////// Graphic ///////////////////////
        if (i + 1) % 10 == 0 {
            let prediction_line: Vec<(f32, f32)> = vec![(x_y_min_max[0], (slope_intercept[0] * x_y_min_max[0]) + slope_intercept[1]), (x_y_min_max[1], (slope_intercept[0] * x_y_min_max[1]) + slope_intercept[1])];
            
            graph((samples).to_vec(), (prediction_line).to_vec(), (prediction_line).to_vec(), x_y_min_max_graph, i+1).ok();
        }
        /////////////////////////////////////////////////////
    }
    
    if true_counter == slope_intercept_trouve.len() {
        println!("\nl'??quation de la droite de pr??diction est : y = a{} + {}", slope_intercept[0], slope_intercept[1]);
        println!("L'algorithme a fait {} essaies pour trouver les bonnes donn??es.", number_end + 1);
        // + 1 because I want to count the first try which is with i = 0

        //////////////////// Graphic ////////////////
        let prediction_line: Vec<(f32, f32)> = vec![(x_y_min_max[0], (slope_intercept[0] * x_y_min_max[0]) + slope_intercept[1]), (x_y_min_max[1], (slope_intercept[0] * x_y_min_max[1]) + slope_intercept[1])];
            
        graph((samples).to_vec(), (prediction_line).to_vec(), (prediction_line).to_vec(), x_y_min_max_graph, number_end+1).ok();
        //////////////////////////////////////////
        
        //// Creation of the gif ////////////
        Command::new("convert")
            .arg("-delay")
            .arg("250")
            .arg("-loop")
            .arg("0")
            .arg("graphs/*.jpeg")
            .arg("graphs/gradient_descent.gif")
            .spawn()
            .expect("command failed to start");
    }
}