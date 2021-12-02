const day01 = (async() => {
    const response = await fetch('data.text');
    const text = await response.text();
    const sonarSweeps = text.split('\r\n').map(t => parseInt(t));
    
    const largerMeasurements = sonarSweeps.reduce((acc, curr, index, array) => 
        array[!index ? 0 : index - 1] < curr ? acc + 1 : acc, 0);
        
    console.log(largerMeasurements);

    document.querySelector('p').innerHTML = (
        `There are <strong>${largerMeasurements}</strong> measurements 
        that are larger than the previous measurement.`
    );
})();