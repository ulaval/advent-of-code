const day01P1 = (async() => {
    const response = await fetch('data.txt');
    const text = await response.text();
    const positions = text.split('\r\n').map(t => t.split(' ').map((p, i) => i === 1 ? parseInt(p): p));

    const horizontalAndDepthPosition = positions.reduce((acc, curr) => {
        switch(curr[0]) {
            case 'forward':
                acc[0] += curr[1];
                break;
            case 'down':
                acc[1] += curr[1];
                break;
            case 'up':
                acc[1] -= curr[1];
                break;
        }
        acc[2] = acc[0] * acc[1];
        return acc;
    }, [0, 0, 0]);

    console.log(horizontalAndDepthPosition[2]);

    const refBody = document.body;
    const reH2 = document.createElement('h2');
    const refUl = document.createElement('ul');
    reH2.innerText = 'Part 1';
    refUl.innerHTML = (
        `<li><strong>Horizontal position: </strong> ${horizontalAndDepthPosition[0]}</li>
         <li><strong>Depth position: </strong> ${horizontalAndDepthPosition[1]}</li>
         <li><strong>Multiplication (horizontal * depth): </strong> ${horizontalAndDepthPosition[2]}</li>`
    );
    refBody.append(reH2);
    refBody.append(refUl);
})();