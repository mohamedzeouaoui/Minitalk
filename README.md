*This project has been created as part of the 42 curriculum by mzeouaou.*

<h1 align="center">Minitalk</h1>

<p align="center">
  <em>A small data exchange program using UNIX signals.</em><br>
  A client sends a string to a server using only <code>SIGUSR1</code> and <code>SIGUSR2</code>.
</p>

<p align="center">
  <img alt="Language" src="https://img.shields.io/badge/language-C-blue">
  <img alt="Norm" src="https://img.shields.io/badge/norminette-passing-brightgreen">
  <img alt="42" src="https://img.shields.io/badge/school-42-black">
</p>

---

## Table of Contents

- [Description](#description)
- [Installation](#installation)
- [Usage](#usage)
- [Bonus](#bonus)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [Testing](#testing)
- [Author](#author)
- [Resources](#resources)

---

## Description

**Minitalk** is a 42 project about **inter-process communication** with UNIX signals. It consists of two programs:

- A **server**, which starts first and prints its **PID**
- A **client**, which takes the server's PID and a string, and sends that string to the server

The only way for them to communicate is through the two user signals `SIGUSR1` and `SIGUSR2`. The server must display the received string quickly and must be able to receive strings from several clients one after the other without restarting.

## Installation

```bash
git clone https://github.com/mohamedzeouaoui/minitalk.git
cd minitalk
make
```

This produces two executables: `server` and `client`.

### Makefile rules

| Rule          | Description                                      |
|---------------|--------------------------------------------------|
| `make`        | Compile `server` and `client`                    |
| `make bonus`  | Compile the bonus versions (if implemented)      |
| `make clean`  | Remove object files                              |
| `make fclean` | Remove object files and executables              |
| `make re`     | Recompile from scratch                           |

## Usage

Start the server in one terminal:

```bash
./server
```

It prints its PID:

```text
Server PID: 12345
```

Send a message from another terminal:

```bash
./client 12345 "Hello, 42!"
```

The server prints:

```text
Hello, 42!
```

## Bonus

If you implemented the bonus part, it adds:

- **Acknowledgment**: the server sends a signal back to the client for each message (or each bit) it receives, so the client knows the message was delivered
- **Unicode support**: characters such as `é`, `你` or emojis are transmitted correctly

> Remove this section if you did not do the bonus.

## Project Structure

```text
minitalk/
├── Makefile
├── minitalk.h            # Prototypes and includes
├── server.c              # Server: receives and prints the message
├── client.c              # Client: sends the message
├── utils.c               # Helper functions
├── server_bonus.c        # Bonus versions
└── client_bonus.c
```

> Adjust this tree to match your own files.

## How It Works

### Encoding

Each character is sent **bit by bit**, from the most significant bit to the least significant one:

| Signal     | Meaning |
|------------|---------|
| `SIGUSR1`  | bit `1` |
| `SIGUSR2`  | bit `0` |

For example, the letter `A` (`01000001`) is sent as: `SIGUSR2`, `SIGUSR1`, `SIGUSR2`, `SIGUSR2`, `SIGUSR2`, `SIGUSR2`, `SIGUSR2`, `SIGUSR1`.

### Server

1. The server prints its PID and waits with `pause()`.
2. A signal handler, installed with `sigaction`, receives each signal and rebuilds the current character bit by bit.
3. Once 8 bits have been received, the character is printed with `write`.
4. When the null character `'\0'` is received, the message is over and a newline is printed. The server is then ready for the next message.

### Client

1. The client reads the server's PID and the string from its arguments.
2. For every bit of every character (plus the final `'\0'`), it sends the matching signal with `kill`.
3. It waits between signals so the server can handle each one.

### Why waiting is needed

Standard UNIX signals are **not queued**: if several identical signals arrive while one is being handled, they can be merged and some bits are lost. For this reason, the client either waits a short time between signals (`usleep`) or waits for an **acknowledgment** from the server before sending the next bit.

## Testing

```bash
# Short message
./client <PID> "Hello"

# Long message
./client <PID> "$(python3 -c 'print("42" * 5000)')"

# Several clients, one after the other
./client <PID> "first" && ./client <PID> "second"

# Empty string
./client <PID> ""
```

Edge cases worth testing:

- Very long strings (thousands of characters)
- Special characters and, for the bonus, Unicode and emojis
- An invalid PID, or wrong number of arguments
- Sending many messages in a row without restarting the server
- Speed: 100 characters should show up almost instantly

## Author

- **Mohamed Zeouaoui**: [@mohamedzeouaoui](https://github.com/mohamedzeouaoui)

## Resources

- `man 2 sigaction`, `man 2 kill`, `man 7 signal`
- [Signals in C (GNU libc manual)](https://www.gnu.org/software/libc/manual/html_node/Signal-Handling.html)
- The 42 Norm

### Use of AI

> Describe here how AI was used in this project (which tasks, which parts), and what you checked and understood yourself.
