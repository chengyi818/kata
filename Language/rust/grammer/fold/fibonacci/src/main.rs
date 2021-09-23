fn tribonacci(n: i32) -> i32 {
    (0..n).fold((0, 1, 1), |t, _| (t.1, t.2, t.0 + t.1 + t.2)).0
}

fn sum(n: i32) -> i32 {
    (0..=n).fold(0, |acc, x| acc + x)
}

fn fibonacci(n: i32) -> i32 {
    (0..=n)
        .fold((0, 1), |t, _| {
            println!("t.0: {}, t.1: {}", t.0, t.1);
            return (t.1, t.0 + t.1);
        })
        .0
}

fn main() {
    println!("res: {}", tribonacci(4));
    println!("res: {}", fibonacci(10));
    println!("sum: {}", sum(100));
}
