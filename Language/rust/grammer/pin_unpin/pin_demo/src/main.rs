#[derive(Default)]
struct AddrTracker(Option<usize>);

impl AddrTracker {
    // 检查自己的内存地址是否发生了变化
    fn check_for_move(&mut self) {
        let current_addr = self as *mut Self as usize;
        println!("当前地址: 0x{:x}", current_addr);
        // match self.0 {
        //     None => self.0 = Some(current_addr), // 第一次检查，记录地址
        //     Some(prev_addr) => {
        //         if prev_addr != current_addr {
        //             println!(
        //                 "恐慌！我从地址 0x{:x} 被移动到了 0x{:x}",
        //                 prev_addr, current_addr
        //             );
        //         }
        //     }
        // }
    }
}

fn main() {
    let mut tracker = AddrTracker::default();
    tracker.check_for_move();

    // 将 tracker 移动到一个新函数
    move_it(tracker);
}

fn move_it(mut tracker: AddrTracker) {
    println!("--- 在 move_it 函数内部 ---");
    tracker.check_for_move();
}
