fn main() {
    let a = 1;
    let b = Box::new(&a);
    println!("Hello, world! {:?} {:?}", a, *b);
}
