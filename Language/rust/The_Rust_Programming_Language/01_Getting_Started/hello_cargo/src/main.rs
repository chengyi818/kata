use std::collections::VecDeque;

#[derive(Debug)]
struct Student {
    id: usize,
}

fn main() {
    let a = "hello".to_string();
    println!("&a: {:p}", &a);
    let b = a;
    println!("&b: {:p}", &b);

    let a = Student { id: 0 };
    println!("&a: {:p}", &a);
    let b = a;
    println!("&b: {:p}", &b);
    let a = Box::new(1);
    let b: Vec<i32> = Vec::new();
}
