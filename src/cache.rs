use std::process::Command;

pub fn clear_cache() {
    Command::new("rm")
        .arg("-r")
        .arg("graphs")
        .spawn()
        .expect("command rm failed to start");

    
    Command::new("rm")
        .arg("gradient_descent.gif")
        .spawn()
        .expect("command rm failed to start");


    Command::new("mkdir")
        .arg("graphs")
        .spawn()
        .expect("command mkdir failed to start");
}