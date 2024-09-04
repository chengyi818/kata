fn main() {
    let val = 3;
    let v: Vec<usize> = vec![1, 2, 3, 4];
    if let Some(i) = find_pos(&v, 3) {
        println!("find val:{:?} in {:?}, index: {:?}", val, v, i);
    }
}

fn find_pos(v: &Vec<usize>, val: usize) -> Option<usize> {
    for (i, j) in v.iter().enumerate() {
        if *j == val {
            return Some(i);
        }
    }
    None
}
