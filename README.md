# Mouse Click Filter Program

This project is a Windows-based mouse filter application written in C. It helps prevent unintended double-clicks caused by hardware issues, such as worn-out switches or debounce problems, by applying a time-based filter to mouse clicks. The program can block clicks that occur too quickly in succession, ensuring that only valid clicks are registered.

## Features

- Filters left and/or right mouse clicks based on a configurable minimum time interval (default: 80 milliseconds).
- Independently manages filters for left and right mouse buttons.
- Prevents hardware double-clicking issues by blocking consecutive fast clicks.
- Provides the option to apply the filter to left clicks, right clicks, or both.
- Outputs a message indicating whether a click was accepted or rejected.

## How It Works

The program hooks into the mouse input using a low-level mouse hook and blocks any clicks that occur too quickly after a previous one. This can help mitigate problems where a mouse, due to hardware issues, accidentally registers double-clicks. The minimum click interval is set to 80 milliseconds, but this can be adjusted in the code as needed.

## Prerequisites

- A Windows machine
- Microsoft Visual Studio or the `cl` compiler from the Visual Studio Build Tools
- Basic knowledge of the command line

## How to Build and Run the Program

### 1. Clone the repository:

```bash
git clone https://github.com/your-username/mouse-click-filter.git
```

### 2. Navigate to the project directory:

```bash
cd mouse-click-filter
```

### 3. Compile the program:

If you're using the Microsoft C/C++ compiler (`cl`), you can compile the program by running the following command:

```bash
cl MouseClickFilter.c user32.lib gdi32.lib
```

This will generate an executable file called `MouseClickFilter.exe`.

### 4. Run the program:

Once compiled, run the program from the command line:

```bash
MouseClickFilter.exe
```

### 5. Select which clicks to filter:

You will be prompted to select which mouse button(s) to apply the filter to:

- 1: Left Click only
- 2: Right Click only
- 3: Both Left and Right Clicks

After selecting an option, the program will start filtering mouse clicks based on the time interval defined in the code.

### 6. Exit the program:

To stop the program, press `Ctrl + C` in the terminal where it is running.

## Customization

You can adjust the following variables in the code to change the behavior of the program:

- `minClickInterval`: Sets the minimum time interval (in milliseconds) that must pass between two consecutive clicks.
- `applyLeftClickFilter` and `applyRightClickFilter`: Determines whether the filter applies to left, right, or both clicks.

### Example: Adjusting the Click Interval

If the double-click issue happens at a different interval, you can modify the `minClickInterval` value in the code. For example, to block clicks that occur within 100 milliseconds, you would set:

```c
DWORD minClickInterval = 100;
```

## Limitations

This program is designed as a **software workaround** for a hardware issue. It can help prevent unwanted double-clicks, but it won't fix the underlying hardware problem. To permanently resolve the issue, consider cleaning or replacing the mouse switch.

## License

This project is open-source and available under the MIT License. Feel free to use, modify, and distribute it as needed.
