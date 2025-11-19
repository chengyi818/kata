struct Buffer<const N: usize> {
    data: [u8; N],
}

const fn compute_buffer_size(factor: usize) -> usize {
    factor * 1024
}

fn main() {
    const SIZE: usize = compute_buffer_size(4);
    let buffer = Buffer::<SIZE> { data: [0; SIZE] };
    let buffer1 = [0; SIZE];
    println!("Buffer size: {} bytes", buffer1.len());
    println!("Buffer size: {} bytes", buffer.data.len());
}
