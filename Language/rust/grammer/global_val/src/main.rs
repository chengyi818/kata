use std::sync::OnceLock;
use std::collections::HashMap;
use std::sync::Mutex;

// 使用 OnceLock + Mutex 创建全局可修改的 HashMap
static MUTABLE_MAP: OnceLock<Mutex<HashMap<String, i32>>> = OnceLock::new();

fn main() {
    // 初始化并添加数据
    {
        let map = MUTABLE_MAP.get_or_init(|| {
            println!("初始化 HashMap (Mutex)");
            Mutex::new(HashMap::new())
        });
        
        let mut map_guard = map.lock().unwrap();
        map_guard.insert("用户1".to_string(), 100);
        map_guard.insert("用户2".to_string(), 200);
        println!("添加初始数据后的 HashMap: {:?}", map_guard);
    } // map_guard 在这里释放锁
    
    // 在另一个作用域中修改
    {
        let map = MUTABLE_MAP.get().unwrap();
        let mut map_guard = map.lock().unwrap();
        map_guard.insert("用户3".to_string(), 300);
        map_guard.insert("用户1".to_string(), 150); // 更新已存在的值
        println!("修改后的 HashMap: {:?}", map_guard);
    }
    
    // 多线程示例
    use std::thread;
    
    let handles: Vec<_> = (0..3)
        .map(|i| {
            thread::spawn(move || {
                let map = MUTABLE_MAP.get().unwrap();
                let mut map_guard = map.lock().unwrap();
                map_guard.insert(format!("线程_{}", i), (i + 1) * 10);
                println!("线程 {} 写入数据", i);
            })
        })
        .collect();
    
    for handle in handles {
        handle.join().unwrap();
    }
    
    // 查看最终结果
    {
        let map = MUTABLE_MAP.get().unwrap();
        let map_guard = map.lock().unwrap();
        println!("最终 HashMap 内容: {:?}", map_guard);
    }
}
