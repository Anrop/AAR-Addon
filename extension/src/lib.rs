use arma_rs::{arma, Extension};

#[macro_use]
extern crate lazy_static;

use std::sync::Mutex;

mod config;
mod mission;
mod organizer;

lazy_static! {
    static ref ORGANIZER: Mutex<organizer::Organizer> = Mutex::new(organizer::Organizer::new());
}

fn init() -> String {
    ORGANIZER.lock().map_or("ERROR".to_string(), |mut o| o.read_config())
}

fn event(json_str: String) -> String {
    ORGANIZER.lock().map_or("ERROR".to_string(), |mut o| o.event(json_str))
}

fn mission(name: String, world: String) -> String {
    ORGANIZER.lock().map_or("ERROR".to_string(), |mut o| o.mission(name, world))
}

#[arma]
fn extension() -> Extension {
    Extension::build()
        .command("init", init)
        .command("event", event)
        .command("mission", mission)
        .finish()
}
