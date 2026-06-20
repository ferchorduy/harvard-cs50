fetch('data/countries-paths.json')
  .then(response => response.json())
  .then(data => {
    document.querySelectorAll('g').forEach(element => {
      element.innerHTML = data[element.id].join('');
    });
  });