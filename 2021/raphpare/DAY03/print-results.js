export const printResults = (part, diagnostic) => {
    const refBody = document.body;
    const reH2 = document.createElement('h2');
    const refUl = document.createElement('ul');
    reH2.innerText = `Part ${part}`;
    refUl.innerHTML = (
        `<li><strong>Gama rate</strong> 
            <ul>
                <li><strong>binary: </strong>${diagnostic.gamaRate.binary}</li>
                <li><strong>decimal: </strong>${diagnostic.gamaRate.decimal}</li>
            </ul>
         </li>
         <li><strong>Epsilon rate</strong> 
            <ul>
                <li><strong>binary: </strong>${diagnostic.epsilonRate.binary}</li>
                <li><strong>decimal: </strong>${diagnostic.epsilonRate.decimal}</li>
            </ul>
         </li>
         <li><strong>Power consumtion: </strong> ${diagnostic.powerConsumtion}</li>`
    );
    refBody.append(reH2);
    refBody.append(refUl);
}