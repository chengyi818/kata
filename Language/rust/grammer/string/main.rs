// https://mp.weixin.qq.com/s/dlKk02BNYGPkMFThwTwFiA

fn main() {
    let mut s1 = String::from("hello");

    let len = calculate_length(&s1);

    println!("The Length is {}.", len);
}

fn calculate_length(s: &String) -> usize {
    s.len()
}
