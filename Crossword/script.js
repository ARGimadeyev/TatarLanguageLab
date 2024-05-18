let fd1 = [
    [' ', ' ', ' ', ' ', ' ', ' ', ' ', 'б', 'э', 'л', 'э', 'ш', ' '],
    [' ', ' ', ' ', ' ', ' ', ' ', ' ', 'а', ' ', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', ' ', ' ', 'в', ' ', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', ' ', ' ', 'ы', ' ', ' ', 'г', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', ' ', ' ', 'р', ' ', ' ', 'ө', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', 'к', 'а', 'с', 'т', 'ы', 'б', 'ы', 'й'],
    [' ', ' ', ' ', ' ', ' ', ' ', ' ', 'а', ' ', ' ', 'ә', ' ', ' '],
    ['ө', 'ч', 'п', 'о', 'ч', 'м', 'а', 'к', ' ', ' ', 'д', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'и', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'я', ' ', ' ']
];

let matrix = document.getElementById("matrix");
for (let i = 0; i < 10; i++) {
    for (let j = 0; j < 13; j++) {
        let div = document.createElement("div");
        div.innerHTML = fd1[i][j];
        div.className = "cell";
        matrix.appendChild(div);
    }
}