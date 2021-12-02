const day01P2 = (async() => {
    const response = await fetch('data.txt');
    const text = await response.text();
    const dataPositions = text.split('\r\n').map(t => t.split(' ').map((p, i) => i === 1 ? parseInt(p): p));

    const positions = dataPositions.reduce((acc, curr) => {
        switch(curr[0]) {
            case 'forward':
                acc.horizontal += curr[1];
                acc.depth += acc.aim * curr[1];
                break;
            case 'down':
                acc.aim += curr[1];
                break;
            case 'up':
                acc.aim -= curr[1];
                break;
        }
        acc.multiplication = acc.horizontal * acc.depth;
        return acc;
    }, {'horizontal' : 0, 'depth': 0, 'aim': 0, 'multiplication': 0});

    console.log(positions.multiplication);

    const refBody = document.body;
    const reH2 = document.createElement('h2');
    const refUl = document.createElement('ul');
    reH2.innerText = 'Part 2';
    refUl.innerHTML = (
        `<li><strong>Horizontal position: </strong> ${positions.horizontal}</li>
         <li><strong>Depth position: </strong> ${positions.depth}</li>
         <li><strong>Aim: </strong> ${positions.aim}</li>
         <li><strong>Multiplication (horizontal * depth): </strong> ${positions.multiplication}</li>`
    );
    refBody.append(reH2);
    refBody.append(refUl);
})();