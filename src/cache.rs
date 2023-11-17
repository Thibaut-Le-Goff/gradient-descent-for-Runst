use std::process::Command;

pub fn clear_cache() {
    // if the project is run from src
    Command::new("rm")
        .arg("-r")
        .arg("../graphs")
        .spawn()
        .expect("command rm failed to start");

    Command::new("rm")
        .arg("../gradient_descent.gif")
        .spawn()
        .expect("command rm failed to start");


    // if the project is run from the 
    // directory of the project or the src
    Command::new("rm")
        .arg("-r")
        .arg("graphs")
        .spawn()
        .expect("command rm failed to start");

    Command::new("rm")
        .arg("gradient_descent.gif")
        .spawn()
        .expect("command rm failed to start");

        
    // if the project is run from the 
    // directory of the project
    Command::new("rm")
        .arg("-r")
        .arg("src/graphs")
        .spawn()
        .expect("command rm failed to start");

    Command::new("rm")
        .arg("src/gradient_descent.gif")
        .spawn()
        .expect("command rm failed to start");
}

pub fn create_cache() {
    Command::new("mkdir")
        .arg("graphs")
        .spawn()
        .expect("command mkdir failed to start");
}