use plotters::prelude::*;

pub fn choose_x_y_min_max(samples: &Vec<(f32, f32)>, input_value: &f32) -> [f32; 4] {
    ///// To determine the length of the prediction ligne on the x and y axis: ////////////////
    let mut x_y_min_max: [f32; 4] = [*input_value; 4];
    
    // determine what are the min and max values in the samples, on the xy axis
    for i in 0..samples.len() {
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

    x_y_min_max
}

pub fn create(samples: Vec<(f32, f32)>, prediction_line: Vec<(f32, f32)>, x_y_min_max: [f32; 4], trial: usize) -> Result<(), Box<dyn std::error::Error>> {
    // send the result of the function in a result containing:
    //  - the result in case of succes = ()
    //  - a box (a pointer but its keeps ownership, in short)
   
    let prediction_line_dot: Vec<(f32, f32)> = prediction_line.clone();

    let tittle: String;

    if trial < 10 {
        tittle = format!("graphs/gradient_descent-graph-number-000{}.jpeg", trial);
    } else if trial < 100 {
        tittle = format!("graphs/gradient_descent-graph-number-00{}.jpeg", trial);
    } else if trial < 1000 {
        tittle = format!("graphs/gradient_descent-graph-number-0{}.jpeg", trial);
    } else {
        tittle = format!("graphs/gradient_descent-graph-number-{}.jpeg", trial);
    };

    let root = BitMapBackend::new(&tittle, (1280, 960)).into_drawing_area();
    root.fill(&WHITE)?; // ? == warn if there is an error (if I understood what error propagation is)

    //determine the size between the chart and the end of the image
    let root = root.margin(60, 60, 60, 200);
    
    let tittle_chart: String = format!("Gradient descent, try number {}", trial);

    // After this point, we should be able to draw construct a chart context
    let mut chart = ChartBuilder::on(&root)
        // Set the caption of the chart
        .caption(&tittle_chart, ("sans-serif", 40))//.into_font())
        // Set the size of the label region
        // the size of the between values
        .x_label_area_size(20)
        .y_label_area_size(40)
        // length of values of the x and y axis
        .build_cartesian_2d(x_y_min_max[0]..x_y_min_max[1], x_y_min_max[2]..x_y_min_max[3])?;

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
    chart.draw_series(LineSeries::new(
        prediction_line,
        GREEN,
    ))?;
    // Similarly, we can draw point series

    chart.draw_series(PointSeries::of_element(
        prediction_line_dot,
        5,
        GREEN,
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
        BLACK,
        &|c, s, st| {
            return EmptyElement::at(c)    // We want to construct a composed element on-the-fly
            + Circle::new((0,0),s,st.filled()) // At this point, the new pixel coordinate is established
            + Text::new(format!("{:?}", c), (10, 0), ("sans-serif", 15).into_font());
        },
    ))?;
    root.present()?;

    Ok(())
}