use serde::{Deserialize, Serialize};

#[derive(Serialize)]
pub struct MissionRequest {
	pub name: String,
    pub world: String,
}

#[derive(Deserialize)]
pub struct MissionResponse {
    pub id: i64,
}
