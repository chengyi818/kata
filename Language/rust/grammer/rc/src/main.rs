use std::{
    cell::RefCell,
    rc::{Rc, Weak},
};

#[derive(Debug)]
struct Node {
    val: i32,
    next: Option<Rc<RefCell<Node>>>,
    head: Option<Weak<RefCell<Node>>>,
}

// impl Drop for Node {
//     fn drop(&mut self) {
//         println!("Dropping {:#?}", self);
//     }
// }

#[test]
fn linked_list() {
    let first = Rc::new(RefCell::new(Node {
        val: 1,
        next: None,
        head: None,
    }));
    let second = Rc::new(RefCell::new(Node {
        val: 2,
        next: None,
        head: None,
    }));
    let third = Rc::new(RefCell::new(Node {
        val: 3,
        next: None,
        head: None,
    }));
    first.borrow_mut().next = Some(Rc::clone(&second));
    second.borrow_mut().next = Some(Rc::clone(&third));
    third.borrow_mut().head = Some(Rc::downgrade(&first));

    // let tmp = first.borrow();
    // println!("tmp: {}", tmp.val);
    let first = Some(first);
    let cur = first.as_ref();
    if cur.is_some() {
        println!("next: {}", cur.unwrap().borrow().val);
    }
}

fn main() {}
