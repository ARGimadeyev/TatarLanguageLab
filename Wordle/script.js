const wordList = ["apple", "berry", "cherry", "grape", "lemon"]; // Список возможных слов
const targetWord = wordList[Math.floor(Math.random() * wordList.length)]; // Слово для угадывания
let currentRow = 0;
let currentCol = 0;
const maxRows = 6;
const wordLength = 5;

document.addEventListener("DOMContentLoaded", () => {
    createBoard();
    createKeyboard();
});

function createBoard() {
    const board = document.getElementById("board");
    for (let i = 0; i < maxRows * wordLength; i++) {
        const cell = document.createElement("div");
        cell.classList.add("cell");
        cell.setAttribute("id", `cell-${i}`);
        board.appendChild(cell);
    }
}

function createKeyboard() {
    const keyboardLayout = [
        "qwertyu", 
        "iopasdf", 
        "ghjklzx",
	    "cvbnm"
    ];

    const keyboard = document.getElementById("keyboard");

    keyboardLayout.forEach(row => {
        row.split('').forEach(key => {
            const button = document.createElement("button");
            button.textContent = key;
            button.classList.add("key");
            button.addEventListener("click", () => handleKeyPress(key));
            keyboard.appendChild(button);
        });
    });

    const enterButton = document.createElement("button");
    enterButton.textContent = "Enter";
    enterButton.classList.add("key", "enter");
    enterButton.addEventListener("click", () => handleEnterPress());
    keyboard.appendChild(enterButton);

    const backspaceButton = document.createElement("button");
    backspaceButton.textContent = "⌫";
    backspaceButton.classList.add("key", "backspace");
    backspaceButton.addEventListener("click", () => handleBackspacePress());
    keyboard.appendChild(backspaceButton);
}

function handleKeyPress(key) {
    if (currentCol < wordLength && currentRow < maxRows) {
        const cell = document.getElementById(`cell-${currentRow * wordLength + currentCol}`);
        cell.textContent = key;
        currentCol++;
    }
}

function handleEnterPress() {
    if (currentCol === wordLength) {
        checkWord();
    }
}

function handleBackspacePress() {
    if (currentCol > 0) {
        currentCol--;
        const cell = document.getElementById(`cell-${currentRow * wordLength + currentCol}`);
        cell.textContent = "";
    }
}

document.addEventListener("keydown", (e) => {
    const key = e.key.toLowerCase();
    if (key === "enter") {
        handleEnterPress();
    } else if (key === "backspace") {
        handleBackspacePress();
    } else if (/^[a-z]$/.test(key)) {
        handleKeyPress(key);
    }
});

function checkWord() {
    const guess = [];
    for (let i = 0; i < wordLength; i++) {
        const cell = document.getElementById(`cell-${currentRow * wordLength + i}`);
        guess.push(cell.textContent);
    }
    const guessWord = guess.join('');
    if (guessWord === targetWord) {
        setMessage("You guessed it!");
        highlightWord(guessWord);
    } else {
        highlightWord(guessWord);
        currentRow++;
        currentCol = 0;
        if (currentRow === maxRows) {
            setMessage(`Game over! The word was ${targetWord}`);
        }
    }
}

function highlightWord(guessWord) {
    const targetArray = targetWord.split('');
    for (let i = 0; i < wordLength; i++) {
        const cell = document.getElementById(`cell-${currentRow * wordLength + i}`);
        if (guessWord[i] === targetArray[i]) {
            cell.classList.add("correct");
            highlightKey(guessWord[i], "correct");
        } else if (targetArray.includes(guessWord[i])) {
            cell.classList.add("present");
            highlightKey(guessWord[i], "present");
        } else {
            cell.classList.add("absent");
            highlightKey(guessWord[i], "absent");
        }
    }
}

function highlightKey(key, status) {
    const keys = document.querySelectorAll(".key");
    keys.forEach(k => {
        if (k.textContent === key) {
            k.classList.add(status);
        }
    });
}

function setMessage(msg) {
    const messageElement = document.getElementById("message");
    messageElement.textContent = msg;
    messageElement.style.opacity = 1;
    setTimeout(() => {
        messageElement.style.opacity = 0;
    }, 3000);
}
