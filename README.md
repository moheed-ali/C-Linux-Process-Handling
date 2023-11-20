# C-Linux-Process-Handling

This repository contains C programs that demonstrate various aspects of process handling in Linux using fork, exec, pipe, and wait.

## Programs

1. **fork_proc.c:** Parent-child fork program.
   - Compile: `gcc fork_proc.c -o fork_proc`
   - Run: `./fork_proc`

2. **pipe_proc.c:** Parent-child bidirectional fork program with pipes.
   - Compile: `gcc pipe_proc.c -o pipe_proc`
   - Run: `./pipe_proc`

3. **single_pipe.c:** Parent-child single pipe fork program.
   - Compile: `gcc single_pipe.c -o single_pipe`
   - Run: `./single_pipe`

4. **wait_proc.c:** Parent-child wait process fork program.
   - Compile: `gcc wait_proc.c -o wait_proc`
   - Run: `./wait_proc`

## How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/moheed-ali/C-Linux-Process-Handling.git
   cd C-Linux-Process-Handling
