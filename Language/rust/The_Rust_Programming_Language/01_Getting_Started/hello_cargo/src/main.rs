fn main() {
    let mut v = vec![0; 3];
    v.iter_mut().for_each(|e| *e += 10);
    println!("{:#?}", v);
}
