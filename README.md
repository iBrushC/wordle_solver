# Wordle Solver
Using a list of all possible words, this program sorts through the best word chooses for the popular game **Wordle**. It includes letter-based and english frequency scoring, allowing for more accurate and faster predictions. Written in (messy) C++.

## How to Use
Use whatever starting word you want, then run the exe:
 - In **Greys**, enter all new grey letters that appeared. If no new grey letters have appeared, enter a single dash (`-`). If the word has been found, you can enter `DONE` to stop the program.
 - In **Yellows**, enter all letters for that turn that are yellow *positionally* using dashes where there is none. If there are no yellows, enter a single dash (`-`).
 - In **Greens**, enter all letters for that turn that are green*positionally* using dashes where there is none. If there are no greens, enter a single dash (`-`).

### Example:
![Example round](https://raw.githubusercontent.com/iBrushC/wordle_solver/main/media/wordle.PNG)

The input for this would be:
```
Greys: d
Yellows: r--n
Greens: -ou
```

After entering the letters, the program with return the five most likely words. Generally, using one of them will either heavily progress or win the game. On average, it takes between 3-4 tries to get it right.
