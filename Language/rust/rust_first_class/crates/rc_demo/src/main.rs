// DAG: 有向无环图

use std::cell::RefCell;
use std::rc::Rc;
use std::str;

#[derive(Debug)]
struct Node {
    id: usize,
    next: Option<Rc<Node>>,
}

impl Node {
    pub fn new(id: usize) -> Self {
        Node { id: id, next: None }
    }

    fn set_next(&mut self, next: Rc<Node>) {
        self.next = Some(next);
    }

    fn get_next(&self) -> Option<Rc<Node>> {
        self.next.clone()
    }
}

fn main() {
    let a = Box::leak(Box::new(1));
    let mut node1 = Node::new(1);
    let mut node2 = Node::new(2);
    let mut node3 = Node::new(3);
    let node4 = Node::new(4);

    node3.set_next(Rc::new(node4));
    node1.set_next(Rc::new(node3));
    node2.set_next(node1.get_next().unwrap());

    // Rc直接包含的数据无法修改
    // let node5 = Node::new(5);
    // let node3 = node1.get_next().unwrap();
    // node3.set_next(Rc::new(node5));

    println!("node1: {:#?}", node1);

    let a = "hello";
    let b = a;
    println!("a: {}, b: {}", a, b);
    println!("&a: {:p}, &b: {:p}", &a, &b);
}
