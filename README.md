# Anrop AAR Addon

Anrop AAR addon for Arma 3.
This repository handles the game server side of the stats tracking by providing the in-game addon for gathering game related data and the extension necessary to provision the data to a backend.

The extension is written in Rust.

## Building

Install Rust and Cargo, simplest way is to use [Rustup](https://rustup.rs/). This is used to compile the native extension.

Install [HEMTT](https://github.com/BrettMayson/HEMTT/releases). This is used to package the mod.

Run `cargo build` to compile extension for current platform.

Run `hemtt build` to assemble Arma 3 files into PBOs.

## Config

Add a JSON file to your CWD when launching Arma named `aar.json`.
The file should have the following format:
````json
{
	"authorization": "token authorization", // Optional
	"url": "http://api.aar.anrop.se"
}
````
