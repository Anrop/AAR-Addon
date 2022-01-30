use serde::{Deserialize, Serialize};
use std::fs;
use std::error::Error;

#[derive(Clone, Deserialize, Serialize)]
pub struct Config {
    pub authorization: String,
    pub url: String,
}

const FILENAME: &str = "aar.json";

pub fn empty_config() -> Config {
    Config {
        authorization: "".to_string(),
        url: "".to_string(),
    }
}

pub fn read_config() -> Result<Config, Box<dyn Error>> {
    let contents = fs::read_to_string(FILENAME)?;
    let config: Config = serde_json::from_str(&contents)?;
    Ok(config)
}
