# 🖥️ OS-CustomCLI-CpuSehcduler

Welcome to **OS-CustomCLI-CpuSehcduler**!  
This project is a hands-on demonstration of custom Operating System concepts, featuring:

- 🖳 A feature-rich Unix/Linux command-line shell with custom parsing, piping, redirection, and history.
- 🧑‍💻 A CPU Scheduler Simulator implementing the Shortest Job First (SJF) scheduling algorithm with a priority queue.

Perfect for students learning OS fundamentals, process management, and C++ system programming!

---

## 🚀 Features

### 🐚 Custom Command-Line Interface (CLI)
- **Basic Unix Shell**: Run commands just like in bash/zsh.
- **History Support**: View and execute previous commands by history index.
- **Pipes (`|`)**: Chain commands with pipes.
- **Input/Output Redirection (`<`, `>`)**: Read from and write to files.
- **Change Directory (`cd`)**: Navigate the file system.
- **Parallel Execution (`&`)**: Run commands in the background.
- **Process Management**: Handles forking, waiting, and process IDs.
- **Error Handling**: Informative error messages for failed commands.
- **History Management**: Keeps the last 10 commands.

### 🕒 CPU Scheduler Simulator
- **SJF Scheduling**: Simulate the Shortest Job First CPU scheduling algorithm.
- **Priority Queue Implementation**: Custom heap-based min-queue for job scheduling.
- **Job Simulation**: Add, process, and visualize job execution order.
- **Educational Output**: Clear console prints of scheduling steps.

---

## 🛠️ How To Use

### 1. Compile the CLI Shell
```bash
g++ -o custom_shell CustomCompiler.cpp
./custom_shell
```
- Use commands as you would in a normal shell, e.g. `ls | grep cpp > files.txt`

### 2. Run the CPU Scheduler Simulator
```bash
g++ -o cpu_scheduler Cpu_Scheduler.cpp
./cpu_scheduler
```
- The simulator will show the SJF scheduling of predefined jobs.

---

## 🎯 Example CLI Usage

```shell
Enter CMD| /home/user :	ls -l | grep cpp > cppfiles.txt
Enter CMD| /home/user :	cat cppfiles.txt
Enter CMD| /home/user :	!!    # Shows command history
Enter CMD| /home/user :	!2    # Repeats the 2nd command in history
Enter CMD| /home/user :	cd /tmp
Enter CMD| /tmp :	exit
```

---

## ✨ Why This Project?

- **For learners**:  
  See how real shells parse and execute commands, manage processes, and handle I/O.
- **For OS students**:  
  Visualize CPU scheduling algorithms in action.
- **For hackers**:  
  Extend and experiment with your own shell features and scheduling policies!

---

## 🤝 Contributions

Got a new scheduling algorithm to simulate? Want to add tab-completion, scripting, or advanced piping?  
Pull requests are welcome!

---

## 👤 Author

- **JoY-BoY-e**

---

## ⚖️ License

MIT

> _Learn Operating Systems by building them. Code your own shell & scheduler today!_ 🖥️⚙️
