# 📁 MyFTP — RFC 959 FTP Server

A lightweight FTP server written in **C**, built as part of the Epitech B-NWP-400 project.  
It follows the [RFC 959](https://www.rfc-editor.org/rfc/rfc959) standard and handles multiple simultaneous clients using `poll()`.

---

## 🚀 Usage

```sh
./myftp <port> <home_directory>
```

| Argument         | Description                              |
|------------------|------------------------------------------|
| `port`           | Port the server listens on (1–65535)     |
| `home_directory` | Root directory served to FTP clients     |

**Example:**
```sh
./myftp 2121 /tmp/ftp
```

---

## ⚙️ Build

```sh
make        # Build the binary
make clean  # Remove object files
make fclean # Remove object files and binary
make re     # Full rebuild
```

---

## ✨ Features

- **Multi-client support** — up to 10 000 concurrent connections via `poll()`
- **Anonymous authentication** — clients log in as `Anonymous`
- **FTP command support:**

| Command | Description                        |
|---------|------------------------------------|
| `USER`  | Provide username                   |
| `PASS`  | Provide password                   |
| `PWD`   | Print current working directory    |
| `CWD`   | Change working directory           |
| `CDUP`  | Move to parent directory           |
| `DELE`  | Delete a file                      |
| `HELP`  | List available commands            |
| `NOOP`  | No operation (keep-alive)          |
| `QUIT`  | Close the connection               |

---

## 🏗️ Project Structure

```
.
├── includes/
│   ├── myftp.h             # Core types & constants
│   ├── server.h            # Server lifecycle
│   ├── authentification.h  # Authentication logic
│   ├── commands.h          # Command dispatcher & handlers
│   └── client_handler.h    # Per-client I/O handling
└── src/
    ├── main.c              # Entry point & argument validation
    ├── server.c            # Server init & main poll loop
    ├── socket_setup.c      # Socket creation & binding
    ├── client_management.c # Add/remove clients
    ├── client_handler.c    # Read & dispatch client data
    ├── authentification.c  # USER / PASS handling
    ├── commands.c          # Core FTP commands
    └── file_commands.c     # Filesystem commands (PWD, CWD, …)
```

---

## 👤 Author

**louis.filhol-valantin** — Epitech 2025
