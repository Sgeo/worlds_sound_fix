use std::path::PathBuf;

use memchr::memmem;

const BAD_SLEEP:  &'static [u8] = &[0x6A, 0x04, 0xFF, 0x15];
const GOOD_SLEEP: &'static [u8] = &[0x6A, 0x00, 0xFF, 0x15];

fn main() {
    let windir = std::env::var("SystemRoot").expect("Unable to find SystemRoot (Windows) directory!");
    let mciseq_path: PathBuf = [&windir, "syswow64", "mciseq.dll"].iter().collect();
    let mut mciseq_data = std::fs::read(mciseq_path).expect("Unable to open system mciseq.dll!");
    let mut found = 0;
    let mut position = 0;
    for pos in memmem::find_iter(&mciseq_data, BAD_SLEEP) {
        found = found + 1;
        if found > 1  {
            panic!("Multiple instances of target instructions found! This utility may need to be rewritten!");
        }
        position = pos;
    }
    if found != 1 {
        panic!("Target instructions not found! This utility may need to be rewritten!");
    }
    for i in 0..GOOD_SLEEP.len() {
        mciseq_data[position + i] = GOOD_SLEEP[i];
    }
    std::fs::write("mciseq.dll", mciseq_data).expect("Unable to write new mciseq.dll!");
}
