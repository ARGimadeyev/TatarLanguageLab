fetch("food/food1.txt")
    .then((res) => res.text())
    .then((text) => {
        let n = Number(text.substring(0, 2));
        let m = Number(text.substring(3, 5));
        console.log(text);
        console.log(n);
        console.log(m);
        console.log(text[5]);
        let field = text.substring(6);
        console.log(field);
        let ar = new Array(n);
        for (let i = 0; i < n; i++) {
            ar[i] = new Array(m);
            for (let j = 0; j < m; ++j) {
                ar[i][j] = ' ';
            }
        }

        console.log(ar);
    })
    .catch((e) => console.error(e));
