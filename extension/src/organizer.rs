use crate::config::{Config, empty_config, read_config};
use crate::mission::{MissionRequest, MissionResponse};
use reqwest::blocking::Client;
use std::collections::HashMap;

pub struct Organizer {
    client: Client,
    config: Config,
    mission_id: i64,
}

impl Organizer {
    pub fn new() -> Organizer {
        Organizer {
            client: Client::new(),
            config: empty_config(),
            mission_id: 0,
        }
    }

    pub fn event(&mut self, json_str: String) -> String {
        match serde_json::from_str::<HashMap<String, serde_json::Value>>(&json_str) {
            Ok(mut event) => {
                event.insert(
                    "timestamp".to_string(),
                    serde_json::Value::String(chrono::Utc::now().to_rfc3339().to_string()),
                );

                let path = format!("{}/missions/{}/events", self.config.url, self.mission_id);

                let result = self
                    .client
                    .post(&path)
                    .json(&event)
                    .send();

                match result {
                    Ok(_) => "OK".to_string(),
                    Err(_) => "ERROR".to_string(),
                }
            },
            Err(e) => {
                println!("{}", e);
                "ERROR".to_string()
            }
        }
    }

    pub fn mission(&mut self, name: String, world: String) -> String {
        let path = format!("{}/missions", self.config.url);

        let result = self
            .client
            .post(&path)
            .json(&MissionRequest { name, world })
            .send();

        let response = match result {
            Ok(response) => response,
            Err(_) => return "-1".to_string(),
        };

        let mission: MissionResponse = match response.json() {
            Ok(mission) => mission,
            Err(_) => return "-1".to_string(),
        };

        self.mission_id = mission.id;
        self.mission_id.to_string()
    }

    pub fn read_config(&mut self) -> String {
        match read_config() {
            Ok(config) => {
                let url = config.url.clone();
                self.config = config;
                url
            },
            Err(e) => {
                println!("{}", e);
                "ERROR".to_string()
            }
        }
    }
}
