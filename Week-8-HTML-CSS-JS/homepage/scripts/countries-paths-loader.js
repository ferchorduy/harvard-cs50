fetch('data/fetched-countries.json')
  .then(response => response.json())
  .then(data => {
    document.querySelectorAll('g').forEach(element => {
      element.innerHTML = data[element.id].join(' ');
    });
  });