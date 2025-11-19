use std::sync::{Arc, Mutex};
use std::thread::sleep;
use std::time::{Duration};
use std::{thread};

fn main() {
    // let data = Arc::new(Mutex::new(vec![1, 2, 3]));
    let data = Arc::new(vec![1, 2, 3]);
    let data_clone = Arc::clone(&data);
    thread::spawn(move || {
        let mut data: Arc<Vec<i32>> = data_clone;
        let a = Arc::get_mut(&mut data).unwrap();
        a.push(4);
        // data.push(4); // 安全修改
    });
    sleep(Duration::new(2, 0));
    println!("{:?}", data);

}

// use std::sync::{Arc, Mutex};
// use std::thread;

// let data = Arc::new(Mutex::new(vec![1, 2, 3]));
// let data_clone = Arc::clone(&data);
// thread::spawn(move || {
//     let mut data = data_clone.lock().unwrap();
//     data.push(4); // 安全修改
// });
