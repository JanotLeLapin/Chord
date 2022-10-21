# Chord

A Discord client/library written in Rust

## Compiling

### Prerequisites

- [Tauri CLI](https://tauri.app/v1/api/cli/)
- [Trunk CLI](https://trunkrs.dev/#install)
- [Rustup](https://rustup.rs/)

If you haven't already, install the wasm32-unknown-unknown target:

```sh
rustup install wasm32-unknown-unknown
```

### Building

Run the following command to build the Chord client front-end:

```sh
cargo tauri build
```

