use std::process::Command;

fn main() {
    let child = Command::new("ls")
        .env("PATH", "/bin")
        .output()
        .expect("failed to execute process");

    // if no error, program will continue..
}
