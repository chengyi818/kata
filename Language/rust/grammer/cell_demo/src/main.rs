use crate::List::{Cons, Nil};
use std::cell::Cell;
use std::cell::RefCell;
use std::rc::Rc;

struct Cache {
    x: i32,
    y: i32,
    sum: Cell<Option<i32>>,
}

impl Cache {
    fn sum(&self) -> i32 {
        match self.sum.get() {
            None => {
                self.sum.set(Some((self.x + self.y) / 2));
                self.sum.get().unwrap()
            }
            Some(sum) => sum,
        }
    }
}

fn main() {
    let i = Cache {
        x: 10,
        y: 6,
        sum: Cell::new(None),
    };
    println!("sum: {}", i.sum());
    println!("sum: {}", i.sum());
}

#[test]
fn refcell_test() {
    let cell = RefCell::new(1);

    let mut cell_ref_1 = cell.borrow_mut(); // Mutably borrow the underlying data
    *cell_ref_1 += 1;
    println!("RefCell value: {:?}", cell_ref_1);

    let mut cell_ref_2 = cell.borrow_mut(); // Mutably borrow the data again (cell_ref_1 is still in scope though...)
    *cell_ref_2 += 1;
    println!("RefCell value: {:?}", cell_ref_2);
}

#[derive(Debug)]
enum List {
    Cons(Rc<RefCell<i32>>, Rc<List>),
    Nil,
}

#[test]
fn list_demo() {
    let value = Rc::new(RefCell::new(5));

    let a = Rc::new(Cons(Rc::clone(&value), Rc::new(Nil)));

    let b = Cons(Rc::new(RefCell::new(3)), Rc::clone(&a));
    let c = Cons(Rc::new(RefCell::new(4)), Rc::clone(&a));

    *value.borrow_mut() += 10;

    println!("a after = {:?}", a);
    println!("b after = {:?}", b);
    println!("c after = {:?}", c);
}
