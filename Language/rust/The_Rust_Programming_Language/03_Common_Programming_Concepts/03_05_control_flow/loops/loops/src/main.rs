fn main() {
    let mut i = 0;
    let result = loop {
        i += 1;
        if i == 6 {
            break i;
        }
        println!("again!");
    };
    println!("result: {}", result);

    let a = [10, 20, 30, 40, 50];

    for element in a.iter() {
        println!("the value is: {}", element);
    }

    for number in (1..4).rev() {
        println!("{}!", number);
    }
    println!("LIFTOFF!!!");
}
